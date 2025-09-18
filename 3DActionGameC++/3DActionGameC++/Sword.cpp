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
	for (auto& attackRange : m_tAttackRange)
	{
		// �U���͈͂̒��S���W���L�����N�^�[�̈ʒu�ɐݒ�
		attackRange.box.center = In_Position;
	}
}

// @brief �p�����[�^�̐ݒ�
void CSword::SetParam(void)
{
	// �U���^�C�v
	m_eAttackType = AttackType::Slash;
	// �U����
	m_fAttackPower.push_back(20.0f);
	m_fAttackPower.push_back(15.0f);

	// �U�����x(�U���Ԋu)
	m_fAttackSpeed = 1.0f;
	// �U���͈�
	Collision::Info AttackRange = {};

	AttackRange.type = Collision::eBox;
	// �{�b�N�X�̒��S���W�ƃT�C�Y��ݒ�
	AttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	AttackRange.box.size = { 1.0f, 10.0f, 10.0f };
	// �^�O��ǉ�
	AttackRange.tag.push_back(Collision::Tag::Attack);

	m_tAttackRange.push_back(AttackRange);

	AttackRange = {};

	AttackRange.type = Collision::eBox;
	// �{�b�N�X�̒��S���W�ƃT�C�Y��ݒ�
	AttackRange.box.center = { 0.0f, 0.0f, 0.0f };
	AttackRange.box.size = { 10.0f, 1.0f, 10.0f };
	// �^�O��ǉ�
	AttackRange.tag.push_back(Collision::Tag::Attack);

	m_tAttackRange.push_back(AttackRange);


	// �U���̎�������
	m_fAttackDurationTime = 0.5f;

	// �R���{�P�\����
	m_fComboGraceTimer = 0.5f;
}
