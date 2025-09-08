/*=====================================================================
* @file NpcBase.h
* @brief NPCの基底クラスのヘッダーファイル
=====================================================================*/

#pragma once

/* 基底クラスのインクルード */
#include "GameObject.h"

/* システム・要素のインクルード */
#include "MoveSystem.h"
#include "VisionSearch.h"
#include "Player.h"
#include "WeaponInclude.h"


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
	/// 移動処理
	/// </summary>
	virtual void Move(void) = 0;

	/// <summary>
	/// 攻撃処理
	/// </summary>
	virtual void Attack(void) = 0;

protected:

	/// <summary>
	/// 所持している武器
	/// </summary>
	CWeapon* m_pWeapon;

	/// <summary>
	/// 攻撃のクールタイム
	/// </summary>
	float m_fAttackCD;

	/// <summary>
	/// 攻撃中かどうか
	/// </summary>
	bool m_bAttack;

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

	/// <summary>
	/// 標的対象のゲームオブジェクト
	/// </summary>
	CPlayer* m_pTargetObject;

public:

	/// <summary>
	/// 所持している武器の取得
	/// </summary>
	/// <returns>所持している武器</returns>
	CWeapon* GetWeapon(void) const { return m_pWeapon; }

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
	/// 現在の索敵状態の設定
	/// </summary>
	/// <param name="InState"></param>
	void SetSearchState(VisionSearchState InState);

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

	/// <summary>
	/// ターゲットの設定
	/// </summary>
	/// <param name="In_TargetObject">索敵対象のオブジェクト</param>
	void SetTarget(CPlayer* In_TargetObject) { m_pTargetObject = In_TargetObject; }

	/// <summary>
	/// ターゲットの取得
	/// </summary>
	/// <returns>ターゲットのポインタ</returns>
	CPlayer* GetTarget(void) { return m_pTargetObject; }
};
