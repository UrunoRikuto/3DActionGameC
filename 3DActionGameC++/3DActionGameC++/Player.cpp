/*
* @file Player.cpp
* @brief プレイヤークラスのCppファイル
* @author 宇留野陸斗
* @date 2025/08/04 クラスの実装
*                  移動処理の追加
*                  視点移動処理の追加
*            08/05 ジャンプ処理の追加
*            08/07 プレイヤーの行動モードの実装
*                  操作キーをDefines.hで一括管理化
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
	, m_eActionMode(PlayerActionMode::Move) // プレイヤーの行動モードを移動モードに設定
	, m_tMovePower(0.0f, 0.0f, 0.0f)	// 初期移動量
	, m_bGround(true) // 地面にいるかどうかの初期値
	, m_bJumping(false) // ジャンプ中かどうかの初期値
	, m_nJumpFrame(GameValue::Player::MoveAction::JUMP_DURATION) // ジャンプフレームの初期値
	, m_fUnderHeight(0.0f) // プレイヤーの真下の地面の高さの初期値
	, m_fSnipingZoom(-1.0f) // 狙撃モードのズーム倍率の初期値
{
	// モデルの生成
	m_pModel = std::make_unique<Model>();
	// モデルの読み込み
	if (!m_pModel->Load(MODEL_PATH("Player.obj")))
	{
		MessageBox(NULL, "プレイヤーモデルの読み込みに失敗しました。", "Error", MB_OK);
	}

	// 位置、補正高さ、スケール、回転の設定
	m_tScale = { 2.0f, 2.0f, 2.0f };
	m_fAjustPositionY = (m_tScale.y * 2) / 2.0f; // プレイヤーの真下の地面の高さを設定
	m_tPosition = { 0.0f, m_fAjustPositionY, 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// レイの生成
	m_pRay = std::make_unique<CRay>();
	m_pRay->SetParam(m_tPosition, XMFLOAT3(0.0f, -1.0f, 0.0f)); // レイの始点と方向を設定

	// 当たり判定の設定
	// 当たり判定情報のサイズを1に設定
	m_tCollisionInfos.resize(1);
	// 当たり判定の種類を設定
	m_tCollisionInfos[0].type = Collision::eBox;
	// タグを追加
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Player);
	// 中心位置を設定
	m_tCollisionInfos[0].box.center = m_tPosition;
	// ボックスの大きさを設定
	m_tCollisionInfos[0].box.size = StructMath::Add(m_tScale, XMFLOAT3(0.0f, m_tScale.y * 2, 0.0f));
}

// @brief デストラクタ
CPlayer::~CPlayer()
{

}

// @brief 更新処理
void CPlayer::Update(void)
{
	m_tOldPosition = m_tPosition; // 現在の位置を前の位置として保存
	// 行動モードの切り替え処理
	ChangeActionMode();

	// プレイヤーの行動モードによって更新処理を分岐
	switch (m_eActionMode)
	{
	case PlayerActionMode::Move: // 移動モード
		MA_Update();
		break;
	case PlayerActionMode::Sniping: // 狙撃モード
		SA_Update();
		break;
	}
}

// @brief 描画処理
void CPlayer::Draw(void)
{
	switch (m_eActionMode)
	{
	case PlayerActionMode::Move:
		SetRender3D();

#ifdef _DEBUG
		// 当たり判定の描画
		for (const auto& collisionInfo : m_tCollisionInfos)
		{
			Collision::DrawCollision(collisionInfo); // 当たり判定の描画（デバッグ用）
		}
#endif // _DEBUG

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
		break;
	case PlayerActionMode::Sniping:
		break;
	}
}

// @brief プレイヤーの真下の地面の高さを設定する
// @param height プレイヤーの真下の地面の高さ
void CPlayer::SetUnderHeight(float height)
{
	if (m_fUnderHeight - m_fAjustPositionY != height )
	{
		m_fUnderHeight = height + m_fAjustPositionY; 
		m_bGround = false;
	}
}

// @brief 当たり判定の衝突時の処理
// @param InCollisionInfo 衝突対象
void CPlayer::Hit(const Collision::Info& InCollisionInfo)
{
	for (auto& tag : InCollisionInfo.tag)
	{
		switch (tag)
		{
		case Collision::Tag::Field:
			if (InCollisionInfo.box.center.y - m_tPosition.y > -0.1f)
			{
				m_tPosition = m_tOldPosition; // プレイヤーの位置を前の位置に戻す
				m_pRay->SetOrigin(m_tPosition); // レイの位置を更新
				m_tCollisionInfos[0].box.center = m_tPosition; // 当たり判定の中心位置を更新
				Camera::GetInstance()->Update(m_tPosition,m_tRotation); // カメラの位置を更新
			}
			break;
		}
	}
}

// @brief 行動モードの切り替え
void CPlayer::ChangeActionMode(void)
{
	using namespace InputKey::Player;
	// 行動モードの切り替えキーが押されたら
	if (IsKeyTrigger(CHANGE_ACTIONMODE))
	{
		switch (m_eActionMode)
		{
		case PlayerActionMode::Move:
			// 移動モードから狙撃モードに切り替え
			m_eActionMode = PlayerActionMode::Sniping;
			// 狙撃モードのズーム倍率を設定
			m_fSnipingZoom = 1.0f;
			// カメラの視野角を狙撃モードに設定
			Camera::GetInstance()->SetFov(1.0f);
			break;
		case PlayerActionMode::Sniping:
			// 狙撃モードから移動モードに切り替え
			m_eActionMode = PlayerActionMode::Move;
			// カメラの視野角を移動モードに設定
			Camera::GetInstance()->SetFov(20.0f);
			// プレイヤーの回転をリセット
			m_tRotation = StructMath::FtoF3(0.0f);
			break;
		}
	}
}

// @brief 移動アクションの更新処理
void CPlayer::MA_Update(void)
{
	// 視点の移動処理
	MA_LookRotation();
	// 移動処理
	MA_Move();
	// 跳躍処理
	MA_Jump();
	// カメラの更新処理
	Camera::GetInstance()->Update(m_tPosition, m_tRotation);
	// 当たり判定の更新
	m_tCollisionInfos[0].box.center = m_tPosition; // 当たり判定の中心位置を更新
	// レイの更新
	m_pRay->SetOrigin(m_tPosition); // レイの位置を更新
}

// @brief 移動アクションの移動処理
void CPlayer::MA_Move(void)
{
	// 名前空間の使用宣言
	using namespace InputKey::Player::MoveAction;
	using namespace GameValue::Player::MoveAction;

	// 前
	if(IsKeyPress(MOVE_FORWARD))
	{
		m_tMovePower.x += MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z += MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// 後
	if (IsKeyPress(MOVE_BACKWARD))
	{
		m_tMovePower.x -= MOVE_SPEED * sinf(TORAD(m_tRotation.y));
		m_tMovePower.z -= MOVE_SPEED * cosf(TORAD(m_tRotation.y));
	}
	// 左
	if (IsKeyPress(MOVE_LEFT))
	{
		m_tMovePower.x -= MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z += MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}
	// 右
	if (IsKeyPress(MOVE_RIGHT))
	{
		m_tMovePower.x += MOVE_SPEED * cosf(TORAD(m_tRotation.y));
		m_tMovePower.z -= MOVE_SPEED * sinf(TORAD(m_tRotation.y));
	}

	// 移動量を適用
	m_tPosition = StructMath::Add(m_tPosition, m_tMovePower);
	// 移動量をリセット
	m_tMovePower = { 0.0f, 0.0f, 0.0f }; 
}

// @brief 移動アクションの跳躍処理
void CPlayer::MA_Jump(void)
{
	// 名前空間の使用宣言
	using namespace InputKey::Player::MoveAction;
	using namespace GameValue::Player::MoveAction;

	// スペースキーが押されたら
	if (IsKeyTrigger(JUMP) && m_bGround)
	{
		// ジャンプ中フラグを立てる
		m_bJumping = true; 
		// ジャンプフレームをリセット
		m_nJumpFrame = 0;
		// 地面にいない状態にする
		m_bGround = false;
		// プレイヤーの真下の地面の高さを保存
		m_fBeforeJumpUnderHeight = m_fUnderHeight;
	}

	// ジャンプ中の処理
	if (m_bJumping) 
	{
		// sin波を使ってジャンプの高さを計算
		float rad = (PI * m_nJumpFrame) / JUMP_DURATION;  // πラジアンを使った滑らかなカーブ
		// ジャンプの高さを計算
		m_tPosition.y = (sin(rad) * JUMP_HEIGHT) + m_fBeforeJumpUnderHeight + m_fAjustPositionY;

		// ジャンプフレームを進める
		m_nJumpFrame++;

		// ジャンプの総フレーム数に達したら
		if (m_nJumpFrame >= JUMP_DURATION || m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
		{
			m_nJumpFrame = JUMP_DURATION; // ジャンプフレームを最大値に設定
			// ジャンプ中フラグを下ろす
			m_bJumping = false;
		}
	}
	// 地面にいる場合は高さを0にする
	if(m_bGround)
	{
		m_tPosition.y = m_fUnderHeight + m_fAjustPositionY;
	}
	else
	{
		if (m_tPosition.y >= m_fUnderHeight + m_fAjustPositionY)
		{
			if (m_nJumpFrame >= JUMP_DURATION / 2)
			{
				m_tPosition.y -= GRAVITY; // 重力を適用
				if (m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
				{
					m_tPosition.y = m_fUnderHeight + m_fAjustPositionY; // 地面の高さに合わせる
					m_bGround = true; // 地面にいる状態にする
				}
			}
		}
		else if(m_tPosition.y < m_fUnderHeight + m_fAjustPositionY)
		{
			m_tPosition.y += 0.2f; // 地面の高さに合わせる
			if (m_tPosition.y > m_fUnderHeight + m_fAjustPositionY)
			{
				m_tPosition.y = m_fUnderHeight + m_fAjustPositionY; // 地面の高さに合わせる
				m_bGround = true; // 地面にいる状態にする
			}
		}
	}
}

// @brief 移動アクションの視点移動
void CPlayer::MA_LookRotation(void)
{
	// 名前空間の使用宣言
	using namespace InputKey::Player::MoveAction;
	using namespace GameValue::Player::MoveAction;
	// 左回転
	if (IsKeyPress(LOOK_LEFT))
	{
		m_tRotation.y -= ROTATION_SPEED;
	}
	// 右回転
	if (IsKeyPress(LOOK_RIGHT))
	{
		m_tRotation.y += ROTATION_SPEED; // 右向き
	}
}

// @brief 狙撃モードの更新処理
void CPlayer::SA_Update(void)
{
	// ズームアクションの処理
	SA_ZoomAction();
	// 視点の移動処理
	SA_LookRotation();
}

// @brief 狙撃モードの視点移動
void CPlayer::SA_LookRotation(void)
{
	// 名前空間の使用宣言
	using namespace InputKey::Player::SnipingAction;
	using namespace GameValue::Player::SnipingAction;

	if (IsKeyPress(SNIPING_LOOK_LEFT))
	{
		m_tRotation.y -= LOOK_SPEED_HORIZONTAL; // 左向き
	}
	if (IsKeyPress(SNIPING_LOOK_RIGHT))
	{
		m_tRotation.y += LOOK_SPEED_HORIZONTAL; // 右向き
	}
	if (IsKeyPress(SNIPING_LOOK_UP))
	{
		m_tRotation.x -= LOOK_SPEED_VERTICAL; // 上向き
	}
	if (IsKeyPress(SNIPING_LOOK_DOWN))
	{
		m_tRotation.x += LOOK_SPEED_VERTICAL; // 下向き
	}

	// カメラの視点位置を計算
	XMFLOAT3 CameraLookPos = XMFLOAT3(
		m_tPosition.x + sinf(TORAD(m_tRotation.y)) * (m_fSnipingZoom * 10.0f),
		m_tPosition.y,
		m_tPosition.z + cosf(TORAD(m_tRotation.y)) * (m_fSnipingZoom * 10.0f)
	);

	// カメラの更新処理
	Camera::GetInstance()->Update(CameraLookPos, m_tRotation);
}

// @brief 狙撃モードの倍率を変更
void CPlayer::SA_ZoomAction(void)
{
	// 名前空間の使用宣言
	using namespace InputKey::Player::SnipingAction;
	using namespace GameValue::Player::SnipingAction;

	if (IsKeyPress(SNIPING_ZOOM_IN)) //ズームイン
	{
		m_fSnipingZoom += ZOOM_POWER;
	}
	if (IsKeyPress(SNIPING_ZOOM_OUT)) //ズームアウト
	{
		m_fSnipingZoom -= ZOOM_POWER;
	}
	// ズーム倍率の制限
	//(仮)武器ごとにズーム制限を作成する
	//(仮)1.0f以上5.0f以下に制限
	if (m_fSnipingZoom < 1.0f)
	{
		m_fSnipingZoom = 1.0f; // 最小ズーム倍率
	}
	else if (m_fSnipingZoom > 10.0f)
	{
		m_fSnipingZoom = 10.0f; // 最大ズーム倍率
	}
}
