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
class CRayCastTarget;

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

private:
	/// <summary>
	/// レイキャストのターゲットオブジェクト
	/// </summary>
	std::unique_ptr<CRayCastTarget> m_pRayCastTarget;

public:// メンバ変数のアクセサ
	/// <summary>
	/// レイキャストのターゲットオブジェクトの取得
	/// </summary>
	/// <returns>レイキャストのターゲットオブジェクト</returns>
	CRayCastTarget* GetRayCastTarget() const { return m_pRayCastTarget.get(); }
};
