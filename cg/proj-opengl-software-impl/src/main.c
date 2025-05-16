#define RGFW_IMPLEMENTATION
#define RGFW_BUFFER
#define RGFW_NOAPI
#include "../deps/RGFW-1.70/RGFW.h"
#include "app_wrapper.h"

u8 icon[4 * 3 * 3] = { 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF };

RGFW_area screenSize;

/* fill buffer with a color, clearing anything that was on it */
void clear(RGFW_window* win, u8 color[4]) {
    /* if all the values are the same */
    if (color[0] == color[1] && color[0] == color[2] && color[0] == color[3]) {
        /* set it all in one function */
        memset(win->buffer, color[0], (u32)screenSize.w * (u32)win->r.h * 4 * sizeof(u8));
        return;
    }

    /* else we'll have to something more complex... */

    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < (u32)win->r.h; y++) {
        for (x = 0; x < screenSize.w; x++) {
            u32 index = (y * 4 * screenSize.w) + x * 4;

            /* copy the color to that pixel */
            memcpy(win->buffer + index, color, 4 * sizeof(u8));
        }
    }
}

/* this can also be used to convert BGR to RGB */
void bitmap_rgbToBgr(u8* bitmap, RGFW_area a) {
    /* loop through each *pixel* (not channel) of the buffer */
    u32 x, y;
    for (y = 0; y < a.h; y++) {
        for (x = 0; x < a.w; x++) {
            u32 index = (y * 4 * a.w) + x * 4;

            u8 red = bitmap[index];
            bitmap[index] = bitmap[index + 2];
            bitmap[index + 2] = red;
        }
    }
}

void drawBitmap(RGFW_window* win, u8* bitmap, RGFW_rect rect) {
    u32 y;
    for (y = 0; y < (u32)rect.h; y++) {
        u32 index = ((u32)rect.y + y) * (4 * screenSize.w) + (u32)rect.x * 4;
        memcpy(win->buffer + index, bitmap + (4 * (u32)rect.w * y), (u32)rect.w * 4 * sizeof(u8));
    }
}

void drawRect(RGFW_window* win, RGFW_rect r, u8 color[4]) {
    for (int x = r.x; x < (r.x + r.w); x++) {
        for (int y = r.y; y < (r.y + r.h); y++) {
            u32 index = (u32)y * (4 * screenSize.w) + (u32)x * 4;

            memcpy(win->buffer + index, color, 4 * sizeof(u8));
        }
    }
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("sgl-app", RGFW_RECT(0, 0, 500, 500), RGFW_windowCenter | RGFW_windowTransparent);
    screenSize = RGFW_getScreenSize();

    app_init(screenSize.w, screenSize.h);
    char* pixels = NULL;

    i8 running = 1;
    u32 frames = 0;
    double frameStartTime = RGFW_getTime();

    while (running) {
        while (RGFW_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit || RGFW_isPressed(win, RGFW_escape)) {
                running = 0;
                break;
            }
        }

        u8 color[4] = { 0, 0, 255, 125 };
        u8 color2[4] = { 255, 0, 0, 255 };
        clear(win, color);
        //drawRect(win, RGFW_RECT(200, 200, 200, 200), color2);

        drawBitmap(win, icon, RGFW_RECT(100, 100, 3, 3));

        app_update(pixels, screenSize.w, screenSize.h);

        // RGFW_window_swapBuffers could work here too, but I want to ensure only the CPU buffer is being swapped
        RGFW_window_swapBuffers_software(win);
        //RGFW_checkFPS(frameStartTime, frames, 60);
        frames++;
    }

    app_release();
    RGFW_window_close(win);
    return 0;
}


//#define STB_IMAGE_IMPLEMENTATION
// #include "app.h"
//
// /* We will use this renderer to draw into this window every frame. */
//static SDL_Window* window = NULL;
//static SDL_Renderer* renderer = NULL;
//static SDL_Texture* texture = NULL;
//static uint32_t* pixels = NULL;
//static int texture_width = 0;
//static int texture_height = 0;
//
//static Application* app;
//
//#define WINDOW_WIDTH 1200
//#define WINDOW_HEIGHT 800
//
//SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
//{
//    SDL_Surface* surface = NULL;
//    char* bmp_path = NULL;
//
//    SDL_SetAppMetadata("Example Renderer Textures", "1.0", "com.example.renderer-textures");
//
//    if (!SDL_Init(SDL_INIT_VIDEO)) {
//        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
//        return SDL_APP_FAILURE;
//    }
//
//    if (!SDL_CreateWindowAndRenderer("examples/renderer/textures", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
//        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
//        return SDL_APP_FAILURE;
//    }
//
//    texture = SDL_CreateTexture(
//        renderer,
//        SDL_PIXELFORMAT_RGBA8888,
//        SDL_TEXTUREACCESS_STREAMING,
//        WINDOW_WIDTH,
//        WINDOW_HEIGHT
//    );
//
//    pixels = (uint32_t*)malloc(WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));
//
//    app = new Application();
//    app->Init(WINDOW_WIDTH, WINDOW_HEIGHT);
//
//    return SDL_APP_CONTINUE;  /* carry on with the program! */
//}
//
///* This function runs when a new event (mouse input, keypresses, etc) occurs. */
//SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
//{
//    if (event->type == SDL_EVENT_QUIT) {
//        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
//    }
//    return SDL_APP_CONTINUE;  /* carry on with the program! */
//}
//
//static uint32_t frame_count = 0;
//
///* This function runs once per frame, and is the heart of the program. */
//SDL_AppResult SDL_AppIterate(void* appstate)
//{
//    SDL_FRect dst_rect;
//    const Uint64 now = SDL_GetTicks();
//
//    /* we'll have some textures move around over a few seconds. */
//    const float direction = ((now % 2000) >= 1000) ? 1.0f : -1.0f;
//    const float scale = ((float)(((int)(now % 1000)) - 500) / 500.0f) * direction;
//
//    frame_count++;
//    // 生成新的像素数据
//    app->Update(pixels, WINDOW_WIDTH, WINDOW_HEIGHT, frame_count);
//    //for (int y = 0; y < WINDOW_HEIGHT; y++) {
//    //    for (int x = 0; x < WINDOW_WIDTH; x++) {
//    //        // 创建动态颜色（随时间变化）
//    //        uint8_t r = (x + frame_count) % 256;
//    //        uint8_t g = (y + frame_count) % 256;
//    //        uint8_t b = (frame_count * 2) % 256;
//    //
//    //        // 将颜色打包为RGBA32格式
//    //        pixels[y * WINDOW_WIDTH + x] = (r << 24) | (g << 16) | (b << 8) | 0xFF;
//    //    }
//    //}
//
//    // 更新纹理
//    SDL_UpdateTexture(
//        texture,
//        NULL,  // 更新整个纹理
//        pixels,
//        WINDOW_WIDTH * sizeof(uint32_t)  // 每行的字节数
//    );
//
//    // 渲染
//    SDL_RenderClear(renderer);
//    SDL_RenderTexture(renderer, texture, NULL, NULL);
//    SDL_RenderPresent(renderer); /* put it all on the screen! */
//
//    ///* bottom right. */
//    //dst_rect.x = ((float)(WINDOW_WIDTH - texture_width)) - (100.0f * scale);
//    //dst_rect.y = (float)(WINDOW_HEIGHT - texture_height);
//    //dst_rect.w = (float)texture_width;
//    //dst_rect.h = (float)texture_height;
//    //SDL_RenderTexture(renderer, texture, NULL, &dst_rect);
//
//    return SDL_APP_CONTINUE;  /* carry on with the program! */
//}
//
///* This function runs once at shutdown. */
//void SDL_AppQuit(void* appstate, SDL_AppResult result)
//{
//    app->Release();
//    SDL_DestroyTexture(texture);
//    free(pixels);
//    /* SDL will clean up the window/renderer for us. */
//}
