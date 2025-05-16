#pragma once

#include "camera.h"
#include "shader_m.h"
#include "sglad.h"
#include "sglm.hpp"
#include "sgl.hpp"
#include "../deps/stb_image.h"
#include "app_shader.hpp"

// LearnOpenGL\src\1.getting_started\7.4.camera_class

#define CUBE_SIZE 10

class Application
{
public:
    void Init(int screenWidth, int screenHeight) {
        sglInit(screenWidth, screenHeight);

        glEnable(GL_DEPTH_TEST);

        shader = new Shader(AppVertexShader::Create, AppFragmentShader::Create);

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        // load and create a texture 
        // -------------------------

        // texture 1
        // ---------
        glGenTextures(1, &texture1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // texture 2
        // ---------
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
        // -------------------------------------------------------------------------------------------
        shader->use();
        shader->setInt("texture1", 0);
        shader->setInt("texture2", 1);
    }

    void Update(uint32_t* pixels, int width, int height, uint32_t time) {
        int SCR_WIDTH = width;
        int SCR_HEIGHT = height;

        // per-frame time logic
        // --------------------
        // TODO
        /*   float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;*/


        // input
        // -----
        //processInput(window); // TODO

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // activate shader
        shader->use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader->setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        shader->setMat4("view", view);

        // render boxes
        // world space positions of our cubes
        static glm::vec3 cubePositions[CUBE_SIZE] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < CUBE_SIZE; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // pull final pixels from sgl
        sglPullPixels(pixels);
    }

    void Release() {
        delete shader;

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        sglRelease();
    }

private:
    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    //void processInput(GLFWwindow* window)
    //{
    //    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    //        glfwSetWindowShouldClose(window, true);

    //    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //        camera.ProcessKeyboard(FORWARD, deltaTime);
    //    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //        camera.ProcessKeyboard(BACKWARD, deltaTime);
    //    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //        camera.ProcessKeyboard(LEFT, deltaTime);
    //    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //        camera.ProcessKeyboard(RIGHT, deltaTime);
    //}

    //// glfw: whenever the window size changed (by OS or user resize) this callback function executes
    //// ---------------------------------------------------------------------------------------------
    //void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    //{
    //    // make sure the viewport matches the new window dimensions; note that width and 
    //    // height will be significantly larger than specified on retina displays.
    //    glViewport(0, 0, width, height);
    //}


    //// glfw: whenever the mouse moves, this callback is called
    //// -------------------------------------------------------
    //void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
    //{
    //    float xpos = static_cast<float>(xposIn);
    //    float ypos = static_cast<float>(yposIn);

    //    if (firstMouse)
    //    {
    //        lastX = xpos;
    //        lastY = ypos;
    //        firstMouse = false;
    //    }

    //    float xoffset = xpos - lastX;
    //    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    //    lastX = xpos;
    //    lastY = ypos;

    //    camera.ProcessMouseMovement(xoffset, yoffset);
    //}

    //// glfw: whenever the mouse scroll wheel scrolls, this callback is called
    //// ----------------------------------------------------------------------
    //void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    //{
    //    camera.ProcessMouseScroll(static_cast<float>(yoffset));
    //}


private:
    Camera camera;
    Shader* shader;
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
};
