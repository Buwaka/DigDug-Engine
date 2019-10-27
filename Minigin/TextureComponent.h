#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <string>

namespace mini
{

	class TextureComponent : public ObjectComponent
	{
	public:
		TextureComponent();
		TextureComponent(std::string path);
		TextureComponent(Texture2D* texture);
		virtual ~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;


		Texture2D* GetTexture();
		void SetTexture(Texture2D* input);
		int width() const;
		int height() const;
		void Flip(SDL_RendererFlip flip);



		virtual void Initialize() override {} ;
		virtual void Update() override;
		virtual void Draw() const override;

	private:
		Texture2D* Texture = nullptr;
		SDL_RendererFlip FlipState = SDL_RendererFlip::SDL_FLIP_NONE;
	};

}