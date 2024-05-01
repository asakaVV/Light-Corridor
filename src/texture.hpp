#pragma once

class TextureObject
{
public:
    TextureObject(unsigned char *image, int width, int height);

    unsigned char *get_image() const;
    int get_width() const;
    int get_height() const;

private:
    unsigned char *_image;
    int _width;
    int _height;
};