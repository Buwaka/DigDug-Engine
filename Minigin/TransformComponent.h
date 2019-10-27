#pragma once
#include "Component.h"
#include "Transform.h"


namespace mini
{
	class TransformComponent :	public ObjectComponent
	{
	public:
		TransformComponent(glm::ivec3 position = glm::ivec3(0, 0, 0), float rotation = 0.f, glm::vec2 scale = glm::vec2(1, 1));
		virtual ~TransformComponent() = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;


		void SetPosition(glm::ivec3 position);
		void SetPosition(int x, int y, int z);
		void SetPosition(int x, int y);
		void SetZposition(int z);
		glm::ivec3 GetPosition() const;
		glm::ivec3 GetWorldPosition() const;

		void Translate(glm::ivec3 position);
		void Translate(int x, int y);
		void Translate(int x, int y, int z);


		void SetRotation(float Rotation);
		float GetRotation() const;
		float GetWorldRotation() const;

		void SetScale(glm::vec2 scale);
		void SetScale(float scale);
		glm::vec2 const& GetScale() const;
		glm::vec2 GetWorldScale() const;


		virtual void Initialize() override {};
		virtual void Update() override {};
		virtual void Draw() const override {};

	private:
		glm::ivec3 Position;
		float Rotation;
		glm::vec2 Scale;
	};
}
