#pragma once
#include "Component.h"
#include <unordered_map>
#include "Sprite.h"


namespace mini
{

	class SpriteComponent : public ObjectComponent
	{
	public:
		SpriteComponent() = default;
		virtual ~SpriteComponent();

		void AddSpriteSheet(std::string name, std::string PathToSheet, unsigned int width, unsigned int height, int x = 0, int y = 0, bool isLooping = true, float Speed = 1.0f, bool SheetIsVertical = false, int famecount = -1);
		void AddSpriteSheet(std::string name, Texture2D* sheet, unsigned int width, unsigned int height, int x = 0, int y = 0, bool isLooping = true, float Speed = 1.0f, bool SheetIsVertical = false, int famecount = -1);

		void SetSpritePosition(std::string name, int x, int y);
		void SetSpriteVisibility(std::string name, bool visible);
		void SetSpriteFrame(std::string name, int frame);
		void SetSpriteLooping(std::string name, bool looping);
		void FlipSprite(std::string name, SDL_RendererFlip flip);

		Sprite* GetSprite(std::string name);

		virtual void Initialize();
		virtual void Update();
		virtual void Draw() const;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

	private:
		std::unordered_map<std::string, Sprite*> Sprites;
		float Timer = 0.0f;

	};

}