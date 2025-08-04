/*
* @file Field.cpp
* @brief フィールドオブジェクトのクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/


/* ヘッダーで利用するシステムのインクルード */
#include <memory>
/* コンポーネントのインクルード */
#include "Model.h"
/* ヘッダーのインクルード */
#include "Field.h"
/* システムのインクルード */
#include "Main.h"
#include "ModelDrawSetting.h"
#include "StructMath.h"

// @brief コンストラクタ
CField::CField()
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("BattleStage_Field.obj")))
	{
		MessageBox(NULL, "フィールドモデルの読み込みに失敗しました。", "Error", MB_OK);
	}
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
		XMFLOAT3(0.0f,0.0f,0.0f), // 位置
		XMFLOAT3(100.0f,1.0f,100.0f), // スケール
		XMFLOAT3(0.0f,0.0f,0.0f), // 回転
		XMFLOAT3(1.0f,1.0f,1.0f), // 色
		m_pModel.get(),       // モデルポインタ
		Camera::GetInstance(),// カメラポインタ
		false                 // 明るくするかどうか
	);

}
