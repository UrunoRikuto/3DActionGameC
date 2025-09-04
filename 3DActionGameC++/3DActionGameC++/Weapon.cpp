/*=====================================================================
* @file Weapon.cpp
* @brief 武器の実装ファイル
=====================================================================*/
#include "Weapon.h"

// @brief コンストラクタ
CWeapon::CWeapon()
	: m_eAttackType(AttackType::Slash) // 攻撃タイプの初期化
	, m_nUpgradeLevel(1) // 武器の強化レベルの初期化
	, m_fWeight(1.0f)	 // 武器の重量の初期化
	, m_fAttackPower{}	 // 武器の攻撃力リストの初期化
{
}

// @brief デストラクタ
CWeapon::~CWeapon()
{
}

// @brief 武器のデータの読み込み
// @param In_DataPath データのフォルダパス
void CWeapon::LoadWeaponData(const std::string In_DataPath)
{
	// 今は未実装
	// 将来的にファイルから武器データを読み込む処理を実装する予定
	// JSONでの読み込みを想定

	// 仮のデータを設定
	m_eAttackType = AttackType::Blow; // 攻撃の種類を斬撃に設定
	m_nUpgradeLevel = 1; // 強化レベル1
	m_fAttackPower[0] = 10.0f; // 強化レベル1の攻撃力
	m_fAttackPower[1] = 15.0f; // 強化レベル2の攻撃力
	m_fAttackPower[2] = 20.0f; // 強化レベル3の攻撃力
	m_fAttackPower[3] = 25.0f; // 強化レベル4の攻撃力
	m_fAttackPower[4] = 30.0f; // 強化レベル5の攻撃力
	m_fWeight = 5.0f; // 武器の重量
}
