/*
* @file Field.cpp
* @brief �t�B�[���h�I�u�W�F�N�g�̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/


/* �w�b�_�[�ŗ��p����V�X�e���E�v�f�̃C���N���[�h */
#include "RayCastTarget.h"
#include <memory>
/* �w�b�_�[�̃C���N���[�h */
#include "Field.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "Defines.h"
#include "Main.h"
#include "ModelDrawSetting.h"
#include "Geometory.h"

// @brief �R���X�g���N�^
CField::CField()
	: CGameObject() // ���N���X�̃R���X�g���N�^���Ăяo��
{
	using namespace GameValue::Field;

	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(MODEL_PATH("BattleStage_Field.obj"),0.1f))
	{
		MessageBox(NULL, "�t�B�[���h���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
	}

	// �ʒu�A�X�P�[���A��]�̐ݒ�
	m_tScale = { FIELD_SIZE, 1.0f, FIELD_SIZE };
	m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// ���C�L���X�g�̃^�[�Q�b�g�I�u�W�F�N�g�̐���
	m_pRayCastTarget = std::make_unique<CRayCastTarget>();
	// ���C�L���X�g�̃^�[�Q�b�g�I�u�W�F�N�g�̃p�����[�^�[��ݒ�
	m_pRayCastTarget->SetParam(m_tPosition, m_tScale);

	// �����蔻����̏�����
	// �����蔻����̃T�C�Y��1�ɐݒ�
	m_tCollisionInfos.resize(1);
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[0].type = Collision::Type::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Field);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[0].box.center = m_tPosition;
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[0].box.size = m_tScale;
}

// @brief �f�X�g���N�^
CField::~CField()
{

}

// @brief �X�V����
void CField::Update(void)
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;


	m_pRayCastTarget->SetPosition(m_tPosition); // ���C�L���X�g�̃^�[�Q�b�g�I�u�W�F�N�g�̈ʒu���X�V
	m_pRayCastTarget->SetScale(m_tScale); // ���C�L���X�g�̃^�[�Q�b�g�I�u�W�F�N�g�̃X�P�[�����X�V
}

// @brief �����蔻��̏Փˎ��̏���
// @param InCollisionInfo �ՓˑΏ�
void CField::Hit(const Collision::Info& InCollisionInfo)
{
	// ���͓��ɉ������Ȃ�
}
