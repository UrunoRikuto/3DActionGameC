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
#include "Geometory.h"

// @brief コンストラクタ
CField::CField()
	: CGameObject() // 基底クラスのコンストラクタを呼び出す
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("BattleStage_Field.obj"),0.1f))
	{
		MessageBox(NULL, "フィールドモデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 位置、スケール、回転の設定
	m_tScale = { 100.0f, 1.0f, 100.0f };   
	m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };
	// 当たり判定情報の初期化
	m_tCollisionInfo.type = Collision::Type::eBox; // 当たり判定のタイプをボックスに設定
	m_tCollisionInfo.box.center = m_tPosition; // 中心位置を設定
	m_tCollisionInfo.box.size = m_tScale; // サイズをスケールに設定
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
	SetRender3D();
	// 当たり判定の描画
	Collision::DrawCollision(m_tCollisionInfo);
	// モデルの描画
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
