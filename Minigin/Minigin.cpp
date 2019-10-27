#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "GameContext.h"
#include "ColorFormats.h"
#include "DigDugScene.h"
#include "CollissionManager.h"
#include "ThreadPool.h"




void mini::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);

	SetFPS(60);

	NextFixedUpdate = std::chrono::seconds(1);

	Time::Init();
	InputManager::GetInstance().Init();

	CollissionManager::GetInstance().Initialize();

	ThreadPool::GetInstance().Init(ThreadCount);

	GameContext::GetInstance().Init();
	GameContext::GetInstance().SetWindow(window);
	GameContext::GetInstance().SetEngine(this);

	srand((int)time(NULL));
}

/**
 * Code constructing the scene world starts here
 */
void mini::Minigin::LoadGame() const
{
	Scene* scene = nullptr;
	SceneManager::GetInstance().CreateScene("Demo", &scene);

	auto go = new GameObject();
	auto textureComp = new TextureComponent("background.jpg");
	go->AddComponent(textureComp);
	scene->Add(go);

	go = new GameObject();
	textureComp = new TextureComponent("logo.png");
	go->AddComponent(textureComp);
	go->GetComponent<TransformComponent>()->SetPosition(216, 180,0);
	scene->Add(go);

	go = new GameObject();
	auto to = new TextComponent("Programming 4 Assignment",36, "Lingua.otf");
	go->GetComponent<TransformComponent>()->SetPosition(80, 20, 0);
	go->AddComponent(to);
	scene->Add(go);

	

	go = new GameObject();
	auto fpscomp = new FPSComponent();
	go->AddComponent(fpscomp);

	scene->Add(go);

	//auto lhs = ResourceManager::GetInstance().LoadTexture("lhs.png");
	//auto rhs = ResourceManager::GetInstance().LoadTexture("rhs.png");
	//lhs->Substract(rhs,15,15);
	//
	//textureComp = new TextureComponent(lhs);
	//go = new GameObject();
	//go->AddComponent(textureComp);
	//go->GetComponent<TransformComponent>()->SetPosition(0, 0, 1);
	//scene.Add(go);


	InputManager::GetInstance().AssignButton(mini::InputTypes::Keyboard, SDLK_F4, 0, new ForceQuitCommand());

	auto Dscene = new DigDugScene();

	SceneManager::GetInstance().RegisterScene(Dscene, true);
}

void mini::Minigin::Cleanup()
{
	SceneManager::GetInstance().Clean();
	InputManager::GetInstance().Clean();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void mini::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("Data/");

	LoadGame();


	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& collission = CollissionManager::GetInstance();

		sceneManager.Initialize();

		Duration FixedTimer = std::chrono::seconds(0);

		GameLoop = true;
		while (GameLoop)
		{
			const Duration dtime = Time::DeltaTime<Seconds>();
			FixedTimer += dtime;

			input.ProcessInput();
			

			while (FixedTimer >= NextFixedUpdate)
			{ 
				sceneManager.FixedUpdate();
				FixedTimer -= NextFixedUpdate;
			}

			collission.Update();

			sceneManager.Update();

			Time::Update();

			renderer.Render();

			const Duration wait = FrameTime - dtime;

			if (wait.count() > 0)
				std::this_thread::sleep_for(wait);
		}
	}

	Cleanup();
}
