#pragma once
#include "Component.h"
#include "GameObject.h"
#include "CollissionCommand.h"
#include "Collider.h"


namespace mini
{
	class CollissionComponent : public ObjectComponent
	{
	public:
		CollissionComponent(Collider body, CollissionCommand* command = nullptr, bool absolutePosition = false);
		virtual ~CollissionComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Draw() const;


		glm::ivec2 GetRelativeLocation() const;
		float GetRelativeRotation() const;
		void SetRelativePosition(int x, int y);
		void SetRelativeRotation(float rot);
		void TranslateRelative(int x, int y);

		Collider& GetCollider() {	return ColliderBody;	};

	private:
		bool AbsolutePosition;
		int relX, relY;
		float relRot;
		Collider ColliderBody;
	};
}