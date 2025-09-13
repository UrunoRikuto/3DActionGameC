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
#include "SceneGame.h"
#include "GameObject.h"
#include <list>

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

// @brief 指定方向に限定した近くの移動ポイントを取得
// @param In_Point 指定位置
// @param In_Dir 指定方向
// @return 指定方向に限定した近くの移動ポイント
XMFLOAT3 CMovePointManager::NearMovePointDir(const XMFLOAT3& In_Point, const XMFLOAT3& In_Dir) const
{
	// 最小距離を初期化
	float minDistance = -1.0f;

	// 最も近い移動ポイントを初期化
	XMFLOAT3 nearestPoint = XMFLOAT3();

	// 移動ポイントのリストを走査して最も近いポイントを探す
	for (const auto& point : m_MovePoints)
	{
		// 移動ポイントが指定方向にあるかどうかを判定
		XMFLOAT3 dirToPoint = StructMath::Sub(point, In_Point);
		if (StructMath::Dot(dirToPoint, In_Dir) < 0.0f)continue;

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
	// 名前空間の使用
	using namespace StructMath;
	using namespace GameValue::MoveSystem;

	std::vector<XMFLOAT3> newMovePointRoute = std::vector<XMFLOAT3>();

	// 現在位置に近い移動ポイントを取得
	XMFLOAT3 currentPointnear = NearMovePoint(In_CurrentPoint);

	// 目的地に近い移動ポイントを取得
	XMFLOAT3 targetPointnear = NearMovePoint(In_TargetPoint);

	//(仮)実装完了までの繋ぎ
	newMovePointRoute.push_back(currentPointnear);
	newMovePointRoute.push_back(targetPointnear);
	return newMovePointRoute;

	// 実装メモ
	// 
	// １．現在位置を参照位置として初期保存
	// ２．参照位置と目的地を結ぶ線分を作成
	// ３．線分上に障害物が被っているかどうかをチェック
	//  ┗─ 障害物の当たり判定を取得して当たり判定に線分が被っているかどうかをチェック
	// ４．被っていない場合は目的地をルートに追加して終了
	// ５．被っている場合は障害物を避けるように移動ポイントをルートに追加
	//	┗─ DistancePointSegment(A,B,C); // Aが点、BとCが線分の両端
	//		 ┗─ 戻り値が点と線分の距離
	// ６．追加した移動ポイントを参照位置として再度２に戻る

}

// @brief 点と線分の距離を計算
// @param In_Point 点
// @param In_SegmentStart 線分の開始点
// @param In_SegmentEnd 線分の最終点
float CMovePointManager::DistancePointSegment(const XMFLOAT3& In_Point, const XMFLOAT3& In_SegmentStart, const XMFLOAT3& In_SegmentEnd) const
{
	// 名前空間の使用
	using namespace StructMath;

	// 線分のベクトル
	XMFLOAT3 segVec = Sub(In_SegmentEnd, In_SegmentStart);
	XMFLOAT3 StartToPoint = Sub(In_Point, In_SegmentStart);

	float ab2 = Dot(segVec, segVec);
	// AとBが同じ点
	if (ab2 == 0.0f)return Length(StartToPoint);

	float t = Dot(StartToPoint, segVec) / ab2;

	if (t < 0.0f)
	{
		// 線分の開始点が最も近い場合
		return Length(StartToPoint);
	}
	else if (t > 1.0f)
	{
		// 線分の終了点が最も近い場合
		return Length(Sub(In_Point, In_SegmentEnd));
	}


	// 線分上の点が最も近い場合
	XMFLOAT3 projection = Add(In_SegmentStart, Mul(segVec, FtoF3(t)));
	return Length(Sub(In_Point, projection));
}
