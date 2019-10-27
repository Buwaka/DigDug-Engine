#include "MiniginPCH.h"
#include "Time.h"

namespace mini
{
	std::chrono::high_resolution_clock::time_point Time::StartPoint = {};
	std::chrono::high_resolution_clock::time_point Time::LastFrame = {};

	Time::Time()
	{
		StartPoint = LastFrame = std::chrono::high_resolution_clock::now();
	}

	Time::~Time()
	{
	}

	void Time::Init()
	{
		GetInstance();
	}

	void Time::Update()
	{
		LastFrame = std::chrono::high_resolution_clock::now();
	}


	float Time::DeltaTime()
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, Seconds> temp = now - LastFrame;
		return temp.count();
	}

	float Time::TotalTime()
	{
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, Seconds> temp = now - StartPoint;
		return temp.count();
	}


}