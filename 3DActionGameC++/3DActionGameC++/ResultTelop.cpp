/*=====================================================================
* @file ResultTelop.cpp
* @brief リザルトテロップの実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "ResultTelop.h"

/* システム・要素のインクルード */
#include "DirectXTex/TextureLoad.h"
#include "VertexBuffer.h"
#include "SpriteDrawer.h"
#include "Texture.h"
#include "Input.h"
#include "Mouse.h"
#include "GameValues.h"
#include <string>
#include "Main.h"


// @brief コンストラクタ
CResultTelop::CResultTelop(bool IsWin)
{
	// テロップの表示時間を設定
	m_fDisplayTime = GameValue::Telop::RESULTTELOP_DISPLAY_TIME;
	// 経過時間を初期化
	m_fElapsedTime = 0.0f;
	// 頂点バッファの作成
	Vertex vtx[] =
	{
		//背景表示の座標
		{{-1500, -800, 0.0f}, {0.0f, 0.0f}},
		{{ 1500, -800, 0.0f}, {1.0f, 0.0f}},
		{{-1500,  800, 0.0f}, {0.0f, 1.0f}},
		{{ 1500,  800, 0.0f}, {1.0f, 1.0f}},
	};
	m_pVertexBuffer = CreateVertexBuffer(vtx, 4);

	HRESULT hr = NULL;
	std::string telopFileName;
	// テクスチャの生成
	if (IsWin)
	{
		telopFileName = TEXTURE_PATH("Telop/QuestClear.png");
	}
	else
	{
		telopFileName = TEXTURE_PATH("Telop/QuestFailed.png");
	}
	// テロップのテクスチャを読み込む
	hr = LoadTextureFromFile(GetDevice(), telopFileName.c_str(), &m_pTexture);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT(telopFileName.c_str(), "テロップの読み込みに失敗しました"), TEXT("エラー"), MB_OK);
	}
}

// @brief デストラクタ
CResultTelop::~CResultTelop()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTexture);
}

// @brief 更新処理
bool CResultTelop::Update()
{
	// 経過時間を更新
	m_fElapsedTime += 1.0f / fFPS;
	// 表示時間を超えたらテロップを非表示にする
	if (m_fElapsedTime >= m_fDisplayTime || 
		IsKeyTrigger(InputKey::TelopEffect::SKIP) || 
		MouseInput::IsTrigger(MouseInput::MouseButton::Left))
	{
		ChangeScene(SceneType::QuestSelect, TransitionType::Fade); // シーンをクエスト選択に変更
		return true; // trueを返して、テロップを削除する
	}
	return false;
}

// @brief 描画処理
void CResultTelop::Draw()
{
	// 背景の描画
	SetSpriteTexture(m_pTexture);

	// スプライトの設定
	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	// スプライトの描画
	DrawSprite(m_pVertexBuffer, sizeof(Vertex));
}
