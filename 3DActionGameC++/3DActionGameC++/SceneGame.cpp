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
/* ヘッダーのインクルード */
#include "SceneGame.h"
#include "Camera.h"

// @brief コンストラクタ
CSceneGame::CSceneGame()
	:CSceneBase()
{
	m_pField = std::make_unique<CField>();
}

// @brief デストラクタ
CSceneGame::~CSceneGame()
{

}

// @brief 更新処理
void CSceneGame::Update(void)
{
	Camera::GetInstance()->Update();
	m_pField->Update();
}

// @brief 描画処理
void CSceneGame::Draw(void)
{
	m_pField->Draw();
}