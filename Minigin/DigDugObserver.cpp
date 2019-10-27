#include "MiniginPCH.h"
#include "DigDugObserver.h"
#include "Enemy.h"
#include "Pooka.h"
#include "Fygar.h"


DigDugObserver::DigDugObserver()
{
	Score = EnemyCount = Lives = 0;
	Level = 1;

}


DigDugObserver::~DigDugObserver()
{
}

void DigDugObserver::onNotify(mini::GameObject * entity, Uint8 digdugEvent)
{

	switch (digdugEvent)
	{
	case DigDugEvent::EVENT_SCORE:
	{
		auto comp1 = entity->GetComponent<Pooka>();
		if (comp1)
		{
			auto enemy = Cast<Pooka>(comp1);
			if (enemy)
			{
				Score += enemy->Score;
			}
		}
		auto comp2 = entity->GetComponent<Fygar>();
		if (comp2)
		{
			auto enemy = Cast<Fygar>(comp2);
			if (enemy)
			{
				Score += enemy->Score;
			}
		}

	}

		break;
	case DigDugEvent::EVENT_LEVEL:
		Level++;
		break;
	case DigDugEvent::EVENT_PLAYERDIED:
		Lives--;
		break;
	case DigDugEvent::EVENT_ENEMYDIED:
		EnemyCount--;
		break;
	}
}

void DigDugObserver::AddLives(int lives)
{
	Lives += lives;
}

void DigDugObserver::ResetLives()
{
	Lives = 0;
}

void DigDugObserver::ResetEnemyCount()
{
	EnemyCount = 0;
}

void DigDugObserver::IncreaseLevel(int i)
{
	Level += i;
}

void DigDugObserver::IncreaseEnemyCount(int i)
{
	EnemyCount += i;
}

void DigDugObserver::BindScore(int ** score)
{
	*score = &Score;
}

void DigDugObserver::BindLives(int ** lives)
{
	*lives = &Lives;
}

void DigDugObserver::BindLevel(int ** level)
{
	*level = &Level;
}
