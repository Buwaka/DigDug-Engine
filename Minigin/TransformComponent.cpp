#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "glm/gtx/vector_angle.hpp"

namespace mini 
{


	TransformComponent::TransformComponent(glm::ivec3 position, float rotation, glm::vec2 scale)
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;

		if (position.z != 0)
		{
			auto obj = GetGameObject();
			if (obj != nullptr)
			{
				obj->SetRenderPosition(position.z);
			}
		}
	}


	void TransformComponent::SetPosition(glm::ivec3 position)
	{
		Position = position;


		if (position.z != 0)
		{
			auto obj = GetGameObject();
			if (obj != nullptr)
			{
				obj->SetRenderPosition(position.z);
			}
		}
	}

	void TransformComponent::SetPosition(int x, int y, int z)
	{
		Position = glm::ivec3(x, y, z);

		if (z != 0)
		{
			auto obj = GetGameObject();
			if (obj != nullptr)
			{
				obj->SetRenderPosition(z);
			}
		}
	}

	void TransformComponent::SetPosition(int x, int y)
	{
		Position = glm::ivec3(x, y, Position.z);
	}

	void TransformComponent::SetZposition(int z)
	{
		Position.z = z;
	}

	glm::ivec3 TransformComponent::GetPosition() const
	{
		return Position;
	}

	glm::ivec3 TransformComponent::GetWorldPosition() const
	{
		glm::ivec3 pos = GetPosition();
		mini::GameObject* parent = GameObject->GetParent();
		while (parent != nullptr)
		{
			auto trans = parent->GetComponent<TransformComponent>();
			if (trans != nullptr)
			{
				glm::rotate(glm::vec2(pos), trans->GetRotation());
				pos += trans->GetPosition();
			}
			parent = parent->GetParent();
		}

		return pos;
	}

	void TransformComponent::Translate(glm::ivec3 position)
	{
		Position += position;

		if (Position.z != 0)
		{
			auto obj = GetGameObject();
			if (obj != nullptr)
			{
				obj->SetRenderPosition(Position.z);
			}
		}
	}

	void TransformComponent::Translate(int x, int y)
	{
		Position += glm::ivec3(x, y, 0);
	}

	void TransformComponent::Translate(int x, int y, int z)
	{
		Position += glm::ivec3(x, y, z);

		if (Position.z != 0)
		{
			auto obj = GetGameObject();
			if (obj != nullptr)
			{
				obj->SetRenderPosition(Position.z);
			}
		}
	}

	void TransformComponent::SetRotation(float rotation)
	{
		Rotation = rotation;
	}

	float TransformComponent::GetRotation() const
	{
		return Rotation;
	}

	float TransformComponent::GetWorldRotation() const
	{
		float rot = GetRotation();
		mini::GameObject* parent = GameObject->GetParent();
		while (parent != nullptr)
		{
			auto trans = parent->GetComponent<TransformComponent>();
			if (trans != nullptr)
			{
				rot += trans->GetRotation();
			}
			parent = parent->GetParent();
		}

		return rot;
	}

	void TransformComponent::SetScale(glm::vec2 scale)
	{
		Scale = scale;
	}

	void TransformComponent::SetScale(float scale)
	{
		Scale.x = scale;
		Scale.y = scale;
	}

	glm::vec2 const& TransformComponent::GetScale() const
	{
		return Scale;
	}

	glm::vec2 TransformComponent::GetWorldScale() const
	{
		glm::vec2 scl = GetScale();
		mini::GameObject* parent = GameObject->GetParent();

		while (parent != nullptr)
		{
			auto trans = parent->GetComponent<TransformComponent>();
			if (trans != nullptr)
			{
				auto temp = trans->GetScale();;
				scl.x *= temp.x;
				scl.y *= temp.y;
			}
			parent = parent->GetParent();
		}

		return scl;
	}
}