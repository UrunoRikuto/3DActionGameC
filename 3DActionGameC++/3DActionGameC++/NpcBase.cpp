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
CNpcBase::CNpcBase(NpcType InType)
	:CGameObject() // 基底クラスのコンストラクタを呼び出す
	,m_eNpcType(InType) // NPCの種類を設定
	, m_eSearchState(VisionSearchState::None) // 索敵状態を初期化
{
	// モデルの作成
	m_pModel = std::make_unique<Model>();

	// 視覚索敵の作成
	m_pVisionSearch = std::make_unique<CVisionSearch>(this);
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

	// 索敵システムの更新(索敵)
	m_eSearchState = m_pVisionSearch->Search(m_tPosition, m_eSearchState);

	// 移動
	XMFLOAT3 movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
	XMFLOAT3 moveDir = Direction(m_tPosition, movePoint);
	SetPosition(Add(m_tPosition, Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// 向きの更新
	m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));

	// 索敵状態による処理
	switch (m_eSearchState)
	{
	case VisionSearchState::None:
		break;
	case VisionSearchState::Doubt:
		break;
	case VisionSearchState::Lost:
		break;
	case VisionSearchState::Discovery:
		break;
	}
}

// @brief 描画処理
void CNpcBase::Draw(void)
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;
	
	// 移動システムのデバッグ描画
	m_pMoveSystem->DebugDraw(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	// 索敵システムのデバッグ描画
	m_pVisionSearch->DebugDraw();

	// 基底クラスの描画
	CGameObject::Draw();
}

// @brief 当たり判定の衝突時の処理
// @param InCollisionInfo 衝突対象
void CNpcBase::Hit(const Collision::Info& InCollisionInfo)
{
	// 今は何もしない
}
