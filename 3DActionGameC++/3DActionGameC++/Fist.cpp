/*=====================================================================
* @file Fist.cpp
* @brief 拳クラス実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Fist.h"

// @brief コンストラクタ
CFist::CFist()
{
	// パラメータの設定
	SetParam();
}

// @brief デストラクタ
CFist::~CFist()
{
}

// @brief 更新
void CFist::Update(XMFLOAT3 In_Position)
{
	// 攻撃範囲の中心座標をキャラクターの位置に設定
	for (auto& attackRange : m_tAttackRange)
	{
		attackRange.box.center = In_Position;
	}
}

// @brief パラメータの設定
void CFist::SetParam(void)
{
	// 攻撃タイプ
	m_eAttackType = AttackType::Blow;
	// 攻撃力
	m_fAttackPower.push_back(10.0f);
	// 攻撃速度(攻撃間隔)
	m_fAttackSpeed = 0.5f;
	// 攻撃範囲
	Collision::Info AttackRange = {};

	AttackRange.type = Collision::eBox;
	// ボックスの中心座標とサイズを設定
	AttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	AttackRange.box.size = { 3.0f, 3.0f, 3.0f };
	// タグを追加
	AttackRange.tag.push_back(Collision::Tag::Attack);
	// 攻撃範囲を追加
	m_tAttackRange.push_back(AttackRange);
	// 攻撃の持続時間
	m_fAttackDurationTime = 0.1f;
	// コンボ猶予時間
	m_fComboGraceTimer = 0.3f;
}
