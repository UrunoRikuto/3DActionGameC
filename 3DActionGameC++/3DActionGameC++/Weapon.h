/*=====================================================================
* @file Weapon.h
* @brief ����̊��N���X�w�b�_�[�t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Collision.h"
#include "Enums.h"
#include "StructMath.h"

/// <summary>
/// ����̊��N���X
/// </summary>
class CWeapon
{
public:
	// @brief �R���X�g���N�^
	CWeapon();

	// @brief �f�X�g���N�^
	virtual ~CWeapon();

	// @brief �p�����[�^�̐ݒ�
	virtual void SetParam(void) = 0;

protected:
	// @brief �U���^�C�v
	AttackType m_eAttackType;

	// @brief �U����
	float m_fAttackPower;

	// @brief �U�����x(�U���Ԋu)
	float m_fAttackSpeed;

	// @brief �U���͈�
	Collision::Info m_tAttackRange;

public:// �A�N�Z�T

	// @brief �U���͂̎擾
	float GetAttackPower(void) const { return m_fAttackPower; }
	// @brief �U�����x�̎擾
	float GetAttackSpeed(void) const { return m_fAttackSpeed; }
	// @brief �U���͈͂̎擾
	const Collision::Info& GetAttackRange(void) const { return m_tAttackRange; }
};
