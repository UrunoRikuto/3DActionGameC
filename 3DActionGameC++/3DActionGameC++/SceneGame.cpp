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
#include "TargetNpc.h"
/* ヘッダーのインクルード */
#include "SceneGame.h"
/* システム・要素のインクルード */
#include "Camera.h"
#include "Defines.h"

/* グローバル変数 */
std::vector<CGameObject*> g_vNullCheckList; // Nullチェック用のゲームオブジェクトのリスト

// @brief コンストラクタ
CSceneGame::CSceneGame()
	:CSceneBase()
{
	// フィールドの生成
	m_pField = std::make_unique<CField>();
	// プレイヤーの生成
	m_pPlayer = std::make_unique<CPlayer>();
	// NPCの生成（ターゲットNPC）
	m_pNpc = std::make_unique<CTargetNpc>();

	g_vNullCheckList.push_back(m_pField.get()); // フィールドのNullチェック用リストに追加
	g_vNullCheckList.push_back(m_pPlayer.get()); // プレイヤーのNullチェック用リストに追加
	g_vNullCheckList.push_back(m_pNpc.get()); // NPCのNullチェック用リストに追加
}

// @brief デストラクタ
CSceneGame::~CSceneGame()
{

}

// @brief 更新処理
void CSceneGame::Update(void)
{
	for(auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Update(); // Nullチェックを行い、オブジェクトが有効な場合のみ更新処理を呼び出す
		}
	}

	//// フィールドの更新処理
	//if (m_pField)m_pField->Update();
	//// プレイヤーの更新処理
	//if (m_pPlayer)m_pPlayer->Update();
	//// NPCの更新処理
	//if (m_pNpc)m_pNpc->Update();

	//(仮)プレイヤーの真下の地面の高さを設定
	m_pPlayer->SetUnderHeight(m_pField->GetPosition().y + m_pField->GetScale().y / 2.0f);
}

// @brief 描画処理
void CSceneGame::Draw(void)
{
	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Draw(); // Nullチェックを行い、オブジェクトが有効な場合のみ描画処理を呼び出す
		}
	}

	//// フィールドの描画処理
	//m_pField->Draw();
	//// プレイヤーの描画処理
	//m_pPlayer->Draw();
	//// NPCの描画処理
	//m_pNpc->Draw();
}