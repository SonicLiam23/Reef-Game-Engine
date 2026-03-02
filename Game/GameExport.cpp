#pragma once
#ifdef GAME_EXPORTS
#define SCRIPT __declspec(dllexport)
#else
#define SCRIPT __declspec(dllimport)
#endif