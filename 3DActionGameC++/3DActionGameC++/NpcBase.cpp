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
	, m_bGround(true) // 地面に立っているかのフラグを初期化
	, m_fUnderHeight(0.0f) // 真下の高さを保存する変数を初期化
{
	// モデルの作成
	m_pModel = std::make_unique<Model>();
	// 視覚索敵の作成
	m_pVisionSearch = std::make_unique<CVisionSearch>(this);

	// レイの作成
	m_pRay = std::make_unique<CRay>();
	m_pRay->SetParam(m_tPosition, XMFLOAT3(0.0f, -1.0f, 0.0f)); // レイの始点と方向を設定
}

// @brief デストラクタ
CNpcBase::~CNpcBase()
{
}

// @brief 最初の方に行う共通更新処理
void CNpcBase::BiginUpdate(void)
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;

	// 索敵システムの更新(索敵)
	SetSearchState(m_pVisionSearch->Search(m_tPosition, m_eSearchState));

}

// @brief 最後の方に行う共通更新処理
void CNpcBase::EndUpdate(void)
{
	// 地面判定
	GroundCheck();

	// Hpゲージの更新
	if (m_pHpGauge)m_pHpGauge->Updatde(m_tPosition, m_fHp);
	// レイの更新
	m_pRay->SetOrigin(m_tPosition); // レイの位置を更新
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

		// 索敵状態を発見状態にする
		SetSearchState(VisionSearchState::Discovery);

		// 体力が0以下になったら破棄フラグを立てる
		if (m_fHp <= 0.0f)
		{
			m_bDestroy = true;
			m_fHp = 0.0f;
		}
	}
}

// @brief 地面判定処理
void CNpcBase::GroundCheck(void)
{
	// 地面にいる場合は高さを0にする
	if (m_bGround)
	{
		m_tPosition.y = m_fUnderHeight + m_fAjustPositionY;
	}
	else
	{
		if (m_tPosition.y >= m_fUnderHeight + m_fAjustPositionY)
		{
			m_tPosition.y -= GRAVITY; // 重力を適用
			if (m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
			{
				m_tPosition.y = m_fUnderHeight + m_fAjustPositionY; // 地面の高さに合わせる
				m_bGround = true; // 地面にいる状態にする
			}
		}
		else if (m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
		{
			m_tPosition.y += 0.2f; // 地面の高さに合わせる
			if (m_tPosition.y > m_fUnderHeight + m_fAjustPositionY)
			{
				m_tPosition.y = m_fUnderHeight + m_fAjustPositionY; // 地面の高さに合わせる
				m_bGround = true; // 地面にいる状態にする
			}
		}
	}
}

// @brief 現在の索敵状態の設定
// @param InState 設定する索敵状態
void CNpcBase::SetSearchState(VisionSearchState InState)
{
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

// @brief プレイヤーの真下の地面の高さを設定する
// @param height プレイヤーの真下の地面の高さ
void CNpcBase::SetUnderHeight(float height)
{
	if (m_fUnderHeight - m_fAjustPositionY != height)
	{
		m_fUnderHeight = height + m_fAjustPositionY;
		m_bGround = false;
	}
}
