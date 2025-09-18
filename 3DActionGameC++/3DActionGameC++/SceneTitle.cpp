/*
* @file SceneTitle.cpp
* @brief タイトルシーンのクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/

#include "SceneBase.h"
#include "SceneTitle.h"
#include "DirectXTex/TextureLoad.h"
#include "Defines.h"
#include "VertexBuffer.h"
#include "Input.h"
#include "Mouse.h"
#include "Main.h"

// @brief コンストラクタ
CSceneTitle::CSceneTitle()
{
	//Vertexの生成
	Vertex vtx[4] = {
	{ {-SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{0.0f,0.0f}},
	{ { SCREEN_WIDTH,-SCREEN_HEIGHT,0.0f},{1.0f,0.0f}},
	{ {-SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{0.0f,1.0f}},
	{ { SCREEN_WIDTH, SCREEN_HEIGHT,0.0f},{1.0f,1.0f}},
	};

	//生成したVertexをBufferのポインタ変数に設定
	m_pVtx = CreateVertexBuffer(vtx, 4);

	HRESULT hr = E_FAIL;
	//タイトルの背景テクスチャの設定
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("BackGround.png"), &m_pTex);
	if (FAILED(hr)) {
		//---デバックモードのみ処理
#ifdef _DEBUG
		MessageBox(NULL, "Title背景画像", "Error", MB_OK);
#endif
	}
}

// @brief デストラクタ
CSceneTitle::~CSceneTitle()
{
	//バッファーポインタの解放
	if (m_pVtx) m_pVtx->Release();
	//テクスチャポインタの解放
	if (m_pTex) m_pTex->Release();
}

// @brief 更新処理
void CSceneTitle::Update(void)
{
	if (IsKeyTrigger(VK_RETURN) || MouseInput::IsTrigger(MouseInput::MouseButton::Left))
	{
		//シーン切り替え処理
		ChangeScene(SceneType::QuestSelect, new CFade(2.0f));
	}
}

// @brief 描画処理
void CSceneTitle::Draw(void)
{
	//背景の描画
	SetSpriteTexture(m_pTex);

	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	DrawSprite(m_pVtx, sizeof(Vertex));
}
