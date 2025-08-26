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

#endif // __DEFINES_H__