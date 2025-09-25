/*=====================================================================
* @file TargetNpc.h
* @brief ターゲットNPCのクラスのヘッダーファイル
=====================================================================*/

#pragma once

/* 基底クラスのインクルード */
#include "NpcBase.h"

/// <summary>
/// ターゲットNPCのクラス
/// </summary>
class CTargetNpc : public CNpcBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="FirstMovePoint">最初の移動ポイント</param>
	/// <param name="NpcType">NPCの種類</param>
	CTargetNpc(XMFLOAT3 FirstMovePoint, NpcType NpcType);
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CTargetNpc();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// 当たり判定の衝突時の処理(攻撃用)
	/// </summary>
	/// <param name="InCollisionInfo">衝突対象</param>
	/// <param name="In_Attack">相手の攻撃力</param>
	void Hit(const Collision::Info& InCollisionInfo, float In_Attack) override;

private:

	/// <summary>
	/// 発見時の更新処理
	/// </summary>
	void DiscoveryUpdate(void) override;

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move(void) override;
	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack(void) override;
};

