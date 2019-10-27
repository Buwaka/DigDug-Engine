#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "SceneComponent.h"
#include <algorithm>
#include <thread>
#include "FPSComponent.h"
#include "ThreadPool.h"

//unsigned int mini::Scene::idCounter = 0;
//MAXIMUM_WAIT_OBJECTS

mini::Scene::Scene(const std::string& name) : Name(name) {}

void mini::Scene::SortGameObjects()
{
	const static auto sortFunc = [](GameObject* lhs, GameObject* rhs) -> bool
	{return lhs->GetRenderPosition() < rhs->GetRenderPosition(); };

	if (!std::is_sorted(Objects.begin(), Objects.end(), sortFunc))
	{
		std::sort(Objects.begin(), Objects.end(), sortFunc);
	}
}

mini::Scene::~Scene()
{
	for (auto gameObject : Objects)
	{
		delete gameObject;
	}

	for (auto scenecomps : SceneComponents)
	{
		delete scenecomps;
	}
}

void mini::Scene::Add(GameObject* object)
{
	Objects.push_back(object);
	object->ObjectInitialize();
}

void mini::Scene::AddSceneComponent(SceneComponent * comp)
{
	comp->SceneObject = this;
	SceneComponents.push_back(comp);
	comp->Initialize();
}

void mini::Scene::RemoveComponent(SceneComponent * comp)
{
	auto it = std::find(SceneComponents.begin(), SceneComponents.end(), comp);
	if (it != SceneComponents.end())
	{
		SceneComponents.erase(it);
		delete comp;
	}
}

void mini::Scene::RemoveAllComponents()
{
	for (auto comp : SceneComponents)
	{
		delete comp;
	}
	SceneComponents.clear();
}

void mini::Scene::RemoveAllObjects()
{
	for (auto obj : Objects)
	{
		delete obj;
	}
	Objects.clear();
}

void mini::Scene::Reset()
{
	RemoveAllComponents();
	RemoveAllObjects();
}

void mini::Scene::RemoveObject(GameObject * object)
{
	auto it = std::find(Objects.begin(), Objects.end(), object);
	if (it != Objects.end()) 
	{
		Objects.erase(it); 
		delete object;
	}
}

void mini::Scene::SceneInitialize()
{
	for (auto sceneComps : SceneComponents)
	{
		sceneComps->Initialize();
	}

	Initialize();

#ifdef mini_FPSCounter
	auto fpscounter = new mini::GameObject("fpscounter", this);
	fpscounter->AddComponent(new mini::FPSComponent());
	fpscounter->SetRenderPosition(INT_MAX - 1);
	Add(fpscounter);
#endif // mini_FPSCounter


}

void mini::Scene::SceneUpdate()
{
	std::vector< std::future<bool> > results;

	for(auto gameObject : Objects)
	{
		auto pack = [gameObject]() {return gameObject->ObjectUpdate(); };
		results.emplace_back(ThreadPool::GetInstance().AddTask(pack));
	}

	for (auto&& result : results)
		result.get();
	results.clear();
	//ThreadPool::GetInstance().WaitForAllTasks();

#ifdef  mini_LateUpdate
	for (auto gameObject : Objects)
	{
		auto pack = [gameObject]() {return gameObject->ObjectLateUpdate(); };
		results.emplace_back(ThreadPool::GetInstance().enqueue(pack));
	}

	for (auto&& result : results)
		result.get();
	results.clear();
#endif //  mini_LateUpdate

	for (auto sceneComps : SceneComponents)
	{
		auto pack = [sceneComps]() {return sceneComps->Update(); };
		results.emplace_back(ThreadPool::GetInstance().AddTask(pack));
	}

	for (auto&& result : results)
		result.get();
	results.clear();

	SortGameObjects();

	Update();
}

void mini::Scene::SceneFixedUpdate()
{
	std::vector< std::future<bool> > results;

	for (auto gameObject : Objects)
	{
		auto pack = [gameObject]() {return gameObject->ObjectFixedUpdate(); };
		results.emplace_back(ThreadPool::GetInstance().AddTask(pack));
	}

	for (auto&& result : results)
		result.get();
	results.clear();

	for (auto sceneComps : SceneComponents)
	{
		auto pack = [sceneComps]() {return sceneComps->FixedUpdate(); };
		results.emplace_back(ThreadPool::GetInstance().AddTask(pack));
	}

	for (auto&& result : results)
		result.get();
	results.clear();

	SortGameObjects();

	FixedUpdate();
}

void mini::Scene::SceneRender() const
{
	for (const auto gameObject : Objects)
	{
		gameObject->ObjectDraw();
	}

#ifdef mini_PostDraw
	for (const auto gameObject : Objects)
	{
		gameObject->PostDraw();
	}
#endif // mini_PostDraw

	for (const auto sceneComps : SceneComponents)
	{
		sceneComps->Draw();
	}

	Render();
}

