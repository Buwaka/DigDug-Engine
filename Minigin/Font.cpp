#include "MiniginPCH.h"
#include "Font.h"

TTF_Font* mini::Font::GetFont() const {
	return mFont;
}


mini::Font::Font(const std::string& fullPath, unsigned int size) : mFont(nullptr), mSize(size)
{
	mFont = TTF_OpenFont(fullPath.c_str(), size);
	if (mFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + fullPath + SDL_GetError());
	}
}

mini::Font::~Font()
{
	TTF_CloseFont(mFont);
}
