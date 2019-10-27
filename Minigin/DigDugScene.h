#pragma once
#include "Scene.h"
#include "Texture2D.h"

class mini::GameObject;
class DigDugCharacter;


class DigDugScene :	public mini::Scene
{
public:
	DigDugScene();
	~DigDugScene();


	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() const override;

	void CleanLevel();

	void InitLevel();

private:
	mini::GameObject* Level;
	mini::GameObject* Player;
	mini::Texture2D* LevelMask;
	unsigned int tick = 0;
};

