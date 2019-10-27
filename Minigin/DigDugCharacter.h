#pragma once
#include "Component.h"
#include "InputCommand.h"
#include "SpriteComponent.h"
#include "CollissionComponent.h"
#include "Enemy.h"
#include "Time.h"
#include "Subject.h"
#include "DigDugObserver.h"

class DigDugCharacter :	public mini::ObjectComponent
{
public:
	enum States
	{
		Idle,
		Walk,
		Shoot,
		Pump
	};


	DigDugCharacter(int player);
	~DigDugCharacter();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override {};

	mini::Sprite* GetMask() const;
	void SetState(States st);
	void Move(float x, float y);
	void SetInput();
	void RemoveInput();
	int GetDamage() { return HoseDamage; };

	mini::Subject subject;
private:
	mini::CollissionComponent* HoseComp;
	int HoseDamage = 100;
	float HoseDistance{};
	States State = Idle;
	mini::SpriteComponent* SpriteComp;
	int PlayerIndex;
	glm::vec2 Direction{1.f,0.f};
	glm::ivec2 Movement{};
};

#pragma region CollissionCommands

class GotHit : public mini::CollissionCommand
{
public:
	GotHit(DigDugCharacter* player) { chara = player; };

	virtual void Execute(mini::Collider* OtherBody, mini::ObjectComponent* OtherComponent) override
	{
		UNREFERENCED_PARAMETER(OtherBody);
		if (IsA<Enemy>(OtherComponent) && mini::Time::TotalTime() > Time)
		{
			chara->subject.Notify(chara->GetGameObject(), DigDugEvent::EVENT_PLAYERDIED);
			//invincibility time
			Time = mini::Time::TotalTime() + 1.0f;
		}
	}

private:
	DigDugCharacter* chara;
	float Time = 0;
};


class HoseHitEnemy : public mini::CollissionCommand
{
public:
	HoseHitEnemy(DigDugCharacter* player) { chara = player; };

	virtual void Execute(mini::Collider* OtherBody, mini::ObjectComponent* OtherComponent) override
	{
		UNREFERENCED_PARAMETER(OtherBody);
		if (IsA<Enemy>(OtherComponent))
		{
			auto enemy = Cast<Enemy>(OtherComponent);
			enemy->Hit(chara->GetDamage());
		}
	}

private:
	DigDugCharacter* chara;
};

#pragma endregion

#pragma region InputCommands

class ShootCommand : public mini::InputCommand
{
public:
	ShootCommand(DigDugCharacter* player) { chara = player; };

	virtual void Execute() override
	{
		chara->SetState(chara->Shoot);
	}

private:
	DigDugCharacter* chara;
};

class MoveCommand_Left : public mini::InputCommand
{
public:
	MoveCommand_Left(DigDugCharacter* player) { chara = player; };

	virtual void Execute() override
	{
		chara->Move(-1.f, 0);
	}

private:
	DigDugCharacter* chara;
};

class MoveCommand_Right : public mini::InputCommand
{
public:
	MoveCommand_Right(DigDugCharacter* player) { chara = player; };

	virtual void Execute() override
	{
		chara->Move(1.f, 0);
	}

private:
	DigDugCharacter* chara;
};

class MoveCommand_Up : public mini::InputCommand
{
public:
	MoveCommand_Up(DigDugCharacter* player) { chara = player; };

	virtual void Execute() override
	{
		chara->Move(0, -1.f);
	}

private:
	DigDugCharacter* chara;
};

class MoveCommand_Down : public mini::InputCommand
{
public:
	MoveCommand_Down(DigDugCharacter* player) { chara = player; };

	virtual void Execute() override
	{
		chara->Move(0, 1.f);
	}

private:
	DigDugCharacter* chara;
};

class MoveCommand_AllDirections : public mini::InputCommand
{
public:
	MoveCommand_AllDirections(DigDugCharacter* player) { chara = player; };

	virtual void Execute() override
	{
		if (std::abs(_x) > std::abs(_y))
		{
			chara->Move(_x, 0);
		}
		else
		{
			chara->Move(0, _y);
		}
	}

	virtual void Set2DFloatValue(float x, float y) override
	{
		this->_x = x;
		this->_y = y;
	}
private:
	DigDugCharacter* chara;
	float _x{}, _y{};
};
#pragma endregion
