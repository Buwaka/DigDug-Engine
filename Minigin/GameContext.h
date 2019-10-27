#pragma once
#include "Singleton.h"
#include "Minigin.h"
#include <SDL.h>

	class GameContext : public mini::Singleton<GameContext>
	{
	public:
		GameContext() = default;
		~GameContext() = default;

		void Init();

		SDL_Window* GetWindow();
		mini::Minigin* GetEngine();

	protected:
		friend mini::Minigin;
		void SetWindow(SDL_Window* window);
		void SetEngine(mini::Minigin* engine);

	private:
		SDL_Window* Window = nullptr;
		mini::Minigin* Engine = nullptr;
	};

