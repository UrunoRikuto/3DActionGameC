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
	// 攻撃範囲の中心座標をキャラクターの位置に設定
	m_tAttackRange.box.center = In_Position;
}

// @brief パラメータの設定
void CSword::SetParam(void)
{
	// 攻撃タイプ
	m_eAttackType = AttackType::Slash;
	// 攻撃力
	m_fAttackPower = 20.0f;
	// 攻撃速度(攻撃間隔)
	m_fAttackSpeed = 1.0f;
	// 攻撃範囲
	m_tAttackRange.type = Collision::eBox;
	// ボックスの中心座標とサイズを設定
	m_tAttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	m_tAttackRange.box.size = { 5.0f, 5.0f, 5.0f };
	// 攻撃の持続時間
	m_fAttackDurationTime = 0.5f;
}
