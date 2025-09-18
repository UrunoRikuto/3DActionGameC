/*=====================================================================
* @file MoveSystem.cpp
* @brief �ړ��V�X�e���̎����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "MoveSystem.h"

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Geometory.h"
#include "Main.h"

// @brief �R���X�g���N�^
CMoveSystem::CMoveSystem(MoveSystemType In_Type, float In_MoveSpeed)
	: m_eMoveSystemType(In_Type) // �ړ��V�X�e���̎�ނ�ݒ�
	, m_fMoveSpeed(In_MoveSpeed) // �ړ����x�̏�����
	, m_vtMovePointList()		// �ړ��|�C���g�̃��X�g��������
	, m_nCurrentPointIndex(0) // ���݂̈ړ��|�C���g�̃C���f�b�N�X��������
	, m_bIsEndPoint(false)
	, m_fAdjustY(0.0f) // Y���W�̒����l��������
{
	// �ړ��|�C���g�̃��X�g��������
	m_vtMovePointList.clear();
}

// @brief �f�X�g���N�^
CMoveSystem::~CMoveSystem()
{

}

// @brief ���Ɉړ�����ړ��|�C���g���擾
// @param In_CurrentPos ���݂̈ʒu
// @return ���Ɉړ�����ړ��|�C���g
XMFLOAT3 CMoveSystem::GetMovePoint(const XMFLOAT3& In_CurrentPos)
{
	// �ړ��|�C���g�̃��X�g����łȂ��ꍇ
	if (m_vtMovePointList.empty())
	{
		// �ړ��|�C���g���Ȃ��ꍇ�͌��݈ʒu��Ԃ�
		return In_CurrentPos;
	}

	XMFLOAT3 MoverPos = In_CurrentPos;
	XMFLOAT3 TargetPos = m_vtMovePointList[m_nCurrentPointIndex];

	//(��)Y���W�̖���{���A�̂悤�Ȃ��̂����Ȃ�����Y���W����Ȃ�
	MoverPos.y = 0.0f;
	TargetPos.y = 0.0f;

	// ���݂̈ʒu���ړ��|�C���g�̈�苗���ȓ��ɂ���ꍇ
	if (StructMath::Distance(MoverPos, TargetPos) < m_fMoveSpeed)
	{
		// ���̈ړ��|�C���g�ɐi��
		switch (m_eMoveSystemType)
		{
		case MoveSystemType::Once:
			m_nCurrentPointIndex++;
			break;
		case MoveSystemType::Loop:
			m_nCurrentPointIndex++;
			break;
		case MoveSystemType::Reverse:
			if (!m_bIsEndPoint)
			{
				m_nCurrentPointIndex++;
			}
			else
			{
				// ���]���Ă���̂Ńf�N�������g
				m_nCurrentPointIndex--;
			}
			break;
		}
	}

	// ���݂̈ړ��|�C���g�̃C���f�b�N�X�����X�g�̃T�C�Y�𒴂��Ă���ꍇ
	if (m_nCurrentPointIndex > static_cast<int>(m_vtMovePointList.size()) - 1) 
	{
		switch (m_eMoveSystemType)
		{
		case MoveSystemType::Once:
			// �Ō�̃|�C���g�ɐݒ�
			m_nCurrentPointIndex = static_cast<int>(m_vtMovePointList.size()) - 1;
			// �I�_�t���O�𗧂Ă�
			m_bIsEndPoint = true;

			// ���������Ȃ��̂Ō��݈ʒu��Ԃ�
			return In_CurrentPos; 
			break;
		case MoveSystemType::Loop:
			// �ŏ��̃|�C���g�ɐݒ�
			m_nCurrentPointIndex = 0;
			// �I�_�t���O�����낷
			m_bIsEndPoint = false;
			break;
		case MoveSystemType::Reverse:
			// �Ō�̃|�C���g�ɐݒ�
			m_nCurrentPointIndex = static_cast<int>(m_vtMovePointList.size()) - 1;
			// �I�_�t���O�𗧂Ă�
			m_bIsEndPoint = true;
			break;
		}
	}
	// ���݂̃|�C���g�̃C���f�b�N�X��0�����̏ꍇ
	else if(m_nCurrentPointIndex < 0)
	{
		//�ŏ��̃|�C���g�ɖ߂�
		m_nCurrentPointIndex = 0;
		// �I�_�t���O�����낷
		m_bIsEndPoint = false;
	}

	// �ǂ̏����ɂ����Ă͂܂�Ȃ��ꍇ�͌��݈ʒu��Ԃ�
	return m_vtMovePointList[m_nCurrentPointIndex];
}

// @brief �ړ��|�C���g�����X�g�ɒǉ�
// @param In_MovePoint �ǉ�����ʒu
void CMoveSystem::AddMovePoint(const XMFLOAT3& In_MovePoint)
{
	// Y���W�̒������s��
	XMFLOAT3 AdjustedPoint = StructMath::Add(In_MovePoint, XMFLOAT3(0.0f, m_fAdjustY, 0.0f)); 

	// �ړ��|�C���g�����X�g�ɒǉ�
	m_vtMovePointList.push_back(AdjustedPoint);
}

// @brief �����̈ړ��|�C���g�����X�g�ɒǉ�
// @param In_MovePoints �ǉ�����ړ��|�C���g���X�g(���т͂��̂܂�)
void CMoveSystem::AddMovePoints(const std::vector<XMFLOAT3>& In_MovePoints)
{
	// Y���W�̒������s��
	std::vector<XMFLOAT3> AdjustedPoints;
	for (const auto& point : In_MovePoints)
	{
		// �e�ړ��|�C���g��Y���W�̒�����K�p
		XMFLOAT3 adjustedPoint = StructMath::Add(point, XMFLOAT3(0.0f, m_fAdjustY, 0.0f));
		AdjustedPoints.push_back(adjustedPoint);
	}

	// �ړ��|�C���g�̃��X�g�ɒǉ�
	m_vtMovePointList.insert(m_vtMovePointList.end(), AdjustedPoints.begin(), AdjustedPoints.end());
}

// @brief �ړ��|�C���g�̃��X�g��V�����ݒ�
// @param In_MovePoints �ݒ肷��ړ��|�C���g���X�g
// @param In_CurrentPos ���݂̈ʒu
void CMoveSystem::SetMovePoints(const std::vector<XMFLOAT3>& In_MovePoints, const XMFLOAT3& In_CurrentPos)
{
	//Y���W�̒������s��
	std::vector<XMFLOAT3> AdjustedPoints;
	for (const auto& point : In_MovePoints)
	{
		// �e�ړ��|�C���g��Y���W�̒�����K�p
		XMFLOAT3 adjustedPoint = StructMath::Add(point, XMFLOAT3(0.0f, m_fAdjustY, 0.0f));
		AdjustedPoints.push_back(adjustedPoint);
	}


	// �ړ��|�C���g�̃��X�g��V�����ݒ�
	m_vtMovePointList = AdjustedPoints;

	// ���݈ʒu����ł��߂��ړ��|�C���g��T��
	float minDistance = StructMath::Abs(StructMath::Distance(In_CurrentPos, m_vtMovePointList[0]));
	int closestIndex = 0;

	for (size_t i = 1; i < m_vtMovePointList.size(); ++i)
	{
		float distance = StructMath::Abs(StructMath::Distance(In_CurrentPos, m_vtMovePointList[i]));
		if (distance < minDistance)
		{
			minDistance = distance;
			closestIndex = static_cast<int>(i);
		}
	}

	// �ł��߂��ړ��|�C���g�̃C���f�b�N�X�����݂̃|�C���g�̃C���f�b�N�X�ɐݒ�
	m_nCurrentPointIndex = closestIndex;

	// ���݂̃|�C���g�̃C���f�b�N�X�����Z�b�g
	m_nCurrentPointIndex = 0;
}

// @brief �ړ��|�C���g�̃��X�g�̃��[�g����
// @param In_CurrentPos ���݂̈ʒu
void CMoveSystem::RestorationMovePoints(XMFLOAT3 In_CurrentPos)
{
	// �ύX�O�̈ړ��|�C���g�̃��X�g����łȂ��ꍇ
	if (!m_vOldRouteMemory.MovePointList.empty())
	{
		// �ړ��|�C���g�̃��X�g�𕜌�
		SetMovePoints(m_vOldRouteMemory.MovePointList, In_CurrentPos);
		// �ړ��V�X�e���̎�ނ𕜌�
		m_eMoveSystemType = m_vOldRouteMemory.MoveType;

		// �ύX�O�̈ړ��|�C���g�̃��X�g���N���A
		m_vOldRouteMemory.MovePointList.clear();
		m_vOldRouteMemory.MoveType = MoveSystemType::Once; // �f�t�H���g�l�Ƀ��Z�b�g
	}
}

// @brief �ړ��|�C���g�𕜌��p�ɕۑ����ă��X�g���N���A
void CMoveSystem::SaveAndClearMovePoints()
{
	// �ύX�O�̈ړ��|�C���g�̃��X�g�Ɍ��݂̃��X�g��ۑ�
	m_vOldRouteMemory.MovePointList = m_vtMovePointList;
	// �ύX�O�̈ړ��V�X�e���̎�ނ�ۑ�
	m_vOldRouteMemory.MoveType = m_eMoveSystemType;
	// �ړ��|�C���g�̃��X�g���N���A
	m_vtMovePointList.clear();
	// ���݂̃|�C���g�̃C���f�b�N�X�����Z�b�g
	m_nCurrentPointIndex = 0;
	// �I�_�t���O�����낷
	m_bIsEndPoint = false;
}

// @brief �f�o�b�O�`�揈��(�ړ����[�g�̕`��)
// @param In_Color �`�悷����̐F
void CMoveSystem::DebugDraw(XMFLOAT4 In_Color)
{
#ifdef _DEBUG
	SetRender3D();

	// �ړ��|�C���g�̃��X�g����łȂ��ꍇ
	if (!m_vtMovePointList.empty())
	{
		switch (m_eMoveSystemType)
		{
		case MoveSystemType::Once:
			// �ړ��|�C���g����Ō���
			for (size_t i = 0; i < m_vtMovePointList.size() - 1; ++i)
			{
				Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[i + 1], In_Color);
			}
			break;
		case MoveSystemType::Loop:
			// �ړ��|�C���g����Ō���
			for (size_t i = 0; i < m_vtMovePointList.size(); ++i)
			{
				if (i == m_vtMovePointList.size() - 1)
				{
					// �Ō�̃|�C���g����ŏ��̃|�C���g�ɐ�������
					Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[0], In_Color);
				}
				else
				{
					// �ړ��|�C���g����Ō���
					Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[i + 1], In_Color);
				}
			}
			break;
		case MoveSystemType::Reverse:
			// �ړ��|�C���g����Ō���
			for (size_t i = 0; i < m_vtMovePointList.size() - 1; ++i)
			{
				Geometory::AddLine(m_vtMovePointList[i], m_vtMovePointList[i + 1], In_Color);
			}
			break;
		}
	}
	// �`������s
	Geometory::DrawLines(); 

#endif // _DEBUG
}
