#include "MiniginPCH.h"
#include "DigDugUI.h"
#include "DigDugObserver.h"


const int width = 288;
const int height = 224;
const int collumnlength = 16;
const int rowlength = 16;

const int collumns = width / collumnlength;
const int rows = height / rowlength;

const int UIStart = 15 * collumnlength;
const int UILength = collumns - UIStart;


DigDugUI::DigDugUI()
{
}


DigDugUI::~DigDugUI()
{
}

void DigDugUI::Initialize()
{

	LevelBox = new mini::TextComponent("0",32);
	LevelBox->SetRelativePosition(UIStart, 0);

	LiveBox = new mini::TextComponent("0", 26);
	LiveBox->SetRelativePosition(UIStart, 40);
	LiveBox->SetColor(SDL_Color{ 255,0,0,255 });

	ScoreBox = new mini::TextComponent("0", 20);
	ScoreBox->SetRelativePosition(UIStart, 80);
	ScoreBox->SetColor(SDL_Color{ 255,255,0,255 });


	GetGameObject()->AddComponent(ScoreBox);
	GetGameObject()->AddComponent(LiveBox);
	GetGameObject()->AddComponent(LevelBox);



}

void DigDugUI::Update()
{ 
	const DigDugObserver& obs = DigDugObserver::GetInstance();

	int scr = obs.GetScore();
	if (scr != Score)
	{
		Score = scr;
		NeedsUpdate = true;
	}

	int liv = obs.GetLives();
	if (liv != Lives)
	{
		Lives = liv;
		NeedsUpdate = true;
	}

	int lev = obs.GetLevel();
	if (lev != Level)
	{
		Level = lev;
		NeedsUpdate = true;
	}


	if (NeedsUpdate)
	{
		ScoreBox->SetText(std::to_string(Score));
		LiveBox->SetText(std::to_string(Lives));
		LevelBox->SetText(std::to_string(Level));
		NeedsUpdate = false;
	}
}

void DigDugUI::Draw() const
{

}
