/*
* @file Player.cpp
* @brief プレイヤークラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*                  移動処理の追加
*                  視点移動処理の追加
*            08/05 ジャンプ処理の追加
*/

/* ヘッダーで利用するシステム・要素のインクルード */

/* ヘッダーのインクルード */
#include "Player.h"
/* システム・要素のインクルード */
#include "Model.h"
#include "Defines.h"
#include "Main.h"
#include "ModelDrawSetting.h"
#include "Camera.h"
#include "Input.h"

// @brief コンストラクタ
CPlayer::CPlayer()
	:CGameObject()// 基底クラスのコンストラクタを呼び出す
	, m_tMovePower(0.0f, 0.0f, 0.0f)	// 初期移動量
	, m_bGround(true) // 地面にいるかどうかの初期値
	, m_bJumping(false) // ジャンプ中かどうかの初期値
	, m_nJumpFrame(0) // ジャンプフレームの初期値
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("Player.obj"), 0.1f))
	{
		MessageBox(NULL, "プレイヤーモデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 位置、スケール、回転の設定
	m_tScale = { 20.0f, 20.0f, 20.0f };
	m_tPosition = { 0.0f, m_tScale.y / 2, 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// 当たり判定の設定
	m_tCollisionInfo.type = Collision::eBox;	 // 当たり判定の種類をボックスに設定
	m_tCollisionInfo.box.center = m_tPosition;	 // 中心位置をプレイヤーの位置に設定
	m_tCollisionInfo.box.size = StructMath::Mul(m_tScale,0.1f);		 // ボックスの大きさを設定
}

// @brief デストラクタ
CPlayer::~CPlayer()
{

}

// @brief 更新処理
void CPlayer::Update(void)
{
	// 視点の移動処理
	LookRotation();
	// 移動処理
	Move();
	// 跳躍処理
	Jump();
	// カメラの更新処理
	Camera::GetInstance()->Update(m_tPosition, m_tRotation);
	// 当たり判定の更新
	m_tCollisionInfo.box.center = m_tPosition; // 当たり判定の中心位置を更新
}

// @brief 描画処理
void CPlayer::Draw(void)
{
	SetRender3D();
	// 当たり判定の描画
	Collision::DrawCollision(m_tCollisionInfo);

	// モデルの描画
	CreateObject(
		m_tPosition,        // 位置
		m_tScale,			// スケール
		m_tRotation,		// 回転
		m_pModel.get(),			// モデルポインタ
		Camera::GetInstance(), // カメラポインタ
		true,					// 明るくするかどうか
		XMFLOAT3(0.5f, 0.5f, 0.5f)// 色
	);
}

// @brief 移動処理
void CPlayer::Move(void)
{
	// 前
	if(IsKeyPress('W'))
	{
		m_tMovePower.x += PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z += PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// 後
	if (IsKeyPress('S'))
	{
		m_tMovePower.x -= PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z -= PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// 左
	if (IsKeyPress('A'))
	{
		m_tMovePower.x -= PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z += PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}
	// 右
	if (IsKeyPress('D'))
	{
		m_tMovePower.x += PLAYER_MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z -= PLAYER_MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}

	// 移動量を適用
	m_tPosition = StructMath::Add(m_tPosition, m_tMovePower);
	// 移動量をリセット
	m_tMovePower = { 0.0f, 0.0f, 0.0f }; 
}

// @brief 跳躍処理
void CPlayer::Jump(void)
{
	// スペースキーが押されたら
	if (IsKeyTrigger(VK_SPACE) && m_bGround) 
	{
		// ジャンプ中フラグを立てる
		m_bJumping = true; 
		// ジャンプフレームをリセット
		m_nJumpFrame = 0;
		// 地面にいない状態にする
		m_bGround = false;
	}
	// ジャンプ中の処理
	if (m_bJumping) 
	{
		// sin波を使ってジャンプの高さを計算
		float rad = (PI * m_nJumpFrame) / PLAYER_JUMP_DURATION;  // πラジアンを使った滑らかなカーブ
		// ジャンプの高さを計算
		m_tPosition.y = (sin(rad) * PLAYER_JUMP_HEIGHT) + m_fUnderHeight;

		// ジャンプフレームを進める
		m_nJumpFrame++;

		// ジャンプの総フレーム数に達したら
		if (m_nJumpFrame >= PLAYER_JUMP_DURATION) 
		{
			// 地面の高さに戻す
			m_tPosition.y = m_fUnderHeight;
			// ジャンプ中フラグを下ろす
			m_bJumping = false;
			// 地面にいる状態にする
			m_bGround = true;
		}
	}
	// 地面にいる場合は高さを0にする
	else if(m_bGround)
	{
		m_tPosition.y = m_fUnderHeight;
	}
}

// @brief 視点移動
void CPlayer::LookRotation(void)
{
	if (IsKeyPress(VK_LEFT))
	{
		m_tRotation.y -= PLAYER_ROTATION_SPEED; // 左向き
	}
	if (IsKeyPress(VK_RIGHT))
	{
		m_tRotation.y += PLAYER_ROTATION_SPEED; // 右向き
	}
}
