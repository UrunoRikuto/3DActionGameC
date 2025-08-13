/*
* @file NpcBase.h
* @brief NPCの基底クラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 NPCの基底クラスの定義
*/

#pragma once

/* 基底クラスのインクルード */
#include "GameObject.h"

/* システム・要素のインクルード */
#include "MoveSystem.h"

/// <summary>
/// NPCの基底クラス
/// </summary>
class CNpcBase : public CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CNpcBase();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CNpcBase();
	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(void);

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw(void);

	/// <summary>
	/// 当たり判定の衝突時の処理
	/// </summary>
	/// <param name="InCollisionInfo">衝突対象</param>
	void Hit(const Collision::Info& InCollisionInfo) override;

protected:
	/// <summary>
	/// 移動システム
	/// </summary>
	std::unique_ptr<CMoveSystem> m_pMoveSystem;

public:
	/// <summary>
	/// 移動システムの取得
	/// </summary>
	/// <returns>移動システムのポインタ</returns>
	CMoveSystem* GetMoveSystem(void) { return m_pMoveSystem.get(); }
};
