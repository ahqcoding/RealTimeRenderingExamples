#include "Texture.h"

Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32*)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

namespace RTR {
    void Texture::load(const std::string& filename)
    {
        image = IMG_Load(filename.c_str());
        if (!image) {
            printf("IMG_Load: %s\n", IMG_GetError());
        }

    }

    Vector4f Texture::getPixel(int x, int y)
    {
        SDL_Color rgba;
        Uint32 data = getpixel(image, x, y);
        SDL_GetRGBA(data, image->format, &rgba.r, &rgba.g, &rgba.b, &rgba.a);
      
        return Vector4f(rgba.r / 255.f, rgba.g / 255.f, rgba.b / 255.f, rgba.a / 255.f);

    }

    Vector4f Texture::getUV(float u, float v)
    {
        return getPixel(u * image->w, (1 - v) * image->h);
    }
}

