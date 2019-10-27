#include "MiniginPCH.h"
#include "CollissionComponent.h"
#include "CollissionManager.h"
#include "TransformComponent.h"

#include "Renderer.h"


mini::CollissionComponent::CollissionComponent(Collider body, CollissionCommand * command, bool absolutePosition)
{
	ColliderBody = body;
	ColliderBody.Command = command;
	AbsolutePosition = absolutePosition;

	if(!AbsolutePosition)
	{
		relX = ColliderBody.X;
		relY = ColliderBody.Y;
		relRot = ColliderBody.Rotation;
	}
}

mini::CollissionComponent::~CollissionComponent()
{
	CollissionManager::GetInstance().UnregisterCollider(&ColliderBody);
}

void mini::CollissionComponent::Initialize()
{
	//register
	CollissionManager::GetInstance().RegisterCollider(&ColliderBody);
	Update();
}

void mini::CollissionComponent::Update()
{
	if (!AbsolutePosition)
	{
		auto trans = GetGameObject()->GetComponent<TransformComponent>();

		if (!trans)
			return;

		auto wpos = trans->GetWorldPosition();
		auto wrot = trans->GetWorldRotation();

		ColliderBody.X = wpos.x + relX;
		ColliderBody.Y = wpos.y + relY;
		ColliderBody.Rotation = wrot + relRot;
	}
}

void mini::CollissionComponent::Draw() const
{

#if defined(_DEBUG) && defined(mini_DebugCollission)
	if (ColliderBody.Active)
	{
		for (auto triangle : ColliderBody.Shape)
		{
			mini::Renderer::GetInstance().DrawTriangle(triangle + ColliderBody.pos);
		}
	}
#endif // _DEBUG && mini_DebugCollission

}

glm::ivec2 mini::CollissionComponent::GetRelativeLocation() const
{
	return glm::ivec2(relX, relY);
}

float mini::CollissionComponent::GetRelativeRotation() const
{
	return relRot;
}

void mini::CollissionComponent::SetRelativePosition(int x, int y)
{
	relX = x;
	relY = y;
}

void mini::CollissionComponent::SetRelativeRotation(float rot)
{
	relRot = rot;
}

void mini::CollissionComponent::TranslateRelative(int x, int y)
{
	relX += x;
	relY += y;
}
