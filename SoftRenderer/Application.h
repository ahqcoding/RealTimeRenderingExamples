#pragma once

#include "Window.h"
#include "Shader.h"
#include "Rasterizer.h"
#include "Camera.h"
namespace RTR {
    class Application
    {
    public:
        Application(int w, int h);;
        ~Application();
        void init();
        void run();
        Window* getWindow() {
            return &mWindow;
        }

        Shader* getShader() {
            return mShader;
        }

        Rasterizer* getRaster() {
            return &mRaster;
        }


        int getWidth() {
            return mWidth;

        }

        int getHeight() {
            return mHeight;
        }


    private:
        int mWidth;
        int mHeight;
        Window mWindow;
        Shader* mShader;
        Rasterizer mRaster;
        Camera mCamera;
    };
}


