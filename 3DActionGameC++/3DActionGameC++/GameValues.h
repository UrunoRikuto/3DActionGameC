/*=====================================================================
* @file GameValues.h
* @brief �Q�[���̒萔�Ǘ��t�@�C��
=====================================================================*/

#pragma once
#include "Defines.h"

/* ���f���̃p�X��` */
namespace ModelPath
{
	// �ړ��|�C���g�̃��f���p�X
	constexpr const char* MOVE_POINT_PATH = MODEL_PATH("Debug/MovePoint.obj");
	// �^�[�Q�b�gNPC�̃��f���p�X
	constexpr const char* TARGET_NPC_PATH = MODEL_PATH("TargetNPC.obj");
	// ��qNPC�̃��f���p�X
	constexpr const char* GUARD_NPC_PATH = MODEL_PATH("GuardNPC.obj");
}

/* �Q�[���̒l */
namespace GameValue
{
	// �v���C���[�̒l
	namespace Player
	{
		// �v���C���[�̍s�����[�h
		namespace MoveAction
		{
			// �ړ����x
			constexpr float MOVE_SPEED = 0.5f;
			// ��]���x
			constexpr float ROTATION_SPEED = 1.0f;
			// �W�����v�̍ő卂��
			constexpr float JUMP_HEIGHT = 5.0f;
			// �W�����v�̑��t���[����
			constexpr int	JUMP_DURATION = 45;
		}
		// �v���C���[�̑_�����[�h
		namespace SnipingAction
		{
			// ���������̎��_�ړ����x
			constexpr float LOOK_SPEED_VERTICAL = 0.5f;
			// ���������̎��_�ړ����x
			constexpr float LOOK_SPEED_HORIZONTAL = 0.5f;
			// �{���ύX�l
			constexpr float ZOOM_POWER = 0.1f;
		}
	}

	namespace Bullet
	{
		// �e�̐�������
		constexpr float LIFE_TIME = 5.0f; // �b
	}

	// NPC�̒l
	namespace Npc
	{
		// �ʏ�NPC�̒l
		namespace Normal
		{
			// ����p
			constexpr float VIEW_ANGLE = 60.0f; // �x
			// ���싗��
			constexpr float VIEW_DISTANCE = 200.0f; // ���[�g��
		}
		// �^�[�Q�b�gNPC�̒l
		namespace Target
		{
			// ����p
			constexpr float VIEW_ANGLE = 60.0f; // �x
			// ���싗��
			constexpr float VIEW_DISTANCE = 200.0f; // ���[�g��
		}
		// ����NPC�̒l
		namespace Patrol
		{
			// ����p
			constexpr float VIEW_ANGLE = 60.0f; // �x
			// ���싗��
			constexpr float VIEW_DISTANCE = 200.0f; // ���[�g��
		}
		// �X�i�C�p�[NPC�̒l
		namespace Sniper
		{
			// ����p
			constexpr float VIEW_ANGLE = 40.0f; // �x
			// ���싗��
			constexpr float VIEW_DISTANCE = 400.0f; // ���[�g��

		}
	}

	// �t�B�[���h�̒l
	namespace Field
	{
		// �t�B�[���h�̃T�C�Y
		constexpr float FIELD_SIZE = 100.0f;
	}

	// �����蔻��̒l
	namespace Collision
	{
		// �Փ˃`�F�b�N�̑Ώی��o����
		constexpr float DETECT_DISTANCE = 10.0f;
	}

	// ���G�̒l
	namespace VisionSearch
	{
		// �X�e���X�␳�̒l(�v���C���[�̎p���ɂ�鎋�F�����̕␳)
		namespace StealthCorrection
		{
			// �����p���̎��F�����␳
			constexpr float STAND = 1.0f;
			// ���Ⴊ�ݎp���̎��F�����␳
			constexpr float CROUCH = 0.8f;
			// �����p���̎��F�����␳
			constexpr float PRONE = 0.5f;
			// �����p���̎��F�����␳
			constexpr float HIDE = 0.3f;
		}

		// ���G�l���ő�l�ɂȂ�܂ł̎���
		constexpr float MAX_DETECTION_TIME = 3.0f; // �b
		// �������܂ł̎���
		constexpr float LOST_TIME = 3.0f; // �b
		// ���������Ƃ��̍��G�l�̌�����
		constexpr float LOST_DETECTION_RATE = 0.5f; // ���������Ƃ��̍��G�l�̌�����

	}

}

/* ���̓L�[ */
namespace InputKey
{
	// �v���C���[�̓��̓L�[
	namespace Player
	{
		// �s�����[�h�؂�ւ�
		constexpr BYTE CHANGE_ACTIONMODE
			= 'F';

		// �ړ����[�h�̓��̓L�[
		namespace MoveAction
		{
			// ���� �O�i
			constexpr BYTE MOVE_FORWARD
				= 'W';
			// ���� ���
			constexpr BYTE MOVE_BACKWARD
				= 'S';
			// ���� ���ړ�
			constexpr BYTE MOVE_LEFT
				= 'A';
			// ���� �E�ړ�
			constexpr BYTE MOVE_RIGHT
				= 'D';
			// ���� �W�����v
			constexpr BYTE JUMP
				= VK_SPACE;
			// ���_ ����]
			constexpr BYTE LOOK_LEFT
				= VK_LEFT;
			// ���_ �E��]
			constexpr BYTE LOOK_RIGHT
				= VK_RIGHT;
		}
		// �_�����[�h�̓��̓L�[
		namespace SnipingAction
		{
			// ���_ ���]
			constexpr BYTE SNIPING_LOOK_UP
				= 'W';
			// ���_ ����]
			constexpr BYTE SNIPING_LOOK_DOWN
				= 'S';
			// ���_ ����]
			constexpr BYTE SNIPING_LOOK_LEFT
				= 'A';
			// ���_ �E��]
			constexpr BYTE SNIPING_LOOK_RIGHT
				= 'D';
			// ���_ �Y�[���C��
			constexpr BYTE SNIPING_ZOOM_IN
				= VK_UP;
			// ���_ �Y�[���A�E�g
			constexpr BYTE SNIPING_ZOOM_OUT
				= VK_DOWN;
			// ���� �ˌ�
			constexpr BYTE SNIPING_SHOOT
				= VK_RETURN;
		}
	}
}