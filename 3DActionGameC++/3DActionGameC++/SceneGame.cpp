/*
* @file SceneGame.cpp
* @brief ゲームシーンのクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/

/* ヘッダーで利用するシステムのインクルード */
#include <memory>
/* ゲームオブジェクトのインクルード */
#include "Field.h"
#include "Player.h"
/* ヘッダーのインクルード */
#include "SceneGame.h"
#include "Camera.h"

// @brief コンストラクタ
CSceneGame::CSceneGame()
	:CSceneBase()
{
	// フィールドの生成
	m_pField = std::make_unique<CField>();
	// プレイヤーの生成
	m_pPlayer = std::make_unique<CPlayer>();
}

// @brief デストラクタ
CSceneGame::~CSceneGame()
{

}

// @brief 更新処理
void CSceneGame::Update(void)
{
	// フィールドの更新処理
	if (m_pField)m_pField->Update();
	// プレイヤーの更新処理
	if (m_pPlayer)m_pPlayer->Update();
}

// @brief 描画処理
void CSceneGame::Draw(void)
{
	// フィールドの描画処理
	m_pField->Draw();
	// プレイヤーの描画処理
	m_pPlayer->Draw();
}