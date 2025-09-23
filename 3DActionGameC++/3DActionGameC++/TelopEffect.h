/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
*
* file：TelopEffect.h
*
* 概要：テロップエフェクトの基底クラスを管理するファイル
*
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/

#pragma once
#include "DirectX.h"

/// <summary>
/// テロップエフェクトの基底クラス
/// </summary>
class CTelopEffect
{
public:
	// コンストラクタ
	CTelopEffect() = default;
	// デストラクタ
	virtual ~CTelopEffect() = default;
	// 更新処理
	virtual bool Update() = 0;
	// 描画処理
	virtual void Draw() = 0;
protected:
	// 頂点バッファ
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	// テクスチャ
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	// テロップの表示時間
	float m_fDisplayTime = 0.0f; // 秒単位
	// テロップの経過時間
	float m_fElapsedTime = 0.0f; // 秒単位
};

