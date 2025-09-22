#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Sprite.h"
#include "Geometory.h"
#include "Input.h"
#include "Mouse.h"
#include "Defines.h"
#include "SceneTitle.h"
#include "SceneQuestSelect.h"
#include "SceneGame.h"
#include "ShaderList.h"
#include "Camera.h"
#include "Fade.h"

RenderTarget* pRTV;
DepthStencil* pDSV;

bool IsLoop = true;
CSceneBase* g_pScene;
CTransition* g_pTransition = nullptr;
CSceneBase* g_pNextScene = nullptr;

HRESULT Init(HWND hWnd, UINT width, UINT height,HINSTANCE hInstance)
{
	HRESULT hr;
	// DirectX初期化
#ifdef _DEBUG
	hr = InitDirectX(hWnd, width, height, false);
#else
	hr = InitDirectX(hWnd, width, height, true);
#endif // _DEBUG

	if (FAILED(hr)) { return hr; }
	srand(timeGetTime());
	InitSpriteDrawer(GetDevice(), GetContext(), SCREEN_WIDTH, SCREEN_HEIGHT);
	Geometory::Init();
	
	Sprite::Init();
	// 他機能初期化
	InitInput();
	MouseInput::Init();
	ShaderList::Init();

	pRTV = GetDefaultRTV();
	pDSV = GetDefaultDSV();

	Camera::CreataeInstance();

	// シーン作成
	g_pScene = new CSceneTitle();

	return hr;
}

void Uninit()
{
	SAFE_DELETE(g_pScene);
	UninitInput();
	ShaderList::Uninit();
	Sprite::Uninit();
	Geometory::Uninit();
	UninitSpriteDrawer();
	UninitDirectX();
}

void Update()
{
	UpdateInput();
	MouseInput::Update();
	g_pScene->Update();
	if (g_pTransition != nullptr)
	{
		g_pTransition->Update();
		if (g_pTransition->IsChange())
		{
			// シーン変更時の処理
			SAFE_DELETE(g_pScene);
			g_pScene = g_pNextScene;
			g_pNextScene = nullptr;
			g_pTransition->SetChange(false);
		}
		if (g_pTransition->IsEnd())
		{
			SAFE_DELETE(g_pTransition);
		}
	}
}

void Draw()
{
	BeginDrawDirectX();

	Geometory::SetProjection(Camera::GetInstance()->GetProjectionMatrix());
	Geometory::SetView(Camera::GetInstance()->GetViewMatrix());
	g_pScene->Draw();
	if (g_pTransition != nullptr)
	{
		g_pTransition->Draw();
	}
	EndDrawDirectX();
}

void SetRender2D()
{
	SetRenderTargets(1, &pRTV, nullptr);
}

void SetRender3D()
{
	SetRenderTargets(1, &pRTV, pDSV);
}

bool IsGameLoop(void)
{
	if (IsKeyPress(VK_ESCAPE) && IsKeyPress(VK_DELETE))
	{
		IsLoop = false;
	}
	return IsLoop;
}

void SetGameEnd(void)
{
	IsLoop = false;
}

void ChangeScene(SceneType Next, TransitionType In_Transition)
{
	switch (In_Transition)
	{
	case TransitionType::Fade:
		g_pTransition = new CFade(2.0f);
		break;
	}

	switch (Next)
	{
	case SceneType::Title:
		g_pNextScene = new CSceneTitle();
		break;
	case SceneType::QuestSelect:
		g_pNextScene = new CSceneQuestSelect();
		break;
	case SceneType::Game:
		g_pNextScene = new CSceneGame();
		break;
	}
}

CSceneBase* GetCurrentScene(void)
{
	return g_pScene;
}

// EOF