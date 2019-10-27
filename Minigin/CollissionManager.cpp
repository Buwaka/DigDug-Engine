#include "MiniginPCH.h"
#include "CollissionManager.h"

mini::CollissionManager::CollissionManager()
{

}

void mini::CollissionManager::RegisterCollider(Collider * body)
{
	Colliders.push_back(body);
}

void mini::CollissionManager::UnregisterCollider(Collider * body)
{
	auto it = std::find(Colliders.begin(), Colliders.end(), body);
	if (it != Colliders.end())
	{
		Colliders.erase(it);
	}
}

void mini::CollissionManager::Update()
{
	for (auto& current : Colliders)
	{
		if (current->Active)
		{
			for (auto& other : Colliders)
			{
				if (current != other && current->Active)
				{
					if (CheckCollission(current, other))
					{
						if (current->Command)
						{
							current->Command->Execute(other, other->Parent);
						}
					}
				}
			}
		}
	}

}


