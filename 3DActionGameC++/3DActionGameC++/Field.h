/*
* @file Field.h
* @brief フィールドオブジェクトのクラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの作成
*/
#pragma once

/* 基底クラスのインクルード */
#include "GameObject.h"

/* 前方宣言 */
class Model;

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
	/// 描画処理
	/// </summary>
	void Draw(void) override;

private:
	// モデルのポインタ
	std::unique_ptr<Model> m_pModel; // フィールドのモデル
};

