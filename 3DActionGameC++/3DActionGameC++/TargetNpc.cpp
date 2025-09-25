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
#include "ResultTelop.h"

#undef max

// @brief コンストラクタ
// @param FirstMovePoint 最初の移動ポイント
// @param NpcType NPCの種類
CTargetNpc::CTargetNpc(XMFLOAT3 FirstMovePoint, NpcType NpcType)
	: CNpcBase(NpcType) // 基底クラスのコンストラクタを呼び出す
{
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

	// 補正高さ
	m_fAjustPositionY = (m_tScale.y * 2) / 2.0f;
	// 位置
	m_tPosition = StructMath::Add(m_pMoveSystem->GetMovePointList()[0], XMFLOAT3(0.0f, m_fAjustPositionY, 0.0f));
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
	m_tCollisionInfos[0].box.center = StructMath::Add(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
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
	m_tCollisionInfos[2].box.center = StructMath::Sub(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[2].AdjustCenter = XMFLOAT3(0.0f, -m_tScale.y, 0.0f); // 中心位置の調整
	// ボックスの大きさを設定
	m_tCollisionInfos[2].box.size = m_tScale;

	switch (m_eNpcType)
	{
	case NpcType::ArenaTarget:
		// 武器の生成
		m_pWeapon = new CSword();
		// 武器の当たり判定にNPCタグを追加
		for (auto& AttackRange : m_pWeapon->GetAttackRanges())
		{
			AttackRange.tag.push_back(Collision::Tag::Npc);
		}
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
	if (m_bDestroy)
	{
		ChangeScene(SceneType::QuestSelect, TransitionType::Fade); // シーンをクエスト選択に変更
	}
	else
	{

		// 基底クラスの更新処理(NPC共通処理)
		CNpcBase::BiginUpdate();

		if (m_eSearchState != VisionSearchState::Discovery)
		{
			// 移動
			Move();
		}
		else
		{
			// 発見時の更新
			DiscoveryUpdate();
		}

		// 基底クラスの更新処理(NPC共通処理)
		CNpcBase::EndUpdate();
	}
}

// @brief 当たり判定の衝突時の処理(攻撃用)
// @param InCollisionInfo 衝突対象
// @param In_Attack 相手の攻撃力
void CTargetNpc::Hit(const Collision::Info& InCollisionInfo, float In_Attack)
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

		if (m_fHp <= 0.0f)
		{
			m_bDestroy = true;
			m_fHp = 0.0f;
			// テロップの追加
			static_cast<CSceneGame*>(GetCurrentScene())->AddTelop(new CResultTelop(true)); 
		}
	}
}

// @brief 発見時の更新処理
void CTargetNpc::DiscoveryUpdate(void)
{
	switch (m_eActionMode)
	{
	case EnemyAction::Select:
		// 行動タイマーをリセット
		m_fActionTimer = 0.0f;
		// 行動をランダムに決定
		m_eActionMode = static_cast<EnemyAction>((rand() % (static_cast<int>(EnemyAction::Max) - 1)) + 1);
		break;
	case EnemyAction::Move:
		Move();
		// 一定時間移動したら行動を選択に戻す
		if (m_fActionTimer > 3.0f)
		{
			m_eActionMode = EnemyAction::Select;
		}
		break;
	case EnemyAction::Attack:
		Move();
		Attack();
		if (m_bAttack || m_fActionTimer > 5.0f)
		{
			// 攻撃が終わったら行動を選択に戻す
			m_eActionMode = EnemyAction::Select;
			// 攻撃中フラグを下ろす
			m_bAttack = false;
		}
		break;
	}
	m_fActionTimer += 1.0f / fFPS;
}

// @brief 移動処理
void CTargetNpc::Move(void)
{
	XMFLOAT3 movePoint = XMFLOAT3();
	float distance = 0.0f;
	switch (m_eSearchState)
	{
	case VisionSearchState::None:
	case VisionSearchState::Doubt:
	case VisionSearchState::Lost:
		movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
		break;
	case VisionSearchState::Discovery:
		switch (m_eActionMode)
		{
		case EnemyAction::Move:
			if (m_fActionTimer == 0.0f)
			{
				m_bClockwise = rand() % 2; // 時計回りに移動するかどうかをランダムに決定
			}
			// プレイヤーの位置を取得
			XMFLOAT3 targetPoint = m_pTargetObject->GetPosition();
			// プレイヤーから一定距離を保って左右移動(時計回りor反時計回り)する
			distance = 30.0f; // プレイヤーからの距離
			if (m_bClockwise)
			{
				// 時計回り
				static float angle = 0.0f;
				angle += 1.0f;
				if (angle >= 360.0f)angle = 0.0f;
				movePoint = { targetPoint.x + distance * cosf(TORAD(angle)), m_tPosition.y, targetPoint.z + distance * sinf(TORAD(angle)) };
			}
			else
			{
				// 反時計回り
				static float angle = 180.0f;
				angle -= 1.0f;
				if (angle < 0.0f)angle = 360.0f;
				movePoint = { targetPoint.x + distance * cosf(TORAD(angle)), m_tPosition.y, targetPoint.z + distance * sinf(TORAD(angle)) };
			}
			break;
		case EnemyAction::Attack:
			XMFLOAT3 playerPos = m_pTargetObject->GetPosition();
			movePoint = { playerPos.x,m_tPosition.y,playerPos.z };
			break;
		}
		break;
	}

	XMFLOAT3 moveDir = StructMath::Direction(m_tPosition, movePoint);
	// 攻撃中でない場合は移動量を適用
	if (!m_bAttack)SetPosition(StructMath::Add(m_tPosition, StructMath::Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// 向きの更新
	if (m_eSearchState != VisionSearchState::Discovery)
	{
		m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));
	}
	else
	{
		// プレイヤーの位置を取得
		XMFLOAT3 targetPoint = m_pTargetObject->GetPosition();
		XMFLOAT3 lookDir = StructMath::Direction(m_tPosition, targetPoint);
		m_tRotation.y = TODEG(atan2f(-lookDir.z, lookDir.x));
	}
}

// @brief 攻撃処理
void CTargetNpc::Attack(void)
{
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
		float maxAttackRange = std::max(weaponCollisionSize.x, weaponCollisionSize.z); // 攻撃範囲の最大値を計算

		if (StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).x > maxAttackRange * 2.0f ||
			StructMath::Abs(StructMath::Sub(playerPos, m_tPosition)).z > maxAttackRange * 2.0f)
		{
			m_bAttack = false;
			return;
		}

		// 武器の更新処理
		// 向きを考慮して位置を調整
		XMFLOAT3 attackDir = StructMath::Direction(m_tPosition, playerPos);

		m_pWeapon->Update(StructMath::Add(m_tPosition, StructMath::Mul(attackDir, maxAttackRange)));

		/// @todo ここで攻撃タイミングの判定を行う(乱数(確率は参照するたびに上昇))

		m_pWeapon->ComboTimerUpdate(); // コンボ猶予時間の更新

		// シーンの取得
		auto scene = static_cast<CSceneGame*>(GetCurrentScene());

		// シーンがなければ何もしない
		if (scene == nullptr)return;

		// 攻撃を生成
		scene->AttackCreate(m_pWeapon->CreateAttack(m_tRotation.y));

		// クールタイムを設定
		m_fAttackCD = m_pWeapon->GetAttackSpeed();

		// 攻撃中フラグを立てる
		m_bAttack = true;
	}
}
