/*=====================================================================
* @file Sword.cpp
* @brief ���N���X�����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "Sword.h"

// @brief �R���X�g���N�^
CSword::CSword()
{
	// �p�����[�^�̐ݒ�
	SetParam();
}

// @brief �f�X�g���N�^
CSword::~CSword()
{

}

// @brief �X�V
// @param In_Position �L�����N�^�[�̈ʒu
void CSword::Update(XMFLOAT3 In_Position)
{
	// �U���͈͂̒��S���W���L�����N�^�[�̈ʒu�ɐݒ�
	m_tAttackRange.box.center = In_Position;
}

// @brief �p�����[�^�̐ݒ�
void CSword::SetParam(void)
{
	// �U���^�C�v
	m_eAttackType = AttackType::Slash;
	// �U����
	m_fAttackPower = 20.0f;
	// �U�����x(�U���Ԋu)
	m_fAttackSpeed = 1.0f;
	// �U���͈�
	m_tAttackRange.type = Collision::eBox;
	// �{�b�N�X�̒��S���W�ƃT�C�Y��ݒ�
	m_tAttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	m_tAttackRange.box.size = { 5.0f, 5.0f, 5.0f };
	// �U���̎�������
	m_fAttackDurationTime = 0.5f;
}
