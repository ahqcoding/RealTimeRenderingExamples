#include "Application.h"
#include "Cube.h"
#include <Mat4.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Model.h"

namespace RTR {
    Application::Application(int w, int h) : 
        mWidth(w), mHeight(h),
        mCamera(Vector3f(0.0, 0.0, 1.0), Vector3f(0.0, 0.0, 0.0), Vector3f(0.0, 1.0, 0.0))
    {

        init();

    }

    Application::~Application() {
        delete mShader;
    }

    void Application::init() {
        mWindow.init(mWidth, mHeight);
        mShader = new BlinnPhongShader();
        mRaster.init(this);
    }


    void Application::run() {

        Model model;
        model.load("Assets/african_head/african_head");
        model.setApplication(this);
        Mat4 viewMatrix = mCamera.getMat4();
    
        Mat4 projMatrix = Mat4::Perspective(90.0f, (float)mWidth / (float)mHeight, 0.1f, 100.f);
      
        Mat4 modelMatrix;
        
        mShader->mvp = projMatrix * viewMatrix * modelMatrix;
        mShader->modelViewMatrix = viewMatrix * modelMatrix;
        mShader->normalMatrix = Mat4::normalMatrix(mShader->modelViewMatrix);
        SDL_Event event;
        bool running = true;
        while (running) {
            const Uint64 start = SDL_GetPerformanceCounter();
            while (SDL_PollEvent(&event)) {
                if ((SDL_QUIT == event.type) ||
                    (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
                {
                    running = false;
                    break;
                }
            }
            
            mWindow.clear();
            model.draw();
            mWindow.update();
            mWindow.draw();
            const Uint64 end = SDL_GetPerformanceCounter();
            const static Uint64 freq = SDL_GetPerformanceFrequency();
            const double seconds = (end - start) / static_cast<double>(freq);
            std::cout << "Frame time: " << seconds * 1000.0 << "ms" << std::endl;
        }
    }
}