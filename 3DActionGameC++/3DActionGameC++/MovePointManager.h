/*
* @file MovePointManager.h
* @brief 移動ポイント管理クラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/14 移動ポイント管理クラスの作成
*/

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
	void CreateData(FieldType In_Type);

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

