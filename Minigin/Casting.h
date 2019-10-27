#pragma once
#include "MiniginPCH.h"
#include <type_traits>

template <typename O,typename I >
O* Cast(I* obj)
{
	return dynamic_cast<O*>(obj);
}

template <typename O, typename I >
bool IsA(I* obj)
{
	//return std::is_base_of<O, I>::value;
	//runtime, so useless in this usecase

	if (Cast<O>(obj))
	{
		return true;
	}
	return false;
}