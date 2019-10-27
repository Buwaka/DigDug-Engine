#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"

mini::TextureComponent::TextureComponent()
{
}

mini::TextureComponent::TextureComponent(std::string path)
{
	Texture = ResourceManager::GetInstance().LoadTexture(path);
}

mini::TextureComponent::TextureComponent(Texture2D * texture)
{
	Texture = texture;
}

mini::TextureComponent::~TextureComponent()
{
	delete Texture;
}

mini::Texture2D * mini::TextureComponent::GetTexture()
{
	return Texture;
}

void mini::TextureComponent::SetTexture(Texture2D * input)
{
	Texture = input;
}

int mini::TextureComponent::width() const
{
	return Texture->width();
}

int mini::TextureComponent::height() const
{
	return Texture->height();
}

void mini::TextureComponent::Flip(SDL_RendererFlip flip)
{
	FlipState = flip;
}

void mini::TextureComponent::Update()
{
	Texture->Update();
}

void mini::TextureComponent::Draw() const
{
	if (Texture != nullptr)
	{
		int x = 0, y = 0;
		float rot = 0.f;
		glm::vec2 scl{ 1,1 };
		auto trans = GameObject->GetComponent<TransformComponent>();

		if (trans)
		{
			auto temp = trans->GetWorldPosition();

			x = temp.x;
			y = temp.y;

			rot = trans->GetWorldRotation();

			scl = trans->GetWorldScale();
		}
		Renderer::GetInstance().RenderTexture(Texture, x, y, rot, scl, FlipState);
	}
}
