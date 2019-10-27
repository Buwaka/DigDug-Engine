#pragma once
#include "SceneComponent.h"
#include <unordered_map>
namespace mini
{
	struct GridState
	{
		int x, y;
		float direction;
	};

	class GridComponent : public SceneComponent
	{
	public:
		GridComponent(int Columns, int rows,unsigned int width, unsigned int height,float marginX = 0.f, float marginY = 0.f, int offsetX = 0, int offsetY = 0);
		~GridComponent();

		void RegisterObject(GameObject* obj);
		void RemoveObject(GameObject* obj);

		//gridspace
		void SetGridState(unsigned int x, unsigned int y, bool state);
		//gridspace
		void SetGridStateRect(SDL_Rect rect, bool state);
		//gridspace
		bool GetGridState(unsigned int x, unsigned int y) const;

		void SetSliding(bool sliding);


		virtual bool Update();


	private:

		int OffsetX, OffsetY, Width, Height, Rows, Columns;
		float MarginX, MarginY;
		std::unordered_map<GameObject*, GridState> Objects;
		bool* Grid;
		bool SlidingAgainstRail;

	};
}
