#include "Framework.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
    /*
    map<wstring, Texture*>::iterator iter = textures.begin();
    for (; iter != textures.end(); iter++)
    {
        delete iter->second;
    }
    textures.clear();
    */
    /*
    for (pair<wstring, Texture*> texture : textures)
    {
        delete texture.second;
    }
    */
    for (auto texture : textures)
    {
        delete texture.second;
    }
    textures.clear();
}

Texture* TextureManager::Add(wstring path, int width, int height, COLORREF transColor)
{
    if (textures.count(path) > 0)
        return textures[path];

    Texture* texture = new Texture(path, width, height, transColor);
    textures[path] = texture;

    return texture;
}

Texture* TextureManager::Add(wstring path, int width, int height, int frameX, int frameY, COLORREF transColor)
{
    if (textures.count(path) > 0)
        return textures[path];

    Texture* texture = new Texture(path, width, height, frameX, frameY, transColor);
    textures[path] = texture;

    return texture;
}
