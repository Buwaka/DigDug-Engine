#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void mini::SceneManager::Initialize()
{
	for (const auto scene : Scenes)
	{
		scene->SceneInitialize();
	}
}

void mini::SceneManager::Update()
{
#ifdef  mini_UpdateAllScenes
	for (auto scene : Scenes)
	{
		scene->SceneUpdate();
	}
#else
	CurrentScene->SceneUpdate();
#endif //  mini_UpdateAllScenes


}

void mini::SceneManager::FixedUpdate()
{
#ifdef  mini_UpdateAllScenes
	for (auto scene : Scenes)
	{
		scene->SceneFixedUpdate();
	}
#else
	CurrentScene->SceneFixedUpdate();
#endif //  mini_UpdateAllScenes


}

void mini::SceneManager::Render()
{
	CurrentScene->SceneRender();
}

void mini::SceneManager::Clean()
{
	for (auto& scene : Scenes)
	{
		delete scene;
	}
}

unsigned int mini::SceneManager::CreateScene(const std::string& name, Scene** Out, bool focus)
{
	*Out = new Scene(name);
	unsigned index = (unsigned) Scenes.size();
	Scenes.push_back(*Out);

	if (CurrentScene == nullptr || focus)
	{
		FocusScene(index);
	}

	return index;
}

unsigned int mini::SceneManager::RegisterScene(Scene * scene, bool focus)
{
	unsigned index = (unsigned) Scenes.size();
	Scenes.push_back(scene);

	if (CurrentScene == nullptr || focus)
	{
		FocusScene(index);
	}

	return index;
}

void mini::SceneManager::FocusScene(unsigned int ID)
{
	if (ID > Scenes.size())
	{
		//logger: error, gamepad i not found
		throw std::runtime_error(std::string("Scene with ID does not exist") + std::to_string(ID));
	}

	CurrentScene = Scenes[ID];
}


