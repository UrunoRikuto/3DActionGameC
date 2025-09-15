/*
* @file SceneGame.cpp
* @brief ゲームシーンのクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/

/* ヘッダーで利用するシステムのインクルード */
#include <memory>
/* ゲームオブジェクトのインクルード */
#include "FieldObject.h"
#include "Player.h"
#include "TargetNpc.h"
#include "GuardNpc.h"
/* ヘッダーのインクルード */
#include "SceneGame.h"
/* システム・要素のインクルード */
#include "Camera.h"
#include "Defines.h"
#include "GameValues.h"
#include "MovePointManager.h"
#include "Quest.h"

/* グローバル変数 */
std::vector<CGameObject*> g_vNullCheckList; // Nullチェック用のゲームオブジェクトのリスト

void CSceneGame::InitArenaStage(void)
{

	// フィールドの生成
	// 地面の生成
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(100.0f, 1.0f, 100.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, 2.0f, 100.0f));
	// 壁の生成
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 20.0f, 1.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 20.0f, 99.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, 100.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 20.0f, 1.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 20.0f, 99.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, -100.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(1.0f, 20.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetRotation(XMFLOAT3(0.0f, 90.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(199.0f, 20.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(100.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, 0.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(1.0f, 20.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetRotation(XMFLOAT3(0.0f, 90.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(199.0f, 20.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(-100.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, 0.0f));

	// 移動ポイントの生成
	CMovePointManager::GetInstance()->CreateData(CQuest::GetInstance()->GetQuestData().stageType);
	//- 移動ポイントマネージャーのインスタンスを取得
	std::vector<XMFLOAT3> pMovePointManager = CMovePointManager::GetInstance()->GetMovePoints();

	// NPCの生成（ターゲットNPC）
	m_pNpc.push_back(std::make_unique<CTargetNpc>(pMovePointManager[0], NpcType::ArenaTarget));
	m_pNpc[0]->GetMoveSystem()->AddMovePoint(pMovePointManager[1]);
	m_pNpc[0]->GetMoveSystem()->AddMovePoint(pMovePointManager[2]);
	m_pNpc[0]->GetMoveSystem()->AddMovePoint(pMovePointManager[3]);
	m_pNpc[0]->GetMoveSystem()->AddMovePoint(pMovePointManager[4]);
}

void CSceneGame::InitPlainStage(void)
{
	//// 移動ポイントの生成
	//CMovePointManager::GetInstance()->CreateData(FieldType::Plain);
	////- 移動ポイントマネージャーのインスタンスを取得
	//std::vector<XMFLOAT3> pMovePointManager = CMovePointManager::GetInstance()->GetMovePoints();

	//// NPCの生成（ターゲットNPC）
	//m_pNpc.push_back(std::make_unique<CTargetNpc>(pMovePointManager[0], NpcType::Normal));
	//m_pNpc[0]->GetMoveSystem()->AddMovePoint(pMovePointManager[1]);

	//// NPCの生成（護衛NPC）
	//m_pNpc.push_back(std::make_unique<CGuardNpc>(pMovePointManager[2], NpcType::Normal));
	//m_pNpc[1]->GetMoveSystem()->AddMovePoint(pMovePointManager[3]);
	//m_pNpc[1]->GetMoveSystem()->AddMovePoint(pMovePointManager[4]);
}

// @brief コンストラクタ
CSceneGame::CSceneGame()
	:CSceneBase()
{
	using namespace GameValue;

	switch (CQuest::GetInstance()->GetQuestData().stageType)
	{
	case StageType::Arena:
		InitArenaStage(); // 闘技場ステージの初期化
		break;
	case StageType::Plain:
		InitPlainStage(); // 平原ステージの初期化
		break;
	}


	// プレイヤーの生成
	m_pPlayer = std::make_unique<CPlayer>();

	// 視覚索敵処理のターゲット設定
	for (auto& npc : m_pNpc)
	{
		npc->SetTarget(m_pPlayer.get());
	}

	// Nullチェック用リストに追加
	for (auto& field : m_pFieldObject)
	{
		g_vNullCheckList.push_back(field.get()); // フィールド
	}
	g_vNullCheckList.push_back(m_pPlayer.get()); // プレイヤー
	for (auto& npc : m_pNpc)
	{
		g_vNullCheckList.push_back(npc.get()); // NPC
	}
}

// @brief デストラクタ
CSceneGame::~CSceneGame()
{

}

// @brief 更新処理
void CSceneGame::Update(void)
{
	for(auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Update(); // Nullチェックを行い、オブジェクトが有効な場合のみ更新処理を呼び出す
		}
	}

	CollisionCheck(); // 当たり判定の衝突チェック

	RayCastCheck(); // レイキャストのチェック

	AttackCollisionCheck(); // 攻撃の当たり判定チェック
}

// @brief 描画処理
void CSceneGame::Draw(void)
{
	// 移動ポイントのデバッグ描画
	CMovePointManager::GetInstance()->DebugDraw(); // 移動ポイントのデバッグ描画

	// 攻撃の当たり判定のデバッグ描画
	for (const auto& attack : m_vAttackCollisionInfos)
	{
		Collision::DrawCollision(attack.CollisionInfo);
	}

	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Draw(); // Nullチェックを行い、オブジェクトが有効な場合のみ描画処理を呼び出す
		}
	}
}

// @brief すべてのフィールドオブジェクトを取得する
// @return すべてのフィールドオブジェクトのリスト
std::vector<CGameObject*> CSceneGame::GetAllFieldObjects(void)
{
	// 格納するリストを作成
	std::vector<CGameObject*> fieldObjects;

	for (auto& obj : g_vNullCheckList)
	{
		// Nullチェックを行う
		if (SafeNullCheck(obj))
		{
			// 当たり判定を走査
			if (!obj->GetCollisionInfo(Collision::Tag::FieldObject).empty())
			{
				fieldObjects.push_back(obj); // 当たり判定が存在する場合、リストに追加
			}
		}
	}

	// リストを返す
	return fieldObjects;
}

// @brief 当たり判定の衝突チェック
void CSceneGame::CollisionCheck(void)
{
	// すべてのゲームオブジェクトの当たり判定情報を取得し、衝突チェックを行う
	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			auto collisionInfo = obj->GetCollisionInfo(Collision::Tag::All);
			for (const auto& info : collisionInfo)
			{
				for (auto& targetObj : g_vNullCheckList)
				{
					if (targetObj == obj) continue; // 自分自身は除外

					auto targetCollisionInfo = targetObj->GetCollisionInfo(Collision::Tag::All);

					for (const auto& targetInfo : targetCollisionInfo)
					{
						Collision::Result result = Collision::Hit(info, targetInfo);
						if (result.isHit)
						{
							obj->Hit(targetInfo); // 衝突時の処理を呼び出す
						}
					}
				}
			}
		}
	}

	// 軽量化する際の処理候補(ブロードとナロー)
	/*
	using namespace GameValue::Collision;

	/// ブロードフェーズ
	// 衝突する可能性のある当たり判定をリストアップする処理

	// 格納リスト
	std::vector<CollisionCheckInfo> collisionList;

	// Nullチェックを行い、オブジェクトが有効な場合のみ処理を行う
	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			// 各オブジェクトの当たり判定情報を取得
			auto collisionInfo = obj->GetCollisionInfo(Collision::Tag::All);
			
			for (const auto& info : collisionInfo)
			{
				CollisionCheckInfo checkInfo;
				checkInfo.SelfInfo = info; // オブジェクトを設定

				for (auto& TargetObject : g_vNullCheckList)
				{
					if (TargetObject == obj) continue; // 自分自身は除外

					auto TargetCollisionInfo = TargetObject->GetCollisionInfo(Collision::Tag::All);

					for (const auto& Targetinfo : TargetCollisionInfo)
					{
						switch (info.type)
						{
						case Collision::Type::eNone:
							break;
						case Collision::Type::eBox:
							if (StructMath::Distance(Targetinfo.box.center,info.box.center) <= DETECT_DISTANCE)
							{
								checkInfo.TargetInfo.push_back(Targetinfo); // 対象の当たり判定情報を設定
							}
							break;
						case Collision::Type::eSphere:
							break;
						case Collision::Type::ePlane:
							break;
						case Collision::Type::eRay:
							break;
						case Collision::Type::eLine:
							break;
						case Collision::Type::ePoint:
							break;
						case Collision::Type::eTriangle:
							break;
						}
					}
				}

				if (!checkInfo.TargetInfo.empty()) // 対象の当たり判定情報がある場合
				{
					collisionList.push_back(checkInfo); // リストに追加
				}
			}
		}
	}



	/// ナローフェーズ
	// リストアップしたオブジェクト同士の詳細な衝突判定
	for (const auto& checkInfo : collisionList)
	{
		for (const auto& targetInfo : checkInfo.TargetInfo)
		{
			Collision::Result result = Collision::Hit(checkInfo.SelfInfo, targetInfo);
			if (result.isHit)
			{
				int a = 0;
			}
		}
	}
	*/
}

// @brief レイキャストのチェック
void CSceneGame::RayCastCheck(void)
{
	float SetUnderHeight = 0.0f; // プレイヤーの真下の地面の高さを設定する変数

	for (auto& obj : m_pFieldObject)
	{
		if (m_pPlayer->GetRay()->Cast(obj->GetCollisionInfo(Collision::Tag::FieldGround)))
		{
			if (SetUnderHeight < obj->GetPosition().y + obj->GetScale().y / 2.0f)
			{
				// レイキャストが当たった場合、プレイヤーの真下の地面の高さを設定
				SetUnderHeight = obj->GetPosition().y + obj->GetScale().y / 2.0f;
			}
		}
	}
	m_pPlayer->SetUnderHeight(SetUnderHeight);

	SetUnderHeight = 0.0f;

	for (auto& npc : m_pNpc)
	{
		for (auto& obj : m_pFieldObject)
		{
			if (npc->GetRay()->Cast(obj->GetCollisionInfo(Collision::Tag::FieldGround)))
			{
				if (SetUnderHeight < obj->GetPosition().y + obj->GetScale().y / 2.0f)
				{
					// レイキャストが当たった場合、NPCの真下の地面の高さを設定
					SetUnderHeight = obj->GetPosition().y + obj->GetScale().y / 2.0f;
				}
			}
		}
		npc->SetUnderHeight(SetUnderHeight); // NPCの真下の地面の高さを設定
	}
}

// @brief 攻撃の当たり判定チェック
void CSceneGame::AttackCollisionCheck(void)
{
	for (auto& attackInfo : m_vAttackCollisionInfos)
	{
		for (auto& obj : g_vNullCheckList)
		{
			if (SafeNullCheck(obj))
			{
				// 自分自身は除外
				// 指定のタグが含まれている場合は除外
				std::vector<Collision::Info>SkipTagCollision;

				for (auto& tag : attackInfo.CollisionInfo.tag)
				{
					switch (tag)
					{
					case Collision::Tag::Npc:
						SkipTagCollision = obj->GetCollisionInfo(Collision::Tag::Npc);
						break;
					case Collision::Tag::Player:
						SkipTagCollision = obj->GetCollisionInfo(Collision::Tag::Player);
						break;
					}
				}
				// 指定のタグが含まれている場合は除外
				if (!SkipTagCollision.empty()) continue;

				auto targetCollisionInfo = obj->GetCollisionInfo(Collision::Tag::All);
				for (const auto& targetInfo : targetCollisionInfo)
				{
					Collision::Result result = Collision::Hit(attackInfo.CollisionInfo, targetInfo);
					if (result.isHit)
					{
						obj->Hit(attackInfo.CollisionInfo, attackInfo.AttackPower); // 衝突時の処理を呼び出す

						// この攻撃の持続時間を0にする
						attackInfo.DurationFrame = 0;
					}
				}
			}
		}

		// 攻撃の持続時間を減少
		attackInfo.DurationFrame -= 1.0f / fFPS;

		// 持続時間が0以下になったら削除
		if (attackInfo.DurationFrame <= 0)
		{
			m_vAttackCollisionInfos.erase(
				std::remove(
					m_vAttackCollisionInfos.begin(),
					m_vAttackCollisionInfos.end(),
					attackInfo), m_vAttackCollisionInfos.end());
		}
	}
}

// @brief 攻撃の生成
// @param In_CollisionInfo 衝突対象
void CSceneGame::AttackCreate(AttackCollision In_CollisionInfo)
{
	// 攻撃の生成
	m_vAttackCollisionInfos.push_back(In_CollisionInfo);
}
