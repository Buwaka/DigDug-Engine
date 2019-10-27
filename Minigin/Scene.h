#pragma once
#include "SceneManager.h"


namespace mini
{
	class GameObject;
	class SceneComponent;
	class Scene
	{
	public:
		void Add(GameObject* object);
		void RemoveObject(GameObject* object);
		void AddSceneComponent(SceneComponent* comp);
		void RemoveComponent(SceneComponent* comp);
		void RemoveAllComponents();
		void RemoveAllObjects();
		void Reset();

		template <typename T>
		T* GetComponent();
		template <typename T>
		std::vector<T*> GetComponents();


		virtual void Initialize() { };
		virtual void Update() { };
		virtual void FixedUpdate() { };
		virtual void Render() const { };

		explicit Scene(const std::string& name);
		virtual ~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		friend SceneManager;
		void SceneInitialize();
		void SceneUpdate();
		void SceneFixedUpdate();
		void SceneRender() const;

	private: 

		void SortGameObjects();

		std::string Name{};
		std::vector <GameObject*> Objects{};
		std::vector <SceneComponent*> SceneComponents{};
		//static unsigned int idCounter; 
	};

	template<typename T>
	inline T * Scene::GetComponent()
	{
		const type_info& ti = typeid(T);
		for (auto* component : SceneComponents)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetComponents()
	{
		std::vector<T*> comps;
		const type_info& ti = typeid(T);
		for (auto* component : SceneComponents)
		{
			if (component && typeid(*component) == ti)
				comps.push_back(static_cast<T*>(component));
		}

		return comps;
	}

}
