#include "texture.hpp"

TextureObject::TextureObject(unsigned char *image, int width, int height) : _image(image), _width(width), _height(height)
{
}

unsigned char *TextureObject::get_image() const
{
    return _image;
}

int TextureObject::get_width() const
{
    return _width;
}

int TextureObject::get_height() const
{
    return _height;
}