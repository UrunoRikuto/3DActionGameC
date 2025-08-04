/*
* @file Field.cpp
* @brief フィールドオブジェクトのクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/


/* ヘッダーで利用するシステム・要素のインクルード */

/* ヘッダーのインクルード */
#include "Field.h"
/* システム・要素のインクルード */
#include "Model.h"
#include "Defines.h"
#include "Main.h"
#include "ModelDrawSetting.h"

// @brief コンストラクタ
CField::CField()
	: CGameObject() // 基底クラスのコンストラクタを呼び出す
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("BattleStage_Field.obj")))
	{
		MessageBox(NULL, "フィールドモデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 位置、スケール、回転の設定
	m_tScale = { 10.0f, 1.0f, 10.0f };   
	m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };
}

// @brief デストラクタ
CField::~CField()
{

}

// @brief 更新処理
void CField::Update(void)
{

}

// @brief 描画処理
void CField::Draw(void)
{
	// モデルの描画
	SetRender3D();
	CreateObject(
		m_tPosition,	// 位置
		m_tScale,		// スケール
		m_tRotation,	// 回転
		m_pModel.get(),       // モデルポインタ
		Camera::GetInstance(),// カメラポインタ
		true,                 // 明るくするかどうか
		XMFLOAT3(1.0f,1.0f,1.0f) // ライティング色
	);

}
