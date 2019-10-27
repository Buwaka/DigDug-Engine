#pragma once
#include "Component.h"
#include <chrono>

namespace mini
{
	class TextComponent;
	class FPSComponent final : public ObjectComponent
	{
	public:
		FPSComponent();
		~FPSComponent();

		virtual void FixedUpdate() override;
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Draw() const override;

	private:

		float AverageFPS;
		unsigned int FPS;
		unsigned int Frames;

		TextComponent* TextBox;
	};

}