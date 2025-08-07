/*
* @file GameObject.cpp
* @brief �Q�[���I�u�W�F�N�g�̊��N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/

/* �w�b�_�[�ŗ��p����V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"

/* �w�b�_�[�̃C���N���[�h */
#include "GameObject.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Main.h"
#include "ModelDrawSetting.h"

// @brief �R���X�g���N�^
CGameObject::CGameObject()
	: m_pModel(nullptr) // ���f���|�C���^�̏�����
	, m_tPosition(0.0f, 0.0f, 0.0f) // �����ʒu
	, m_fAjustPositionY(0.0f) // �v���C���[�̐^���̒n�ʂ̍����̏����l
	, m_tScale(1.0f, 1.0f, 1.0f) // �����X�P�[��
	, m_tRotation(0.0f, 0.0f, 0.0f) // ������]
	, m_tCollisionInfos{} // �����蔻����̏�����
{
	
}

// @brief �f�X�g���N�^
CGameObject::~CGameObject()
{

}

// @brief �X�V����
void CGameObject::Update()
{

}

// @brief �`�揈��
void CGameObject::Draw()
{
	SetRender3D();
#ifdef _DEBUG
	// �f�o�b�O���[�h�ł̓����蔻��̕`��
	// �����蔻��̕`��
	for (const auto& collisionInfo : m_tCollisionInfos)
	{
		Collision::DrawCollision(collisionInfo);
	}
#endif // _DEBUG

	// ���f���̕`��
	CreateObject(
		m_tPosition,	// �ʒu
		m_tScale,		// �X�P�[��
		m_tRotation,	// ��]
		m_pModel.get(),       // ���f���|�C���^
		Camera::GetInstance(),// �J�����|�C���^
		true,                 // ���邭���邩�ǂ���
		XMFLOAT3(0.5f, 0.5f, 0.5f) // ���C�e�B���O�F
	);
}

// @brief �����蔻�����ǉ�����֐�
// @param InTag �ǉ����铖���蔻����
Collision::Info CGameObject::GetCollisionInfo(Collision::Tag InTag)
{
	// �w�肳�ꂽ�^�O�̓����蔻���������
	for (const auto& collisionInfo : m_tCollisionInfos)
	{
		for (const auto& tag : collisionInfo.tag)
		{
			if (tag == InTag)
			{
				return collisionInfo; // ���������ꍇ�͂��̏���Ԃ�
			}
		}
	}
	// ������Ȃ������ꍇ�͋��Collision::Info��Ԃ�
	return Collision::Info();
}
