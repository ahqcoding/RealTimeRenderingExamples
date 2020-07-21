#include "Window.h"
namespace RTR {
    Window::Window()
    {

    }

    void Window::init(int width, int height)
    {
        mWidth = width;
        mHeight = height;
        frameBuffer.init(width, height);
        mWindow = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
        mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    }
    void Window::clear() {
        frameBuffer.clear();
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(mRenderer);
    }

    Window::~Window()
    {
        SDL_DestroyTexture(mTexture);
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
    }
}
