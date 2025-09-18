/*=====================================================================
* @file Weapon.h
* @brief ����̊��N���X�w�b�_�[�t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Collision.h"
#include "Enums.h"
#include "StructMath.h"
#include <list>

// �U���̓����蔻����
struct AttackCollision
{
	// �����蔻����
	Collision::Info CollisionInfo;
	// �����t���[��
	float DurationFrame;
	// �U����
	float AttackPower;
	// ���������G���e�B�e�B��ID���X�g
	std::list<int> HitEntityIDList;

	bool operator==(const AttackCollision& other) const
	{
		return &CollisionInfo == &other.CollisionInfo && &DurationFrame == &other.DurationFrame;
	}
};

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

	// @brief �X�V
	virtual void Update(XMFLOAT3 In_Position) = 0;

	// @brief �R���{�^�C�}�[�̍X�V
	void ComboTimerUpdate(void);

	// @�U���̐���
	// @param Dir ����
	AttackCollision CreateAttack(float Dir);

protected:

	// @brief �p�����[�^�̐ݒ�
	virtual void SetParam(void) = 0;

protected:

	// @brief �U���^�C�v
	AttackType m_eAttackType;

	// @brief �U���͈�
	std::vector<Collision::Info> m_tAttackRange;

	// @brief �U����
	std::vector<float> m_fAttackPower;

	// @brief �U�����x(�U���Ԋu)
	float m_fAttackSpeed;

	// @brief �U���̎�������
	float m_fAttackDurationTime;

	// @brief �R���{��
	int m_nComboCount;

	// @brief �R���{�^�C�}�[
	float m_fComboTimer;

	// @brief �R���{�P�\����
	float m_fComboGraceTimer;

public:// �A�N�Z�T

	// @brief �U���^�C�v�̎擾
	AttackType GetAttackType(void) const { return m_eAttackType; }
	// @brief �U���͂̎擾
	float GetAttackPower(void) const { return m_fAttackPower[m_nComboCount]; }
	// @brief �U�����x�̎擾
	float GetAttackSpeed(void) const { return m_fAttackSpeed; }
	// @brief �U���͈͂̎擾
	Collision::Info GetAttackRange(void) { return m_tAttackRange[m_nComboCount]; }
	std::vector<Collision::Info>& GetAttackRanges(void) { return m_tAttackRange; }
	// @brief ���������������U���͈͂̎擾
	Collision::Info GetAttackRangeDir(float Dir);
	// @brief �U���̎������Ԃ̎擾
	float GetAttackDurationFrame(void) const { return m_fAttackDurationTime; }

};
