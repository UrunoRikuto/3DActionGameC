/*=====================================================================
* @file Weapon.cpp
* @brief 武器の基底クラス実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Weapon.h"

/* システム・要素のインクルード */
#include "Defines.h"


// @brief コンストラクタ
CWeapon::CWeapon()
	: m_eAttackType(AttackType::Blow)
	, m_fAttackPower(0.0f)
	, m_fAttackSpeed(0.0f)
	, m_tAttackRange{}
	, m_fAttackDurationTime(0.0f)
	, m_nComboCount(0)
	, m_fComboTimer(0.0f)
	, m_fComboGraceTimer(1.0f)
{

}

// @brief デストラクタ
CWeapon::~CWeapon()
{

}

// @brief コンボタイマーの更新
void CWeapon::ComboTimerUpdate(void)
{
	// コンボタイマーを増加
	m_fComboTimer += 1.0f / fFPS;

	// コンボ猶予時間を過ぎていたらコンボ数をリセット
	if (m_fComboTimer > m_fComboGraceTimer)
	{
		m_nComboCount = 0;
	}
}

// @brief 攻撃の生成
// @param Dir 向き
AttackCollision CWeapon::CreateAttack(float Dir)
{
	AttackCollision AttackInfo;

	AttackInfo.DurationFrame = GetAttackDurationFrame();
	AttackInfo.AttackPower = GetAttackPower();
	AttackInfo.CollisionInfo = GetAttackRangeDir(Dir);

	// コンボ数を増加
	m_nComboCount++;

	// コンボ数が攻撃範囲の数を超えたらコンボ数をリセット
	if (m_nComboCount > static_cast<int>(m_tAttackRange.size() - 1))
	{
		m_nComboCount = 0;
	}

	// コンボ時間をリセット
	m_fComboTimer = 0.0f;

	return AttackInfo;
}

// @brief 攻撃範囲の取得
// @param Dir 向き
Collision::Info CWeapon::GetAttackRangeDir(float Dir)
{
	Collision::Info AttackRange;

	AttackRange.box.center = m_tAttackRange[m_nComboCount].box.center;
	AttackRange.tag = m_tAttackRange[m_nComboCount].tag;
	AttackRange.type = m_tAttackRange[m_nComboCount].type;

	// 向きを考慮して攻撃範囲のサイズを変更
	AttackRange.box.size.x = m_tAttackRange[m_nComboCount].box.size.x * fabsf(cosf(TORAD(Dir))) + m_tAttackRange[m_nComboCount].box.size.z * fabsf(sinf(TORAD(Dir)));
	AttackRange.box.size.z = m_tAttackRange[m_nComboCount].box.size.x * fabsf(sinf(TORAD(Dir))) + m_tAttackRange[m_nComboCount].box.size.z * fabsf(cosf(TORAD(Dir)));
	AttackRange.box.size.y = m_tAttackRange[m_nComboCount].box.size.y;

	return AttackRange;
}