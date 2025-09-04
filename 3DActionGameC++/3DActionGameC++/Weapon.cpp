/*=====================================================================
* @file Weapon.cpp
* @brief ����̎����t�@�C��
=====================================================================*/
#include "Weapon.h"

// @brief �R���X�g���N�^
CWeapon::CWeapon()
	: m_eAttackType(AttackType::Slash) // �U���^�C�v�̏�����
	, m_nUpgradeLevel(1) // ����̋������x���̏�����
	, m_fWeight(1.0f)	 // ����̏d�ʂ̏�����
	, m_fAttackPower{}	 // ����̍U���̓��X�g�̏�����
{
}

// @brief �f�X�g���N�^
CWeapon::~CWeapon()
{
}

// @brief ����̃f�[�^�̓ǂݍ���
// @param In_DataPath �f�[�^�̃t�H���_�p�X
void CWeapon::LoadWeaponData(const std::string In_DataPath)
{
	// ���͖�����
	// �����I�Ƀt�@�C�����畐��f�[�^��ǂݍ��ޏ�������������\��
	// JSON�ł̓ǂݍ��݂�z��

	// ���̃f�[�^��ݒ�
	m_eAttackType = AttackType::Blow; // �U���̎�ނ��a���ɐݒ�
	m_nUpgradeLevel = 1; // �������x��1
	m_fAttackPower[0] = 10.0f; // �������x��1�̍U����
	m_fAttackPower[1] = 15.0f; // �������x��2�̍U����
	m_fAttackPower[2] = 20.0f; // �������x��3�̍U����
	m_fAttackPower[3] = 25.0f; // �������x��4�̍U����
	m_fAttackPower[4] = 30.0f; // �������x��5�̍U����
	m_fWeight = 5.0f; // ����̏d��
}
