#pragma once
#include "GameObject.h"
#include "Casting.h"

namespace mini
{ 

	class ObjectComponent
	{
	public:
		ObjectComponent() = default;
		virtual ~ObjectComponent() = default;

		ObjectComponent(const ObjectComponent& other) = delete;
		ObjectComponent(ObjectComponent&& other) noexcept = delete;
		ObjectComponent& operator=(const ObjectComponent& other) = delete;
		ObjectComponent& operator=(ObjectComponent&& other) noexcept = delete;

		GameObject* GetGameObject() const { return GameObject; }

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() {};
		virtual void FixedUpdate() {};
		virtual void Draw() const = 0;
		virtual void PostDraw() const {};

		void Destroy()
		{
			GetGameObject()->RemoveComponent(this);
		};
		void DestroyObject()
		{
			GetGameObject()->Destroy();
		};


		mini::GameObject* GameObject;
	};
}