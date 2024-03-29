#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>

#pragma warning(disable : 4201)
#include <glm/glm.hpp>
#include <SDL.h>
//#pragma warning(default : 4201)


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Log.h" // Various logging functions
#include "EngineSettings.h"