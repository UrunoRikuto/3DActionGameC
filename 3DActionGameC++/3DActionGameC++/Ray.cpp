/*
* @file Ray.cpp
* @brief レイのクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 レイキャストのクラスの実装
*/

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
// @param InTarget ターゲットオブジェクト(Box)
bool CRay::Cast(CRayCastTarget* InTarget)
{
	//// レイの始点と方向を取得
	//XMFLOAT3 origin = m_tOrigin;         // レイの始点
	//XMFLOAT3 direction = StructMath::Normalize(m_tDirection); // レイの方向（正規化）

	//// ターゲットの位置とスケールを取得
	//XMFLOAT3 targetPosition = InTarget->GetPosition(); // ターゲットの位置
	//XMFLOAT3 targetScale = InTarget->GetScale();       // ターゲットのスケール

	//// AABBの最小/最大点を計算
	//XMFLOAT3 boxMin = StructMath::Sub(targetPosition, StructMath::Div(targetScale, 2.0f));
	//XMFLOAT3 boxMax = StructMath::Add(targetPosition, StructMath::Div(targetScale, 2.0f));

	//// 各軸でtMin, tMaxを計算（スラブ法）
	//float tMin = -FLT_MAX;
	//float tMax = FLT_MAX;

	//auto checkAxis = [&](float origin, float direction, float minB, float maxB) -> bool {
	//	if (fabsf(direction) < 1e-6f) {
	//		// 動かない軸なのに範囲外なら false（明示的に）
	//		if (origin < minB || origin > maxB)
	//			return false;
	//		// 範囲内ならスキップ対象
	//		return true;
	//	}
	//	float t1 = (minB - origin) / direction;
	//	float t2 = (maxB - origin) / direction;
	//	if (t1 > t2) std::swap(t1, t2);
	//	tMin = std::max(tMin, t1);
	//	tMax = std::min(tMax, t2);
	//	return tMin <= tMax;
	//	};

	//bool hitX = checkAxis(origin.x, direction.x, boxMin.x, boxMax.x);
	//bool hitY = checkAxis(origin.y, direction.y, boxMin.y, boxMax.y);
	//bool hitZ = checkAxis(origin.z, direction.z, boxMin.z, boxMax.z);

	//// 全ての軸で交差していれば当たり
	//if (hitX && hitY && hitZ) {
	//	return true;
	//}

	// レイの始点がターゲットのBoxのX軸とZ軸の範囲内にあるかチェック
	if (m_tOrigin.x >= InTarget->GetPosition().x - InTarget->GetScale().x / 2.0f &&
		m_tOrigin.x <= InTarget->GetPosition().x + InTarget->GetScale().x / 2.0f &&
		m_tOrigin.z >= InTarget->GetPosition().z - InTarget->GetScale().z / 2.0f &&
		m_tOrigin.z <= InTarget->GetPosition().z + InTarget->GetScale().z / 2.0f)
	{
		return true; // レイがターゲットに当たった
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
