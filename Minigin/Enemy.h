#pragma once
#include "Subject.h"
#include "Component.h"

class Enemy : public mini::ObjectComponent
{
public:
	Enemy() = default;
	virtual ~Enemy() = default;

	virtual void Hit(int damage) = 0;

	int Score = 0;
	mini::Subject subject;
};

