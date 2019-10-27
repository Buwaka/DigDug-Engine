#pragma once
#include "MiniginPCH.h"
#include "GameContext.h"

namespace mini
{
	class InputCommand
	{
	public:
		virtual ~InputCommand() = default;
		virtual void Execute() = 0;

		// override for triggers and single axis sticks
		virtual void SetFloatValue(float value) { UNREFERENCED_PARAMETER(value); };
		// override for dual axis sticks
		virtual void Set2DFloatValue(float x, float y) { UNREFERENCED_PARAMETER(x); UNREFERENCED_PARAMETER(y); };
	};


	class ForceQuitCommand : public InputCommand
	{
	public:
		virtual void Execute() override
		{
			GameContext::GetInstance().GetEngine()->Quit();
		};
	};
}