/*
* @file NpcBase.cpp
* @brief NPCの基底クラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 NPCの基底クラスの実装
*/

/* ヘッダーのインクルード */
#include "NpcBase.h"
/* システム・要素のインクルード */
#include "Model.h"

// @brief コンストラクタ
CNpcBase::CNpcBase()
{
	// モデルの作成
	m_pModel = std::make_unique<Model>();
}

// @brief デストラクタ
CNpcBase::~CNpcBase()
{
}

// @brief 更新処理
void CNpcBase::Update(void)
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;
	
	using namespace StructMath;

	// 移動
	XMFLOAT3 movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
	SetPosition(Add(m_tPosition, Mul(Direction(m_tPosition, movePoint), m_pMoveSystem->GetMoveSpeed())));
}

// @brief 描画処理
void CNpcBase::Draw(void)
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;
	
	// 移動システムのデバッグ描画
	m_pMoveSystem->DebugDraw(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	// 基底クラスの描画
	CGameObject::Draw();
}

// @brief 当たり判定の衝突時の処理
// @param InCollisionInfo 衝突対象
void CNpcBase::Hit(const Collision::Info& InCollisionInfo)
{
	// 今は何もしない
}
