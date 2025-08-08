/*
* @file RayCastTarget.cpp
* @brief レイキャストのターゲットクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 レイキャストのターゲットクラスの実装
*/

/* ヘッダーのインクルード */
#include "RayCastTarget.h"

// @brief コンストラクタ
CRayCastTarget::CRayCastTarget()
	: m_tPosition(0.0f, 0.0f, 0.0f) // ターゲットの位置の初期化
	, m_tScale(1.0f, 1.0f, 1.0f) // ターゲットのスケールの初期化
{

}

// @brief デストラクタ
CRayCastTarget::~CRayCastTarget()
{

}

// @brief パラメーターの設定
// @param position ターゲットの位置
// @param scale ターゲットのスケール
void CRayCastTarget::SetParam(const XMFLOAT3& position, const XMFLOAT3& scale)
{
	// ターゲットの位置を設定
	m_tPosition = position; 
	// ターゲットのスケールを設定
	m_tScale = scale;
}
