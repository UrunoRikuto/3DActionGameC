/*=====================================================================
* @file StatusParameter.h
* @brief �X�e�[�^�X�p�����[�^�[�̃w�b�_�[�t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Enums.h"
#include "Defines.h"
#include "GameValues.h"
#include <string>

/// <summary>
/// �X�e�[�^�X�p�����[�^�[�̃N���X
/// </summary>
class CStatusParameter
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CStatusParameter();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CStatusParameter();

	/// <summary>
	/// �X�e�[�^�X�̏���������
	/// </summary>
	void InitStatus(void);

	/// <summary>
	/// �X�e�[�^�X�f�[�^�̓ǂݍ��ݏ���
	/// </summary>
	/// <param name="In_DataPath">�f�[�^�̃t�@�C���p�X</param>
	void LoadStatus(const std::string In_DataPath);

	/// <summary>
	/// �X�e�[�^�X�f�[�^�̕ۑ�����
	/// </summary>
	/// <param name="In_DataPath">�ۑ���̃t�@�C���p�X</param>
	void SaveStatus(const std::string In_DataPath);

	/// <summary>
	/// ���x���A�b�v����
	/// </summary>
	/// <param name="InType">���x���A�b�v�����鍀��</param>
	void LevelUp(StatusParameterType InType);

private:

	/// <summary>
	/// ������
	/// </summary>
	int m_nVitalityLevel;

	/// <summary>
	/// �ؗ�
	/// </summary>
	int m_nMuscleLevel;

	/// <summary>
	/// ���_��
	/// </summary>
	int m_nMentalLevel;

	/// <summary>
	/// ���v��
	/// </summary>
	int m_nEnduranceLevel;

	/// <summary>
	/// �Z��
	/// </summary>
	int m_nSkillLevel;

public: // �����o�ϐ��̃A�N�Z�T

	/// <summary>
	/// �����̓��x���̎擾
	/// </summary>
	/// <returns>�����̓��x��</returns>
	int GetVitalityLevel(void) const { return m_nVitalityLevel; };

	/// <summary>
	/// �ؗ̓��x���̎擾
	/// </summary>
	/// <returns>�ؗ̓��x��</returns>
	int GetMuscleLevel(void) const { return m_nMuscleLevel; };

	/// <summary>
	/// ���_�̓��x���̎擾
	/// </summary>
	/// <returns>���_�̓��x��</returns>
	int GetMentalLevel(void) const { return m_nMentalLevel; };

	/// <summary>
	/// ���v�̓��x���̎擾
	/// </summary>
	/// <returns>���v�̓��x��</returns>
	int GetEnduranceLevel(void) const { return m_nEnduranceLevel; };

	/// <summary>
	/// �Z�ʃ��x���̎擾
	/// </summary>
	/// <returns>�Z�ʃ��x��</returns>
	int GetSkillLevel(void) const { return m_nSkillLevel; };
};
