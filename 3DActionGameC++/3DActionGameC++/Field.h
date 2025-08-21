/*
* @file Field.h
* @brief フィールドオブジェクトのクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの作成
*/
#pragma once

/* 基底クラスのインクルード */
#include "GameObject.h"

/// <summary>
/// フィールドオブジェクトのクラス
/// </summary>
class CField : public CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CField();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CField();
	
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// 当たり判定の衝突時の処理
	/// </summary>
	/// <param name="InCollisionInfo">衝突対象</param>
	void Hit(const Collision::Info& InCollisionInfo) override;

};
