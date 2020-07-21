#pragma once
#include <SDL2/SDL.h>
#undef main
#include <vector>
#include "framebuffer.h"
namespace RTR {
    class Window
    {
    public:
        Window();
        ~Window();

        void init(int width, int height);

        void clear();

        void update() {

            SDL_UpdateTexture
            (
                mTexture,
                NULL,
                &frameBuffer.pixels[0],
                mWidth * 4
            );


        }

        void draw() {
            SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
            SDL_RenderPresent(mRenderer);
        }

        SDL_Window* getWindow() {
            return mWindow;
        }

        SDL_Renderer* getRenderer() {
            return mRenderer;
        }

        SDL_Texture* getTexture() {
            return mTexture;
        }

        FrameBuffer* getFrameBuffer() {
            return &frameBuffer;
        }
    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
        FrameBuffer frameBuffer;
    };
}


