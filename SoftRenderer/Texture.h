#pragma once
#include <SDL2/SDL_image.h>
#include <string>
#include <RTRMath.h>
namespace RTR {

	class Texture {
	public:
		Texture() {

		}
		~Texture() {
			delete image;
		}

		int getWidth() {
			return image->w;
		}
		int getHeight() {
			return image->h;
		}
		void load(const std::string& filename);
		Vector4f getPixel(int x, int y);
		Vector4f getUV(float u, float v);
		SDL_Surface* image;
	};
}