/*=====================================================================
* @file MovePointManager.cpp
* @brief 移動ポイント管理クラスの実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "MovePointManager.h"
/* システム・要素のインクルード */
#include "Model.h"
#include "Defines.h"
#include "GameValues.h"
#include "ModelDrawSetting.h"
#include "Main.h"

// インスタンスの初期化
std::unique_ptr<CMovePointManager> CMovePointManager::m_pInstance = nullptr;

// @brief 移動ポイントの作成
void CMovePointManager::CreateData(FieldType In_Type)
{
	// フィールドの種類に応じて移動ポイントを設定
	switch (In_Type)
	{
	case FieldType::Plain:
		// 平原の移動ポイントを設定
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,200.0f));
		m_MovePoints.push_back(XMFLOAT3(200.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,200.0f));
		break;
	}

	m_pMovePointModels.resize(m_MovePoints.size());

	for (auto& model : m_pMovePointModels)
	{
		model = std::make_unique<Model>();
		model->Load(ModelPath::MOVE_POINT_PATH);
	}
}

// @brief インスタンスを取得する関数
// @details インスタンスが存在しない場合は新たに作成する
// @return インスタンスのポインタ
CMovePointManager* CMovePointManager::GetInstance(void)
{
	// インスタンスが存在しない場合は新たに作成
	if (!m_pInstance)
	{
		m_pInstance = std::make_unique<CMovePointManager>();
	}
	// インスタンスのポインタを返す
	return m_pInstance.get();
}

// @brief コンストラクタ
CMovePointManager::CMovePointManager()
{

}

// @brief デストラクタ
CMovePointManager::~CMovePointManager()
{

}

// @brief デバック描画処理
void CMovePointManager::DebugDraw(void)
{
#ifdef _DEBUG
	SetRender3D();
	for (int i = 0; i < m_pMovePointModels.size(); i++)
	{
		CreateObject(
			m_MovePoints[i],			// 位置
			StructMath::FtoF3(5.0f),// スケール
			StructMath::FtoF3(0.0f),// 回転
			m_pMovePointModels[i].get(),			// モデルポインタ
			Camera::GetInstance(),	// カメラポインタ
			true,					// 明るくするかどうか
			XMFLOAT3(0.5f, 0.5f, 0.5f) // ライティング色
		);
	}
#endif // _DEBUG
}

// @brief 近くの移動ポイントを取得
// @param In_Point 指定位置
// @return 指定位置の近くの移動ポイント
XMFLOAT3 CMovePointManager::NearMovePoint(const XMFLOAT3& In_Point) const
{
	// 最小距離を初期化
	float minDistance = -1.0f;

	// 最も近い移動ポイントを初期化
	XMFLOAT3 nearestPoint = XMFLOAT3();

	// 移動ポイントのリストを走査して最も近いポイントを探す
	for (const auto& point : m_MovePoints)
	{
		// 指定位置と移動ポイントの距離を計算
		float distance = StructMath::Abs(StructMath::Distance(In_Point, point));

		// 最小距離よりも小さい場合は更新
		// 0より小さい場合は初回なので更新
		if (distance < minDistance || minDistance < 0.0f)
		{
			// 最小距離と最も近い移動ポイントを更新
			minDistance = distance;
			nearestPoint = point;
		}
	}

	return nearestPoint;
}

// @brief 移動ルートの作成
// @param In_CurrentPoint 現在の位置
// @param In_TargetPoint 目的地
// @return 現在位置から目的地までの移動ルート
std::vector<XMFLOAT3> CMovePointManager::CreateMoveRoute(const XMFLOAT3& In_CurrentPoint, const XMFLOAT3& In_TargetPoint) const
{
	std::vector<XMFLOAT3> newMovePointRoute = std::vector<XMFLOAT3>();

	// 現在位置に近い移動ポイントを取得
	XMFLOAT3 currentPointnear = NearMovePoint(In_CurrentPoint);

	// 目的地に近い移動ポイントを取得
	XMFLOAT3 targetPointnear = NearMovePoint(In_TargetPoint);

	// 現在位置から目的地の方向ベクトルを計算
	XMFLOAT3 direction = StructMath::Direction(currentPointnear, targetPointnear);

	// 現在地から目的地を結ぶ直線上にある移動ポイントをすべて取得
	for (const auto& point : m_MovePoints)
	{

	}

	// 現在位置の近くの移動ポイントをルートの最初に追加
	newMovePointRoute.push_back(currentPointnear);


	// 目的地の近くの移動ポイントをルートの最後に追加
	newMovePointRoute.push_back(targetPointnear);

	return newMovePointRoute;
}
