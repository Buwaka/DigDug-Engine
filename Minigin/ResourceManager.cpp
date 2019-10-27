#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void mini::ResourceManager::Init(std::string&& dataPath)
{
	mDataPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

mini::Texture2D* mini::ResourceManager::LoadTexture(const std::string& file)
{
	std::string fullPath = mDataPath + file;
	auto surface = IMG_Load(fullPath.c_str());
	if (surface == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return new Texture2D(surface);
}

mini::Font* mini::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	return new Font(mDataPath + file, size);
}
