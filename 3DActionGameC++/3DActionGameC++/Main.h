#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>
#include "Enums.h"
#include "SceneBase.h"
#include "Transition.h"

HRESULT Init(HWND hWnd, UINT width, UINT height, HINSTANCE hInstance);
void Uninit();
void Update();
void Draw();

void SetRender2D();

void SetRender3D();

bool IsGameLoop(void);
void SetGameEnd(void);

void ChangeScene(SceneType Next, TransitionType In_Transition);

CSceneBase* GetCurrentScene(void);

#endif // __MAIN_H__