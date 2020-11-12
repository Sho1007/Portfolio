#pragma once

class TextureManager
{
private:
	map<wstring, Texture*> textures;

	TextureManager();
	~TextureManager();
public:
	static TextureManager* Get()
	{
		static TextureManager instance;
		return &instance;
	}

	Texture* Add(wstring path, int width, int height, COLORREF transColor = MAGENTA);
	Texture* Add(wstring path, int width, int height,
		int frameX, int frameY, COLORREF transColor = MAGENTA);
	Texture* Find(wstring path) { return textures[path]; }
};