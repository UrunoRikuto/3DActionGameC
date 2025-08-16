/*
* @file Field.cpp
* @brief フィールドオブジェクトのクラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*/


/* ヘッダーで利用するシステム・要素のインクルード */
#include "RayCastTarget.h"
#include <memory>
/* ヘッダーのインクルード */
#include "Field.h"
/* システム・要素のインクルード */
#include "Model.h"
#include "Defines.h"
#include "Main.h"
#include "ModelDrawSetting.h"
#include "Geometory.h"

// @brief コンストラクタ
CField::CField()
	: CGameObject() // 基底クラスのコンストラクタを呼び出す
{
	using namespace GameValue::Field;

	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("BattleStage_Field.obj"),0.1f))
	{
		MessageBox(NULL, "フィールドモデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 位置、スケール、回転の設定
	m_tScale = { FIELD_SIZE, 1.0f, FIELD_SIZE };
	m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// レイキャストのターゲットオブジェクトの生成
	m_pRayCastTarget = std::make_unique<CRayCastTarget>();
	// レイキャストのターゲットオブジェクトのパラメーターを設定
	m_pRayCastTarget->SetParam(m_tPosition, m_tScale);

	// 当たり判定情報の初期化
	// 当たり判定情報のサイズを1に設定
	m_tCollisionInfos.resize(1);
	// 当たり判定の種類を設定
	m_tCollisionInfos[0].type = Collision::Type::eBox;
	// タグを追加
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Field);
	// 中心位置を設定
	m_tCollisionInfos[0].box.center = m_tPosition;
	// ボックスの大きさを設定
	m_tCollisionInfos[0].box.size = m_tScale;
}

// @brief デストラクタ
CField::~CField()
{

}

// @brief 更新処理
void CField::Update(void)
{
	// 破棄フラグが立っている場合は更新を行わない
	if (m_bDestroy)return;


	m_pRayCastTarget->SetPosition(m_tPosition); // レイキャストのターゲットオブジェクトの位置を更新
	m_pRayCastTarget->SetScale(m_tScale); // レイキャストのターゲットオブジェクトのスケールを更新
}

// @brief 当たり判定の衝突時の処理
// @param InCollisionInfo 衝突対象
void CField::Hit(const Collision::Info& InCollisionInfo)
{
	// 今は特に何もしない
}
