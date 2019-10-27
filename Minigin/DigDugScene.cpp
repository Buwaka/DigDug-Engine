#include "MiniginPCH.h"
#include "DigDugScene.h"
#include "TransformComponent.h"
#include "ColorFormats.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "DigDugCharacter.h"
#include "InputManager.h"
#include "InputCommand.h"
#include "ResourceManager.h"
#include "GridComponent.h"
#include "FPSComponent.h"
#include "CollissionComponent.h"
#include "Pooka.h"
#include "Fygar.h"
#include "DigDugUI.h"
#include "DigDugObserver.h"

const int width = 288;
const int height = 224;
const int collumnlength = 16;
const int rowlength = 16;

const int collumns = width / collumnlength;
const int rows = height / rowlength;

const int colorcount = 5;
const int RowIndex[colorcount] = { 3,4,4,4,3 };

const int UIStart = 13;
const int UILength = collumns - UIStart;

const int StartPlayfield = 2; //rows from top
const int EndPlayfield = rows - 1;

const int TicksPerUpdate = 4;

int PookaCount = 2;
int FygarCount = 1;




DigDugScene::DigDugScene() : Scene("DigdugScene")
{
	mini::Renderer::GetInstance().SetResolution(width, height);
	mini::Renderer::GetInstance().SetScale(2);

	mini::InputManager::GetInstance().AssignButton(mini::InputTypes::Keyboard, SDLK_ESCAPE, 0, new mini::ForceQuitCommand());




}


DigDugScene::~DigDugScene()
{

	delete LevelMask;
}

void DigDugScene::Initialize()
{
	int currentlevel = DigDugObserver::GetInstance().GetLevel();
	if (currentlevel < 1 || currentlevel > 9)
	{
		GameContext::GetInstance().GetEngine()->Quit();
	}
	 

	InitLevel();
	auto obj = new mini::GridComponent(width / collumnlength, height / rowlength, rowlength, collumnlength);
	AddSceneComponent(obj);


	Player = new mini::GameObject("Player", this);
	auto chara = new DigDugCharacter(0);
	Player->GetComponent<mini::TransformComponent>()->SetPosition(3 * rowlength, 3 * collumnlength, 2);
	Player->AddComponent(chara);

	Add(Player);

	size_t controllercount = mini::InputManager::GetInstance().GetControllerCount();
	for (size_t i = 1; i < controllercount; i++)
	{
		Player = new mini::GameObject("Player " + std::to_string(i), this);
		chara = new DigDugCharacter((int)i);
		Player->GetComponent<mini::TransformComponent>()->SetPosition((3 + (int)i) * rowlength, 3 * collumnlength, 2);
		Player->AddComponent(chara);

		Add(Player);
	}


	//pooka
	for (int i = 0; i < PookaCount; i++)
	{
		auto pookaobj = new mini::GameObject("Pooka" + std::to_string(i + 1),this);
		auto pooka = new Pooka();
		pookaobj->AddComponent(pooka);
		Add(pookaobj);
		pooka->SetRandomPosition(0, StartPlayfield * rowlength, UIStart * collumnlength, (rows - StartPlayfield) * rowlength);
		pookaobj->SetRenderPosition(3);
	}

	//Fygar
	for (int i = 0; i < FygarCount; i++)
	{
		auto Fygarobj = new mini::GameObject("Fygar" + std::to_string(i + 1), this);
		auto fygar = new Fygar();
		Fygarobj->AddComponent(fygar);
		Add(Fygarobj);
		fygar->SetRandomPosition(0, StartPlayfield * rowlength, UIStart * collumnlength, (rows - StartPlayfield) * rowlength);
		Fygarobj->SetRenderPosition(3);
	}



	//disable air as walkable
	obj->SetGridStateRect(SDL_Rect{ 0, 0, collumns, StartPlayfield }, false);
	//disable sidebar
	obj->SetGridStateRect(SDL_Rect{ UIStart, 0, UILength, rows }, false);
	//Set Ground barrier
	obj->SetGridStateRect(SDL_Rect{ 0, EndPlayfield, collumns, 1 }, false);


	auto UI = new mini::GameObject("UI", this);
	UI->AddComponent(new DigDugUI());
	UI->GetComponent<mini::TransformComponent>()->SetPosition(0, 0, INT_MAX );
	Add(UI);
}

void DigDugScene::Update()
{
	//optimization because addmask is slow
	if ((tick %= TicksPerUpdate) == 0)
	{
		auto& obs = DigDugObserver::GetInstance();
		auto trans = Player->GetComponent<mini::TransformComponent>();
		auto pos = trans->GetWorldPosition();
		auto textcomp = Level->GetComponent<mini::TextureComponent>();

		LevelMask->Substract(Player->GetComponent<DigDugCharacter>()->GetMask(), (int)pos.x, (int)pos.y);

		if (textcomp)
		{
			textcomp->GetTexture()->AddMask(LevelMask);
		}

		if (obs.GetLives() <= 0)
		{
			obs.IncreaseLevel(-1);
			PookaCount--;
			FygarCount--;
			CleanLevel();
		}

		if (obs.GetEnemyCount() <= 0)
		{
			DigDugObserver::GetInstance().IncreaseLevel();
			PookaCount++;
			FygarCount++;
			CleanLevel();
		}
	}
	tick++;
}

void DigDugScene::Render() const
{
	//auto trans = Player->GetComponent<mini::TransformComponent>();
	//auto pos = trans->GetWorldPosition();
	//mini::Renderer::GetInstance().RenderTexture(*LevelMask, 0, 0, 0, SDL_RendererFlip::SDL_FLIP_NONE);
	//mini::Renderer::GetInstance().RenderTexture(Player->GetMask(), pos.x, pos.y,0,SDL_RendererFlip::SDL_FLIP_NONE);


}

void DigDugScene::CleanLevel()
{
	if(LevelMask)
		delete LevelMask;
	Reset();
	DigDugObserver::GetInstance().ResetEnemyCount();
	DigDugObserver::GetInstance().ResetLives();
	Initialize();

}

void DigDugScene::InitLevel()
{
	Level = new mini::GameObject();
	auto textureComp = new mini::TextureComponent("DigDugLevelRGB.png");
	auto temp = textureComp->GetTexture();


	float H = (float)(rand() % 360);
	hsv<float> BaseColor{ H,1,1 };
	SDL_Color Color;


	int x = textureComp->height();
	for (size_t i = 0; i < colorcount; i++)
	{
		BaseColor.s = float(colorcount - i) / colorcount;
		auto rgb = hsv2rgb(BaseColor);
		Color = rgb;

		x = x - (RowIndex[i] * rowlength);
		textureComp->GetTexture()->Colorize(&Color, 0, x, textureComp->width(), RowIndex[i] * rowlength);
	}



	LevelMask = mini::ResourceManager::GetInstance().LoadTexture("DigDugLevelMask.png");

	temp->AddMask(LevelMask);
	Level->AddComponent(textureComp);
	Level->GetComponent<mini::TransformComponent>()->SetPosition(0, 0, 1);
	Add(Level);
}
