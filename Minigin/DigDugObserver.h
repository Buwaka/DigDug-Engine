#pragma once
#include "Observer.h"
#include "Singleton.h"

enum DigDugEvent : Uint8
{
	EVENT_SCORE = 0,
	EVENT_LEVEL = 1,
	EVENT_PLAYERDIED = 2,
	EVENT_ENEMYDIED = 3
};

class DigDugObserver : public mini::Observer, public mini::Singleton<DigDugObserver>
{
public:
	DigDugObserver();
	~DigDugObserver();

	virtual void onNotify(mini::GameObject* entity, Uint8 digdugEvent) override;

	int const& GetScore() const { return Score; };
	int const& GetLives() const { return Lives; };
	int const& GetLevel() const { return Level; };
	int const& GetEnemyCount() const { return EnemyCount; };

	void AddLives(int lives);
	void ResetLives();
	void ResetEnemyCount();
	void IncreaseLevel(int i = 1);
	void IncreaseEnemyCount(int i = 1);

	void BindScore(int** score);
	void BindLives(int** lives);
	void BindLevel(int** level);

private:
	int Score, Lives, Level, EnemyCount;
};

