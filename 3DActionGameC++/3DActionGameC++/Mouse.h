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

	// @brief �}�E�X�̏�����
	static void Init(void);

	// @brief �}�E�X�̍X�V����
	static void Update(void);

	// @brief �}�E�X�̃{�^����������Ă��邩
	// @param In_Type �}�E�X�̃{�^���̎��
	static bool IsPress(MouseButton In_Type);

	// @brief �}�E�X�̃{�^���������ꂽ�u�Ԃ�
	// @param In_Type �}�E�X�̃{�^���̎��
	static bool IsTrigger(MouseButton In_Type);

	// @brief �}�E�X�̃{�^���������ꂽ�u�Ԃ�
	// @param In_Type �}�E�X�̃{�^���̎��
	static bool IsRelease(MouseButton In_Type);

	// @brief �}�E�X���ړ�������
	// @param In_Type �}�E�X�̈ړ�����
	static bool IsMove(MouseMove In_Type);
private:
	static POINT m_CenterMousePos;
	static POINT m_CurrentMousePos;
};