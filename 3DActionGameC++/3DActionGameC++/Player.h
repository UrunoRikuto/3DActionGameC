/*
* @file Player.h
* @brief プレイヤークラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの定義
*/
#pragma once

/* 基底クラスのインクルード */
#include "GameObject.h"

/// <summary>
/// プレイヤーのクラス
/// </summary>
class CPlayer : public CGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CPlayer();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~CPlayer();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(void) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(void) override;

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move(void);

	/// <summary>
	/// 跳躍処理
	/// </summary>
	void Jump(void);

	/// <summary>
	/// 視点移動
	/// </summary>
	void LookRotation(void);

private:
	/// <summary>
	/// プレイヤーの移動量
	/// </summary>
	XMFLOAT3 m_tMovePower;

	/// <summary>
	/// 地面に立っているかのフラグ
	/// </summary>
	bool m_bGround;

	/// <summary>
	/// ジャンプ中かどうかのフラグ
	/// </summary>
	bool m_bJumping;

	/// <summary>
	/// ジャンプの現在フレーム数
	/// </summary>
	int m_nJumpFrame;
};

