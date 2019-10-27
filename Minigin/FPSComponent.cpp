#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"

mini::FPSComponent::FPSComponent()
{
	AverageFPS = 0;
	FPS = 0;
	Frames = 0;
	TextBox = nullptr;
}

mini::FPSComponent::~FPSComponent()
{
	delete TextBox;
}

void mini::FPSComponent::FixedUpdate()
{
	FPS = Frames;
	AverageFPS = (AverageFPS + FPS) / 2;
	Frames = 0;

	if (TextBox == nullptr)
	{
		throw std::runtime_error(std::string("FPS Component not initialized: ") + GameObject->GetName());
	}

	TextBox->SetText(std::to_string(FPS) + " : " + std::to_string(AverageFPS).substr(0, 6));
	TextBox->Update();
}

void mini::FPSComponent::Initialize()
{
	TextBox = new TextComponent(std::to_string(FPS), 16, DEBUG_FONT, {255,255,0,255});
	TextBox->Initialize();
	TextBox->GameObject = GetGameObject();
}

void mini::FPSComponent::Update()
{

	Frames++;
}

void mini::FPSComponent::Draw() const
{
	//Frames++;
	TextBox->Draw();
}
