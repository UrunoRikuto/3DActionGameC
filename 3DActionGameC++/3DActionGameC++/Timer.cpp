/*=====================================================================
* @file Timer.h
* @brief タイマーのcppファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Timer.h"

/* システム・要素のインクルード */
#include "Defines.h"
#include "VertexBuffer.h"
#include "DirectXTex/TextureLoad.h"
#include "Main.h"
#include "GameValues.h"

// シングルトンのインスタンスの初期化
CTimer* CTimer::m_pInstance = nullptr;


// @brief コンストラクタ
CTimer::CTimer()
	:m_fElapsedTime(0.0f)
{
	HRESULT hr = E_FAIL;

	/// 背景データの作成

	// Vertexの生成
	Vertex vtx[4] = {
	{ {-GameValue::Timer::GAUGE_SIZE_X,-SCREEN_HEIGHT,0.0f},{0.0f,0.0f}},
	{ { GameValue::Timer::GAUGE_SIZE_X,-SCREEN_HEIGHT,0.0f},{1.0f,0.0f}},
	{ {-GameValue::Timer::GAUGE_SIZE_X, SCREEN_HEIGHT,0.0f},{0.0f,1.0f}},
	{ { GameValue::Timer::GAUGE_SIZE_X, SCREEN_HEIGHT,0.0f},{1.0f,1.0f}},
	};
	// 生成したVertexをBufferのポインタ変数に設定
	m_pGaugeBackVtx = CreateVertexBuffer(vtx, 4);
	// 背景テクスチャの設定
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("UI/TimerBack.png"), &m_pGaugeBackTex);


	/// 前景データの作成

	// 生成したVertexをBufferのポインタ変数に設定
	m_pGaugeFrontVtx = CreateVertexBuffer(vtx, 4);

	// 前景テクスチャの設定
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("UI/TimerFront.png"), &m_pGaugeFrontTex);

}

// @brief デストラクタ
CTimer::~CTimer()
{
	// バッファーポインタの解放
	if (m_pGaugeBackVtx) m_pGaugeBackVtx->Release();
	if (m_pGaugeFrontVtx) m_pGaugeFrontVtx->Release();
	// テクスチャポインタの解放
	if (m_pGaugeBackTex) m_pGaugeBackTex->Release();
	if (m_pGaugeFrontTex) m_pGaugeFrontTex->Release();
}

// @brief タイマーの更新
bool CTimer::Update()
{
	m_fElapsedTime += 1.0f / fFPS;

	if (m_fElapsedTime >= m_fLimitTime)
	{
		m_fElapsedTime = m_fLimitTime;
		return true;
	}

	return false;
}

// @brief タイマー描画
void CTimer::Draw()
{
	//前景の描画
	SetSpriteTexture(m_pGaugeFrontTex);

	SetSpritePos(-SCREEN_WIDTH + GameValue::Timer::GAUGE_SIZE_X, (SCREEN_HEIGHT / 2 * (1.0f - ((m_fLimitTime - m_fElapsedTime) / m_fLimitTime))) * 1.95f);
	SetSpriteScale(0.9f, ((m_fLimitTime - m_fElapsedTime) / m_fLimitTime));
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);
	DrawSprite(m_pGaugeFrontVtx, sizeof(Vertex));
	//背景の描画
	SetSpriteTexture(m_pGaugeBackTex);

	SetSpritePos(-SCREEN_WIDTH + GameValue::Timer::GAUGE_SIZE_X, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	DrawSprite(m_pGaugeBackVtx, sizeof(Vertex));

}

// @brief タイマーのリセット
void CTimer::Reset()
{
	m_fElapsedTime = 0.0f;
}
