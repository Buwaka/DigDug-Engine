#pragma once
#include "Singleton.h"
#include <SDL.h>
#include "Collider.h"


namespace mini
{
	class Texture2D;
	class Sprite;
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D* texture, const int x, const int y, const float rotation, const glm::vec2 scale, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;
		void RenderTexture(const Sprite* sprite, const int x, const int y, const float rotation, const glm::vec2 scale, SDL_RendererFlip flip) const;
		void RenderTexture(SDL_Texture* texture, const int x, const int y, const int width, const int height, const float rotation, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE) const;
		void RenderTexture(SDL_Surface* surface, const int x, const int y, const float rotation, SDL_RendererFlip flip) const;

		//debug
		void DrawTriangle(Triangle triangle);
		void DrawLine(glm::ivec2 p1, glm::ivec2 p2);

		void SetResolution(int width, int height);
		void SetScale(int scale);
		int GetWindowWidth() const;
		int GetWindowHeight() const;
		void ClearScreen(SDL_Color* color = nullptr);

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }

	private:
		SDL_Renderer* mRenderer = nullptr;
		SDL_Surface* Texture = nullptr;
		SDL_Window* Window = nullptr;
		int Width, Height;
		int WindowID;
		bool Scaled = false;
		SDL_Color BackgroundColor;
	};
}

