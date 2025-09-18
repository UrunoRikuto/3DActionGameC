/*=====================================================================
* @file Sword.cpp
* @brief 剣クラス実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "Sword.h"

// @brief コンストラクタ
CSword::CSword()
{
	// パラメータの設定
	SetParam();
}

// @brief デストラクタ
CSword::~CSword()
{

}

// @brief 更新
// @param In_Position キャラクターの位置
void CSword::Update(XMFLOAT3 In_Position)
{
	for (auto& attackRange : m_tAttackRange)
	{
		// 攻撃範囲の中心座標をキャラクターの位置に設定
		attackRange.box.center = In_Position;
	}
}

// @brief パラメータの設定
void CSword::SetParam(void)
{
	// 攻撃タイプ
	m_eAttackType = AttackType::Slash;
	// 攻撃力
	m_fAttackPower.push_back(20.0f);
	m_fAttackPower.push_back(15.0f);

	// 攻撃速度(攻撃間隔)
	m_fAttackSpeed = 1.0f;
	// 攻撃範囲
	Collision::Info AttackRange = {};

	AttackRange.type = Collision::eBox;
	// ボックスの中心座標とサイズを設定
	AttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	AttackRange.box.size = { 1.0f, 10.0f, 10.0f };
	// タグを追加
	AttackRange.tag.push_back(Collision::Tag::Attack);

	m_tAttackRange.push_back(AttackRange);

	AttackRange = {};

	AttackRange.type = Collision::eBox;
	// ボックスの中心座標とサイズを設定
	AttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	AttackRange.box.size = { 10.0f, 1.0f, 10.0f };
	// タグを追加
	AttackRange.tag.push_back(Collision::Tag::Attack);

	m_tAttackRange.push_back(AttackRange);


	// 攻撃の持続時間
	m_fAttackDurationTime = 0.5f;

	// コンボ猶予時間
	m_fComboGraceTimer = 0.5f;
}
