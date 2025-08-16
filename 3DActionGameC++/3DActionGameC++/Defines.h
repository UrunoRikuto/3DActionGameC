/*
* @file Defines.h
* @brief 定数やマクロの定義ファイル
* @author 宇留野陸斗
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <assert.h>
#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>

#include <DirectXMath.h>

static const int FPS = 60;
static const float fFPS = static_cast<float>(FPS);

//ファイルパス
#define ASSET_PATH(path) ("Assets/" path)
#define MODEL_PATH(path) (ASSET_PATH("Model/" path))
#define TEXTURE_PATH(path) (ASSET_PATH("Texture/" path))

// 3D空間定義
#define CMETER(value) (value * 0.01f)
#define METER(value) (value * 1.0f)
#define MSEC(value) (value / fFPS)
#define CMSEC(value) MSEC(CMETER(value))

#define PI (3.1415f)
#define TORAD(deg) ((deg / 180) * PI)
#define TODEG(rad) ((rad / PI) * 180)

static const float GRAVITY = 0.28f;

// タイトル
static const char* APP_TITLE = "3DActionGame";

// 画面サイズ
static const int SCREEN_WIDTH	= 1920;
static const int SCREEN_HEIGHT	= 1080;

// ヌルチェック
template<typename T>
inline bool SafeNullCheck(T* p)
{
	if (p == nullptr)
	{
		assert(p != nullptr && "ポインタがnullptrです。");
		return false;
	}
	return true;
}

//メモリ開放
#define SAFE_DELETE(p)			do{if(p){delete p; p = nullptr;}}while(0)
#define SAFE_DELETE_ARRAY(p)	do{if(p){delete[] p; p = nullptr;}}while(0)
#define SAFE_RELEASE(p)			do{if(p){p->Release(); p = nullptr;}}while(0)
#define SAFE_NULLPTR(p)			do{if(p){p = nullptr;}}while(0)

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

/* ゲームの値 */
namespace GameValue
{
	// プレイヤーの値
	namespace Player
	{
		// プレイヤーの行動モード
		namespace MoveAction
		{
			// 移動速度
			constexpr float MOVE_SPEED = 0.5f;
			// 回転速度
			constexpr float ROTATION_SPEED = 1.0f;
			// ジャンプの最大高さ
			constexpr float JUMP_HEIGHT = 5.0f;
			// ジャンプの総フレーム数
			constexpr int	JUMP_DURATION = 45;
		}
		// プレイヤーの狙撃モード
		namespace SnipingAction
		{
			// 垂直方向の視点移動速度
			constexpr float LOOK_SPEED_VERTICAL = 0.5f;
			// 水平方向の視点移動速度
			constexpr float LOOK_SPEED_HORIZONTAL = 0.5f;
			// 倍率変更値
			constexpr float ZOOM_POWER = 0.1f;
		}
	}

	namespace Bullet
	{
		// 弾の生存時間
		constexpr float LIFE_TIME = 5.0f; // 秒
	}

	// NPCの値
	namespace Npc
	{
	}

	// フィールドの値
	namespace Field
	{
		// フィールドのサイズ
		constexpr float FIELD_SIZE = 100.0f;
	}

	// 当たり判定の値
	namespace Collision
	{
		// 衝突チェックの対象検出距離
		constexpr float DETECT_DISTANCE = 10.0f;
	}
}

/* 入力キー */
namespace InputKey
{
	// プレイヤーの入力キー
	namespace Player
	{
		// 行動モード切り替え
		constexpr BYTE CHANGE_ACTIONMODE
			= 'F';

		// 移動モードの入力キー
		namespace MoveAction
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
			// 視点 左回転
			constexpr BYTE LOOK_LEFT
				= VK_LEFT;
			// 視点 右回転
			constexpr BYTE LOOK_RIGHT
				= VK_RIGHT;
		}
		// 狙撃モードの入力キー
		namespace SnipingAction
		{
			// 視点 上回転
			constexpr BYTE SNIPING_LOOK_UP
				= 'W';
			// 視点 下回転
			constexpr BYTE SNIPING_LOOK_DOWN
				= 'S';
			// 視点 左回転
			constexpr BYTE SNIPING_LOOK_LEFT
				= 'A';
			// 視点 右回転
			constexpr BYTE SNIPING_LOOK_RIGHT
				= 'D';
			// 視点 ズームイン
			constexpr BYTE SNIPING_ZOOM_IN
				= VK_UP;
			// 視点 ズームアウト
			constexpr BYTE SNIPING_ZOOM_OUT
				= VK_DOWN;
			// 動作 射撃
			constexpr BYTE SNIPING_SHOOT
				= VK_RETURN;
		}
	}
}

#endif // __DEFINES_H__