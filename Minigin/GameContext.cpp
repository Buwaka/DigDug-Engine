#include "MiniginPCH.h"
#include "GameContext.h"

void GameContext::Init()
{
}

SDL_Window* GameContext::GetWindow()
{
	return Window;
}

mini::Minigin * GameContext::GetEngine()
{
	return Engine;
}

void GameContext::SetWindow(SDL_Window* window)
{
	Window = window;
}

void GameContext::SetEngine(mini::Minigin * engine)
{
	Engine = engine;
}
