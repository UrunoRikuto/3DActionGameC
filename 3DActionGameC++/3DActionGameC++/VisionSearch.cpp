/*
* @file VisionSearch.cpp
* @brief VisionSensor�N���X�̎����t�@�C��
* @author �F���엤�l
* @date 2025/08/19 �N���X�̎���
*/



/* �w�b�_�[�̃C���N���[�h */
#include "VisionSearch.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Defines.h"

// @brief �R���X�g���N�^
// @param In_Self �������g�̃I�u�W�F�N�g
CVisionSearch::CVisionSearch(CNpcBase* In_Self)
	: m_tDirection(0.0f, 0.0f, 1.0f) // ����������Z���������ɐݒ�
	, m_fDetectionValue(0.0f) // ���������l��0�ɐݒ�
	, m_fViewDistance(0.0f) // ���싗����NPC�̒l����擾
	, m_pSelfObject(In_Self)// ���G���s���I�u�W�F�N�g��ݒ�
	, m_pTargetObject(nullptr) // ���G�Ώۂ̃I�u�W�F�N�g��������
	, m_fLostTimer(0.0f) // �������^�C�}�[��������
{
	m_pRay = new CRay(); // ���C(����)�̃C���X�^���X�𐶐�
}

// @brief �f�X�g���N�^
CVisionSearch::~CVisionSearch()
{

}

// @brief �p�����[�^�[�̏����ݒ�
// @param In_ViewDistance ���싗��
// @param In_TargetObject ���G�Ώۂ̃I�u�W�F�N�g
void CVisionSearch::InitParam(float In_ViewDistance, CPlayer* In_TargetObject)
{
	m_fViewDistance = In_ViewDistance; // ���싗����ݒ�
	m_pTargetObject = In_TargetObject; // ���G�Ώۂ̃I�u�W�F�N�g��ݒ�
}

// @brief ���G����
// @param In_SelfPosition ���g�̈ʒu
// @param In_CurrentSearchState ���݂̍��G���
// @return �X�V��̍��G���
VisionSearchState CVisionSearch::Search(const XMFLOAT3& In_SelfPosition, VisionSearchState In_CurrentSearchState)
{
	// ���O��Ԃ̎g�p
	using namespace GameValue::Npc;
	using namespace GameValue::StealthCorrection;

	// NPC�̎�ނ��擾
	NpcType npcType = m_pSelfObject->GetNpcType();
	//  NPC�̎�ނɂ���Ď��F�����𒲐�
	switch (npcType)
	{
	case NpcType::Normal:
		m_fViewDistance = Normal::VIEW_DISTANCE; // �ʏ�NPC�̎��싗����ݒ�
		break;
	case NpcType::Target:
		m_fViewDistance = Target::VIEW_DISTANCE; // �^�[�Q�b�gNPC�̎��싗����ݒ�
		break;
	case NpcType::Sniper:
		m_fViewDistance = Sniper::VIEW_DISTANCE; // �X�i�C�p�[NPC�̎��싗����ݒ�
		break;
	case NpcType::Patrol:
		m_fViewDistance = Patrol::VIEW_DISTANCE; // ����NPC�̎��싗����ݒ�
		break;
	}

	// �v���C���[�̎p����Ԃ��擾
	PlayerPosture playerPosture = m_pTargetObject->GetPosture();
	// �v���C���[�̎p����Ԃɉ����Ď��F�����𒲐�
	switch (playerPosture)
	{
	case PlayerPosture::Stand:
		m_fViewDistance *= STAND_CORRECTION; // �����p���̎��F�����͂��̂܂�
		break;
	case PlayerPosture::Crouch:
		m_fViewDistance *= CROUCH_CORRECTION; // ���Ⴊ�ݎp���̎��F������␳
		break;
	case PlayerPosture::Prone:
		m_fViewDistance *= PRONE_CORRECTION; // �����p���̎��F������␳
		break;
	case PlayerPosture::Hide:
		m_fViewDistance *= HIDE_CORRECTION; // �����p���̎��F������␳
		break;
	}

	// �^�[�Q�b�g�̈ʒu���擾
	XMFLOAT3 TargetPos = m_pTargetObject->GetPosition();

	// �^�[�Q�b�g�Ƃ̋������v�Z
	float distance = StructMath::Distance(In_SelfPosition, TargetPos);

	// �^�[�Q�b�g�����싗�����ɂ��邩�ǂ������`�F�b�N
	if (distance < m_fViewDistance)
	{
		switch (In_CurrentSearchState)
		{
		case VisionSearchState::None:
			/// @Todo: ����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ����̃`�F�b�N
			/// �O�p�`�̓��O������g�p���āA����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ������m�F����

			/// @Todo: �^�[�Q�b�g�Ƃ̊Ԃɏ�Q�������邩�ǂ����̃`�F�b�N
			/// ���C�L���X�g���g�p���ăI�u�W�F�N�g�����m����
			/// ���m�ł��Ȃ��������Ԃ��^��ɕύX
			/// ���m�����ꍇ�������Ȃ�
			
			// �^�[�Q�b�g�̂���ʒu
			m_pRay->SetOrigin(In_SelfPosition);
			// �^�[�Q�b�g�̕������v�Z
			m_pRay->SetDirection(StructMath::Normalize(StructMath::Sub(TargetPos, In_SelfPosition)));

			// ���C�L���X�g�����s���āA�^�[�Q�b�g�Ƃ̊Ԃɏ�Q�������邩�ǂ������`�F�b�N

			/// @Todo: �t�B�[���h�I�u�W�F�N�g�̃^�O�����I�u�W�F�N�g���܂Ƃ߂鏈�����쐬����

			// if(m_pRay->Cast())

			return VisionSearchState::Doubt;
			break;
		case VisionSearchState::Doubt:
			/// @Todo: ����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ����̃`�F�b�N
			/// �O�p�`�̓��O������g�p���āA����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ������m�F����

			/// @Todo: �^�[�Q�b�g�Ƃ̊Ԃɏ�Q�������邩�ǂ����̃`�F�b�N
			/// ���C�L���X�g���g�p���ăI�u�W�F�N�g�����m����
			/// ���m�ł��Ȃ������甭���l��i�߂�
			/// ���m�����ꍇ�ALostTimer�����Z����
			m_fLostTimer += 1.0f / fFPS; // �t���[�����[�g�ɉ����ă^�C�}�[�����Z
			break;
		case VisionSearchState::Lost:
			/// @Todo: ����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ����̃`�F�b�N
			/// �O�p�`�̓��O������g�p���āA����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ������m�F����
			/// ���m�ł��Ȃ������ꍇ�����l������������


			break;
		case VisionSearchState::Discovery:
			/// @Todo: ���F�������Ȃ��ɔ������
			/// @Todo: ���F�����O�Ȃ�LostTimer�����Z����
			m_fLostTimer += 1.0f / fFPS; // �t���[�����[�g�ɉ����ă^�C�}�[�����Z
			break;
		}
	}
	
	//switch (In_CurrentSearchState)
	//{
	//	// ���G�l�����Z�b�g
	//case VisionSearchState::None:
	//	m_fDetectionValue = 0.0f;
	//	break;
	//	// �^�[�Q�b�g���^��̏ꍇ�A���G�l�𑝉�
	//case VisionSearchState::Doubt:
	//	float DetectionPower = 1.0f / fFPS * (m_fViewDistance / distance);
	//	m_fDetectionValue += DetectionPower;
	//	break;
	//	// �^�[�Q�b�g�����������ꍇ�A���G�l������
	//case VisionSearchState::Lost:
	//	float DetectionPower = 1.0f / fFPS;
	//	m_fDetectionValue -= DetectionPower; 
	//	break;
	//	// �^�[�Q�b�g�𔭌������ꍇ�A���G�l���ő�ɐݒ�
	//case VisionSearchState::Discovery:
	//	m_fDetectionValue = 1.0f; 
	//	break;
	//}

	//if (m_fDetectionValue > 1.0f)
	//{
	//	// ���G�l���ő�l�𒴂����ꍇ��1.0f�ɐ���
	//	m_fDetectionValue = 1.0f;
	//	// �^�[�Q�b�g�𔭌�������ԂɑJ��
	//	return VisionSearchState::Discovery;
	//}
	//else if (m_fDetectionValue < 0.0f)
	//{
	//	// ���G�l��0�����ɂȂ����ꍇ��0.0f�ɐ���
	//	m_fDetectionValue = 0.0f;
	//	// �^�[�Q�b�g������������ԂɑJ��
	//	return VisionSearchState::None;
	//}
	
	return In_CurrentSearchState;
}

// @brief �f�o�b�N�`�揈��
void CVisionSearch::DebugDraw(void)
{

}
