/*������������������������������������������������������������������������������������������������������������������������������
*
* file�FEasing.h
*
* �T�v�F�C�[�W���O�֐����Ǘ�����t�@�C��
*
������������������������������������������������������������������������������������������������������������������������������*/

#pragma once
#include "StructMath.h"
#include <cmath>

/*����������������������������*/
/*���@�@�@EaseOutQuart�@�@�@��*/
/*����������������������������*/

/// <summary>
/// EaseOutQuart�̃C�[�W���O�֐�
/// </summary>
/// <param name="t">�o�ߎ���</param>
/// <returns>�v�Z����</returns>
inline  float easeOutQuart(float t)
{
    return 1 - pow(1 - t, 4);
}
/// <summary>
/// EaseOutQuart�̈ړ��֐�
/// </summary>
/// <param name="t">�o�ߎ���</param>
/// <param name="start">�����ʒu</param>
/// <param name="end">�ŏI�ʒu</param>
/// <returns>�v�Z����</returns>
inline XMFLOAT2 easeMoveOutQuart(float t, XMFLOAT2 start, XMFLOAT2 end) 
{
    float easedT = easeOutQuart(t);
    return 
    {
        start.x + (end.x - start.x) * easedT,
        start.y + (end.y - start.y) * easedT
    };
}




/*����������������������������*/
/*���@�@�@EaseOutBack�@�@�@ ��*/
/*����������������������������*/

/// <summary>
/// EaseOutBack�̃C�[�W���O�֐�
/// </summary>
/// <param name="t">�o�ߎ���</param>
/// <param name="overshoot">�ߏ��</param>
/// <returns>�v�Z����</returns>
inline float easeOutBack(float t, float overshoot = 1.70158f) 
{
    return 1 + (--t) * t * ((overshoot + 1) * t + overshoot);
}

/// <summary>
/// EaseOutBack�̈ړ��֐�
/// </summary>
/// <param name="t">�o�ߎ���</param>
/// <param name="start">�J�n�ʒu</param>
/// <param name="end">�ŏI�ʒu</param>
/// <param name="overshoot">�ߏ��</param>
/// <returns>�v�Z����</returns>
inline XMFLOAT2 easeMoveOutBack(float t, XMFLOAT2 start, XMFLOAT2 end, float overshoot = 1.70158f)
{
    float easedT = easeOutBack(t, overshoot);
    return 
    {
        start.x + (end.x - start.x) * easedT,
        start.y + (end.y - start.y) * easedT
    };
}




/*����������������������������*/
/*���@�@�@EaseOutQuint�@�@�@��*/
/*����������������������������*/

/// <summary>
/// EaseOutQuint�̃C�[�W���O�֐�
/// </summary>
/// <param name="t">���ݎ���</param>
/// <returns>�v�Z����</returns>
inline float easeOutQuint(float t) 
{
    return 1 - pow(1 - t, 5);
}

/// <summary>
/// EaseOutQuint�̈ړ��֐�
/// </summary>
/// <param name="t">���ݎ���</param>
/// <param name="start">�J�n�ʒu</param>
/// <param name="end">�ŏI�ʒu</param>
/// <returns>�v�Z����</returns>
inline XMFLOAT2 easeMoveOutQuint(float t, XMFLOAT2 start, XMFLOAT2 end)
{
	float easedT = easeOutQuint(t);
	return
	{
		start.x + (end.x - start.x) * easedT,
		start.y + (end.y - start.y) * easedT
	};
}
