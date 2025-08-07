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
	CTargetNpc();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CTargetNpc();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void) override;
};

