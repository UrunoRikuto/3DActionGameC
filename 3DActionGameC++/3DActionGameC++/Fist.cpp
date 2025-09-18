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
	for (auto& attackRange : m_tAttackRange)
	{
		attackRange.box.center = In_Position;
	}
}

// @brief �p�����[�^�̐ݒ�
void CFist::SetParam(void)
{
	// �U���^�C�v
	m_eAttackType = AttackType::Blow;
	// �U����
	m_fAttackPower.push_back(10.0f);
	// �U�����x(�U���Ԋu)
	m_fAttackSpeed = 0.5f;
	// �U���͈�
	Collision::Info AttackRange = {};

	AttackRange.type = Collision::eBox;
	// �{�b�N�X�̒��S���W�ƃT�C�Y��ݒ�
	AttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	AttackRange.box.size = { 3.0f, 3.0f, 3.0f };
	// �^�O��ǉ�
	AttackRange.tag.push_back(Collision::Tag::Attack);
	// �U���͈͂�ǉ�
	m_tAttackRange.push_back(AttackRange);
	// �U���̎�������
	m_fAttackDurationTime = 0.1f;
	// �R���{�P�\����
	m_fComboGraceTimer = 0.3f;
}
