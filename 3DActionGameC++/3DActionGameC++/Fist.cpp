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
	m_tAttackRange.box.center = In_Position;
}

// @brief パラメータの設定
void CFist::SetParam(void)
{
	// 攻撃タイプ
	m_eAttackType = AttackType::Blow;
	// 攻撃力
	m_fAttackPower = 10.0f;
	// 攻撃速度(攻撃間隔)
	m_fAttackSpeed = 0.5f;
	// 攻撃範囲
	m_tAttackRange.type = Collision::eBox;
	// ボックスの中心座標とサイズを設定
	m_tAttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	m_tAttackRange.box.size = { 3.0f, 3.0f, 3.0f };
	// タグを追加
	m_tAttackRange.tag.push_back(Collision::Tag::Attack);
	// 攻撃の持続時間
	m_fAttackDurationTime = 0.1f;
}
