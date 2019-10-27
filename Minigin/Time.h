#pragma once
#include <chrono>
#include "Singleton.h"
namespace mini
{
	typedef std::ratio<1, 1> Seconds;
	class Time : Singleton<Time>
	{
	public:
		Time();
		~Time();

		static void Init();

		static void Update();

		template <typename T>
		static std::chrono::duration<float,T> DeltaTime();

		static float DeltaTime();
		static float TotalTime();

	private:
		static std::chrono::high_resolution_clock::time_point StartPoint;
		static std::chrono::high_resolution_clock::time_point LastFrame;

	};

	template <typename T>
	std::chrono::duration<float, T> Time::DeltaTime()
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float,T> temp = now - LastFrame;
		return temp;
	}
}
