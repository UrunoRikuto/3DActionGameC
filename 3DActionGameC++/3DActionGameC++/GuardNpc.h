/*=====================================================================
* @file GuardNpc.h
* @brief 護衛NPCのクラスのヘッダーファイル
=====================================================================*/

#pragma once

/* 基底クラスのインクルード */
#include "NpcBase.h"
/* システム・要素のインクルード */
#include "Enums.h"

/// <summary>
/// 護衛NPCのクラス
/// </summary>
class CGuardNpc : public CNpcBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="FirstMovePoint">最初の移動ポイント</param>
	/// <param name="NpcType">NPCの種類</param>
	CGuardNpc(XMFLOAT3 FirstMovePoint, NpcType NpcType);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CGuardNpc();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void) override;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move(void) override;
	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack(void) override;

};

