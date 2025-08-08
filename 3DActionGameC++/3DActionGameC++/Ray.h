/*
* @file Ray.h
* @brief レイのクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 レイキャストのクラスの定義
*/
#pragma once

/* システム・要素のインクルード */
#include "StructMath.h"
#include "RayCastTarget.h"


/// <summary>
/// レイ(光線)クラス
/// </summary>
class CRay
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CRay();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CRay();

	/// <summary>
	/// レイキャストの実行
	/// </summary>
	/// <param name="InTarget">ターゲットオブジェクト</param>
	/// <returns>レイが当たっているかどうか</returns>
	bool Cast(CRayCastTarget* InTarget);

	/// <summary>
	/// パラメーターの設定
	/// </summary>
	/// <param name="origin">レイの始点</param>
	/// <param name="direction">レイの方向</param>
	void SetParam(const XMFLOAT3& origin, const XMFLOAT3& direction);

	/// <summary>
	/// レイの始点の設定
	/// </summary>
	/// <param name="origin"></param>
	void SetOrigin(const XMFLOAT3& origin) { m_tOrigin = origin; }
private:
	/// <summary>
	/// レイの始点
	/// </summary>
	XMFLOAT3 m_tOrigin;
	/// <summary>
	/// レイの方向
	/// </summary>
	XMFLOAT3 m_tDirection;
};
