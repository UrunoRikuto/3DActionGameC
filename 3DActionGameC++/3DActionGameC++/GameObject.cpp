/*
* @file GameObject.cpp
* @brief �Q�[���I�u�W�F�N�g�̊��N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/

/* �w�b�_�[�ŗ��p����V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"

/* �w�b�_�[�̃C���N���[�h */
#include "GameObject.h"

// @brief �R���X�g���N�^
CGameObject::CGameObject()
	: m_pModel(nullptr) // ���f���|�C���^�̏�����
	, m_tPosition(0.0f, 0.0f, 0.0f) // �����ʒu
	, m_tScale(1.0f, 1.0f, 1.0f) // �����X�P�[��
	, m_tRotation(0.0f, 0.0f, 0.0f) // ������]
{
	
}

// @brief �f�X�g���N�^
CGameObject::~CGameObject()
{

}

// @brief �X�V����
void CGameObject::Update()
{

}

// @brief �`�揈��
void CGameObject::Draw()
{

}
