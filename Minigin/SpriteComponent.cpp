#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"



void mini::SpriteComponent::AddSpriteSheet(std::string name, std::string PathToSheet, unsigned int width, unsigned int height, int x, int y, bool isLooping, float Speed, bool SheetIsVertical, int famecount)
{
	Texture2D* temp = ResourceManager::GetInstance().LoadTexture(PathToSheet);
	Sprites[name] = new Sprite(width, height, temp, x, y, isLooping, Speed, SheetIsVertical, famecount);
	delete temp;

}

void mini::SpriteComponent::AddSpriteSheet(std::string name, Texture2D* sheet, unsigned int width, unsigned int height, int x, int y, bool isLooping, float Speed, bool SheetIsVertical, int famecount)
{
	Sprites[name] = new Sprite(width, height, sheet, x, y, isLooping, Speed, SheetIsVertical, famecount);
}

void mini::SpriteComponent::SetSpritePosition(std::string name, int x, int y)
{
	auto temp = Sprites.at(name);

	temp->RelativeX = x;
	temp->Y = y;

}

void mini::SpriteComponent::SetSpriteVisibility(std::string name, bool visible)
{
	auto temp = Sprites.at(name);

	temp->visible = visible;

}

void mini::SpriteComponent::SetSpriteFrame(std::string name, int frame)
{
	auto temp = Sprites.at(name);

	temp->SetFrame(frame);
}

void mini::SpriteComponent::SetSpriteLooping(std::string name, bool looping)
{
	auto temp = Sprites.at(name);

	temp->isLooping = looping;
}

void mini::SpriteComponent::FlipSprite(std::string name, SDL_RendererFlip flip)
{
	auto temp = Sprites.at(name);

	temp->Flip = flip;
}

mini::Sprite * mini::SpriteComponent::GetSprite(std::string name)
{
	return Sprites.at(name);
}

void mini::SpriteComponent::Initialize()
{
}

void mini::SpriteComponent::Update()
{
	//float delta = Time::DeltaTime();

	//for (auto& element : Sprites)
	//{
	//	int spritetime = int( std::round(Timer + (delta * element.second->FrameSpeed)));
	//	element.second->SetTimerFrame(spritetime);
	//}
	//Timer += delta;
}

mini::SpriteComponent::~SpriteComponent()
{
	for (auto& element : Sprites)
	{
		delete element.second;
	}
}

void mini::SpriteComponent::Draw() const
{
	int x = 0, y = 0;
	float rot = 0.f;
	glm::vec2 scl{1,1};
	auto trans = GameObject->GetComponent<TransformComponent>();

	if (trans)
	{
		auto temp = trans->GetWorldPosition();

		x = temp.x;
		y = temp.y;

		rot = trans->GetWorldRotation();

		scl = trans->GetWorldScale();
	}

	for (auto& element : Sprites)
	{
		auto sprite = element.second;
		if (sprite->visible)
		{
			Renderer::GetInstance().RenderTexture(sprite, x, y, rot, scl, sprite->Flip);
		}
	}

#ifdef mini_SpritePerFrameReset
	for (auto& element : Sprites)
	{
		element.second->Reset();
	}
#endif // mini_SpriteCleanup
}
