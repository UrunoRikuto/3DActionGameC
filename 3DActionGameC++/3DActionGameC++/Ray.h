/*=====================================================================
* @file Ray.h
* @brief レイのヘッダーファイル
=====================================================================*/
#pragma once

/* システム・要素のインクルード */
#include "StructMath.h"
#include "Collision.h"


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
	/// <param name="In_TargetInfos">ターゲットコリジョン</param>
	/// <returns>レイが当たっているかどうか</returns>
	bool Cast(std::vector<Collision::Info> In_TargetInfos);

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

public:
	/// <summary>
	/// レイの始点の取得
	/// </summary>
	/// <returns>レイの始点</returns>
	const XMFLOAT3& GetOrigin() const { return m_tOrigin; }
	/// <summary>
	/// レイの方向の取得
	/// </summary>
	/// <returns>レイの方向</returns>
	const XMFLOAT3& GetDirection() const { return m_tDirection; }
	/// <summary>
	/// レイの方向の設定
	/// </summary>
	/// <param name="direction">新しく設定する方向</param>
	void SetDirection(const XMFLOAT3& direction) { m_tDirection = direction; }
};
