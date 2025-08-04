/*
* @file Player.cpp
* @brief プレイヤークラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
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
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("Player.obj")))
	{
		MessageBox(NULL, "プレイヤーモデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 位置、スケール、回転の設定
	m_tScale = { 2.0f, 2.0f, 2.0f };
	m_tPosition = { 0.0f, 0.0f, 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };
}

// @brief デストラクタ
CPlayer::~CPlayer()
{

}

// @brief 更新処理
void CPlayer::Update(void)
{
	// プレイヤーの移動処理
	Move();
	// カメラの更新処理
	Camera::GetInstance()->Update(m_tPosition, m_tRotation);
}

// @brief 描画処理
void CPlayer::Draw(void)
{
	// モデルの描画
	SetRender3D();
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
		m_tMovePower.z += 0.1f;
	}
	// 後
	if (IsKeyPress('S'))
	{
		m_tMovePower.z -= 0.1f;
	}
	// 左
	if (IsKeyPress('A'))
	{
		m_tMovePower.x -= 0.1f;
	}
	// 右
	if (IsKeyPress('D'))
	{
		m_tMovePower.x += 0.1f;
	}

	// 移動量を適用
	m_tPosition = StructMath::Add(m_tPosition, m_tMovePower);

	m_tMovePower = { 0.0f, 0.0f, 0.0f }; // 移動量をリセット
}
