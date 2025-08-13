/*
* @file GuardNpc.cpp
* @brief ��qNPC�̃N���X�̎����t�@�C��
* @author �F���엤�l
* @date 2025/08/14 ��qNPC�̃N���X�̎���
*/

/* �w�b�_�[�̃C���N���[�h */
#include "GuardNpc.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "Defines.h"

// @brief�R���X�g���N�^
CGuardNpc::CGuardNpc(XMFLOAT3 In_SpawnPoint)
	:CNpcBase() // ���N���X�̃R���X�g���N�^���Ăяo��
{	
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(ModelPath::GUARD_NPC_PATH))
	{
		MessageBox(NULL, "�^�[�Q�b�gNPC���f���̓ǂݍ��݂Ɏ��s���܂����B", "Error", MB_OK);
	}
	// �ʒu�A�X�P�[���A��]�̐ݒ�
	m_tScale = { 2.0f,2.0f,2.0f };
	m_tPosition = { In_SpawnPoint.x, In_SpawnPoint.y + (m_tScale.y * 3) / 2, In_SpawnPoint.z };
	m_tRotation = { 0.0f, 0.0f, 0.0f };

	// �����蔻��̐ݒ�
	// �����蔻����̃T�C�Y��3�ɐݒ�
	m_tCollisionInfos.resize(3);
	//--- ���̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[0].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::TargetNpc);
	m_tCollisionInfos[0].tag.push_back(Collision::Tag::Head);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[0].box.center = StructMath::Add(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[0].AdjustCenter = XMFLOAT3(0.0f, m_tScale.y, 0.0f); // ���S�ʒu�̒���
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[0].box.size = m_tScale;
	//--- �̂̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[1].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::TargetNpc);
	m_tCollisionInfos[1].tag.push_back(Collision::Tag::Body);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[1].box.center = m_tPosition;
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[1].box.size = m_tScale;
	//--- ���̓����蔻����̏�����
	// �����蔻��̎�ނ�ݒ�
	m_tCollisionInfos[2].type = Collision::eBox;
	// �^�O��ǉ�
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::TargetNpc);
	// �^�O��ǉ�
	m_tCollisionInfos[2].tag.push_back(Collision::Tag::Foot);
	// ���S�ʒu��ݒ�
	m_tCollisionInfos[2].box.center = StructMath::Sub(m_tPosition, XMFLOAT3(0.0f, m_tScale.y, 0.0f));
	m_tCollisionInfos[2].AdjustCenter = XMFLOAT3(0.0f, -m_tScale.y, 0.0f); // ���S�ʒu�̒���
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[2].box.size = m_tScale;

	// �ړ��V�X�e���̏�����
	m_pMoveSystem = std::make_unique<CMoveSystem>(MoveSystemType::Reverse, 0.1f);
	// �ړ��|�C���g�̒ǉ�
	std::vector<XMFLOAT3> movePoints = {
		m_tPosition,
		XMFLOAT3(m_tPosition.x - 40.0f,m_tPosition.y,m_tPosition.z),
		XMFLOAT3(m_tPosition.x - 40.0f,m_tPosition.y,m_tPosition.z - 40.0f),
		XMFLOAT3(m_tPosition.x,m_tPosition.y,m_tPosition.z - 40.0f)
	};

	m_pMoveSystem->AddMovePoints(movePoints);
}

// @brief�f�X�g���N�^
CGuardNpc::~CGuardNpc()
{

}

// @brief �X�V����
void CGuardNpc::Update(void)
{
	// ���N���X�̍X�V����(NPC���ʏ���)
	CNpcBase::Update();
}
