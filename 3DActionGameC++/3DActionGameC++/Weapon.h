/*=====================================================================
* @file Weapon.h
* @brief 武器の基底クラスヘッダーファイル
=====================================================================*/
#pragma once

/* システム・要素のインクルード */
#include "Collision.h"
#include "Enums.h"
#include "StructMath.h"
#include <list>

// 攻撃の当たり判定情報
struct AttackCollision
{
	// 当たり判定情報
	Collision::Info CollisionInfo;
	// 持続フレーム
	float DurationFrame;
	// 攻撃力
	float AttackPower;
	// 当たったエンティティのIDリスト
	std::list<int> HitEntityIDList;

	bool operator==(const AttackCollision& other) const
	{
		return &CollisionInfo == &other.CollisionInfo && &DurationFrame == &other.DurationFrame;
	}
};

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

	// @brief 更新
	virtual void Update(XMFLOAT3 In_Position) = 0;

	// @brief コンボタイマーの更新
	void ComboTimerUpdate(void);

	// @攻撃の生成
	// @param Dir 向き
	AttackCollision CreateAttack(float Dir);

protected:

	// @brief パラメータの設定
	virtual void SetParam(void) = 0;

protected:

	// @brief 攻撃タイプ
	AttackType m_eAttackType;

	// @brief 攻撃範囲
	std::vector<Collision::Info> m_tAttackRange;

	// @brief 攻撃力
	std::vector<float> m_fAttackPower;

	// @brief 攻撃速度(攻撃間隔)
	float m_fAttackSpeed;

	// @brief 攻撃の持続時間
	float m_fAttackDurationTime;

	// @brief コンボ数
	int m_nComboCount;

	// @brief コンボタイマー
	float m_fComboTimer;

	// @brief コンボ猶予時間
	float m_fComboGraceTimer;

public:// アクセサ

	// @brief 攻撃タイプの取得
	AttackType GetAttackType(void) const { return m_eAttackType; }
	// @brief 攻撃力の取得
	float GetAttackPower(void) const { return m_fAttackPower[m_nComboCount]; }
	// @brief 攻撃速度の取得
	float GetAttackSpeed(void) const { return m_fAttackSpeed; }
	// @brief 攻撃範囲の取得
	Collision::Info GetAttackRange(void) { return m_tAttackRange[m_nComboCount]; }
	std::vector<Collision::Info>& GetAttackRanges(void) { return m_tAttackRange; }
	// @brief 方向を加味した攻撃範囲の取得
	Collision::Info GetAttackRangeDir(float Dir);
	// @brief 攻撃の持続時間の取得
	float GetAttackDurationFrame(void) const { return m_fAttackDurationTime; }

};
