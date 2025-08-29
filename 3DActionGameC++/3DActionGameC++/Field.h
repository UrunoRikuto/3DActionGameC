/*=====================================================================
* @file Field.h
* @brief フィールドオブジェクトのヘッダーファイル
=====================================================================*/
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
