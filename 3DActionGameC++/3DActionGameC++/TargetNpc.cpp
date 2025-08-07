/*
* @file TargetNpc.cpp
* @brief ターゲットNPCのクラスのCppファイル
* @author 宇留野陸斗
* * @date 2025/08/04 ターゲットNPCのクラスの実装
*/

/* ヘッダーのインクルード */
#include "TargetNpc.h"
/* システム・要素のインクルード */
#include "Model.h"

// @brief コンストラクタ
CTargetNpc::CTargetNpc()
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("TargetNPC.obj")))
	{
		MessageBox(NULL, "ターゲットNPCモデルの読み込みに失敗しました。", "Error", MB_OK);
	}
	// 位置、スケール、回転の設定
	m_tScale = { 2.0f,2.0f,2.0f };
	m_tPosition = { 0.0f, (m_tScale.y * 3) / 2, 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// 当たり判定の設定
	// 当たり判定情報のサイズを3に設定
	m_tCollisionInfos.resize(3); 
	//--- 頭の当たり判定情報の初期化
	// 当たり判定の種類を設定
	m_tCollisionInfos[0].type = Collision::eBox;
	// タグを追加
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::TargetNpc);
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Head);
	// 中心位置を設定
	m_tCollisionInfos[0].box.center = StructMath::Add(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	// ボックスの大きさを設定
	m_tCollisionInfos[0].box.size = m_tScale;
	//--- 体の当たり判定情報の初期化
	// 当たり判定の種類を設定
	m_tCollisionInfos[1].type = Collision::eBox;
	// タグを追加
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::TargetNpc);
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::Body);
	// 中心位置を設定
	m_tCollisionInfos[1].box.center = m_tPosition;
	// ボックスの大きさを設定
	m_tCollisionInfos[1].box.size = m_tScale;
	//--- 足の当たり判定情報の初期化
	// 当たり判定の種類を設定
	m_tCollisionInfos[2].type = Collision::eBox;
	// タグを追加
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::TargetNpc);
	// タグを追加
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::Foot);
	// 中心位置を設定
	m_tCollisionInfos[2].box.center = StructMath::Sub(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	// ボックスの大きさを設定
	m_tCollisionInfos[2].box.size = m_tScale;
}

// @brief デストラクタ
CTargetNpc::~CTargetNpc()
{

}

// @brief 更新処理
void CTargetNpc::Update(void)
{

}
