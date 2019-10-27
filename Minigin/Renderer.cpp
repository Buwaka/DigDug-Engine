#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Sprite.h"

void mini::Renderer::Init(SDL_Window * window)
{
	BackgroundColor = SDL_Color{ 0,0,0,255 };
	Window = window;
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_GetWindowSize(window, &Width, &Height);
	SDL_GL_SetSwapInterval(1);
	WindowID = SDL_GetWindowID(Window);
	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void mini::Renderer::Render()
{
	ClearScreen();

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(mRenderer);


}

void mini::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void mini::Renderer::RenderTexture(const Texture2D* texture, const int x, const int y, const float rotation, const glm::vec2 scale, SDL_RendererFlip flip) const
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	dst.w = (int) std::round(dst.w * scale.x);
	dst.h = (int) std::round(dst.h * scale.y);

	SDL_RenderCopyEx(GetSDLRenderer(), texture->GetSDLTexture(), nullptr, &dst,rotation,NULL, flip);
}

void mini::Renderer::RenderTexture(const Sprite* sprite, const int x, const int y, const float rotation, const glm::vec2 scale, SDL_RendererFlip flip) const
{
	SDL_Rect dst,src;
	dst.x = sprite->RelativeX + x;
	dst.y = sprite->Y + y;
	dst.w = (int)std::round(sprite->width * scale.x);
	dst.h = (int)std::round(sprite->height * scale.y);

	src = sprite->GetFrameRect();

	SDL_RenderCopyEx(GetSDLRenderer(), sprite->Texture->GetSDLTexture(), &src, &dst, rotation + sprite->Rotation, NULL, flip);

	for (auto& inst : sprite->Instances)
	{
		dst.x = inst.RelativeX + x;
		dst.y = inst.Y + y;
		src = sprite->GetFrameRect(inst.FrameIndex);
		SDL_RenderCopyEx(GetSDLRenderer(), sprite->Texture->GetSDLTexture(), &src, &dst, rotation + inst.Rotation, NULL, flip);
	}
}

void mini::Renderer::RenderTexture(SDL_Texture* texture, const int x, const int y, const int width, const int height, const float rotation, SDL_RendererFlip flip) const
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderCopyEx(GetSDLRenderer(), texture, nullptr, &dst, rotation, NULL, flip);
}

void mini::Renderer::RenderTexture(SDL_Surface * surface, const int x, const int y, float rotation, SDL_RendererFlip flip) const
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = surface->w;
	dst.h = surface->h;

	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(GetSDLRenderer(), surface);

	SDL_RenderCopyEx(GetSDLRenderer(), tempTexture, nullptr, &dst, rotation, NULL, flip);

	SDL_DestroyTexture(tempTexture);
}

void mini::Renderer::DrawTriangle(Triangle triangle)
{
	DrawLine(triangle.p1, triangle.p2);
	DrawLine(triangle.p2, triangle.p3);
	DrawLine(triangle.p3, triangle.p1);

}

void mini::Renderer::DrawLine(glm::ivec2 p1, glm::ivec2 p2)
{
	auto color = mini_DebugColor;
	SDL_SetRenderDrawColor(GetSDLRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(GetSDLRenderer(), p1.x, p1.y, p2.x, p2.y);
	SDL_SetRenderDrawColor(mRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
}

void mini::Renderer::SetResolution(int width, int height)
{
	Width = width;
	Height = height;
	SDL_SetWindowSize(Window, Width, Height);
}

void mini::Renderer::SetScale(int scale)
{
	SDL_RenderSetLogicalSize(mRenderer, Width, Height);
	Width *= scale;
	Height *= scale;
	SDL_SetWindowSize(Window, Width, Height);
}

int mini::Renderer::GetWindowWidth() const
{
	return Width;
}

int mini::Renderer::GetWindowHeight() const
{
	return Height;
}

void mini::Renderer::ClearScreen(SDL_Color* color)
{
	if (color != nullptr)
	{
		SDL_SetRenderDrawColor(mRenderer, color->r, color->g, color->b, color->a);
	}
	else
	{
		SDL_SetRenderDrawColor(mRenderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
	}

	SDL_RenderClear(mRenderer);
}
