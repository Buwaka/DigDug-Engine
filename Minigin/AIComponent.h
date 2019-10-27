#pragma once
#include "Component.h"
#include "InputCommand.h"

namespace mini
{
	class AIComponent : public mini::ObjectComponent
	{
	public:
		//bitfields so if necessary it can be upgraded into holding multiple behaviors
		enum Behavior : Uint8
		{
			Wander = 2 << 0,
			Seek = 2 << 1,
			Flee = 2 << 2,
			Count = (Flee << 1) - 1
		};


		AIComponent(Behavior behavior, InputCommand* command, int ticksPerUpdate = 1);
		~AIComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Draw() const override {};

	protected:
		void wander(InputCommand* command);

	private:
		Uint8 Behaviors;
		InputCommand* Command;
		int Tick = 0;
		int TicksPerUpdate = 1;
	};

}