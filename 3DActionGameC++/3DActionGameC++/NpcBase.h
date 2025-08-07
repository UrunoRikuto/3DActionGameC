/*
* @file NpcBase.h
* @brief NPCの基底クラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 NPCの基底クラスの定義
*/

#pragma once

/* 基底クラスのインクルード */
#include "GameObject.h"

/// <summary>
/// NPCの基底クラス
/// </summary>
class CNpcBase : public CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CNpcBase() = default;
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CNpcBase() = default;
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(void) = 0;
};
