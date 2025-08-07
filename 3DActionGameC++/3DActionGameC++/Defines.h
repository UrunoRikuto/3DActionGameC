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

//メモリ開放
#define SAFE_DELETE(p)			do{if(p){delete p; p = nullptr;}}while(0)
#define SAFE_DELETE_ARRAY(p)	do{if(p){delete[] p; p = nullptr;}}while(0)
#define SAFE_RELEASE(p)			do{if(p){p->Release(); p = nullptr;}}while(0)
#define SAFE_NULLPTR(p)			do{if(p){p = nullptr;}}while(0)

/* ゲームの値 */
namespace GameValue
{
	// プレイヤーの値
	namespace Player
	{
		// プレイヤーの行動モード
		namespace MoveAction
		{
			constexpr float MOVE_SPEED = 0.5f;		// 移動速度
			constexpr float ROTATION_SPEED = 1.0f;	// 回転速度
			constexpr float JUMP_HEIGHT = 3.0f;		// ジャンプの最大高さ
			constexpr int	JUMP_DURATION = 45;		// ジャンプの総フレーム数
		}
		// プレイヤーの狙撃モード
		namespace SnipingAction
		{
			constexpr float LOOK_SPEED_VERTICAL = 0.5f;		// 垂直方向の視点移動速度
			constexpr float LOOK_SPEED_HORIZONTAL = 0.5f;	// 水平方向の視点移動速度
			constexpr float ZOOM_POWER = 1.0f;				// 倍率変更値
		}
	}

	// フィールドの値
	namespace Field
	{
		constexpr float FIELD_SIZE = 1000.0f;	// フィールドのサイズ
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
			// 前進
			constexpr BYTE MOVE_FORWARD
				= 'W';
			// 後退
			constexpr BYTE MOVE_BACKWARD
				= 'S';
			// 左移動
			constexpr BYTE MOVE_LEFT
				= 'A';
			// 右移動
			constexpr BYTE MOVE_RIGHT
				= 'D';
			// ジャンプ
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
			// 狙撃モードの視点 上回転
			constexpr BYTE SNIPING_LOOK_UP
				= 'W';
			// 狙撃モードの視点 下回転
			constexpr BYTE SNIPING_LOOK_DOWN
				= 'S';
			// 狙撃モードの視点 左回転
			constexpr BYTE SNIPING_LOOK_LEFT
				= 'A';
			// 狙撃モードの視点 右回転
			constexpr BYTE SNIPING_LOOK_RIGHT
				= 'D';
			// 狙撃モードの視点 ズームイン
			constexpr BYTE SNIPING_ZOOM_IN
				= VK_UP;
			// 狙撃モードの視点 ズームアウト
			constexpr BYTE SNIPING_ZOOM_OUT
				= VK_DOWN;
		}
	}
}

#endif // __DEFINES_H__