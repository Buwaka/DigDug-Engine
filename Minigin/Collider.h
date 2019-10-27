#pragma once
#include "CollissionCommand.h"
namespace mini
{
	struct Triangle
	{
		union 
		{

			struct { glm::ivec2 p1, p2, p3; };
			struct { glm::ivec2 data[3]; };
		};
		Triangle() : data()
		{};

		Triangle operator+(glm::ivec2 const& rhs)
		{
			Triangle t;
			t.p1 = p1 + rhs;
			t.p2 = p2 + rhs;
			t.p3 = p3 + rhs;
			return t;
		}

	};
	//inline Triangle operator+(Triangle& lhs, glm::ivec2 rhs)
	//{
	//	Triangle t;
	//	t.p1 = lhs.p1 + rhs;
	//	t.p2 = lhs.p2 + rhs;
	//	t.p3 = lhs.p3 + rhs;
	//	return t;
	//}

	static inline std::vector<Triangle> RectangleCollider(int width, int height)
	{
		float halfwidth = (float) width / 2;
		float halfheight = (float) height / 2;

		glm::ivec2 LT = { (int) -std::floor(halfwidth), (int) std::ceil(halfheight)  };
		glm::ivec2 LB = { (int) -std::floor(halfwidth), (int)-std::floor(halfheight) };
		glm::ivec2 RT = { (int)  std::ceil(halfwidth) , (int) std::ceil(halfheight)  };
		glm::ivec2 RB = { (int)  std::ceil(halfwidth) , (int)-std::floor(halfheight) };

		Triangle left, right;

		left.p1 = LT;
		left.p2 = RB;
		left.p3 = LB;

		right.p1 = LT;
		right.p2 = RT;
		right.p3 = RB;

		std::vector<Triangle> out;
		out.push_back(left);
		out.push_back(right);

		return out;
	};


	

	struct Collider
	{
		std::vector<Triangle> Shape;

		union
		{
			struct { int X, Y; };
			glm::ivec2 pos;
		};

		float Rotation;

		bool Active = true;
		ObjectComponent* Parent;
		CollissionCommand* Command;

		Collider() : Shape(), pos(glm::ivec2(0,0)), Rotation(), Command(nullptr), Parent(nullptr) {};

		Collider(std::vector<Triangle> shape, CollissionCommand* command, ObjectComponent* parent) : pos(glm::ivec2(0, 0)), Rotation()
		{
			Shape = shape;
			Command = command;
			Parent = parent;
		};

		Collider(std::vector<Triangle> shape, int x, int y, float rotation, CollissionCommand* command, ObjectComponent* parent)
		{
			Shape = shape;
			X = x;
			Y = y;
			Rotation = rotation;
			Command = command;
			Parent = parent;
		};

		~Collider()
		{
			if (Command)
			{
				delete Command;
			}
		}
	};





	static int sign(glm::ivec2& p1, glm::ivec2& p2, glm::ivec2& p3)
	{
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
	}
	//https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
	static bool PointInTriangle(glm::ivec2& pt, Triangle& triangle)
	{
		int d1, d2, d3;
		bool has_neg, has_pos;

		d1 = sign(pt, triangle.p1, triangle.p2);
		d2 = sign(pt, triangle.p2, triangle.p3);
		d3 = sign(pt, triangle.p3, triangle.p1);

		has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
		has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

		return !(has_neg && has_pos);
	}

	static bool IsPointOverlap(glm::ivec2 point, Collider* shape)
	{
		for (Triangle triangle : shape->Shape)
		{
			auto movedtriangle = triangle + shape->pos;
			if (PointInTriangle(point, movedtriangle))
			{
				return true;
			}
		}
		return false;
	}


	static inline bool CheckCollission(Collider * lhs, Collider * rhs)
	{
		for (auto& triangle : lhs->Shape)
		{
			for (auto& point : triangle.data)
			{
				if (IsPointOverlap(point + glm::ivec2(lhs->X,lhs->Y), rhs))
				{
					return true;
				}
			}
		}
		return false;
	}
}