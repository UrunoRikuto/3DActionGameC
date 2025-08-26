/*
* @file MovePointManager.cpp
* @brief 移動ポイント管理クラスの実装ファイル
* @author 宇留野陸斗
* @date 2025/08/14 移動ポイント管理クラスの作成
*/

/* ヘッダーのインクルード */
#include "MovePointManager.h"
/* システム・要素のインクルード */
#include "Model.h"
#include "Defines.h"
#include "GameValues.h"
#include "ModelDrawSetting.h"
#include "Main.h"

// インスタンスの初期化
std::unique_ptr<CMovePointManager> CMovePointManager::m_pInstance = nullptr;

// @brief 移動ポイントの作成
void CMovePointManager::CreateData(FieldType In_Type)
{
	// フィールドの種類に応じて移動ポイントを設定
	switch (In_Type)
	{
	case FieldType::Plain:
		// 平原の移動ポイントを設定
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,200.0f));
		m_MovePoints.push_back(XMFLOAT3(200.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,200.0f));
		break;
	}

	m_pMovePointModels.resize(m_MovePoints.size());

	for (auto& model : m_pMovePointModels)
	{
		model = std::make_unique<Model>();
		model->Load(ModelPath::MOVE_POINT_PATH);
	}
}

// @brief インスタンスを取得する関数
// @details インスタンスが存在しない場合は新たに作成する
// @return インスタンスのポインタ
CMovePointManager* CMovePointManager::GetInstance(void)
{
	// インスタンスが存在しない場合は新たに作成
	if (!m_pInstance)
	{
		m_pInstance = std::make_unique<CMovePointManager>();
	}
	// インスタンスのポインタを返す
	return m_pInstance.get();
}

// @brief コンストラクタ
CMovePointManager::CMovePointManager()
{

}

// @brief デストラクタ
CMovePointManager::~CMovePointManager()
{

}

// @brief デバック描画処理
void CMovePointManager::DebugDraw(void)
{
#ifdef _DEBUG
	SetRender3D();
	for (int i = 0; i < m_pMovePointModels.size(); i++)
	{
		CreateObject(
			m_MovePoints[i],			// 位置
			StructMath::FtoF3(1.0f),// スケール
			StructMath::FtoF3(0.0f),// 回転
			m_pMovePointModels[i].get(),			// モデルポインタ
			Camera::GetInstance(),	// カメラポインタ
			true,					// 明るくするかどうか
			XMFLOAT3(0.5f, 0.5f, 0.5f) // ライティング色
		);
	}
#endif // _DEBUG
}
