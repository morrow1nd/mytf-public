#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "app.h"

 /* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* texture = NULL;
static uint32_t* pixels = NULL;
static int texture_width = 0;
static int texture_height = 0;

static Application* app;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_Surface* surface = NULL;
    char* bmp_path = NULL;

    SDL_SetAppMetadata("Example Renderer Textures", "1.0", "com.example.renderer-textures");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/textures", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );

    pixels = (uint32_t*)malloc(WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));





    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void generate_pixels(uint32_t* pixels, int width, int height, uint32_t time) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // 创建动态颜色（随时间变化）
            uint8_t r = (x + time) % 256;
            uint8_t g = (y + time) % 256;
            uint8_t b = (time * 2) % 256;

            // 将颜色打包为RGBA32格式
            pixels[y * width + x] = (r << 24) | (g << 16) | (b << 8) | 0xFF;
        }
    }
}

static uint32_t frame_count = 0;

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    SDL_FRect dst_rect;
    const Uint64 now = SDL_GetTicks();

    /* we'll have some textures move around over a few seconds. */
    const float direction = ((now % 2000) >= 1000) ? 1.0f : -1.0f;
    const float scale = ((float)(((int)(now % 1000)) - 500) / 500.0f) * direction;


    frame_count++;
    // 生成新的像素数据
    generate_pixels(pixels, WINDOW_WIDTH, WINDOW_HEIGHT, frame_count);

    // 更新纹理
    SDL_UpdateTexture(
        texture,
        NULL,  // 更新整个纹理
        pixels,
        WINDOW_WIDTH * sizeof(uint32_t)  // 每行的字节数
    );

    // 渲染
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer); /* put it all on the screen! */

    ///* bottom right. */
    //dst_rect.x = ((float)(WINDOW_WIDTH - texture_width)) - (100.0f * scale);
    //dst_rect.y = (float)(WINDOW_HEIGHT - texture_height);
    //dst_rect.w = (float)texture_width;
    //dst_rect.h = (float)texture_height;
    //SDL_RenderTexture(renderer, texture, NULL, &dst_rect);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(texture);
    /* SDL will clean up the window/renderer for us. */
}