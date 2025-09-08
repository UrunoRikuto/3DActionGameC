/*=====================================================================
* @file GameObject.cpp
* @brief ゲームオブジェクトの基底クラスのCppファイル
=====================================================================*/

/* ヘッダーで利用するシステム・要素のインクルード */
#include "Model.h"

/* ヘッダーのインクルード */
#include "GameObject.h"
/* システム・要素のインクルード */
#include "ModelDrawSetting.h"

// @brief コンストラクタ
CGameObject::CGameObject()
	: m_pModel(nullptr) // モデルポインタの初期化
	, m_tPosition(0.0f, 0.0f, 0.0f) // 初期位置
	, m_fAjustPositionY(0.0f) // プレイヤーの真下の地面の高さの初期値
	, m_tScale(1.0f, 1.0f, 1.0f) // 初期スケール
	, m_tRotation(0.0f, 0.0f, 0.0f) // 初期回転
	, m_tCollisionInfos{} // 当たり判定情報の初期化
	, m_bDestroy(false) // 破棄フラグの初期化
{
	
}

// @brief デストラクタ
CGameObject::~CGameObject()
{

}

// @brief 更新処理
void CGameObject::Update()
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;

}

// @brief 描画処理
void CGameObject::Draw()
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;

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
std::vector<Collision::Info> CGameObject::GetCollisionInfo(Collision::Tag InTag)
{
	if (InTag == Collision::Tag::All)
	{
		// 全ての当たり判定情報を返す
		return m_tCollisionInfos;
	}

	std::vector<Collision::Info> result; // 結果を格納するベクター

	// 指定されたタグの当たり判定情報を検索
	for (const auto& collisionInfo : m_tCollisionInfos)
	{
		for (const auto& tag : collisionInfo.tag)
		{
			if (tag == InTag)
			{
				// 見つかった場合はその情報を結果に追加
				result.push_back(collisionInfo);
			}
		}
	}
	// 結果を返す
	return result;
}

// @brief 位置情報を設定する関数
// @param position 設定する位置情報
void CGameObject::SetPosition(const XMFLOAT3& position)
{
	m_tPosition = position; // 位置情報を設定
	// 当たり判定の中心位置も更新
	for (auto& collisionInfo : m_tCollisionInfos)
	{
		if (collisionInfo.type == Collision::Type::eBox)
		{
			collisionInfo.box.center = StructMath::Add(m_tPosition,collisionInfo.AdjustCenter); // ボックスの中心位置を更新
		}
	}
}

// @brief スケール情報を設定する関数
// @param scale 設定するスケール情報
void CGameObject::SetScale(const XMFLOAT3& scale)
{
	m_tScale = scale; // スケール情報を設定
	// 当たり判定の大きさも更新
	for (auto& collisionInfo : m_tCollisionInfos)
	{
		if (collisionInfo.type == Collision::Type::eBox)
		{
			collisionInfo.box.size = m_tScale; // ボックスの大きさを更新
		}
	}
}
