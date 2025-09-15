/*=====================================================================
* @file Quest.h
* @brief �N�G�X�g�Ǘ��N���X�̃w�b�_�[�t�@�C��
=====================================================================*/

#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Enums.h"

// @brief �N�G�X�g�f�[�^�\����
// @param stageType �X�e�[�W�̎��
// @param limitTime ��������
// @param maxDeathCount �ő厀�S�\��
struct QuestData
{
	// �X�e�[�W�̎��
	StageType stageType;
	// ��������
	float limitTime;
	// �ő厀�S�\��
	int maxDeathCount;
};


//@brief �N�G�X�g�Ǘ��N���X
class CQuest
{
	// �V���O���g���p�^�[��
private:
	static CQuest* m_pInstance;

public:
	// @brief �C���X�^���X�̎擾
	// @return �C���X�^���X�̃|�C���^
	static CQuest* GetInstance();

private:
	// @brief �R���X�g���N�^
	CQuest();

public:
	// @brief �f�X�g���N�^
	~CQuest();

	// @brief �N�G�X�g�f�[�^�̐ݒ�
	void SetQuestData(const QuestData& In_QuestData);

	// @brief �N�G�X�g�f�[�^�̎擾
	// @return �N�G�X�g�f�[�^�̎Q��
	const QuestData& GetQuestData(void);

	// @brief �N�G�X�g�f�[�^�̃N���A
	void ClearQuestData(void);

private:
	// @brief �N�G�X�g�f�[�^
	QuestData m_QuestData;
};