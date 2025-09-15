/*=====================================================================
* @file FieldObject.cpp
* @brief フィールドオブジェクトの実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "FieldObject.h"

/* システム・要素のインクルード */
#include "Model.h"
#include "GameValues.h"
#include "Quest.h"

// @brief コンストラクタ
CFieldObject::CFieldObject(FieldObjectType In_Type)
	: CGameObject() // 基底クラスのコンストラクタを呼び出す
{
	using namespace GameValue::Field;

	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// フィールドオブジェクトの種類に応じて初期化
	switch (In_Type)
	{
	case FieldObjectType::Wall:
		// モデルの読み込み
		switch (CQuest::GetInstance()->GetQuestData().stageType)
		{
		case StageType::Arena:
			if (!m_pModel->Load(MODEL_PATH("ArenaStage_Wall.obj"), 0.1f))
			{
				MessageBox(NULL, "壁のモデルの読み込みに失敗しました。", "Error", MB_OK);
			}
			break;
		case StageType::Plain:
			if (!m_pModel->Load(MODEL_PATH("PlainStage_Wall.obj"), 0.1f))
			{
				MessageBox(NULL, "壁のモデルの読み込みに失敗しました。", "Error", MB_OK);
			}
			break;
		}

		// 位置、スケール、回転の設定
		m_tScale = { 1.0f, 1.0f, 1.0f };
		m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
		m_tRotation = { 0.0f, 0.0f, 0.0f };

		// 当たり判定情報の初期化
		// 当たり判定情報のサイズを1に設定
		m_tCollisionInfos.resize(1);
		// 当たり判定の種類を設定
		m_tCollisionInfos[0].type = Collision::Type::eBox;
		// タグを追加
		m_tCollisionInfos[0].tag.push_back(Collision::Tag::FieldWall);
		// 中心位置を設定
		m_tCollisionInfos[0].box.center = m_tPosition;
		// ボックスの大きさを設定
		m_tCollisionInfos[0].box.size = m_tScale;
		break;
	case FieldObjectType::Ground:
		// モデルの読み込み
		switch (CQuest::GetInstance()->GetQuestData().stageType)
		{
		case StageType::Arena:
			if (!m_pModel->Load(MODEL_PATH("ArenaStage_Field.obj"), 0.1f))
			{
				MessageBox(NULL, "フィールドモデルの読み込みに失敗しました。", "Error", MB_OK);
			}
			break;
		case StageType::Plain:
			if (!m_pModel->Load(MODEL_PATH("PlainStage_Field.obj"), 0.1f))
			{
				MessageBox(NULL, "フィールドモデルの読み込みに失敗しました。", "Error", MB_OK);
			}
			break;
		}

		// 位置、スケール、回転の設定
		m_tScale = { 1.0f, 1.0f, 1.0f };
		m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
		m_tRotation = { 0.0f, 0.0f, 0.0f };

		// 当たり判定情報の初期化
		// 当たり判定情報のサイズを1に設定
		m_tCollisionInfos.resize(1);
		// 当たり判定の種類を設定
		m_tCollisionInfos[0].type = Collision::Type::eBox;
		// タグを追加
		m_tCollisionInfos[0].tag.push_back(Collision::Tag::FieldGround);
		// 中心位置を設定
		m_tCollisionInfos[0].box.center = m_tPosition;
		// ボックスの大きさを設定
		m_tCollisionInfos[0].box.size = m_tScale;
		break;
	}
}

// @brief デストラクタ
CFieldObject::~CFieldObject()
{

}

// @brief 更新処理
void CFieldObject::Update(void)
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;

}

// @brief 当たり判定の衝突時の処理
void CFieldObject::Hit(const Collision::Info& InCollisionInfo)
{

}
