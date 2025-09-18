/*=====================================================================
* @file MoveSystem.cpp
* @brief 移動システムの実装ファイル
=====================================================================*/

/* ヘッダーのインクルード */
#include "MoveSystem.h"

/* システム・要素のインクルード */
#include "Geometory.h"
#include "Main.h"

// @brief コンストラクタ
CMoveSystem::CMoveSystem(MoveSystemType In_Type, float In_MoveSpeed)
	: m_eMoveSystemType(In_Type) // 移動システムの種類を設定
	, m_fMoveSpeed(In_MoveSpeed) // 移動速度の初期化
	, m_vtMovePointList()		// 移動ポイントのリストを初期化
	, m_nCurrentPointIndex(0) // 現在の移動ポイントのインデックスを初期化
	, m_bIsEndPoint(false)
	, m_fAdjustY(0.0f) // Y座標の調整値を初期化
{
	// 移動ポイントのリストを初期化
	m_vtMovePointList.clear();
}

// @brief デストラクタ
CMoveSystem::~CMoveSystem()
{

}

// @brief 次に移動する移動ポイントを取得
// @param In_CurrentPos 現在の位置
// @return 次に移動する移動ポイント
XMFLOAT3 CMoveSystem::GetMovePoint(const XMFLOAT3& In_CurrentPos)
{
	// 移動ポイントのリストが空でない場合
	if (m_vtMovePointList.empty())
	{
		// 移動ポイントがない場合は現在位置を返す
		return In_CurrentPos;
	}

	XMFLOAT3 MoverPos = In_CurrentPos;
	XMFLOAT3 TargetPos = m_vtMovePointList[m_nCurrentPointIndex];

	//(仮)Y座標の無視{洞窟のようなものを作らない限りY座標入らない
	MoverPos.y = 0.0f;
	TargetPos.y = 0.0f;

	// 現在の位置が移動ポイントの一定距離以内にある場合
	if (StructMath::Distance(MoverPos, TargetPos) < m_fMoveSpeed)
	{
		// 次の移動ポイントに進む
		switch (m_eMoveSystemType)
		{
		case MoveSystemType::Once:
			m_nCurrentPointIndex++;
			break;
		case MoveSystemType::Loop:
			m_nCurrentPointIndex++;
			break;
		case MoveSystemType::Reverse:
			if (!m_bIsEndPoint)
			{
				m_nCurrentPointIndex++;
			}
			else
			{
				// 反転しているのでデクリメント
				m_nCurrentPointIndex--;
			}
			break;
		}
	}

	// 現在の移動ポイントのインデックスがリストのサイズを超えている場合
	if (m_nCurrentPointIndex > static_cast<int>(m_vtMovePointList.size()) - 1) 
	{
		switch (m_eMoveSystemType)
		{
		case MoveSystemType::Once:
			// 最後のポイントに設定
			m_nCurrentPointIndex = static_cast<int>(m_vtMovePointList.size()) - 1;
			// 終点フラグを立てる
			m_bIsEndPoint = true;

			// もう動かないので現在位置を返す
			return In_CurrentPos; 
			break;
		case MoveSystemType::Loop:
			// 最初のポイントに設定
			m_nCurrentPointIndex = 0;
			// 終点フラグを下ろす
			m_bIsEndPoint = false;
			break;
		case MoveSystemType::Reverse:
			// 最後のポイントに設定
			m_nCurrentPointIndex = static_cast<int>(m_vtMovePointList.size()) - 1;
			// 終点フラグを立てる
			m_bIsEndPoint = true;
			break;
		}
	}
	// 現在のポイントのインデックスが0未満の場合
	else if(m_nCurrentPointIndex < 0)
	{
		//最初のポイントに戻す
		m_nCurrentPointIndex = 0;
		// 終点フラグを下ろす
		m_bIsEndPoint = false;
	}

	// どの条件にも当てはまらない場合は現在位置を返す
	return m_vtMovePointList[m_nCurrentPointIndex];
}

// @brief 移動ポイントをリストに追加
// @param In_MovePoint 追加する位置
void CMoveSystem::AddMovePoint(const XMFLOAT3& In_MovePoint)
{
	// Y座標の調整を行う
	XMFLOAT3 AdjustedPoint = StructMath::Add(In_MovePoint, XMFLOAT3(0.0f, m_fAdjustY, 0.0f)); 

	// 移動ポイントをリストに追加
	m_vtMovePointList.push_back(AdjustedPoint);
}

// @brief 複数の移動ポイントをリストに追加
// @param In_MovePoints 追加する移動ポイントリスト(並びはそのまま)
void CMoveSystem::AddMovePoints(const std::vector<XMFLOAT3>& In_MovePoints)
{
	// Y座標の調整を行う
	std::vector<XMFLOAT3> AdjustedPoints;
	for (const auto& point : In_MovePoints)
	{
		// 各移動ポイントにY座標の調整を適用
		XMFLOAT3 adjustedPoint = StructMath::Add(point, XMFLOAT3(0.0f, m_fAdjustY, 0.0f));
		AdjustedPoints.push_back(adjustedPoint);
	}

	// 移動ポイントのリストに追加
	m_vtMovePointList.insert(m_vtMovePointList.end(), AdjustedPoints.begin(), AdjustedPoints.end());
}

// @brief 移動ポイントのリストを新しく設定
// @param In_MovePoints 設定する移動ポイントリスト
// @param In_CurrentPos 現在の位置
void CMoveSystem::SetMovePoints(const std::vector<XMFLOAT3>& In_MovePoints, const XMFLOAT3& In_CurrentPos)
{
	//Y座標の調整を行う
	std::vector<XMFLOAT3> AdjustedPoints;
	for (const auto& point : In_MovePoints)
	{
		// 各移動ポイントにY座標の調整を適用
		XMFLOAT3 adjustedPoint = StructMath::Add(point, XMFLOAT3(0.0f, m_fAdjustY, 0.0f));
		AdjustedPoints.push_back(adjustedPoint);
	}


	// 移動ポイントのリストを新しく設定
	m_vtMovePointList = AdjustedPoints;

	// 現在位置から最も近い移動ポイントを探す
	float minDistance = StructMath::Abs(StructMath::Distance(In_CurrentPos, m_vtMovePointList[0]));
	int closestIndex = 0;

	for (size_t i = 1; i < m_vtMovePointList.size(); ++i)
	{
		float distance = StructMath::Abs(StructMath::Distance(In_CurrentPos, m_vtMovePointList[i]));
		if (distance < minDistance)
		{
			minDistance = distance;
			closestIndex = static_cast<int>(i);
		}
	}

	// 最も近い移動ポイントのインデックスを現在のポイントのインデックスに設定
	m_nCurrentPointIndex = closestIndex;

	// 現在のポイントのインデックスをリセット
	m_nCurrentPointIndex = 0;
}

// @brief 移動ポイントのリストのルート復元
// @param In_CurrentPos 現在の位置
void CMoveSystem::RestorationMovePoints(XMFLOAT3 In_CurrentPos)
{
	// 変更前の移動ポイントのリストが空でない場合
	if (!m_vOldRouteMemory.MovePointList.empty())
	{
		// 移動ポイントのリストを復元
		SetMovePoints(m_vOldRouteMemory.MovePointList, In_CurrentPos);
		// 移動システムの種類を復元
		m_eMoveSystemType = m_vOldRouteMemory.MoveType;

		// 変更前の移動ポイントのリストをクリア
		m_vOldRouteMemory.MovePointList.clear();
		m_vOldRouteMemory.MoveType = MoveSystemType::Once; // デフォルト値にリセット
	}
}

// @brief 移動ポイントを復元用に保存してリストをクリア
void CMoveSystem::SaveAndClearMovePoints()
{
	// 変更前の移動ポイントのリストに現在のリストを保存
	m_vOldRouteMemory.MovePointList = m_vtMovePointList;
	// 変更前の移動システムの種類を保存
	m_vOldRouteMemory.MoveType = m_eMoveSystemType;
	// 移動ポイントのリストをクリア
	m_vtMovePointList.clear();
	// 現在のポイントのインデックスをリセット
	m_nCurrentPointIndex = 0;
	// 終点フラグを下ろす
	m_bIsEndPoint = false;
}

// @brief デバッグ描画処理(移動ルートの描画)
// @param In_Color 描画する線の色
void CMoveSystem::DebugDraw(XMFLOAT4 In_Color)
{
#ifdef _DEBUG
	SetRender3D();

	// 移動ポイントのリストが空でない場合
	if (!m_vtMovePointList.empty())
	{
		switch (m_eMoveSystemType)
		{
		case MoveSystemType::Once:
			// 移動ポイントを線で結ぶ
			for (size_t i = 0; i < m_vtMovePointList.size() - 1; ++i)
			{
				Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[i + 1], In_Color);
			}
			break;
		case MoveSystemType::Loop:
			// 移動ポイントを線で結ぶ
			for (size_t i = 0; i < m_vtMovePointList.size(); ++i)
			{
				if (i == m_vtMovePointList.size() - 1)
				{
					// 最後のポイントから最初のポイントに線を引く
					Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[0], In_Color);
				}
				else
				{
					// 移動ポイントを線で結ぶ
					Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[i + 1], In_Color);
				}
			}
			break;
		case MoveSystemType::Reverse:
			// 移動ポイントを線で結ぶ
			for (size_t i = 0; i < m_vtMovePointList.size() - 1; ++i)
			{
				Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[i + 1], In_Color);
			}
			break;
		}
	}
	// 描画を実行
	Geometory::DrawLines(); 

#endif // _DEBUG
}
