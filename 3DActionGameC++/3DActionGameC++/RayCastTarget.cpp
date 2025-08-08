/*
* @file RayCastTarget.cpp
* @brief ���C�L���X�g�̃^�[�Q�b�g�N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 ���C�L���X�g�̃^�[�Q�b�g�N���X�̎���
*/

/* �w�b�_�[�̃C���N���[�h */
#include "RayCastTarget.h"

// @brief �R���X�g���N�^
CRayCastTarget::CRayCastTarget()
	: m_tPosition(0.0f, 0.0f, 0.0f) // �^�[�Q�b�g�̈ʒu�̏�����
	, m_tScale(1.0f, 1.0f, 1.0f) // �^�[�Q�b�g�̃X�P�[���̏�����
{

}

// @brief �f�X�g���N�^
CRayCastTarget::~CRayCastTarget()
{

}

// @brief �p�����[�^�[�̐ݒ�
// @param position �^�[�Q�b�g�̈ʒu
// @param scale �^�[�Q�b�g�̃X�P�[��
void CRayCastTarget::SetParam(const XMFLOAT3& position, const XMFLOAT3& scale)
{
	// �^�[�Q�b�g�̈ʒu��ݒ�
	m_tPosition = position; 
	// �^�[�Q�b�g�̃X�P�[����ݒ�
	m_tScale = scale;
}
