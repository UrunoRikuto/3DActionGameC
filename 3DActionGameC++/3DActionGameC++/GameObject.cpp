/*=====================================================================
* @file GameObject.cpp
* @brief �Q�[���I�u�W�F�N�g�̊��N���X��Cpp�t�@�C��
=====================================================================*/

/* �w�b�_�[�ŗ��p����V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"

/* �w�b�_�[�̃C���N���[�h */
#include "GameObject.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "ModelDrawSetting.h"

// @brief �R���X�g���N�^
CGameObject::CGameObject()
	: m_pModel(nullptr) // ���f���|�C���^�̏�����
	, m_tPosition(0.0f, 0.0f, 0.0f) // �����ʒu
	, m_fAjustPositionY(0.0f) // �v���C���[�̐^���̒n�ʂ̍����̏����l
	, m_tScale(1.0f, 1.0f, 1.0f) // �����X�P�[��
	, m_tRotation(0.0f, 0.0f, 0.0f) // ������]
	, m_tCollisionInfos{} // �����蔻����̏�����
	, m_bDestroy(false) // �j���t���O�̏�����
{
	
}

// @brief �f�X�g���N�^
CGameObject::~CGameObject()
{

}

// @brief �X�V����
void CGameObject::Update()
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

}

// @brief �`�揈��
void CGameObject::Draw()
{
	// �j���t���O�������Ă���ꍇ�͍X�V���s��Ȃ�
	if (m_bDestroy)return;

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
std::vector<Collision::Info> CGameObject::GetCollisionInfo(Collision::Tag InTag)
{
	if (InTag == Collision::Tag::All)
	{
		// �S�Ă̓����蔻�����Ԃ�
		return m_tCollisionInfos;
	}

	std::vector<Collision::Info> result; // ���ʂ��i�[����x�N�^�[

	// �w�肳�ꂽ�^�O�̓����蔻���������
	for (const auto& collisionInfo : m_tCollisionInfos)
	{
		for (const auto& tag : collisionInfo.tag)
		{
			if (tag == InTag)
			{
				// ���������ꍇ�͂��̏������ʂɒǉ�
				result.push_back(collisionInfo);
			}
		}
	}
	// ���ʂ�Ԃ�
	return result;
}

// @brief �ʒu����ݒ肷��֐�
// @param position �ݒ肷��ʒu���
void CGameObject::SetPosition(const XMFLOAT3& position)
{
	m_tPosition = position; // �ʒu����ݒ�
	// �����蔻��̒��S�ʒu���X�V
	for (auto& collisionInfo : m_tCollisionInfos)
	{
		if (collisionInfo.type == Collision::Type::eBox)
		{
			collisionInfo.box.center = StructMath::Add(m_tPosition,collisionInfo.AdjustCenter); // �{�b�N�X�̒��S�ʒu���X�V
		}
	}
}

// @brief �X�P�[������ݒ肷��֐�
// @param scale �ݒ肷��X�P�[�����
void CGameObject::SetScale(const XMFLOAT3& scale)
{
	m_tScale = scale; // �X�P�[������ݒ�
	// �����蔻��̑傫�����X�V
	for (auto& collisionInfo : m_tCollisionInfos)
	{
		if (collisionInfo.type == Collision::Type::eBox)
		{
			collisionInfo.box.size = m_tScale; // �{�b�N�X�̑傫�����X�V
		}
	}
}
