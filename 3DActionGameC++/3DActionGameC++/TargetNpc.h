/*
* @file TargetNpc.h
* @brief ターゲットNPCのクラスのヘッダーファイル
* @author 宇留野陸斗
* * @date 2025/08/04 ターゲットNPCのクラスの定義
*/

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
};

