/*=====================================================================
* @file Weapon.h
* @brief ����̃w�b�_�[�t�@�C��
=====================================================================*/
#pragma once
#include <string>
#include "Enums.h"

/// <summary>
/// ����̃N���X
/// </summary>
class CWeapon
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CWeapon();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CWeapon();

	/// <summary>
	/// ����̃f�[�^�̓ǂݍ���
	/// </summary>
	/// <param name="In_DataPath">�f�[�^�̃t�@�C���p�X</param>
	void LoadWeaponData(const std::string In_DataPath);
private:

	/// <summary>
	/// �U���̎��
	/// </summary>
	AttackType m_eAttackType;

	/// <summary>
	/// ����̋������x��
	/// </summary>
	int m_nUpgradeLevel;

	/// <summary>
	/// �U���̓��X�g
	/// </summary>
	float m_fAttackPower[5];

	/// <summary>
	/// �d��
	/// </summary>
	float m_fWeight;

public: //�����o�ϐ��̃A�N�Z�T

	/// <summary>
	/// �U���̎�ނ̎擾
	/// </summary>
	/// <returns> �U���̎��</returns>
	AttackType GetAttackType(void)const { return m_eAttackType; }
	/// <summary>
	/// �������x���̎擾
	/// </summary>
	/// <returns>�������x��</returns>
	int GetUpgradeLevel(void)const { return m_nUpgradeLevel; }
	/// <summary>
	/// �U���͂̎擾
	/// </summary>
	/// <returns>�U����</returns>
	float GetAttackPower(void)const { return m_fAttackPower[m_nUpgradeLevel - 1]; }
	/// <summary>
	/// �d�ʂ̎擾
	/// </summary>
	/// <returns>�d��</returns>
	float GetWeight(void)const { return m_fWeight; }
};

