/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
* file：Fade.cpp
*
* 概要：フェード処理を管理するファイル
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

#include "Fade.h"
#include "DirectXTex/TextureLoad.h"
#include "VertexBuffer.h"
#include "Defines.h"

/// <summary>
/// コンストラクタ
/// </summary>
CFade::CFade(float In_MaxFadeTime)
	: m_fAlpha(0.0f)
	, m_fTime(In_MaxFadeTime)
	, m_bFadeOut(true)
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
	hr = LoadTextureFromFile(GetDevice(), TEXTURE_PATH("Fade_BackGround.png"), &m_pTex);
	if (FAILED(hr)) {
		//---デバックモードのみ処理
#ifdef _DEBUG
		MessageBox(NULL, "フェード背景画像", "Error", MB_OK);
#endif
	}
}

/// <summary>
/// デストラクタ
/// </summary>
CFade::~CFade()
{
	SAFE_RELEASE(m_pVtx);
	SAFE_RELEASE(m_pTex);
}

/// <summary>
/// 更新処理
/// </summary>
void CFade::Update()
{
	// フェードアウトフラグが立っている場合はフェードアウト、そうでなければフェードイン
	if (m_bFadeOut)
	{
		// アルファ値が1.0f未満の場合はフェードアウト
		if (m_fAlpha < 1.0f)
		{
			// アルファ値を徐々に増やす
			m_fAlpha += 1.0f / (fFPS * (m_fTime / 2.0f));
			// アルファ値が1.0fを超えたら1.0fに制限し、フェードアウトフラグを解除
			if (m_fAlpha >= 1.0f)
			{
				m_fAlpha = 1.0f;
				m_bFadeOut = false;
				// フェードアウトが完了したらチェンジフラグを立てる
				// これにより、次のシーンへの切り替えが可能になる
				m_bChange = true; 
			}
		}
	}
	// フェードアウトフラグが立っていない場合はフェードイン
	else
	{
		// アルファ値が0.0fより大きい場合はフェードイン
		if (m_fAlpha > 0.0f)
		{
			// アルファ値を徐々に減らす
			m_fAlpha -= 1.0f / (fFPS * (m_fTime / 2.0f));
			// アルファ値が0.0fを下回ったら0.0fに制限し、フェード完了フラグを立てる
			if (m_fAlpha <= 0.0f)
			{
				m_fAlpha = 0.0f;
				m_bEnd = true;
			}
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void CFade::Draw()
{
	//背景の描画
	SetSpriteTexture(m_pTex);

	// スプライトの設定
	SetSpritePos(0.0f, 0.0f);
	SetSpriteScale(1.0f, 1.0f);
	SetSpriteColor(1.0f, 1.0f, 1.0f, m_fAlpha);
	SetSpriteUVPos(0.0f, 0.0f);
	SetSpriteUVScale(1.0f, 1.0f);

	// スプライトの描画
	DrawSprite(m_pVtx, sizeof(Vertex));
}
