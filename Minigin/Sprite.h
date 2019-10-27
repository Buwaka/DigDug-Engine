#pragma once
#include "Texture2D.h"
#include "Renderer.h"

namespace mini
{
	struct Instance
	{
		int FrameIndex = -1;
		int RelativeX = 0, Y = 0;
		float Rotation = 0.f;
	};


	class Sprite
	{
	public:
		Sprite(int width, int height, Texture2D* Texture, int x = 0, int y = 0, bool isLooping = true, float Speed = 1.0f, bool SheetIsVertical = false, int FrameCount = -1, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);
		~Sprite();

		Sprite(const Sprite& other) = delete;
		Sprite(Sprite&& other) = delete;
		Sprite& operator=(const Sprite& other) = delete;
		Sprite& operator=(Sprite&& other) = delete;

		SDL_Rect GetFrameRect(int frame = -1) const;
		void AddInstance(int x, int y, int frame = -1);
		void SetFrame(int frame);
		void Reset();

		int RelativeX = 0, Y = 0;
		float Rotation = 0.f;

		float FrameSpeed = 1.0f;

		bool isLooping = false;
		bool visible = false;
		SDL_RendererFlip Flip = SDL_RendererFlip::SDL_FLIP_NONE;

	protected:
		friend class SpriteComponent;
		void SetTimerFrame(int frame);

	private:
		friend class Renderer;
		friend class Texture2D;
		int TimerFrame;
		int FrameIndex = -1;


		std::vector<Instance> Instances;
		int FrameCount, width, height;
		bool sheetIsVertical = false;
		Texture2D* Texture;
	};

}