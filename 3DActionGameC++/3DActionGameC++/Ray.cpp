/*=====================================================================
* @file Ray.cpp
* @brief レイのCppファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Ray.h"
/* システム・要素のインクルード */
#include <math.h>
#include <utility>

// @brief コンストラクタ
CRay::CRay()
	: m_tOrigin(0.0f, 0.0f, 0.0f) // レイの始点の初期化
	, m_tDirection(0.0f, 0.0f, 0.0f) // レイの方向の初期化
{

}

// @brief デストラクタ
CRay::~CRay()
{

}

// @brief レイキャストの実行
// @param In_TargetInfos ターゲットコリジョン
// @return レイが当たっているかどうか
bool CRay::Cast(std::vector<Collision::Info> In_TargetInfos)
{
	/// @Todo レイとBoxの当たり判定を実装する
	/// 現在はy軸を無視してX軸とZ軸の範囲内にあるかどうかで判定


	// ターゲット情報をループ
	for (const auto& TargetInfo : In_TargetInfos) 
	{
		Collision::Box TargetBox = TargetInfo.box; // ターゲットのBox情報を取得

		// レイの始点がターゲットのBoxのX軸とZ軸の範囲内にあるかチェック
		if (m_tOrigin.x >= TargetBox.center.x - TargetBox.size.x / 2.0f &&
			m_tOrigin.x <= TargetBox.center.x + TargetBox.size.x / 2.0f &&
			m_tOrigin.z >= TargetBox.center.z - TargetBox.size.z / 2.0f &&
			m_tOrigin.z <= TargetBox.center.z + TargetBox.size.z / 2.0f)
		{
			return true; // レイがターゲットに当たった
		}
	}
	return false;
}

// @brief パラメーターの設定
// @param origin レイの始点
// @param direction レイの方向
void CRay::SetParam(const XMFLOAT3& origin, const XMFLOAT3& direction)
{
	m_tOrigin = origin; // レイの始点を設定
	m_tDirection = direction; // レイの方向を設定
}
