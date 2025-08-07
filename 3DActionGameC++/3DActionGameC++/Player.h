/*
* @file Player.h
* @brief プレイヤークラスのヘッダーファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの定義
*                  移動処理の定義
*                  視点移動処理の定義
*            08/05 ジャンプ処理の定義
*            08/07 プレイヤーの行動モードの定義
*/
#pragma once

/* システム・要素のインクルード */
#include "Enums.h"

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

	/// <summary>
	/// プレイヤーの真下の地面の高さを設定する関数
	/// </summary>
	/// <param name="height">設定するオブジェクトのY軸</param>
	void SetUnderHeight(float height) { m_fUnderHeight = height + (m_tScale.y / 2.0f); }

private:
	/// <summary>
	/// 行動モードの切り替え
	/// </summary>
	void ChangeActionMode(void);

	/// <summary>
	/// 移動アクションの更新処理
	/// </summary>
	void MA_Update(void);

	/// <summary>
	///  移動アクションの移動処理
	/// </summary>
	void MA_Move(void);

	/// <summary>
	///  移動アクションの跳躍処理
	/// </summary>
	void MA_Jump(void);

	/// <summary>
	///  移動アクションの視点移動
	/// </summary>
	void MA_LookRotation(void);


	/// <summary>
	/// 狙撃モードの更新処理
	/// </summary>
	void SA_Update(void);

	/// <summary>
	/// 狙撃モードの視点移動
	/// </summary>
	/// <param name=""></param>
	void SA_LookRotation(void);

private:
	/// <summary>
	/// プレイヤーの行動モード
	/// </summary>
	PlayerActionMode m_eActionMode;

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

	/// <summary>
	/// 真下の高さを保存する変数
	/// </summary>
	float m_fUnderHeight;
};

