#pragma once
#include "MiniginPCH.h"
//#include "Collider.h"

namespace mini
{
	struct Collider;
	class ObjectComponent;

	class CollissionCommand
	{
	public:
		virtual ~CollissionCommand() = default;
		virtual void Execute(Collider* OtherBody, ObjectComponent* OtherComponent) = 0;
	};




}