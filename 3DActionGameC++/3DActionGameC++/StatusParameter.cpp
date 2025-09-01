/*=====================================================================
* @file StatusParameter.cpp
* @brief �X�e�[�^�X�p�����[�^�[�̎����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "StatusParameter.h"

// @brief �R���X�g���N�^
CStatusParameter::CStatusParameter()
	: m_nVitalityLevel(1)	// �����͂̏����l
	, m_nMuscleLevel(1)		// �ؗ͂̏����l
	, m_nMentalLevel(1)		// ���_�͂̏����l
	, m_nEnduranceLevel(1)	// ���v�͂̏����l
	, m_nSkillLevel(1)		// �Z�ʂ̏����l
{

}

// @brief �f�X�g���N�^
CStatusParameter::~CStatusParameter()
{

}

// @brief �X�e�[�^�X�̏���������
void CStatusParameter::InitStatus(void)
{
	// ���ׂẴX�e�[�^�X���x����1�ɐݒ�
	m_nVitalityLevel = 1;
	m_nMuscleLevel = 1;
	m_nMentalLevel = 1;
	m_nEnduranceLevel = 1;
	m_nSkillLevel = 1;
}

// @brief �X�e�[�^�X�f�[�^�̓ǂݍ��ݏ���
// @param In_DataPath �f�[�^�̃t�H���_�p�X
void CStatusParameter::LoadStatus(const std::string In_DataPath)
{
	// ���͖�����
	// �����I�Ƀt�@�C������X�e�[�^�X�f�[�^��ǂݍ��ޏ�������������\��
	// JSON�ł̓ǂݍ��݂�z��
}

// @brief �X�e�[�^�X�f�[�^�̕ۑ�����
// @param In_DataPath �ۑ���̃t�H���_�p�X
void CStatusParameter::SaveStatus(const std::string In_DataPath)
{
	// ���͖�����
	// �����I�Ƀt�@�C���ɃX�e�[�^�X�f�[�^��ۑ����鏈������������\��
	// JSON�ł̕ۑ���z��
}

// @brief ���x���A�b�v����
// @param InType ���x���A�b�v�����鍀��
void CStatusParameter::LevelUp(StatusParameterType InType)
{
	switch (InType)
	{
	case StatusParameterType::Vitality:		// ������
		m_nVitalityLevel++;
		break;
	case StatusParameterType::Muscle:		// �ؗ�
		m_nMuscleLevel++;
		break;
	case StatusParameterType::Mental:		// ���_��
		m_nMentalLevel++;
		break;
	case StatusParameterType::Endurance:	// ���v��
		m_nEnduranceLevel++;
		break;
	case StatusParameterType::Skill:		// �Z��
		m_nSkillLevel++;
		break;
	}
}
