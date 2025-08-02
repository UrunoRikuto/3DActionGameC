#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Sprite.h"
#include "Geometory.h"
#include "Input.h"
#include "Defines.h"
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "ShaderList.h"

RenderTarget* pRTV;
DepthStencil* pDSV;

bool IsLoop = true;
CSceneBase* m_pScene;

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
	ShaderList::Init();

	pRTV = GetDefaultRTV();
	pDSV = GetDefaultDSV();

	Camera::CreateCamera();

	// シーン作成
	m_pScene = new CSceneTitle();

	return hr;
}

void Uninit()
{
	SAFE_DELETE(m_pScene);
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
	m_pScene->Update();
}

void Draw()
{
	BeginDrawDirectX();

	m_pScene->Draw();

	Geometory::SetProjection(Camera::GetInfo()->GetProjectionMatrix());
	Geometory::SetView(Camera::GetInfo()->GetViewMatrix());

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

void ChangeScene(SceneType Next)
{
	SAFE_DELETE(m_pScene);

	switch (Next)
	{
	case SceneType::Title:
		m_pScene = new CSceneTitle();
		break;
	case SceneType::Game:
		m_pScene = new CSceneGame();
		break;
	}
}

// EOF