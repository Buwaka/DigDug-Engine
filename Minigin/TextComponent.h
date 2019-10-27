#pragma once

#include "Component.h"
#include <SDL.h>

namespace mini
{


	class Font;
	class Texture2D;

	class TextComponent : public ObjectComponent
	{
	public:
		void Update() override;
		void Draw() const override;
		void Initialize() override;
		void PostDraw() const override;

		void SetText(const std::string& text);
		void Flip(SDL_RendererFlip flip);
		void SetColor(SDL_Color color);

		void SetRelativePosition(int x, int y);
		void SetRelativePosition(glm::ivec2 relPosition);
		void SetRelativeRotation(float degrees);

		glm::ivec2 GetRelativePosition() const;
		float GetRelativeRotation() const;


		explicit TextComponent(const std::string& text, unsigned int size = 36, const std::string& font = "Lingua.otf", SDL_Color color = { 255,255,255,255 });
		virtual ~TextComponent();
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		glm::ivec2 RelPosition;
		float RelRotation = 0.f;

		bool NeedsUpdate;
		std::string Text;
		Font* FontText;
		Texture2D* Texture;
		SDL_Color Color;
		SDL_RendererFlip FlipState = SDL_RendererFlip::SDL_FLIP_NONE;
	};

}
