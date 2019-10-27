#include "MiniginPCH.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "SurfaceMath.h"
#include "Sprite.h"
#include "ResourceManager.h"


mini::Texture2D::Texture2D(SDL_Texture* texture)
{
	Texture = texture;
}

mini::Texture2D::Texture2D(SDL_Surface * surface, bool GenerateTextureImmediately)
{
	Image = surface;

	//Mask = SDL_CreateRGBSurfaceWithFormat(0, Image->w, Image->h, 8, SDL_PIXELFORMAT_RGB24);
	//SDL_FillRect(Mask, NULL, SDL_MapRGB(Mask->format,255,255,255));

	ConvertToRGB();


	rect.x = 0;
	rect.y = 0;
	rect.w = Image->w;
	rect.h = Image->h;


	if (GenerateTextureImmediately)
	{
		Update();
		NeedsUpdate = false;
	}
}


mini::Texture2D::~Texture2D()
{
	if(Texture)
		SDL_DestroyTexture(Texture);

	if (Image)
		SDL_FreeSurface(Image);
}

void mini::Texture2D::Update()
{
	if (NeedsUpdate && Image)
	{
		if (Texture)
			SDL_DestroyTexture(Texture);

		Texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), Image);
		SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);

		NeedsUpdate = false;
	}
}

void mini::Texture2D::SetChannels(unsigned int channels)
{
	Channels = channels;
}

void mini::Texture2D::Add(Texture2D * rhs, int x, int y, int width, int height)
{
	SurfaceMath::Add(Image, rhs->Image, x, y, width, height);

	NeedsUpdate = true;
}


void mini::Texture2D::Substract(Texture2D * rhs, int x, int y, int width, int height)
{
	auto dst = rhs->rect;

	if(width == INT_MAX)
		dst.w = width;

	if (height == INT_MAX)
		dst.h = height;

	SurfaceMath::Substract(Image, rhs->Image, rect, dst, x, y);

	NeedsUpdate = true;
}

void mini::Texture2D::AddMask(std::string mask, int x, int y, int width, int height, bool overwrite)
{
	Texture2D* temp = ResourceManager::GetInstance().LoadTexture(mask);
	AddMask(temp, x, y, width, height, overwrite);
	delete temp;
}

void mini::Texture2D::AddMask(Texture2D * mask, int x, int y, int width, int height, bool overwrite)
{
	if (Image)
	{
		AddMask(mask->Image, x, y, width, height, overwrite);
	}
}

void mini::Texture2D::Add(Sprite * rhs, int x, int y)
{
	auto frame = rhs->GetFrameRect();
	SurfaceMath::Add(Image, rhs->Texture->Image, frame.x + x, frame.y + y, frame.w, frame.h);

	NeedsUpdate = true;
}

void mini::Texture2D::Substract(Sprite * rhs, int x, int y)
{
	auto frame = rhs->GetFrameRect();
	SurfaceMath::Substract(Image, rhs->Texture->Image, rect, frame, x, y);

	NeedsUpdate = true;
}

void mini::Texture2D::Overlay(Sprite * rhs, int x, int y)
{
	auto frame = rhs->GetFrameRect();
	SurfaceMath::Overlay(Image, rhs->Texture->Image, frame.x + x, frame.y + y, frame.w, frame.h);

	NeedsUpdate = true;
}

void mini::Texture2D::AddMask(Sprite * mask, int x, int y, bool overwrite)
{
	auto frame = mask->GetFrameRect();
	SurfaceMath::AddMask(&Image, mask->Texture->Image, rect, frame, x, y, overwrite);

	NeedsUpdate = true;
}

void mini::Texture2D::AddMask(SDL_Surface * mask, int x, int y, int width, int height, bool overwrite)
{
	if (Image)
	{
		SDL_Rect dst{};
		dst.w = width;
		dst.h = height;
		SurfaceMath::AddMask(&Image, mask, rect, dst, x, y, overwrite);

		NeedsUpdate = true;
	}
}

void mini::Texture2D::Colorize(SDL_Color * color, int x, int y, int width, int height)
{
	if (Image)
	{
		SurfaceMath::Colorize(Image, color, SurfaceMath::_RGB::R, x, y, width, height);
		NeedsUpdate = true;
	}

}

void mini::Texture2D::Scale(int width, int height)
{
	if (Image)
	{
		auto temp = SurfaceMath::Scale(Image, width, height);
		SDL_FreeSurface(Image);
		Image = temp;
		NeedsUpdate = true;
	}
}

void mini::Texture2D::Crop(int x, int y, int width, int height)
{
	if (Image)
	{
		auto temp = SurfaceMath::Crop(Image, x, y, width, height);
		SDL_FreeSurface(Image);
		Image = temp;
		NeedsUpdate = true;
	}
}

mini::Texture2D* mini::Texture2D::GetCropedTexture(int x, int y, int width, int height)
{
	return new Texture2D(SurfaceMath::Crop(Image, x, y, width, height));
}

void mini::Texture2D::SetCropedTexture(Texture2D * rhs,int x, int y, int width, int height)
{

	Image = SurfaceMath::Crop(rhs->Image, x, y, width, height);

	NeedsUpdate = true;

}

SDL_PixelFormat * mini::Texture2D::GetFormat() const
{
	return Image->format;
}

void mini::Texture2D::Overlay(Texture2D * rhs, int x, int y, int width, int height)
{
	SurfaceMath::Overlay(Image, rhs->Image, x, y, width, height);

	NeedsUpdate = true;
}

void mini::Texture2D::ConvertToRGB()
{
	if (Image)
	{
		if (Image->format->palette != NULL)
		{
			auto temp = SDL_ConvertSurfaceFormat(Image, SDL_PIXELFORMAT_RGBA32, 0);
			SDL_FreeSurface(Image);
			Image = temp;
		}
	}

}

SDL_Rect mini::Texture2D::GetRect() const
{
	return SDL_Rect();
}

unsigned int mini::Texture2D::GetChannels() const
{
	return Channels;
}

int mini::Texture2D::width() const
{
	if(Image)
		return Image->w;

	return 0;
}

int mini::Texture2D::height() const
{
	if (Image)
		return Image->h;

	return 0;
}

SDL_Texture* mini::Texture2D::GetSDLTexture() const
{
	return Texture;
}

mini::Texture2D::Texture2D()
{
}

