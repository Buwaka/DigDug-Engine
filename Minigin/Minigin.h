#pragma once
#include <chrono>
#include "Time.h"

struct SDL_Window;

namespace mini
{
#define QUITBTN VK_F4

	typedef std::chrono::duration<float, Seconds> Duration;

	class Minigin
	{
		uint16_t FPS;
		Duration FrameTime;
		Duration NextFixedUpdate;
		bool GameLoop;
		SDL_Window* window{};
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();
		inline uint16_t GetFPS() { return FPS; };
		inline void SetFPS(uint16_t fps) {
			FPS = fps; 
			FrameTime = Duration(1.f / FPS);
		};

		inline void Quit() { GameLoop = false; };

	};

}