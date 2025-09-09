/*=====================================================================
* @file NpcBase.cpp
* @brief NPCの基底クラスのCppファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "NpcBase.h"
/* システム・要素のインクルード */
#include "Model.h"

// @brief コンストラクタ
// @param InType NPCの種類
CNpcBase::CNpcBase(NpcType InType)
	:CGameObject() // 基底クラスのコンストラクタを呼び出す
	, m_eNpcType(InType) // NPCの種類を設定
	, m_eSearchState(VisionSearchState::None) // 索敵状態を初期化
	, m_fAttackCD(0.0f) // 攻撃のクールタイムを初期化
	, m_bAttack(false) // 攻撃中かどうかの初期化
	, m_pHpGauge(nullptr) // 体力ゲージの初期化
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
	SetSearchState(m_pVisionSearch->Search(m_tPosition, m_eSearchState));

	// Hpゲージの更新
	if (m_pHpGauge)m_pHpGauge->Updatde(m_tPosition, m_fHp);
}

// @brief 描画処理
void CNpcBase::Draw(void)
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;

	// 体力ゲージの描画
	m_pHpGauge->Draw();
	
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

// @brief 当たり判定の衝突時の処理(攻撃用)
// @param InCollisionInfo 衝突対象
// @param In_Attack 相手の攻撃力
void CNpcBase::Hit(const Collision::Info& InCollisionInfo, float In_Attack)
{
	int IsPlayerAttackCheck = 0;

	// プレイヤーの攻撃に当たったかどうかを判定
	// プレイヤータグと攻撃タグの両方があればプレイヤーの攻撃に当たったと判定
	for (auto& tag : InCollisionInfo.tag)
	{
		switch (tag)
		{
		case Collision::Tag::Player:
			IsPlayerAttackCheck++;
			break;
		case Collision::Tag::Attack:
			IsPlayerAttackCheck++;
			break;
		}
	}

	// プレイヤーの攻撃に当たった場合
	if (IsPlayerAttackCheck >= 2)
	{
		// 体力を減らす
		m_fHp -= In_Attack;
		// 体力が0以下になったら破棄フラグを立てる
		if (m_fHp <= 0.0f)
		{
			m_bDestroy = true;
			m_fHp = 0.0f;
		}
	}
}

// @brief 現在の索敵状態の設定
// @param InState 設定する索敵状態
void CNpcBase::SetSearchState(VisionSearchState InState)
{
	/// @Todo 索敵状態に応じた処理を追加する
	/// 例: Noneから状態が変化した場合はMoveSystemの移動ポイントを仮保存しておくなど
	/// (次にNoneに戻ったときに同じルートを回れるように)

	// 状態が変化していない場合は何もしない
	if (m_eSearchState == InState)return;

	// 現在の状態による処理
	switch (m_eSearchState)
	{
	case VisionSearchState::None:
		/// 移動ルートを保存してクリア
		m_pMoveSystem->SaveAndClearMovePoints();
		break;
	case VisionSearchState::Doubt:
		/// 移動ルートをクリア
		m_pMoveSystem->ClearMovePoints();
		break;
	case VisionSearchState::Lost:
		break;
	case VisionSearchState::Discovery:
		break;
	}

	// 状態の更新
	m_eSearchState = InState;

	// 新しい状態による処理
	switch (InState)
	{
	case VisionSearchState::None:
		/// 移動ルートを復元
		m_pMoveSystem->RestorationMovePoints(m_tPosition);
		break;
	case VisionSearchState::Doubt:
		/// プレイヤーの位置までの移動ルートを設定
		m_pMoveSystem->SetMovePoints(CMovePointManager::GetInstance()->CreateMoveRoute(m_tPosition, m_pTargetObject->GetPosition()), m_tPosition);
		m_pMoveSystem->SetMoveSystemType(MoveSystemType::Once);
		break;
	case VisionSearchState::Lost:
		break;
	case VisionSearchState::Discovery:
		break;
	}
}
