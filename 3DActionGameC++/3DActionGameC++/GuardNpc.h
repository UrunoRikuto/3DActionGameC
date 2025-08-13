/*
* @file GuardNpc.h
* @brief 護衛NPCのクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/14 護衛NPCのクラスの定義
*/

#pragma once

/* 基底クラスのインクルード */
#include "NpcBase.h"

/// <summary>
/// 護衛NPCのクラス
/// </summary>
class CGuardNpc : public CNpcBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CGuardNpc(XMFLOAT3 In_SpawnPoint);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CGuardNpc();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void) override;


};

