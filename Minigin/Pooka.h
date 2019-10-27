#pragma once
#include "Component.h"
#include "InputCommand.h"
#include "SpriteComponent.h"
#include "Enemy.h"


class Pooka : public Enemy
{
public:

	enum States
	{
		Idle,
		Walk,
		Invincible,
		Shoot,
		Pump
	};

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Hit(int damage) override;

	void Move(float x, float y);
	void SetRandomPosition(int Boundsx, int Boundsy, int width, int height);
	

	Pooka();
	~Pooka();

private:
	int tick = 0;
	States State = Idle;
	mini::SpriteComponent* SpriteComp;
	glm::vec2 Direction{ 1.f,0.f };
	glm::ivec2 Movement{};
};

class MoveCommandPooka : public mini::InputCommand
{
public:
	MoveCommandPooka(Pooka* player) { chara = player; };

	virtual void Execute() override
	{
		chara->Move(_x, _y);
	}

	virtual void Set2DFloatValue(float x, float y) override
	{
		_x = x;
		_y = y;
	}

private:
	float _x, _y;
	Pooka* chara;
};