/*
* @file GameObject.cpp
* @brief ゲームオブジェクトの基底クラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/

/* ヘッダーで利用するシステム・要素のインクルード */
#include "Model.h"

/* ヘッダーのインクルード */
#include "GameObject.h"
/* システム・要素のインクルード */
#include "Main.h"
#include "ModelDrawSetting.h"

// @brief コンストラクタ
CGameObject::CGameObject()
	: m_pModel(nullptr) // モデルポインタの初期化
	, m_tPosition(0.0f, 0.0f, 0.0f) // 初期位置
	, m_fAjustPositionY(0.0f) // プレイヤーの真下の地面の高さの初期値
	, m_tScale(1.0f, 1.0f, 1.0f) // 初期スケール
	, m_tRotation(0.0f, 0.0f, 0.0f) // 初期回転
	, m_tCollisionInfos{} // 当たり判定情報の初期化
{
	
}

// @brief デストラクタ
CGameObject::~CGameObject()
{

}

// @brief 更新処理
void CGameObject::Update()
{

}

// @brief 描画処理
void CGameObject::Draw()
{
	SetRender3D();
#ifdef _DEBUG
	// デバッグモードでの当たり判定の描画
	// 当たり判定の描画
	for (const auto& collisionInfo : m_tCollisionInfos)
	{
		Collision::DrawCollision(collisionInfo);
	}
#endif // _DEBUG

	// モデルの描画
	CreateObject(
		m_tPosition,	// 位置
		m_tScale,		// スケール
		m_tRotation,	// 回転
		m_pModel.get(),       // モデルポインタ
		Camera::GetInstance(),// カメラポインタ
		true,                 // 明るくするかどうか
		XMFLOAT3(0.5f, 0.5f, 0.5f) // ライティング色
	);
}

// @brief 当たり判定情報を追加する関数
// @param InTag 追加する当たり判定情報
Collision::Info CGameObject::GetCollisionInfo(Collision::Tag InTag)
{
	// 指定されたタグの当たり判定情報を検索
	for (const auto& collisionInfo : m_tCollisionInfos)
	{
		for (const auto& tag : collisionInfo.tag)
		{
			if (tag == InTag)
			{
				return collisionInfo; // 見つかった場合はその情報を返す
			}
		}
	}
	// 見つからなかった場合は空のCollision::Infoを返す
	return Collision::Info();
}
