#include "MiniginPCH.h"
#include "AIComponent.h"

mini::AIComponent::AIComponent(Behavior behavior, InputCommand* command, int ticksPerUpdate)
{
	Behaviors = behavior;
	Command = command;
	TicksPerUpdate = ticksPerUpdate;
}

mini::AIComponent::~AIComponent()
{
	delete Command;
}

void mini::AIComponent::Initialize()
{
}

void mini::AIComponent::Update()
{
	if ((Tick %= TicksPerUpdate) == 0)
	{
		switch (Behaviors)
		{
		case Wander:
			wander(Command);
			break;
		case Seek:
			break;
		case Flee:
			break;
		}

		Command->Execute();
	}
	Tick++;
}

void mini::AIComponent::wander(InputCommand* command)
{
	float x, y;
	x = float(rand() - (RAND_MAX/2)) / float(RAND_MAX);
	y = float(rand() - (RAND_MAX/2)) / float(RAND_MAX);
	command->Set2DFloatValue(x, y);
}
