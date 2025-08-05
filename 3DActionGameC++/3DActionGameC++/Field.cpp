/*
* @file Field.cpp
* @brief �t�B�[���h�I�u�W�F�N�g�̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/


/* �w�b�_�[�ŗ��p����V�X�e���E�v�f�̃C���N���[�h */

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
	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(MODEL_PATH("BattleStage_Field.obj"),0.1f))
	{
		MessageBox(NULL, "�t�B�[���h���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
	}

	// �ʒu�A�X�P�[���A��]�̐ݒ�
	m_tScale = { 100.0f, 1.0f, 100.0f };   
	m_tPosition = { 0.0f, 0.0f - (m_tScale.y / 2), 0.0f };
	m_tRotation = { 0.0f, 0.0f, 0.0f };
	// �����蔻����̏�����
	m_tCollisionInfo.type = Collision::Type::eBox; // �����蔻��̃^�C�v���{�b�N�X�ɐݒ�
	m_tCollisionInfo.box.center = m_tPosition; // ���S�ʒu��ݒ�
	m_tCollisionInfo.box.size = m_tScale; // �T�C�Y���X�P�[���ɐݒ�
}

// @brief �f�X�g���N�^
CField::~CField()
{

}

// @brief �X�V����
void CField::Update(void)
{

}

// @brief �`�揈��
void CField::Draw(void)
{
	SetRender3D();
	// �����蔻��̕`��
	Collision::DrawCollision(m_tCollisionInfo);
	// ���f���̕`��
	CreateObject(
		m_tPosition,	// �ʒu
		m_tScale,		// �X�P�[��
		m_tRotation,	// ��]
		m_pModel.get(),       // ���f���|�C���^
		Camera::GetInstance(),// �J�����|�C���^
		true,                 // ���邭���邩�ǂ���
		XMFLOAT3(1.0f,1.0f,1.0f) // ���C�e�B���O�F
	);

}
