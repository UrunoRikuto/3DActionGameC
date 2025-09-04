/*=====================================================================
* @file Weapon.h
* @brief 武器のヘッダーファイル
=====================================================================*/
#pragma once
#include <string>
#include "Enums.h"

/// <summary>
/// 武器のクラス
/// </summary>
class CWeapon
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CWeapon();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CWeapon();

	/// <summary>
	/// 武器のデータの読み込み
	/// </summary>
	/// <param name="In_DataPath">データのファイルパス</param>
	void LoadWeaponData(const std::string In_DataPath);
private:

	/// <summary>
	/// 攻撃の種類
	/// </summary>
	AttackType m_eAttackType;

	/// <summary>
	/// 武器の強化レベル
	/// </summary>
	int m_nUpgradeLevel;

	/// <summary>
	/// 攻撃力リスト
	/// </summary>
	float m_fAttackPower[5];

	/// <summary>
	/// 重量
	/// </summary>
	float m_fWeight;

public: //メンバ変数のアクセサ

	/// <summary>
	/// 攻撃の種類の取得
	/// </summary>
	/// <returns> 攻撃の種類</returns>
	AttackType GetAttackType(void)const { return m_eAttackType; }
	/// <summary>
	/// 強化レベルの取得
	/// </summary>
	/// <returns>強化レベル</returns>
	int GetUpgradeLevel(void)const { return m_nUpgradeLevel; }
	/// <summary>
	/// 攻撃力の取得
	/// </summary>
	/// <returns>攻撃力</returns>
	float GetAttackPower(void)const { return m_fAttackPower[m_nUpgradeLevel - 1]; }
	/// <summary>
	/// 重量の取得
	/// </summary>
	/// <returns>重量</returns>
	float GetWeight(void)const { return m_fWeight; }
};

