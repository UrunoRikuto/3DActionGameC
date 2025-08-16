/*
* @file Bullet.h
* @brief 弾丸クラスのヘッダーファイル
* @author 宇留野陸斗
* * @date 2025/08/16 クラスの定義
*/
#pragma once

/* 基底クラスのインクルード */
#include "GameObject.h"

/// <summary>
/// @brief 弾丸クラス
/// </summary>
class CBullet : public CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CBullet();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CBullet();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// パラメーターの設定
	/// </summary>
	/// <param name="direction"></param>
	/// <param name="movePower"></param>
	void SetParam(const XMFLOAT3& direction, float movePower);

	/// <summary>
	/// 当たり判定の衝突時の処理
	/// </summary>
	/// <param name="InCollisionInfo">衝突対象</param>
	void Hit(const Collision::Info& InCollisionInfo) override;

private:

	/// <summary>
	/// 進行方向
	/// </summary>
	XMFLOAT3 m_tDirection;

	/// <summary>
	/// 移動力
	/// </summary>
	float m_fMovePower;

	/// <summary>
	/// 弾の生存時間
	/// </summary>
	float m_fLifeTime;

public: // アクセサ
	/// <summary>
	/// 進行方向の取得
	/// </summary>
	/// <returns>進行方向</returns>
	const XMFLOAT3& GetDirection() const { return m_tDirection; }

	/// <summary>
	/// 移動力の取得
	/// </summary>
	const float& GetMovePower() const { return m_fMovePower; }
};

