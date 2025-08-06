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

//�������J��
#define SAFE_DELETE(p)			do{if(p){delete p; p = nullptr;}}while(0)
#define SAFE_DELETE_ARRAY(p)	do{if(p){delete[] p; p = nullptr;}}while(0)
#define SAFE_RELEASE(p)			do{if(p){p->Release(); p = nullptr;}}while(0)
#define SAFE_NULLPTR(p)			do{if(p){p = nullptr;}}while(0)

/* �Q�[���̒l */
constexpr float PLAYER_MOVE_SPEED = 0.5f;		// �v���C���[�̈ړ����x
constexpr float PLAYER_ROTATION_SPEED = 1.0f;	// �v���C���[�̉�]���x
constexpr float PLAYER_JUMP_HEIGHT = 3.0f;		// �v���C���[�̃W�����v�̍ő卂��
constexpr int	PLAYER_JUMP_DURATION = 45;		// �v���C���[�̃W�����v�̑��t���[����

/* ���̓L�[ */
constexpr BYTE PLAYER_MOVE_FORWARD_KEY = 'W';	// �O�i�L�[
constexpr BYTE PLAYER_MOVE_BACKWARD_KEY = 'S';	// ��ރL�[
constexpr BYTE PLAYER_MOVE_LEFT_KEY = 'A';		// ���ړ��L�[
constexpr BYTE PLAYER_MOVE_RIGHT_KEY = 'D';		// �E�ړ��L�[
constexpr BYTE PLAYER_JUMP_KEY = VK_SPACE;	// �W�����v�L�[
constexpr BYTE PLAYER_LOOK_LEFT_KEY = VK_LEFT;	// �������L�[
constexpr BYTE PLAYER_LOOK_RIGHT_KEY = VK_RIGHT; // �E�����L�[
constexpr BYTE PLAYER_CHANGE_ACTIONMODE_KEY = 'F'; // �s�����[�h�؂�ւ��L�[


#endif // __DEFINES_H__