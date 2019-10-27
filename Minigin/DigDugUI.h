#pragma once
#include "Component.h"
#include "TextComponent.h"

class DigDugUI : public mini::ObjectComponent
{
public:
	DigDugUI();
	~DigDugUI();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;

private:
	bool NeedsUpdate = false;
	mini::TextComponent* ScoreBox, *LiveBox, *LevelBox;
	int Score, Lives, Level;
};

