#pragma once
#include <Windows.h>

class MouseInput
{
public:
	enum class MouseButton
	{
		Left,
		Right,
		Middle
	};

	enum class MouseMove
	{
		Up,
		Down,
		Left,
		Right
	};

	// @brief マウスの初期化
	static void Init(void);

	// @brief マウスの更新処理
	static void Update(void);

	// @brief マウスのボタンが押されているか
	// @param In_Type マウスのボタンの種類
	static bool IsPress(MouseButton In_Type);

	// @brief マウスのボタンが押された瞬間か
	// @param In_Type マウスのボタンの種類
	static bool IsTrigger(MouseButton In_Type);

	// @brief マウスのボタンが離された瞬間か
	// @param In_Type マウスのボタンの種類
	static bool IsRelease(MouseButton In_Type);

	// @brief マウスが移動したか
	// @param In_Type マウスの移動方向
	static bool IsMove(MouseMove In_Type);
private:
	static POINT m_CenterMousePos;
	static POINT m_CurrentMousePos;
};