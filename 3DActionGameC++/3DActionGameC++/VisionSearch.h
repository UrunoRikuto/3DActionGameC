/*
* @file VisionSearch.h
* @brief VisionSearchクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/19 クラスの定義
*/
#pragma once

/* システム・要素のインクルード */
#include "StructMath.h"
#include "Enums.h"
#include "Player.h"
#include "NpcBase.h"

/// <summary>
/// 視覚索敵クラス
/// </summary>
class CVisionSearch
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="In_Self">自身のオブジェクト</param>
	CVisionSearch(CNpcBase* In_Self);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CVisionSearch();

	/// <summary>
	/// パラメーターの初期設定
	/// </summary>
	/// <param name="In_ViewDistance">視認距離</param>
	/// <param name="In_TargetObject">索敵対象のオブジェクト</param>
	void InitParam(float In_ViewDistance, CPlayer* In_TargetObject);

	/// <summary>
	/// 索敵処理
	/// </summary>
	/// <param name="In_SelfPosition">自身の位置</param>
	/// <param name="In_CurrentSearchState">現在の索敵状態</param>
	/// <returns>更新後の索敵状態</returns>
	VisionSearchState Search(const XMFLOAT3& In_SelfPosition, VisionSearchState In_CurrentSearchState);

	/// <summary>
	/// 視覚索敵の描画処理
	/// </summary>
	void DebugDraw(void);

private:

	/// <summary>
	/// 見ている方向
	/// </summary>
	XMFLOAT3 m_tDirection;

	/// <summary>
	/// 視認距離
	/// </summary>
	float m_fViewDistance;

	/// <summary>
	/// 発見値
	/// </summary>
	float m_fDetectionValue;

	/// <summary>
	/// 見失い状態になるまでの経過時間
	/// </summary>
	float m_fLostTimer;

	/// <summary>
	/// 索敵を行うゲームオブジェクト
	/// </summary>
	CNpcBase* m_pSelfObject;

	/// <summary>
	/// 索敵対象のゲームオブジェクト
	/// </summary>
	CPlayer* m_pTargetObject;

public:// アクセサ
	/// <summary>
	/// 見ている方向の設定
	/// </summary>
	/// <param name="direction">見ている方向</param>
	void SetDirection(const XMFLOAT3& direction) { m_tDirection = direction; }
	/// <summary>
	/// 見ている方向の取得
	/// </summary>
	/// <returns>見ている方向</returns>
	const XMFLOAT3& GetDirection(void) const { return m_tDirection; }
	/// <summary>
	/// 発見値の取得
	/// </summary>
	/// <returns>発見値</returns>
	float GetDetectionValue(void) const { return m_fDetectionValue; }
};

