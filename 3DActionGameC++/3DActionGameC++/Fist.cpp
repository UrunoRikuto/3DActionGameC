/*=====================================================================
* @file Fist.cpp
* @brief ���N���X�����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "Fist.h"

// @brief �R���X�g���N�^
CFist::CFist()
{
	// �p�����[�^�̐ݒ�
	SetParam();
}

// @brief �f�X�g���N�^
CFist::~CFist()
{
}

// @brief �X�V
void CFist::Update(XMFLOAT3 In_Position)
{
	// �U���͈͂̒��S���W���L�����N�^�[�̈ʒu�ɐݒ�
	m_tAttackRange.box.center = In_Position;
}

// @brief �p�����[�^�̐ݒ�
void CFist::SetParam(void)
{
	// �U���^�C�v
	m_eAttackType = AttackType::Blow;
	// �U����
	m_fAttackPower = 10.0f;
	// �U�����x(�U���Ԋu)
	m_fAttackSpeed = 0.5f;
	// �U���͈�
	m_tAttackRange.type = Collision::eBox;
	// �{�b�N�X�̒��S���W�ƃT�C�Y��ݒ�
	m_tAttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	m_tAttackRange.box.size = { 3.0f, 3.0f, 3.0f };
	// �^�O��ǉ�
	m_tAttackRange.tag.push_back(Collision::Tag::Attack);
	// �U���̎�������
	m_fAttackDurationTime = 0.1f;
}
