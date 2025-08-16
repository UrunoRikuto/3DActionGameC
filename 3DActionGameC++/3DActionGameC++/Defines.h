/*
* @file Defines.h
* @brief �萔��}�N���̒�`�t�@�C��
* @author �F���엤�l
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

//�t�@�C���p�X
#define ASSET_PATH(path) ("Assets/" path)
#define MODEL_PATH(path) (ASSET_PATH("Model/" path))
#define TEXTURE_PATH(path) (ASSET_PATH("Texture/" path))

// 3D��Ԓ�`
#define CMETER(value) (value * 0.01f)
#define METER(value) (value * 1.0f)
#define MSEC(value) (value / fFPS)
#define CMSEC(value) MSEC(CMETER(value))

#define PI (3.1415f)
#define TORAD(deg) ((deg / 180) * PI)
#define TODEG(rad) ((rad / PI) * 180)

static const float GRAVITY = 0.28f;

// �^�C�g��
static const char* APP_TITLE = "3DActionGame";

// ��ʃT�C�Y
static const int SCREEN_WIDTH	= 1920;
static const int SCREEN_HEIGHT	= 1080;

// �k���`�F�b�N
template<typename T>
inline bool SafeNullCheck(T* p)
{
	if (p == nullptr)
	{
		assert(p != nullptr && "�|�C���^��nullptr�ł��B");
		return false;
	}
	return true;
}

//�������J��
#define SAFE_DELETE(p)			do{if(p){delete p; p = nullptr;}}while(0)
#define SAFE_DELETE_ARRAY(p)	do{if(p){delete[] p; p = nullptr;}}while(0)
#define SAFE_RELEASE(p)			do{if(p){p->Release(); p = nullptr;}}while(0)
#define SAFE_NULLPTR(p)			do{if(p){p = nullptr;}}while(0)

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

#endif // __DEFINES_H__