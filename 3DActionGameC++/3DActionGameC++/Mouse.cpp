#include "Mouse.h"
#include "Input.h"
#include "Defines.h"

POINT MouseInput::m_CenterMousePos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
POINT MouseInput::m_CurrentMousePos = { 0,0 };

bool MouseInput::IsPress(MouseButton In_Type)
{
	switch (In_Type)
	{
	case MouseInput::MouseButton::Left:
		if (IsKeyPress(VK_LBUTTON))
		{
			return true;
		}
		break;
	case MouseInput::MouseButton::Right:
		if (IsKeyPress(VK_RBUTTON))
		{
			return true;
		}
		break;
	case MouseInput::MouseButton::Middle:
		if (IsKeyPress(VK_MBUTTON))
		{
			return true;
		}
		break;
	}

	return false;
}

bool MouseInput::IsTrigger(MouseButton In_Type)
{
	switch (In_Type)
	{
	case MouseInput::MouseButton::Left:
		if (IsKeyTrigger(VK_LBUTTON))
		{
			return true;
		}
		break;
	case MouseInput::MouseButton::Right:
		if (IsKeyTrigger(VK_RBUTTON))
		{
			return true;
		}
		break;
	case MouseInput::MouseButton::Middle:
		if (IsKeyTrigger(VK_MBUTTON))
		{
			return true;
		}
		break;
	}

	return false;
}

bool MouseInput::IsRelease(MouseButton In_Type)
{
	switch (In_Type)
	{
	case MouseInput::MouseButton::Left:
		if (IsKeyRelease(VK_LBUTTON))
		{
			return true;
		}
		break;
	case MouseInput::MouseButton::Right:
		if (IsKeyRelease(VK_RBUTTON))
		{
			return true;
		}
		break;
	case MouseInput::MouseButton::Middle:
		if (IsKeyRelease(VK_MBUTTON))
		{
			return true;
		}
		break;
	}

	return false;
}

bool MouseInput::IsMove(MouseMove In_Type)
{
	switch (In_Type)
	{
	case MouseInput::MouseMove::Up:
		if (m_CurrentMousePos.y < m_CenterMousePos.y)
		{
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			GetCursorPos(&m_CurrentMousePos);
			return true;
		}
		break;
	case MouseInput::MouseMove::Down:
		if (m_CurrentMousePos.y > m_CenterMousePos.y)
		{
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			GetCursorPos(&m_CurrentMousePos);
			return true;
		}
		break;
	case MouseInput::MouseMove::Left:
		if (m_CurrentMousePos.x < m_CenterMousePos.x)
		{
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			GetCursorPos(&m_CurrentMousePos);
			return true;
		}
		break;
	case MouseInput::MouseMove::Right:
		if (m_CurrentMousePos.x > m_CenterMousePos.x)
		{
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			GetCursorPos(&m_CurrentMousePos);
			return true;
		}
		break;
	}
	return false;
}

void MouseInput::Init(void)
{
	// マウスの位置を画面中央にリセット
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_CenterMousePos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
}

void MouseInput::Update(void)
{
	GetCursorPos(&m_CurrentMousePos);
}