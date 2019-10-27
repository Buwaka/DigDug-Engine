#pragma once
#include "Scene.h"
#include "Casting.h"

namespace mini
{
#define NamePlaceholder "PlaceHolder"

	class ObjectComponent;
	class GameObject final
	{
	public:
		virtual void Initialize() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		virtual void Draw() const {};
		virtual void PostDraw() const {};


		GameObject(std::string name = NamePlaceholder, Scene* scene = nullptr);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		Scene* GetScene();
		void AddComponent(ObjectComponent* comp);
		void SetParent(GameObject* parent);
		void SetRenderPosition(int pos);
		int GetRenderPosition() const;
		GameObject* GetParent();
		void SetName(std::string name);
		std::string const & GetName() const;


		template <typename T>
		T* GetComponent(bool searchChildren = false);
		template <typename T>
		std::vector<T*> GetComponents(bool searchChildren = false);
		template <typename T>
		void RemoveComponent(T* component);
		void Destroy();


	protected:
		friend Scene;
		bool ObjectInitialize();
		bool ObjectUpdate();
		bool ObjectLateUpdate();
		bool ObjectFixedUpdate();
		void ObjectDraw() const;
		void ObjectPostDraw() const;

	private:
		Scene* ParentScene;
		std::vector<ObjectComponent*> Components;
		std::vector<GameObject*> Children;
		GameObject* Parent;
		std::string Name;
		int RenderPosition = 0;
		static unsigned int ID;
		bool Visible = true;

#ifdef _DEBUG 
		bool Done = false;
#endif
	};

	template <typename T>
	T* GameObject::GetComponent(bool searchChildren)
	{
		const type_info& ti = typeid(T);
		for (auto* component : Components)
		{
			if (component && typeid(*component) == ti)
				return static_cast<T*>(component);
		}

		if (searchChildren)
		{
			for (auto* child : Children)
			{
				auto temp = child->GetComponent<T>(searchChildren);
				if (temp != nullptr)
					return temp;
			}
		}

		return nullptr;
	}

	template <typename T>
	std::vector<T*> GameObject::GetComponents(bool searchChildren)
	{
		std::vector<T*> comps;
		const type_info& ti = typeid(T);
		for (auto* component : Components)
		{
			if (component && typeid(*component) == ti)
				comps.push_back(static_cast<T*>(component));
		}

		if (searchChildren)
		{
			for (auto* child : Children)
			{
				auto temp = child->GetComponents<T>(searchChildren);
				if (temp.size() > 0)
				{
					comps.reserve(comps.size() + temp.size());                
					comps.insert(comps.end(), temp.begin(), temp.end());
				}
			}
		}

		return comps;
	}

	template <typename T>
	void GameObject::RemoveComponent(T* component)
	{
		auto it = std::find(Components.begin(), Components.end(), component);
		if (it != Components.end()) 
		{ 
			Components.erase(it); 
		}
	}
}
