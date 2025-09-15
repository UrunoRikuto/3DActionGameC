/*=====================================================================
* @file MovePointManager.h
* @brief 移動ポイント管理クラスのヘッダーファイル
=====================================================================*/

#pragma once

/* システム・要素のインクルード */
#include <vector>
#include <memory>
#include "Enums.h"
#include "StructMath.h"
#include "Model.h"

/// <summary>
/// 移動ポイント管理クラス
/// </summary>
class CMovePointManager
{
private:
	/// <summary>
	/// 管理クラスのインスタンス
	/// </summary>
	static std::unique_ptr<CMovePointManager> m_pInstance;
public:
	
	/// <summary>
	/// 移動ポイントとインスタンスの作成
	/// </summary>
	/// <param name="In_Type">フィールドの種類</param>
	void CreateData(StageType In_Type);

	/// <summary>
	/// インスタンスを取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static CMovePointManager* GetInstance(void);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CMovePointManager();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CMovePointManager();

	/// <summary>
	/// デバック描画処理
	/// </summary>
	void DebugDraw(void);

	/// <summary>
	/// 近くの移動ポイントを取得
	/// </summary>
	/// <param name="In_Point">指定位置</param>
	/// <returns>指定位置の近くの移動ポイント</returns>
	XMFLOAT3 NearMovePoint(const XMFLOAT3& In_Point) const;

	/// <summary>
	/// 指定方向に限定した近くの移動ポイントを取得
	/// </summary>
	/// <param name="In_Point">指定位置</param>
	/// <param name="In_Dir">指定方向</param>
	/// <returns>指定方向に限定した近くの移動ポイント</returns>
	XMFLOAT3 NearMovePointDir(const XMFLOAT3& In_Point, const XMFLOAT3& In_Dir) const;

	/// <summary>
	/// 移動ルートの作成
	/// </summary>
	/// <param name="In_CurrentPoint">現在の位置</param>
	/// <param name="In_TargetPoint">目的地</param>
	/// <returns>現在位置から目的地までの移動ルート</returns>
	std::vector<XMFLOAT3> CreateMoveRoute(const XMFLOAT3& In_CurrentPoint, const XMFLOAT3& In_TargetPoint) const;

private:

	/// <summary>
	/// 点と線分の距離を計算
	/// </summary>
	/// <param name="In_Point">点</param>
	/// <param name="In_SegmentStart">線分の開始点</param>
	/// <param name="In_SegmentEnd">線分の最終点</param>
	/// <returns>点と線分の距離</returns>
	float DistancePointSegment(const XMFLOAT3& In_Point, const XMFLOAT3& In_SegmentStart, const XMFLOAT3& In_SegmentEnd) const;

private:
	/// <summary>
	/// 移動ポイントの座標
	/// </summary>
	std::vector<XMFLOAT3> m_MovePoints;

	/// <summary>
	/// 移動ポイントのモデル
	/// </summary>
	std::vector<std::unique_ptr<Model>> m_pMovePointModels;

public:// アクセサ
	/// <summary>
	/// 移動ポイントの座標を取得
	/// </summary>
	/// <returns>移動ポイントの座標</returns>
	const std::vector<XMFLOAT3>& GetMovePoints(void) const { return m_MovePoints; }
};

