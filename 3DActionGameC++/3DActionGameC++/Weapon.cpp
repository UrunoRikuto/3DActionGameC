/*=====================================================================
* @file Weapon.cpp
* @brief ����̊��N���X�����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "Weapon.h"

// @brief �R���X�g���N�^
CWeapon::CWeapon()
	: m_eAttackType(AttackType::Blow)
	, m_fAttackPower(0.0f)
	, m_fAttackSpeed(0.0f)
	, m_tAttackRange()
{

}

// @brief �f�X�g���N�^
CWeapon::~CWeapon()
{

}
