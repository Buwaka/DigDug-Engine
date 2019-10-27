#pragma once

#include "Singleton.h"
#include "Minigin.h"
#include "Collider.h"

namespace mini
{
	class CollissionManager final : public Singleton<CollissionManager>
	{
	public:
		CollissionManager();
		~CollissionManager() {};
		//collissioncomponent has to update the position of the Collider

		void RegisterCollider(Collider* body);
		void UnregisterCollider(Collider* body);

		void Initialize() {};
		void Update();

	protected:
		friend Minigin;
		void Clean() {};

	private:
		std::vector<Collider*> Colliders;
	};



}