/*=====================================================================
* @file Weapon.cpp
* @brief ����̊��N���X�����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "Weapon.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Defines.h"


// @brief �R���X�g���N�^
CWeapon::CWeapon()
	: m_eAttackType(AttackType::Blow)
	, m_fAttackPower(0.0f)
	, m_fAttackSpeed(0.0f)
	, m_tAttackRange{}
	, m_fAttackDurationTime(0.0f)
	, m_nComboCount(0)
	, m_fComboTimer(0.0f)
	, m_fComboGraceTimer(1.0f)
{

}

// @brief �f�X�g���N�^
CWeapon::~CWeapon()
{

}

// @brief �R���{�^�C�}�[�̍X�V
void CWeapon::ComboTimerUpdate(void)
{
	// �R���{�^�C�}�[�𑝉�
	m_fComboTimer += 1.0f / fFPS;

	// �R���{�P�\���Ԃ��߂��Ă�����R���{�������Z�b�g
	if (m_fComboTimer > m_fComboGraceTimer)
	{
		m_nComboCount = 0;
	}
}

// @brief �U���̐���
// @param Dir ����
AttackCollision CWeapon::CreateAttack(float Dir)
{
	AttackCollision AttackInfo;

	AttackInfo.DurationFrame = GetAttackDurationFrame();
	AttackInfo.AttackPower = GetAttackPower();
	AttackInfo.CollisionInfo = GetAttackRangeDir(Dir);

	// �R���{���𑝉�
	m_nComboCount++;

	// �R���{�����U���͈͂̐��𒴂�����R���{�������Z�b�g
	if (m_nComboCount > static_cast<int>(m_tAttackRange.size() - 1))
	{
		m_nComboCount = 0;
	}

	// �R���{���Ԃ����Z�b�g
	m_fComboTimer = 0.0f;

	return AttackInfo;
}

// @brief �U���͈͂̎擾
// @param Dir ����
Collision::Info CWeapon::GetAttackRangeDir(float Dir)
{
	Collision::Info AttackRange;

	AttackRange.box.center = m_tAttackRange[m_nComboCount].box.center;
	AttackRange.tag = m_tAttackRange[m_nComboCount].tag;
	AttackRange.type = m_tAttackRange[m_nComboCount].type;

	// �������l�����čU���͈͂̃T�C�Y��ύX
	AttackRange.box.size.x = m_tAttackRange[m_nComboCount].box.size.x * fabsf(cosf(TORAD(Dir))) + m_tAttackRange[m_nComboCount].box.size.z * fabsf(sinf(TORAD(Dir)));
	AttackRange.box.size.z = m_tAttackRange[m_nComboCount].box.size.x * fabsf(sinf(TORAD(Dir))) + m_tAttackRange[m_nComboCount].box.size.z * fabsf(cosf(TORAD(Dir)));
	AttackRange.box.size.y = m_tAttackRange[m_nComboCount].box.size.y;

	return AttackRange;
}