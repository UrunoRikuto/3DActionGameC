/*=====================================================================
* @file FieldObject.cpp
* @brief �t�B�[���h�I�u�W�F�N�g�̎����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "FieldObject.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "GameValues.h"
#include "Quest.h"

// @brief �R���X�g���N�^
CFieldObject::CFieldObject(FieldObjectType In_Type)
	: CGameObject() // ���N���X�̃R���X�g���N�^���Ăяo��
{
	using namespace GameValue::Field;

	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// �t�B�[���h�I�u�W�F�N�g�̎�ނɉ����ď�����
	switch (In_Type)
	{
	case FieldObjectType::Wall:
		// ���f���̓ǂݍ���
		switch (CQuest::GetInstance()->GetQuestData().stageType)
		{
		case StageType::Arena:
			if (!m_pModel->Load(MODEL_PATH("ArenaStage_Wall.obj"), 0.1f))
			{
				MessageBox(NULL, "�ǂ̃��f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
			}
			break;
		case StageType::Plain:
			if (!m_pModel->Load(MODEL_PATH("PlainStage_Wall.obj"), 0.1f))
			{
				MessageBox(NULL, "�ǂ̃��f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
			}
			break;
		}

		// �ʒu�A�X�P�[���A��]�̐ݒ�
		m_tScale = { 1.0f, 1.0f, 1.0f };
		m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
		m_tRotation = { 0.0f, 0.0f, 0.0f };

		// �����蔻����̏�����
		// �����蔻����̃T�C�Y��1�ɐݒ�
		m_tCollisionInfos.resize(1);
		// �����蔻��̎�ނ�ݒ�
		m_tCollisionInfos[0].type = Collision::Type::eBox;
		// �^�O��ǉ�
		m_tCollisionInfos[0].tag.push_back(Collision::Tag::FieldWall);
		// ���S�ʒu��ݒ�
		m_tCollisionInfos[0].box.center = m_tPosition;
		// �{�b�N�X�̑傫����ݒ�
		m_tCollisionInfos[0].box.size = m_tScale;
		break;
	case FieldObjectType::Ground:
		// ���f���̓ǂݍ���
		switch (CQuest::GetInstance()->GetQuestData().stageType)
		{
		case StageType::Arena:
			if (!m_pModel->Load(MODEL_PATH("ArenaStage_Field.obj"), 0.1f))
			{
				MessageBox(NULL, "�t�B�[���h���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
			}
			break;
		case StageType::Plain:
			if (!m_pModel->Load(MODEL_PATH("PlainStage_Field.obj"), 0.1f))
			{
				MessageBox(NULL, "�t�B�[���h���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
			}
			break;
		}

		// �ʒu�A�X�P�[���A��]�̐ݒ�
		m_tScale = { 1.0f, 1.0f, 1.0f };
		m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
		m_tRotation = { 0.0f, 0.0f, 0.0f };

		// �����蔻����̏�����
		// �����蔻����̃T�C�Y��1�ɐݒ�
		m_tCollisionInfos.resize(1);
		// �����蔻��̎�ނ�ݒ�
		m_tCollisionInfos[0].type = Collision::Type::eBox;
		// �^�O��ǉ�
		m_tCollisionInfos[0].tag.push_back(Collision::Tag::FieldGround);
		// ���S�ʒu��ݒ�
		m_tCollisionInfos[0].box.center = m_tPosition;
		// �{�b�N�X�̑傫����ݒ�
		m_tCollisionInfos[0].box.size = m_tScale;
		break;
	}
}

// @brief �f�X�g���N�^
CFieldObject::~CFieldObject()
{

}

// @brief �X�V����
void CFieldObject::Update(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

}

// @brief �����蔻��̏Փˎ��̏���
void CFieldObject::Hit(const Collision::Info& InCollisionInfo)
{

}
