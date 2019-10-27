#include "MiniginPCH.h"
#include "DigDugCharacter.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"
#include "GridComponent.h"



#define Player_Walk_Vertical "Player_Walk_Vertical"
#define Player_Walk_Horizontal "Player_Walk_Horizontal"

#define Player_Hose_Vertical "Player_Hose_Vertical"
#define Player_Hose_Horizontal "Player_Hose_Horizontal"

#define Player_Mask "Player_Mask"

const int BlockLength = 16;
const int HoseLength = 3 * BlockLength;
const float WalkSpeed = 1.0f;
const float HoseSpeed = 120.f;
const int HoseWidth = 16; //for collission
const glm::ivec2 RelHosePosition = { 16 ,10 };
const int LifeCount = 3;

DigDugCharacter::DigDugCharacter(int player)
{
	PlayerIndex = player;

}

DigDugCharacter::~DigDugCharacter()
{
	auto grid = GetGameObject()->GetScene()->GetComponent<mini::GridComponent>();

	if (grid)
	{
		grid->RemoveObject(GetGameObject());
	}

	RemoveInput();
}

void DigDugCharacter::Initialize()
{
	SetInput();

	auto sprite = new mini::SpriteComponent();

	sprite->AddSpriteSheet(Player_Walk_Vertical, "DigDugPlayerVertical.png", 16, 16, 0, 0, true, 5);
	sprite->AddSpriteSheet(Player_Walk_Horizontal, "DigDugPlayerHorizontal.png", 16, 16, 0, 0, true, 5);

	auto PlayerCollider = mini::Collider(mini::RectangleCollider(BlockLength, BlockLength), BlockLength / 2, BlockLength / 2, 0, nullptr, this);
	auto PlayerCol = new mini::CollissionComponent(PlayerCollider, new GotHit(this));
	GetGameObject()->AddComponent(PlayerCol);

	sprite->AddSpriteSheet(Player_Hose_Vertical, "DigDugHoseVertical.png", 16, 16, 0, 0, false);
	sprite->AddSpriteSheet(Player_Hose_Horizontal, "DigDugHoseHorizontal.png", 16, 16, 0, 0, false);



	auto HoseCollider = mini::Collider(mini::RectangleCollider(HoseWidth, HoseWidth), RelHosePosition.x, RelHosePosition.y, 0, nullptr, this);
	HoseCollider.Active = false;
	HoseComp = new mini::CollissionComponent(HoseCollider,new HoseHitEnemy(this));
	GetGameObject()->AddComponent(HoseComp);


	sprite->AddSpriteSheet(Player_Mask, "DigDugPlayerMask.png", 16, 16, 0, 0);

	sprite->GetSprite(Player_Walk_Horizontal)->visible = true;

	GetGameObject()->AddComponent(sprite);
	SpriteComp = sprite;


	auto grid = GetGameObject()->GetScene()->GetComponent<mini::GridComponent>();

	if (grid)
	{
		grid->RegisterObject(GetGameObject());
	}

	subject.AddObserver(&DigDugObserver::GetInstance());
	DigDugObserver::GetInstance().AddLives(LifeCount);
}

void DigDugCharacter::Update()
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
		if (std::abs(Direction.x) > std::abs(Direction.y))
		{
			SpriteComp->GetSprite(Player_Walk_Horizontal)->visible = true;
			SpriteComp->GetSprite(Player_Walk_Horizontal)->Flip = (Direction.x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}
		else
		{
			SpriteComp->GetSprite(Player_Walk_Vertical)->visible = true;
			SpriteComp->GetSprite(Player_Walk_Vertical)->Flip = (Direction.y > 0) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
		}

		break;
	case Walk:
		trans->Translate(Movement.x, Movement.y);

		if (std::abs(Direction.x) > std::abs(Direction.y))
		{
			SpriteComp->GetSprite(Player_Walk_Horizontal)->visible = true;
			SpriteComp->GetSprite(Player_Walk_Horizontal)->Flip = (Direction.x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		}
		else
		{
			SpriteComp->GetSprite(Player_Walk_Vertical)->visible = true;
			SpriteComp->GetSprite(Player_Walk_Vertical)->Flip = (Direction.y > 0) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
		}

		//SpriteComp frame += time;
		State = Idle;

		break;
	case Shoot:
		HoseDistance += mini::Time::DeltaTime() * HoseSpeed;

		if (std::abs(Direction.x) > std::abs(Direction.y))
		{
			SpriteComp->GetSprite(Player_Walk_Horizontal)->visible = true;
			SpriteComp->GetSprite(Player_Walk_Horizontal)->Flip = (Direction.x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

			SpriteComp->GetSprite(Player_Hose_Horizontal)->visible = true;
			SpriteComp->GetSprite(Player_Hose_Horizontal)->SetFrame(0);
			SpriteComp->GetSprite(Player_Hose_Horizontal)->Flip = (Direction.x < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
			SpriteComp->GetSprite(Player_Hose_Horizontal)->RelativeX = (int)copysignf(float(HoseDistance), Direction.x);
			HoseComp->SetRelativePosition(RelHosePosition.x + (int)copysignf(float(HoseDistance), Direction.x), RelHosePosition.y);

			float temp = HoseDistance;
			int i = 1;
			while (temp / BlockLength >= 1.0f)
			{
				SpriteComp->GetSprite(Player_Hose_Horizontal)->AddInstance((int)copysignf(float(i * BlockLength), Direction.x),0, 1);
				temp -= BlockLength;
				i++;
			}
		}
		else
		{
			SpriteComp->GetSprite(Player_Walk_Vertical)->visible = true;
			SpriteComp->GetSprite(Player_Walk_Vertical)->Flip = (Direction.y > 0) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;

			SpriteComp->GetSprite(Player_Hose_Vertical)->visible = true;
			SpriteComp->GetSprite(Player_Hose_Vertical)->SetFrame(0);
			SpriteComp->GetSprite(Player_Hose_Vertical)->Flip = (Direction.y > 0) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
			SpriteComp->GetSprite(Player_Hose_Vertical)->Y = (int)copysignf(float(HoseDistance), Direction.y);
			HoseComp->SetRelativePosition(RelHosePosition.x, RelHosePosition.y +(int)copysignf(float(HoseDistance), Direction.y));

			float temp = HoseDistance;
			int i = 1;
			while (temp / BlockLength >= 1.0f)
			{
				SpriteComp->GetSprite(Player_Hose_Vertical)->AddInstance(0, (int)copysignf(float(i * BlockLength), Direction.y),1);
				temp -= BlockLength;
				i++;
			}



		}

		HoseComp->GetCollider().Active = true;

		if (HoseDistance >= HoseLength)
		{
			State = Idle;
			HoseDistance = 0;
			HoseComp->GetCollider().Active = false;
			HoseComp->SetRelativePosition(RelHosePosition.x, RelHosePosition.y);
		}


		break;
	case Pump:
		break;
	}


	Movement = glm::vec2(0, 0);
}

mini::Sprite * DigDugCharacter::GetMask() const
{
	return SpriteComp->GetSprite(Player_Mask);
}

void DigDugCharacter::Move(float x, float y)
{
	if (State != Shoot)
	{
		Direction = glm::vec2(x, y);
		State = Walk;
	}
}

void DigDugCharacter::SetInput()
{
	auto& input = mini::InputManager::GetInstance();

	//controller
	input.AssignButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_Up, PlayerIndex, new MoveCommand_Up(this));
	input.AssignButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_Down, PlayerIndex, new MoveCommand_Down(this));
	input.AssignButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_left, PlayerIndex, new MoveCommand_Left(this));
	input.AssignButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_Right, PlayerIndex, new MoveCommand_Right(this));
	input.AssignButton(mini::InputTypes::XInput, mini::ControllerButton::Left_ThumbStick, PlayerIndex, new MoveCommand_AllDirections(this));
	input.AssignButton(mini::InputTypes::XInput, mini::ControllerButton::Button_A, PlayerIndex, new ShootCommand(this));

	//keyboard
	if (PlayerIndex == 0)
	{
		input.AssignButton(mini::InputTypes::Keyboard, SDLK_UP, PlayerIndex, new MoveCommand_Up(this));
		input.AssignButton(mini::InputTypes::Keyboard, SDLK_DOWN, PlayerIndex, new MoveCommand_Down(this));
		input.AssignButton(mini::InputTypes::Keyboard, SDLK_LEFT, PlayerIndex, new MoveCommand_Left(this));
		input.AssignButton(mini::InputTypes::Keyboard, SDLK_RIGHT, PlayerIndex, new MoveCommand_Right(this));
		input.AssignButton(mini::InputTypes::Keyboard, SDLK_SPACE, PlayerIndex, new ShootCommand(this));
	}
}

void DigDugCharacter::RemoveInput()
{
	auto& input = mini::InputManager::GetInstance();

	//controller
	input.RemoveButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_Up, PlayerIndex);
	input.RemoveButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_Down, PlayerIndex);
	input.RemoveButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_left, PlayerIndex);
	input.RemoveButton(mini::InputTypes::XInput, mini::ControllerButton::Dpad_Right, PlayerIndex);
	input.RemoveButton(mini::InputTypes::XInput, mini::ControllerButton::Left_ThumbStick, PlayerIndex);
	input.RemoveButton(mini::InputTypes::XInput, mini::ControllerButton::Button_A, PlayerIndex);

	//keyboard
	if (PlayerIndex == 0)
	{
		input.RemoveButton(mini::InputTypes::Keyboard, SDLK_UP, PlayerIndex);
		input.RemoveButton(mini::InputTypes::Keyboard, SDLK_DOWN, PlayerIndex);
		input.RemoveButton(mini::InputTypes::Keyboard, SDLK_LEFT, PlayerIndex);
		input.RemoveButton(mini::InputTypes::Keyboard, SDLK_RIGHT, PlayerIndex);
		input.RemoveButton(mini::InputTypes::Keyboard, SDLK_SPACE, PlayerIndex);
	}
}

void DigDugCharacter::SetState(States st)
{
	State = st;
}
