/*=====================================================================
* @file GameValues.h
* @brief ゲームの定数管理ファイル
=====================================================================*/

#pragma once
#include "Defines.h"
#include "Enums.h"
#include "StructMath.h"

/* モデルのパス定義 */
namespace ModelPath
{
	// 移動ポイントのモデルパス
	constexpr const char* MOVE_POINT_PATH = MODEL_PATH("Debug/MovePoint.obj");
	// ターゲットNPCのモデルパス
	constexpr const char* TARGET_NPC_PATH = MODEL_PATH("TargetNPC.obj");
	// 護衛NPCのモデルパス
	constexpr const char* GUARD_NPC_PATH = MODEL_PATH("GuardNPC.obj");
}

/* テクスチャのパス定義 */
namespace TexturePath
{
	// Hpゲージのテクスチャパス
	constexpr const char* HP_GAUGE_PATH = TEXTURE_PATH("UI/HpGauge.png");
	// 索敵ゲージのテクスチャパス
	constexpr const char* DETECTION_GAUGE_PATH = TEXTURE_PATH("UI/DetectionGauge.png");
}
/* ゲームの値 */
namespace GameValue
{
	// @brief エンティティのID
	static int Entity_ID = 0;

	// プレイヤーの値
	namespace Player
	{
		// 移動速度
		constexpr float MOVE_SPEED = 0.5f;
		// 回転速度
		constexpr float ROTATION_SPEED = 2.5f;
		// ジャンプの最大高さ
		constexpr float JUMP_HEIGHT = 5.0f;
		// ジャンプの総フレーム数
		constexpr int	JUMP_DURATION = 45;
		// 最大体力
		constexpr float MAX_HP = 100.0f;
	}

	namespace Bullet
	{
		// 弾の生存時間
		constexpr float LIFE_TIME = 5.0f; // 秒
	}

	// NPCの値
	namespace Npc
	{
		// 通常NPCの値
		namespace ArenaTarget
		{
			// 視野角
			constexpr float VIEW_ANGLE = 60.0f; // 度
			// 視野距離
			constexpr float VIEW_DISTANCE = 200.0f; // メートル
			// 体力
			constexpr float MAX_HP = 10.0f;
		}

		// ジャンプの最大高さ
		constexpr float JUMP_HEIGHT = 5.0f;
		// ジャンプの総フレーム数
		constexpr int	JUMP_DURATION = 45;
	}

	// フィールドの値
	namespace Field
	{
		// プレイヤーの生成位置
		constexpr XMFLOAT3 PLAYER_SPOWN_POINT[static_cast<int>(StageType::MAX)] =
		{
			XMFLOAT3(0.0f,0.0f,-180.0f),		// 闘技場
			XMFLOAT3(0.0f,0.0f,-180.0f),		// 草原
		};
	}

	// 当たり判定の値
	namespace Collision
	{
		// 衝突チェックの対象検出距離
		constexpr float DETECT_DISTANCE = 10.0f;
	}

	// 索敵の値
	namespace VisionSearch
	{
		// ステルス補正の値(プレイヤーの姿勢による視認距離の補正)
		namespace StealthCorrection
		{
			// 立ち姿勢の視認距離補正
			constexpr float STAND = 1.0f;
			// しゃがみ姿勢の視認距離補正
			constexpr float CROUCH = 0.8f;
			// 伏せ姿勢の視認距離補正
			constexpr float PRONE = 0.5f;
			// 潜伏姿勢の視認距離補正
			constexpr float HIDE = 0.3f;
		}

		// 索敵値が最大値になるまでの時間
		constexpr float MAX_DETECTION_TIME = 3.0f; // 秒
		// 見失うまでの時間
		constexpr float LOST_TIME = 3.0f; // 秒
		// 見失ったときの索敵値の減少率
		constexpr float LOST_DETECTION_RATE = 0.5f; // 見失ったときの索敵値の減少率

	}

	// 移動システムの値
	namespace MoveSystem
	{
		// 通過可能な幅
		constexpr float PASSABLE_RANGE = 10.0f;
	}

	// タイマーの値
	namespace Timer
	{
		// バーのサイズ
		constexpr float GAUGE_SIZE_X = 20.0f;
		constexpr float GAUGE_SIZE_Y = SCREEN_HEIGHT;
		
	}

	// テロップの値
	namespace Telop
	{
		// クエストクリアテロップの表示時間
		constexpr float RESULTTELOP_DISPLAY_TIME = 5.0f; // 秒
	}
}

/* 入力キー */
namespace InputKey
{
	// プレイヤーの入力キー
	namespace Player
	{
		// 動作 前進
		constexpr BYTE MOVE_FORWARD
			= 'W';
		// 動作 後退
		constexpr BYTE MOVE_BACKWARD
			= 'S';
		// 動作 左移動
		constexpr BYTE MOVE_LEFT
			= 'A';
		// 動作 右移動
		constexpr BYTE MOVE_RIGHT
			= 'D';
		// 動作 ジャンプ
		constexpr BYTE JUMP
			= VK_SPACE;
	}

	// クエスト選択シーンの入力キー
	namespace QuestSelect
	{
		// 決定キー
		constexpr BYTE DECIDE
			= VK_RETURN;
		// キャンセルキー
		constexpr BYTE CANCEL
			= VK_ESCAPE;
		// 次
		constexpr BYTE NEXT
			= 'D';
		// 前
		constexpr BYTE BEFORE
			= 'A';
	}

	// テロップエフェクトの入力キー
	namespace TelopEffect
	{
		// スキップキー
		constexpr BYTE SKIP
			= VK_RETURN;
	}
}