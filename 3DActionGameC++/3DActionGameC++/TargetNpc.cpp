/*
* @file TargetNpc.cpp
* @brief �^�[�Q�b�gNPC�̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* * @date 2025/08/04 �^�[�Q�b�gNPC�̃N���X�̎���
*/

/* �w�b�_�[�̃C���N���[�h */
#include "TargetNpc.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "MoveSystem.h"

// @brief �R���X�g���N�^
CTargetNpc::CTargetNpc(XMFLOAT3 In_SpawnPoint)
{
	// ���f���̐���
	m_pModel = std::make_unique<Model>();
	// ���f���̓ǂݍ���
	if (!m_pModel->Load(MODEL_PATH("TargetNPC.obj")))
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
	// �{�b�N�X�̑傫����ݒ�
	m_tCollisionInfos[2].box.size = m_tScale;

	// �ړ��V�X�e���̏�����
	m_pMoveSystem = std::make_unique<CMoveSystem>(MoveSystemType::Loop, 0.1f);
	// �ړ��|�C���g�̒ǉ�
	std::vector<XMFLOAT3> movePoints = {
		m_tPosition,
		{ 40.0f, m_tPosition.y, 40.0f },
		{ 40.0f, m_tPosition.y,  0.0f }
	};

	m_pMoveSystem->AddMovePoints(movePoints);
}

// @brief �f�X�g���N�^
CTargetNpc::~CTargetNpc()
{

}

// @brief �X�V����
void CTargetNpc::Update(void)
{
	using namespace StructMath;

	// �ړ�
	XMFLOAT3 movePoint = m_pMoveSystem->GetMovePoint(m_tPosition);
	SetPosition(Add(m_tPosition, Mul(Direction(m_tPosition, movePoint), m_pMoveSystem->GetMoveSpeed())));
}
