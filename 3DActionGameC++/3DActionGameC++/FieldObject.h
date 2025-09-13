/*=====================================================================
* @file FieldObject.h
* @brief フィールドオブジェクトのヘッダーファイル
=====================================================================*/

#pragma once
#include "GameObject.h"
#include "Enums.h"

/// <summary>
/// フィールドオブジェクトのクラス
/// </summary>
class CFieldObject : public CGameObject
{
public:
	// コンストラクタ
	CFieldObject(FieldObjectType In_Type);
	// デストラクタ
	virtual ~CFieldObject();
	// 更新処理
	void Update(void) override;
	// 当たり判定の衝突時の処理
	void Hit(const Collision::Info& InCollisionInfo) override;
};

