#include "MiniginPCH.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <iterator>

mini::GridComponent::GridComponent(int columns, int rows, unsigned int Gridwidth, unsigned int Gridheight, float marginX, float marginY, int offsetX, int offsetY)
{
	Rows = rows;
	Columns = columns;
	Width = Gridwidth;
	Height = Gridheight;
	OffsetX = offsetX;
	OffsetY = offsetY;
	MarginX = marginX;
	MarginY = marginY;

	const int amount = Rows * Columns;
	Grid = new bool[amount] {true};
	//memset(Grid, true, amount / 8);
	std::fill(Grid, Grid + amount, true);
}

mini::GridComponent::~GridComponent()
{
	delete[] Grid;
}

void mini::GridComponent::RegisterObject(GameObject* obj)
{
	auto trans = obj->GetComponent<TransformComponent>();
	if(trans)
	{
		auto wpos = trans->GetWorldPosition();
		GridState state;
		state.x = wpos.x;
		state.y = wpos.y;
		state.direction = trans->GetWorldRotation();
		Objects[obj] = state;

		return;
	}

	//logger object doesn't have a position/transform
}

void mini::GridComponent::RemoveObject(GameObject* obj)
{
	Objects.erase(obj);
}

void mini::GridComponent::SetGridState(unsigned int x, unsigned int y, bool state)
{
	Grid[(y * Rows) + x] = state;
}

void mini::GridComponent::SetGridStateRect(SDL_Rect rectInGridspace, bool state)
{
	int pitch = Columns;
	int totalheight = (rectInGridspace.y * pitch) + (pitch * rectInGridspace.h);
	int totalWidth = rectInGridspace.x + rectInGridspace.w;

	for (int y = rectInGridspace.y * pitch; y < totalheight; y += pitch)
	{
		for (int x = rectInGridspace.x; x < totalWidth; x++)
		{
			Grid[y + x] = state;
		}
	}
}

bool mini::GridComponent::GetGridState(unsigned int x, unsigned int y) const
{
	return Grid[(y * Rows) + x];
}

void mini::GridComponent::SetSliding(bool sliding)
{
	SlidingAgainstRail = sliding;
}

bool mini::GridComponent::Update()
{
	for(auto& obj : Objects)
	{
		auto& gobj = obj.first;
		auto& lastState = obj.second;
		auto trans = gobj->GetComponent<TransformComponent>();
		auto wpos = trans->GetWorldPosition();

		int GridX = (int) std::floor( ((float)wpos.x / Width) - ((float)OffsetX / Width));
		int GridY = (int) std::floor( ((float)wpos.y / Height) - ((float)OffsetY / Height));

		bool IsWalkAble = Grid[(GridY * Columns) + GridX];

		if(IsWalkAble)
		{
			lastState.x = wpos.x;
			lastState.y = wpos.y;
			lastState.direction = trans->GetWorldRotation();
		}
		else
		{
			trans->Translate(lastState.x - wpos.x, lastState.y - wpos.y);
		}
	}

	return true;
}
