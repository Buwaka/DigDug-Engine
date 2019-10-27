#pragma once
#include "Scene.h"

namespace mini
{

	class SceneComponent
	{
	public:
		SceneComponent() = default;
		virtual ~SceneComponent() = default;

		SceneComponent(const SceneComponent& other) = delete;
		SceneComponent(SceneComponent&& other) noexcept = delete;
		SceneComponent& operator=(const SceneComponent& other) = delete;
		SceneComponent& operator=(SceneComponent&& other) noexcept = delete;

		Scene* GetGameObject() const { return SceneObject; }

		virtual bool Initialize() { return true; };
		virtual bool Update() { return true; };
		virtual bool FixedUpdate() { return true; };
		virtual void Draw() {};


		Scene* SceneObject = nullptr;
	};
}