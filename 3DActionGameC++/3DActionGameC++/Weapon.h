/*=====================================================================
* @file Weapon.h
* @brief 武器の基底クラスヘッダーファイル
=====================================================================*/
#pragma once

/* システム・要素のインクルード */
#include "Collision.h"
#include "Enums.h"
#include "StructMath.h"

/// <summary>
/// 武器の基底クラス
/// </summary>
class CWeapon
{
public:
	// @brief コンストラクタ
	CWeapon();

	// @brief デストラクタ
	virtual ~CWeapon();

	// @brief パラメータの設定
	virtual void SetParam(void) = 0;

protected:
	// @brief 攻撃タイプ
	AttackType m_eAttackType;

	// @brief 攻撃力
	float m_fAttackPower;

	// @brief 攻撃速度(攻撃間隔)
	float m_fAttackSpeed;

	// @brief 攻撃範囲
	Collision::Info m_tAttackRange;

public:// アクセサ

	// @brief 攻撃力の取得
	float GetAttackPower(void) const { return m_fAttackPower; }
	// @brief 攻撃速度の取得
	float GetAttackSpeed(void) const { return m_fAttackSpeed; }
	// @brief 攻撃範囲の取得
	const Collision::Info& GetAttackRange(void) const { return m_tAttackRange; }
};
