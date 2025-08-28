/*
* @file MoveSystem.h
* @brief 移動システムの定義ファイル
* @author 宇留野陸斗
* @date 2025/08/13 移動システムクラスの定義
*            08/14 Y座標の調整値を追加
*/
#pragma once

/* システム・要素のインクルード */
#include <memory>
#include <vector>
#include "StructMath.h"
#include "Enums.h"
#include "MovePointManager.h"

/// <summary>
/// 復元用の保存構造体
/// </summary>
struct MovePointListMemory
{
	std::vector<XMFLOAT3> MovePointList = {};
	MoveSystemType MoveType = MoveSystemType::Once;
};

/// <summary>
/// 移動システムクラス
/// </summary>
class CMoveSystem
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="In_Type">移動システムの種類</param>
	/// <param name="In_MoveSpeed">移動速度</param>
	CMoveSystem(MoveSystemType In_Type, float In_MoveSpeed);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CMoveSystem();

	/// <summary>
	/// デバック描画処理(移動ルートの描画)
	/// </summary>
	/// <param name="In_Color">描画する線の色</param>
	void DebugDraw(XMFLOAT4 In_Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	
	/// <summary>
	/// 移動ポイントの取得
	/// </summary>
	/// <param name="In_CurrentPos">現在の位置</param>
	/// <returns>次に移動する移動ポイント</returns>
	XMFLOAT3 GetMovePoint(const XMFLOAT3& In_CurrentPos);

	/// <summary>
	/// 移動ポイントの追加
	/// </summary>
	/// <param name="In_MovePoint">追加する移動ポイント</param>
	void AddMovePoint(const XMFLOAT3& In_MovePoint);

	/// <summary>
	/// 複数の移動ポイントを追加
	/// </summary>
	/// <param name="In_MovePoints">追加する移動ポイントリスト(並びはそのまま)</param>
	void AddMovePoints(const std::vector<XMFLOAT3>& In_MovePoints);

	/// <summary>
	/// 移動ポイントのリストを新しく設定
	/// </summary>
	/// <param name="In_MovePoints">設定する移動ポイント</param>
	/// <param name="In_CurrentPos">現在の位置</param>
	void SetMovePoints(const std::vector<XMFLOAT3>& In_MovePoints , const XMFLOAT3& In_CurrentPos);

	/// <summary>
	/// 移動ポイントのリストのルート復元
	/// </summary>
	/// <param name="In_CurrentPos">現在の位置</param>
	void RestorationMovePoints(XMFLOAT3 In_CurrentPos);

	/// <summary>
	/// 移動ポイントを復元用に保存してリストをクリア
	/// </summary>
	void SaveAndClearMovePoints();

	/// <summary>
	/// 移動ポイントのリストをクリア
	/// </summary>
	void ClearMovePoints() { m_vtMovePointList.clear(); }
private:
	/// <summary>
	/// 移動システムの種類
	/// </summary>
	MoveSystemType m_eMoveSystemType;

	/// <summary>
	/// 移動ポイントのリスト
	/// </summary>
	std::vector<XMFLOAT3> m_vtMovePointList;

	/// <summary>
	/// ルート復元用の保存
	/// </summary>
	MovePointListMemory m_vOldRouteMemory;

	/// <summary>
	/// 移動量
	/// </summary>
	float m_fMoveSpeed;

	/// <summary>
	/// 現在のポイントのインデックス
	/// </summary>
	int m_nCurrentPointIndex;

	/// <summary>
	/// 最終位置に到達したかどうかのフラグ
	/// </summary>
	bool m_bIsEndPoint;

	/// <summary>
	/// Y軸の調整値
	/// </summary>
	float m_fAdjustY;

public:// アクセサー

	/// <summary>
	/// 移動量を取得
	/// </summary>
	/// <returns>移動量</returns>
	float GetMoveSpeed() const { return m_fMoveSpeed; }

	/// <summary>
	/// 移動ポイントのリストを取得
	/// </summary>
	/// <returns>移動ポイントのリスト</returns>
	const std::vector<XMFLOAT3>& GetMovePointList() const { return m_vtMovePointList; }

	/// <summary>
	/// Y座標の調整値を取得
	/// </summary>
	/// <param name="In_AdjustY">調整値</param>
	void SetAdjustY(float In_AdjustY) { m_fAdjustY = In_AdjustY; }

	/// <summary>
	/// 移動システムの種類を設定
	/// </summary>
	/// <param name="In_Type">設定する移動システム</param>
	void SetMoveSystemType(MoveSystemType In_Type) { m_eMoveSystemType = In_Type; }
};
