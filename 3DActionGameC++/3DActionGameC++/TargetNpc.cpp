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
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::TargetNpc);
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
	m_tCollisionInfos[2].AdjustCenter = XMFLOAT3(0.0f, -m_tScale.y, 0.0f); // 中心位置の調整
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
	// 名前空間の使用
	using namespace StructMath;

	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;
	

	// 基底クラスの更新処理(NPC共通処理)
	CNpcBase::Update();

	// 移動
	XMFLOAT3 movePoint = XMFLOAT3();

	switch (m_eSearchState)
	{
	case VisionSearchState::None:
	case VisionSearchState::Doubt:
	case VisionSearchState::Lost:
		movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
		break;
	case VisionSearchState::Discovery:
		movePoint = m_pTargetObject->GetPosition();
		break;
	}

	XMFLOAT3 moveDir = Direction(m_tPosition, movePoint);
	SetPosition(Add(m_tPosition, Mul(moveDir, m_pMoveSystem->GetMoveSpeed())));
	// 向きの更新
	m_tRotation.y = TODEG(atan2f(-moveDir.z, moveDir.x));
}
