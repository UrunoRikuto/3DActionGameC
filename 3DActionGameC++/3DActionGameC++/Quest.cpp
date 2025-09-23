/*=====================================================================
* @file Quest.cpp
* @brief �N�G�X�g�Ǘ��N���X�̎����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "Quest.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Timer.h"
#include "Main.h"

// �V���O���g���̃C���X�^���X�̏�����
CQuest* CQuest::m_pInstance = nullptr;

// @brief �C���X�^���X�̎擾
CQuest* CQuest::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CQuest();
	}

	return m_pInstance;
}

void CQuest::DeleteInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

// @brief �R���X�g���N�^
CQuest::CQuest()
	: m_QuestData{}
{

}

// @brief �f�X�g���N�^
CQuest::~CQuest()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

// @brief �N�G�X�g�f�[�^�̐ݒ�
// @param In_QuestData �ݒ肷��N�G�X�g�f�[�^
void CQuest::SetQuestData(const QuestData& In_QuestData)
{
	// �N�G�X�g�f�[�^�̐ݒ�
	m_QuestData = In_QuestData;
	// �������Ԃ̐ݒ�
	CTimer::GetInstance()->SetLimitTime(m_QuestData.limitTime);
	CTimer::GetInstance()->Reset();
}

// @brief �N�G�X�g�f�[�^�̎擾
// @return �N�G�X�g�f�[�^�̎Q��
const QuestData& CQuest::GetQuestData(void)
{
	return m_QuestData;
}

// @brief �N�G�X�g�f�[�^�̃N���A
void CQuest::ClearQuestData(void)
{
	m_QuestData = QuestData{};
}

// @brief ���S�\�񐔂̌���
void CQuest::SubPossibleDeathCount(void)
{
	// ���S�\�񐔂̌���
	m_QuestData.PossibleDeathCount--;
	if (m_QuestData.PossibleDeathCount < 0)
	{
		// �N�G�X�g���s�̃e���b�v��\��
		// ���ŃN�G�X�g�I���V�[���Ɉȍ~
		ChangeScene(SceneType::QuestSelect, TransitionType::Fade);
	}
}
