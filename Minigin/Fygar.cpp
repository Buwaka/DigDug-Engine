#include "MiniginPCH.h"
#include "Fygar.h"
#include "TransformComponent.h"
#include "Time.h"
#include "CollissionComponent.h"
#include "SpriteComponent.h"
#include "AIComponent.h"
#include "GridComponent.h"
#include "DigDugObserver.h"

#define Fygar_Idle "Fygar_Idle"

const int BlockLength = 16;
const float WalkSpeed = 1.0f;
const int ticks = 20;
const int score = 100;

void Fygar::Initialize()
{
	auto sprite = new mini::SpriteComponent();

	sprite->AddSpriteSheet(Fygar_Idle, "DigDugFygar.png", 16, 16, 0, 0, true, 5);

	auto PlayerCollider = mini::Collider(mini::RectangleCollider(BlockLength, BlockLength), BlockLength / 2, BlockLength / 2, 0, nullptr, this);
	auto PlayerCol = new mini::CollissionComponent(PlayerCollider);

	auto AI = new mini::AIComponent(mini::AIComponent::Wander, new MoveCommandFygar(this), ticks);

	GetGameObject()->AddComponent(AI);
	GetGameObject()->AddComponent(PlayerCol);
	GetGameObject()->AddComponent(sprite);
	SpriteComp = sprite;

	auto grid = GetGameObject()->GetScene()->GetComponent<mini::GridComponent>();

	if (grid)
	{
		grid->RegisterObject(GetGameObject());
	}
	Score = score;

	subject.AddObserver(&DigDugObserver::GetInstance());
	DigDugObserver::GetInstance().IncreaseEnemyCount();
}

void Fygar::Update()
{
	auto trans = GetGameObject()->GetComponent<mini::TransformComponent>();

	if (!trans)
		return;

	Direction = glm::normalize(Direction);
	Movement = glm::roundEven(Direction * WalkSpeed);

	switch (State)
	{
	case Idle:

		//SpriteComp frame = 0;

		SpriteComp->GetSprite(Fygar_Idle)->visible = true;

		if (std::abs(Direction.x) > std::abs(Direction.y))
		{
			SpriteComp->GetSprite(Fygar_Idle)->Rotation = 0.f;
			SpriteComp->GetSprite(Fygar_Idle)->Flip = (Direction.x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}
		else
		{
			SpriteComp->GetSprite(Fygar_Idle)->Rotation = 270.f;
			SpriteComp->GetSprite(Fygar_Idle)->Flip = (Direction.y > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		break;
	case Walk:
		SpriteComp->GetSprite(Fygar_Idle)->visible = true;

		if (std::abs(Direction.x) > std::abs(Direction.y))
		{
			trans->Translate(Movement.x, 0);
			SpriteComp->GetSprite(Fygar_Idle)->Rotation = 0.f;
			SpriteComp->GetSprite(Fygar_Idle)->Flip = (Direction.x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}
		else
		{
			trans->Translate(0, Movement.y);
			SpriteComp->GetSprite(Fygar_Idle)->Rotation = 270.f;
			SpriteComp->GetSprite(Fygar_Idle)->Flip = (Direction.y > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}

		//State = Idle;
		break;
	case Shoot:
		break;
	case Pump:
		break;
	}


	Movement = glm::vec2(0, 0);
}

void Fygar::Move(float x, float y)
{
	if (State != Shoot)
	{
		Direction = glm::vec2(x, y);
		State = Walk;
	}
}

void Fygar::SetRandomPosition(int Boundsx, int Boundsy, int width, int height)
{
	int x, y;
	x = (rand() % (width - Boundsx)) + Boundsx;
	y = (rand() % (height - Boundsy)) + Boundsy;

	auto trans = GetGameObject()->GetComponent<mini::TransformComponent>();

	if (!trans)
		return;

	trans->SetPosition(x, y);
}

void Fygar::Draw() const
{
}

void Fygar::Hit(int damage)
{
	UNREFERENCED_PARAMETER(damage);
	subject.Notify(GetGameObject(), DigDugEvent::EVENT_SCORE);
	subject.Notify(GetGameObject(), DigDugEvent::EVENT_ENEMYDIED);
	DestroyObject();
}

Fygar::Fygar()
{
}


Fygar::~Fygar()
{
	auto grid = GetGameObject()->GetScene()->GetComponent<mini::GridComponent>();
	if (grid)
	{
		grid->RemoveObject(GetGameObject());
	}

}
