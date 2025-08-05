/*
* @file GameObject.h
* @brief ゲームオブジェクトの基底クラスのhファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの作成
*                  モデルのポインタ
*                  位置情報
*                  スケール情報
*                  回転情報の追加
*            08/05 当たり判定情報
*/
#pragma once

#include <memory>
#include "StructMath.h"
#include "Collision.h"

/* 前方宣言 */
class Model;

/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>
class CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CGameObject();
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CGameObject();

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw();

protected:
	/// <summary>
	/// モデルのポインタ
	/// </summary>
	std::unique_ptr<Model> m_pModel;

	/// <summary>
	/// 当たり判定情報
	/// </summary>
	Collision::Info m_tCollisionInfo;

	/// <summary>
	/// 位置情報
	///	</summary>
	XMFLOAT3 m_tPosition;

	/// <summary>
	/// 大きさ情報
	/// </summary>
	XMFLOAT3 m_tScale;

	/// <summary>
	/// 回転情報
	/// </summary>
	XMFLOAT3 m_tRotation;
};

