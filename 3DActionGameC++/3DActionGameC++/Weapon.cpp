/*=====================================================================
* @file Weapon.cpp
* @brief 武器の基底クラス実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Weapon.h"

// @brief コンストラクタ
CWeapon::CWeapon()
	: m_eAttackType(AttackType::Blow)
	, m_fAttackPower(0.0f)
	, m_fAttackSpeed(0.0f)
	, m_tAttackRange()
	, m_fAttackDurationTime(0.0f)
{

}

// @brief デストラクタ
CWeapon::~CWeapon()
{

}
