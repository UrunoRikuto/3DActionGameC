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
#include "VisionSearch.h"

/// <summary>
/// NPCの基底クラス
/// </summary>
class CNpcBase : public CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CNpcBase(NpcType InType);
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
	/// NCPの種類
	/// </summary>
	NpcType m_eNpcType;

	/// <summary>
	/// 現在の索敵状態
	/// </summary>
	VisionSearchState m_eSearchState;

	/// <summary>
	/// 視覚索敵システム
	/// </summary>
	std::unique_ptr<CVisionSearch> m_pVisionSearch;

	/// <summary>
	/// 移動システム
	/// </summary>
	std::unique_ptr<CMoveSystem> m_pMoveSystem;

public:
	/// <summary>
	/// NPCの種類の取得
	/// </summary>
	/// <returns> NCPの種類</returns>
	NpcType GetNpcType(void) const { return m_eNpcType; }

	/// <summary>
	/// 現在の索敵状態の取得
	/// </summary>
	/// <returns>現在の索敵状態</returns>
	VisionSearchState GetSearchState(void) const { return m_eSearchState; }

	/// <summary>
	/// 視覚索敵システムの取得
	/// </summary>
	/// <returns>視覚索敵システムのポインタ</returns>
	CVisionSearch* GetVisionSearch(void) { return m_pVisionSearch.get(); }

	/// <summary>
	/// 移動システムの取得
	/// </summary>
	/// <returns>移動システムのポインタ</returns>
	CMoveSystem* GetMoveSystem(void) { return m_pMoveSystem.get(); }
};
