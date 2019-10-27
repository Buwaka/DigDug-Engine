#pragma once

//Debug font
#define DEBUG_FONT "REFSAN.TTF"

//Uncomment to update every scene per frame instead of only the focussed scene
//#define mini_UpdateAllScenes

//Uncomment to enable LateUpdate in gameobjects, will be slightly slower but it exists for when manually ordering isn't a possibility
//#define mini_LateUpdate

//Uncomment to enable PostDraw, can be useful for fast UI, but it will be faster if you just use gameobject ordering, if possible
//#define mini_PostDraw

//Uncomment to enable per frame sprite visibility Resets, can make code less bloated
#define mini_SpritePerFrameReset

//Uncomment to view collission shapes during debug
//#define mini_DebugCollission

//DEBUG color for collission
#define mini_DebugColor SDL_Color{ 255,0,0,255 }

//FPS counter
//#define mini_FPSCounter

// threadcount
#define ThreadCount 8