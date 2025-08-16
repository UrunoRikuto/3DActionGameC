/*
* @file Bullet.cpp
* @brief �e�ۃN���X�̎����t�@�C��
* @author �F���엤�l
* * @date 2025/08/16 �N���X�̎���
*/

/* �w�b�_�[�̃C���N���[�h */
#include "Bullet.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"

// @brief �R���X�g���N�^
CBullet::CBullet()
	:CGameObject() // ���N���X�̃R���X�g���N�^���Ăяo��
	, m_tDirection(0.0f, 0.0f, 0.0f) // �����i�s������ݒ�
	, m_fMovePower(0.1f) // �����ړ��͂�ݒ�
	, m_fLifeTime(0.0f) // �e�̐������Ԃ�ݒ�
{
	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(MODEL_PATH("Bullet.obj"), 0.01f))
	{
		MessageBox(NULL, "�e�ۃ��f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
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
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Field);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[0].box.center = m_tPosition;
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[0].box.size = m_tScale;
}

// @brief �f�X�g���N�^
CBullet::~CBullet()
{

}

// @brief �X�V����
void CBullet::Update(void)
{
	// ���O��Ԃ̎d�l
	using namespace GameValue::Bullet;

	// �e�ۂ̈ʒu��i�s�����ɉ����čX�V
	m_tPosition = StructMath::Add(m_tPosition, StructMath::Mul(m_tDirection, m_fMovePower));

	// �������Ԃ��X�V
	m_fLifeTime += 1.0f / fFPS;

	// �������Ԃ���莞�Ԃ𒴂�����e�ۂ��폜
	if (m_fLifeTime > LIFE_TIME) // 5�b�Œe�ۂ��폜
	{
		// �������폜
		delete this; // ���������[�N��h�����߂Ɏ������g���폜
		return;
	}
}

// @brief �p�����[�^�[�̐ݒ�
// @param direction �i�s����
// @param movePower �ړ���
void CBullet::SetParam(const XMFLOAT3& direction, float movePower)
{
	m_tDirection = direction; // �i�s������ݒ�
	m_fMovePower = movePower; // �ړ��͂�ݒ�
}

// @brief �����蔻��̏Փˎ��̏���
// @param InCollisionInfo �ՓˑΏ�
void CBullet::Hit(const Collision::Info& InCollisionInfo)
{
	// �Փ˂����ꍇ�A�e�ۂ��폜
	delete this; // ���������[�N��h�����߂Ɏ������g���폜
}
