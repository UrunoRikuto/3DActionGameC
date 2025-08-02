#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>
#include "Enums.h"

HRESULT Init(HWND hWnd, UINT width, UINT height, HINSTANCE hInstance);
void Uninit();
void Update();
void Draw();

void SetRender2D();

void SetRender3D();

bool IsGameLoop(void);
void SetGameEnd(void);

void ChangeScene(SceneType Next);

#endif // __MAIN_H__