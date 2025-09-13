/*=====================================================================
* @file VisionSearch.cpp
* @brief ���o���G�̎����t�@�C��
=====================================================================*/


/* �w�b�_�[�Ŏg�p����C���N���[�h */
#include "NpcBase.h"
#include "Ray.h"

/* �w�b�_�[�̃C���N���[�h */
#include "VisionSearch.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Defines.h"
#include "GameValues.h"
#include "Main.h"
#include "SceneGame.h"
#include "Geometory.h"

// @brief �R���X�g���N�^
// @param In_Self �������g�̃I�u�W�F�N�g
CVisionSearch::CVisionSearch(CNpcBase* In_Self)
	: m_tDirection(0.0f, 0.0f, 1.0f) // ����������Z���������ɐݒ�
	, m_fDetectionValue(0.0f) // ���������l��0�ɐݒ�
	, m_pSelfObject(In_Self)// ���G���s���I�u�W�F�N�g��ݒ�
	, m_fLostTimer(0.0f) // �������^�C�}�[��������
	, m_TrianglePoint{} // �O�p�`�̒��_�|�C���g��������
	, m_pDetectionGauge(nullptr) // ���G�Q�[�W��������
{
	m_pRay = new CRay(); // ���C(����)�̃C���X�^���X�𐶐�
}

// @brief �f�X�g���N�^
CVisionSearch::~CVisionSearch()
{

}

// @brief ���G����
// @param In_SelfPosition ���g�̈ʒu
// @param In_CurrentSearchState ���݂̍��G���
// @return �X�V��̍��G���
VisionSearchState CVisionSearch::Search(const XMFLOAT3& In_SelfPosition, VisionSearchState In_CurrentSearchState)
{
	// ���O��Ԃ̎g�p
	using namespace GameValue::Npc;
	using namespace GameValue::VisionSearch;
	using namespace StructMath;

	// ����p�̍X�V
	UpdateViewAngle();

	// NPC�̎�ނ��擾
	NpcType npcType = m_pSelfObject->GetNpcType();
	//  NPC�̎�ނɂ���Ď��F�����𒲐�
	switch (npcType)
	{
	case NpcType::Normal:
		m_fViewDistance = Normal::VIEW_DISTANCE; // �ʏ�NPC�̎��싗����ݒ�
		break;
	}

	// �v���C���[�̎p����Ԃ��擾
	CPlayer* pTarget = m_pSelfObject->GetTarget();
	PlayerPosture playerPosture = pTarget->GetPosture();
	// �v���C���[�̎p����Ԃɉ����Ď��F�����𒲐�
	switch (playerPosture)
	{
	case PlayerPosture::Stand:
		m_fViewDistance *= StealthCorrection::STAND; // �����p���̎��F�����͂��̂܂�
		break;
	case PlayerPosture::Crouch:
		m_fViewDistance *= StealthCorrection::CROUCH; // ���Ⴊ�ݎp���̎��F������␳
		break;
	case PlayerPosture::Prone:
		m_fViewDistance *= StealthCorrection::PRONE; // �����p���̎��F������␳
		break;
	case PlayerPosture::Hide:
		m_fViewDistance *= StealthCorrection::HIDE; // �����p���̎��F������␳
		break;
	}

	// �^�[�Q�b�g�̈ʒu���擾
	XMFLOAT3 TargetPos = pTarget->GetPosition();

	// �^�[�Q�b�g�Ƃ̋������v�Z
	float distance = Distance(In_SelfPosition, TargetPos);

	// ���G��Ԃɂ���ď����𕪊�
	switch (In_CurrentSearchState)
	{
	case VisionSearchState::None:
		// �^�[�Q�b�g�����싗�����ɂ��邩�ǂ������`�F�b�N
		if (distance < m_fViewDistance)
		{
			// �^�[�Q�b�g�̂���ʒu
			m_pRay->SetOrigin(In_SelfPosition);
			// �^�[�Q�b�g�̕������v�Z
			m_pRay->SetDirection(Normalize(Sub(TargetPos, In_SelfPosition)));

			// ����p���Ƀ^�[�Q�b�g�����邩�ǂ����̃`�F�b�N
			if (CheckTargetInViewAngle())
			{
				// �^�[�Q�b�g�Ƃ̊Ԃɏ�Q�������邩�ǂ����̃`�F�b�N
				if (CheckObstacle())
				{
					// �^�[�Q�b�g�Ƃ̊Ԃɏ�Q��������ꍇ�́A�ُ�Ȃ���Ԃ��ێ�
					return VisionSearchState::None;
				}
				// ���F�������Ƀ^�[�Q�b�g�����āA��Q�����Ȃ��ꍇ�͋^���ԂɑJ��
				return VisionSearchState::Doubt;
			}
		}
		break;
	case VisionSearchState::Doubt:
		// �^�[�Q�b�g�����싗�����ɂ��邩�ǂ������`�F�b�N
		if (distance < m_fViewDistance)
		{
			// ����p���Ƀ^�[�Q�b�g�����邩�ǂ����̃`�F�b�N
			if (CheckTargetInViewAngle())
			{
				// �^�[�Q�b�g�Ƃ̊Ԃɏ�Q�������邩�ǂ����̃`�F�b�N
				if (CheckObstacle())
				{
					// LostTimer�����Z
					m_fLostTimer += 1.0f / fFPS;
				}
				else
				{
					// �����l�𑝉�
					// �����l�𑝉�������B�������߂��قǑ����ʂ��傫���Ȃ�悤�ɒ���
					m_fDetectionValue += 1.0f / fFPS * (m_fViewDistance / distance);
					
					// LostTimer�����Z�b�g
					m_fLostTimer = 0.0f;
				}

				// �������l����莞�Ԃ𒴂����ꍇ�͌�������ԂɑJ��
				if (m_fLostTimer > LOST_TIME)
				{
					// LostTimer����莞�Ԃ𒴂����ꍇ�͌�������ԂɑJ��
					// �����l����芄������������
					m_fDetectionValue *= LOST_DETECTION_RATE;
					// LostTimer�����Z�b�g
					m_fLostTimer = 0.0f;

					return VisionSearchState::Lost;
				}
				// �����l���ő�l�𒴂����ꍇ�͔�����ԂɑJ��
				if (m_fDetectionValue > MAX_DETECTION_TIME)
				{
					m_fDetectionValue = MAX_DETECTION_TIME; // �����l���ő�l�ɐ���
					return VisionSearchState::Discovery; // ������ԂɑJ��
				}
			}
		}
		// �Q�[�WUI����������Ă��Ȃ��ꍇ�͐���
		if (m_pDetectionGauge == nullptr)
		{
			m_pDetectionGauge = new CGaugeUI(1.0f, true, GaugeType::Detection);
			// �Q�[�WUI�̃p�����[�^�ݒ�
			m_pDetectionGauge->SetParam({ 3.0f,2.0f,1.0f });
		}
		else
		{
			// �Q�[�WUI�̍X�V
			m_pDetectionGauge->Updatde(
				Add(In_SelfPosition, XMFLOAT3(0.0f, 3.0f, 0.0f)), // ���g�̈ʒu�̏�����ɕ\��
				m_fDetectionValue); // �����l�̊�����ݒ�
		}

		break;
	case VisionSearchState::Lost:
		// �^�[�Q�b�g�����싗�����ɂ��邩�ǂ������`�F�b�N
		if (distance < m_fViewDistance)
		{
			// ����p���Ƀ^�[�Q�b�g�����邩�ǂ����̃`�F�b�N
			if (CheckTargetInViewAngle())
			{
				// �^�[�Q�b�g�Ƃ̊Ԃɏ�Q�������邩�ǂ����̃`�F�b�N
				if (CheckObstacle())
				{
					// LostTimer�����Z
					m_fLostTimer += 1.0f / fFPS;
				}
				else
				{
					// �����l�𑝉�
					m_fDetectionValue += 1.0f / fFPS * (m_fViewDistance / distance);
				}
			}
		}
		else
		{
			// LostTimer�����Z
			m_fLostTimer += 1.0f / fFPS;
			// �����l�����Z�b�g
			m_fDetectionValue = 0.0f;
		}

		// �������l����莞�Ԃ𒴂����ꍇ�ُ͈�Ȃ���ԂɑJ��
		if (m_fLostTimer > LOST_TIME)
		{
			// LostTimer�����Z�b�g
			m_fLostTimer = 0.0f;
			// �����l�����Z�b�g
			m_fDetectionValue = 0.0f;

			return VisionSearchState::None;
		}
		// �����l���ő�l�𒴂����ꍇ�͔�����ԂɑJ��
		if (m_fDetectionValue > MAX_DETECTION_TIME)
		{
			// �����l���ő�l�ɐ���
			m_fDetectionValue = MAX_DETECTION_TIME;
			// ������ԂɑJ��
			return VisionSearchState::Discovery;
			// �Q�[�WUI�̍폜
			if (m_pDetectionGauge != nullptr)
			{
				delete m_pDetectionGauge;
				m_pDetectionGauge = nullptr;
			}
		}
		break;
	case VisionSearchState::Discovery:
		// �^�[�Q�b�g�����싗�����ɂ��邩�ǂ������`�F�b�N
		if (distance < m_fViewDistance)
		{
			return VisionSearchState::Discovery; // ������Ԃ��ێ�
		}
		else
		{
			// �^�[�Q�b�g�����싗���O�ɏo���ꍇ�͌�������ԂɑJ��
			return VisionSearchState::Lost; // ��������ԂɑJ��
		}
		break;

	}

	return In_CurrentSearchState;
}

// @brief �f�o�b�N�`�揈��
void CVisionSearch::DebugDraw(void)
{
#ifdef _DEBUG

	SetRender3D();
	// ����p(�O�p�`)�̕`��
	// �O�p�`�̒��_�����Ԑ����쐬
	Geometory::AddLine(m_TrianglePoint[0], m_TrianglePoint[1], XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	Geometory::AddLine(m_TrianglePoint[1], m_TrianglePoint[2], XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	Geometory::AddLine(m_TrianglePoint[2], m_TrianglePoint[0], XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));

	// �^�[�Q�b�g�Ƃ̋���
	XMFLOAT3 selfPos = m_pSelfObject->GetPosition();
	XMFLOAT3 targetPos = m_pSelfObject->GetTarget()->GetPosition();
	XMFLOAT4 Color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	// ���F�������ɂ���ꍇ�͐ԐF�A���Ȃ��ꍇ�͗ΐF�Ő���`��
	if (StructMath::Distance(selfPos, targetPos) < m_fViewDistance)
	{
		Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	Geometory::AddLine(selfPos, targetPos, Color);

	// ���̕`��
	Geometory::DrawLines();

#endif // _DEBUG
}

// @brief ����p�̍X�V
void CVisionSearch::UpdateViewAngle(void)
{
	// ���O��Ԃ̎g�p
	using namespace GameValue::Npc;

	// ����p
	float viewAngle = 60.0f;
	// ���싗��
	float viewDistance = 20.0f;

	// NPC�̎�ނ��擾
	NpcType npcType = m_pSelfObject->GetNpcType();
	//  NPC�̎�ނɂ���Ď��F�����Ǝ���p�𒲐�
	switch (npcType)
	{
	case NpcType::Normal:
		viewAngle = Normal::VIEW_ANGLE;
		viewDistance = Normal::VIEW_DISTANCE;
		break;
	}

	// �v�Z
	float angle = viewAngle / 2.0f;
	float height = viewDistance;

	// ���G�҂̈ʒu
	XMFLOAT3 selfPos = m_pSelfObject->GetPosition();
	XMVECTOR basePos = XMLoadFloat3(&selfPos);

	// ����p�̒[�����[�J���Œ�`
	XMFLOAT3 limitPos[2] = {
		{height, 0.0f,  tanf(TORAD(angle)) * height},
		{height, 0.0f, -tanf(TORAD(angle)) * height}
	};

	// ����p�̒[�����[���h���W�ɕϊ�
	float RotY = m_pSelfObject->GetRotation().y;
	// Y����]�s��̍쐬
	XMMATRIX rotationMatrix = XMMatrixRotationY(TORAD(RotY));

	// 2�̒��_��ϊ�
	for (int i = 0; i < 2; ++i)
	{
		XMVECTOR pos = XMLoadFloat3(&limitPos[i]);

		// ���L�����̈ʒu�����_�Ƃ������΍��W�ɕϊ����ĉ�]
		pos = XMVector3Transform(pos, rotationMatrix);

		// ���[���h���W�ɖ߂�
		pos += basePos;

		XMStoreFloat3(&limitPos[i], pos);
	}

	// �^�[�Q�b�g�̍��W������p�͈͓̔��ɂ��邩�ǂ������`�F�b�N
	// �O�p�`�̓��O������g�p���āA����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ������m�F����
	m_TrianglePoint[0] = selfPos;
	m_TrianglePoint[1] = limitPos[0];
	m_TrianglePoint[2] = limitPos[1];
}

// @brief �^�[�Q�b�g�����F�������ɂ��邩�ǂ������`�F�b�N
// @return �������ꍇtrue�Ȃ������ꍇfalse
bool CVisionSearch::CheckObstacle(void) const
{
	// ���݂̃V�[�����擾
	CSceneGame* pSceneGame = static_cast<CSceneGame*>(GetCurrentScene());

	// �t�B�[���h�I�u�W�F�N�g�̃��X�g���擾
	for (auto object : pSceneGame->GetAllFieldObjects())
	{
		// �I�u�W�F�N�g�̃R���W���������擾
		if (m_pRay->Cast(object->GetCollisionInfo(Collision::Tag::FieldObject)))
		{
			// ��Q�������邱�Ƃ�����
			return true;
		}
	}

	// ��Q�����Ȃ����Ƃ�����
	return false;
}

// @brief ����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ������`�F�b�N
// @return �����ꍇtrue���Ȃ������ꍇ�ꍇfalse
bool CVisionSearch::CheckTargetInViewAngle(void)
{
	// �^�[�Q�b�g�̈ʒu���擾
	XMFLOAT3 targetPos = m_pSelfObject->GetTarget()->GetPosition();

	// �^�[�Q�b�g������p�͈͓̔��ɂ��邩�ǂ������`�F�b�N
	if (CheckPointInTriangle(targetPos))
	{
		// �|�C���g���O�p�`�͈͓̔��ɂ��邱�Ƃ�����
		return true;
	}


	// �^�[�Q�b�g������p�͈͓̔��ɂ��Ȃ����Ƃ�����
	return false;
}

// @brief ����p�͈͓̔��Ƀ|�C���g�����邩�ǂ����̃`�F�b�N
// @param P �m�F����|�C���g
// @param A �O�p�`�̒��_
// @param B �O�p�`�̒��_
// @param C �O�p�`�̒��_
bool CVisionSearch::CheckPointInTriangle(const XMFLOAT3& Point) const
{
	// ���O��Ԃ̎g�p
	using namespace StructMath;

	// �x�N�g���̌v�Z
	XMFLOAT3 v0 = Sub(m_TrianglePoint[1], m_TrianglePoint[0]);
	XMFLOAT3 v1 = Sub(m_TrianglePoint[2], m_TrianglePoint[0]);
	XMFLOAT3 v2 = Sub(Point, m_TrianglePoint[0]);
	// ���ς̌v�Z
	float dot00 = Dot(v0, v0);
	float dot01 = Dot(v0, v1);
	float dot02 = Dot(v0, v2);
	float dot11 = Dot(v1, v1);
	float dot12 = Dot(v1, v2);
	// �o�����[�̌v�Z
	float invDenom = 1.0f / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	// �|�C���g���O�p�`�͈͓̔��ɂ��邩�ǂ������`�F�b�N
	if ((u >= 0) && (v >= 0) && (u + v <= 1))
	{
		// �|�C���g���O�p�`�͈͓̔��ɂ��邱�Ƃ�����
		return true;
	}
	return false;
}
