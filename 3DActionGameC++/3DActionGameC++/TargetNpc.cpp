/*=====================================================================
* @file TargetNpc.cpp
* @brief ターゲットNPCのクラスのCppファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "TargetNpc.h"
/* システム・要素のインクルード */
#include "Model.h"
#include "Defines.h"
#include "GameValues.h"
#include "MoveSystem.h"

// @brief コンストラクタ
// @param FirstMovePoint 最初の移動ポイント
// @param NpcType NPCの種類
CTargetNpc::CTargetNpc(XMFLOAT3 FirstMovePoint, NpcType NpcType)
	: CNpcBase(NpcType) // 基底クラスのコンストラクタを呼び出す
{
	// 名前空間の使用
	using namespace StructMath;

	// モデルの読み込み
	if (!m_pModel->Load(ModelPath::TARGET_NPC_PATH))
	{
		MessageBox(NULL, "ターゲットNPCモデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 大きさの設定
	m_tScale = { 2.0f,2.0f,2.0f };

	// 移動システムの初期化
	m_pMoveSystem = std::make_unique<CMoveSystem>(MoveSystemType::Loop, 0.1f);
	// Y座標の調整値を設定
	m_pMoveSystem->SetAdjustY(m_tScale.y / 2.0f); // NPCの高さの半分を調整値に設定
	// 移動ポイントの追加
	m_pMoveSystem->AddMovePoint(FirstMovePoint);

	// 位置
	m_tPosition = m_pMoveSystem->GetMovePointList()[0];
	// 回転
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// 当たり判定の設定
	// 当たり判定情報のサイズを3に設定
	m_tCollisionInfos.resize(3); 
	//--- 頭の当たり判定情報の初期化
	// 当たり判定の種類を設定
	m_tCollisionInfos[0].type = Collision::eBox;
	// タグを追加
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Npc);
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Head);
	// 中心位置を設定
	m_tCollisionInfos[0].box.center = Add(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[0].AdjustCenter = XMFLOAT3(0.0f, m_tScale.y, 0.0f); // 中心位置の調整
	// ボックスの大きさを設定
	m_tCollisionInfos[0].box.size = m_tScale;
	//--- 体の当たり判定情報の初期化
	// 当たり判定の種類を設定
	m_tCollisionInfos[1].type = Collision::eBox;
	// タグを追加
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::Npc);
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::Body);
	// 中心位置を設定
	m_tCollisionInfos[1].box.center = m_tPosition;
	// ボックスの大きさを設定
	m_tCollisionInfos[1].box.size = m_tScale;
	//--- 足の当たり判定情報の初期化
	// 当たり判定の種類を設定
	m_tCollisionInfos[2].type = Collision::eBox;
	// タグを追加
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::Npc);
	// タグを追加
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::Foot);
	// 中心位置を設定
	m_tCollisionInfos[2].box.center = Sub(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[2].AdjustCenter = XMFLOAT3(0.0f, -m_tScale.y, 0.0f); // 中心位置の調整
	// ボックスの大きさを設定
	m_tCollisionInfos[2].box.size = m_tScale;

	switch (m_eNpcType)
	{
	case NpcType::ArenaTarget:
		// 武器の生成
		m_pWeapon = new CSword();
		// 武器の当たり判定にNPCタグを追加
		m_pWeapon->GetAttackRange().tag.push_back(Collision::Tag::Npc);
		// 体力の設定
		m_fHp = GameValue::Npc::ArenaTarget::MAX_HP;
		break;
	}

	// 体力ゲージの作成
	m_pHpGauge = new CGaugeUI(m_fHp, false, GaugeType::Health);
	// 体力ゲージのパラメータ設定
	m_pHpGauge->SetParam({ 5.0f,2.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f, 5.0f, 0.0f });
}

// @brief デストラクタ
CTargetNpc::~CTargetNpc()
{

}

// @brief 更新処理
void CTargetNpc::Update(void)
{

	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;
	

	// 基底クラスの更新処理(NPC共通処理)
	CNpcBase::Update();

	// 攻撃
	//Attack();
	// 移動
	Move();

}

// @brief 移動処理
void CTargetNpc::Move(void)
{
	// 名前空間の使用
	using namespace StructMath;
	using namespace GameValue::Npc;

	XMFLOAT3 movePoint = XMFLOAT3();

	switch (m_eSearchState)
	{
	case VisionSearchState::None:
	case VisionSearchState::Doubt:
	case VisionSearchState::Lost:
		movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
		break;
	case VisionSearchState::Discovery:
		XMFLOAT3 playerPos = m_pTargetObject->GetPosition();
		movePoint = { playerPos.x,m_tPosition.y,playerPos.z };
		break;
	}

	XMFLOAT3 moveDir = Direction(m_tPosition, movePoint);
	// 攻撃中でない場合は移動量を適用
	if (!m_bAttack)SetPosition(Add(m_tPosition, Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// 向きの更新
	m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));
}

// @brief 攻撃処理
void CTargetNpc::Attack(void)
{
	// 名前空間の使用宣言
	using namespace StructMath;

	// クールタイムが残っている場合はクールタイムを減らす
	if (m_fAttackCD > 0.0f)
	{
		m_fAttackCD -= 1.0f / fFPS;
		if (m_fAttackCD < 0.0f)m_fAttackCD = 0.0f;
	}
	else
	{
		// 索敵状態が発見以外なら何もしない
		if (m_eSearchState != VisionSearchState::Discovery)return;

		// 武器があれば攻撃
		if (m_pWeapon == nullptr)return;

		// プレイヤーが攻撃範囲内にいるかどうかを判定
		// プレイヤーの位置を取得
		XMFLOAT3 playerPos = m_pTargetObject->GetPosition();
		// 攻撃範囲外なら何もしない
		XMFLOAT3 weaponCollisionSize = m_pWeapon->GetAttackRange().box.size;

		if (StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).x > weaponCollisionSize.x * 2 ||
			StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).z > weaponCollisionSize.z * 2)
		{
			m_bAttack = false;
			return;
		}



		// 武器の更新処理
		// 向きを考慮して位置を調整
		XMFLOAT3 attackDir = StructMath::Direction(m_tPosition, playerPos);

		m_pWeapon->Update(Add(m_tPosition, Mul(attackDir, m_pWeapon->GetAttackRange().box.size.x)));

		// シーンの取得
		auto scene = (CSceneGame*)GetCurrentScene();

		// シーンがなければ何もしない
		if (scene == nullptr)return;

		// 攻撃を生成
		scene->AttackCreate({ m_pWeapon->GetAttackRange(),m_pWeapon->GetAttackDurationFrame(), m_pWeapon->GetAttackPower() });

		// クールタイムを設定
		m_fAttackCD = m_pWeapon->GetAttackSpeed();

		// 攻撃中フラグを立てる
		m_bAttack = true;
	}
}
