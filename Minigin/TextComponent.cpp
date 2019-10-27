#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TransformComponent.h"

mini::TextComponent::TextComponent(const std::string & text, unsigned int size, const std::string & font, SDL_Color color) 
{
	Text = text;
	Color = color;
	FontText = ResourceManager::GetInstance().LoadFont(font, size);
	NeedsUpdate = true;
	Texture = nullptr;
}

mini::TextComponent::~TextComponent()
{
	delete Texture;
	delete FontText;
}


void mini::TextComponent::Update()
{
	if (NeedsUpdate)
	{
		if(FontText == nullptr)
		{
			throw std::runtime_error(std::string("Font not set ") + GameObject->GetName());
		}

		const auto surf = TTF_RenderText_Blended(FontText->GetFont(), Text.c_str(), Color);


		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + GameObject->GetName() + SDL_GetError());
		}


		if (Texture != nullptr)
			delete Texture;

		Texture = new Texture2D(surf);

		NeedsUpdate = false;
	}
}

void mini::TextComponent::Initialize()
{
}

void mini::TextComponent::PostDraw() const
{
}

void mini::TextComponent::Draw() const
{
	if (Texture != nullptr)
	{
		glm::ivec2 pos = RelPosition;
		float rot = RelRotation;
		glm::vec2 scl{ 1,1 };
		auto trans = GameObject->GetComponent<TransformComponent>();

		if (trans)
		{
			auto temp = trans->GetWorldPosition();

			pos += glm::ivec2(temp);

			rot += trans->GetWorldRotation();

			scl = trans->GetWorldScale();
		}

		Renderer::GetInstance().RenderTexture(Texture, pos.x, pos.y, rot, scl, FlipState);
	}
}

void mini::TextComponent::SetText(const std::string& text)
{
	Text = text;
	NeedsUpdate = true;
}

void mini::TextComponent::Flip(SDL_RendererFlip flip)
{
	FlipState = flip;
}

void mini::TextComponent::SetColor(SDL_Color color)
{
	Color = color;
}

void mini::TextComponent::SetRelativePosition(int x, int y)
{
	RelPosition = glm::ivec2(x, y);
}

void mini::TextComponent::SetRelativePosition(glm::ivec2 relPosition)
{
	RelPosition = relPosition;
}

void mini::TextComponent::SetRelativeRotation(float degrees)
{
	RelRotation = degrees;
}

glm::ivec2 mini::TextComponent::GetRelativePosition() const
{
	return RelPosition;
}

float mini::TextComponent::GetRelativeRotation() const
{
	return RelRotation;
}





