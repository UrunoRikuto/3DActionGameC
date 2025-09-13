/*=====================================================================
* @file MovePointManager.cpp
* @brief �ړ��|�C���g�Ǘ��N���X�̎����t�@�C��
=====================================================================*/

/* �w�b�_�[�̃C���N���[�h */
#include "MovePointManager.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Model.h"
#include "Defines.h"
#include "GameValues.h"
#include "ModelDrawSetting.h"
#include "Main.h"
#include "SceneGame.h"
#include "GameObject.h"
#include <list>

// �C���X�^���X�̏�����
std::unique_ptr<CMovePointManager> CMovePointManager::m_pInstance = nullptr;

// @brief �ړ��|�C���g�̍쐬
void CMovePointManager::CreateData(FieldType In_Type)
{
	// �t�B�[���h�̎�ނɉ����Ĉړ��|�C���g��ݒ�
	switch (In_Type)
	{
	case FieldType::Plain:
		// �����̈ړ��|�C���g��ݒ�
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(100.0f, 1.0f,200.0f));
		m_MovePoints.push_back(XMFLOAT3(200.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,100.0f));
		m_MovePoints.push_back(XMFLOAT3(300.0f, 1.0f,200.0f));
		break;
	}

	m_pMovePointModels.resize(m_MovePoints.size());

	for (auto& model : m_pMovePointModels)
	{
		model = std::make_unique<Model>();
		model->Load(ModelPath::MOVE_POINT_PATH);
	}
}

// @brief �C���X�^���X���擾����֐�
// @details �C���X�^���X�����݂��Ȃ��ꍇ�͐V���ɍ쐬����
// @return �C���X�^���X�̃|�C���^
CMovePointManager* CMovePointManager::GetInstance(void)
{
	// �C���X�^���X�����݂��Ȃ��ꍇ�͐V���ɍ쐬
	if (!m_pInstance)
	{
		m_pInstance = std::make_unique<CMovePointManager>();
	}
	// �C���X�^���X�̃|�C���^��Ԃ�
	return m_pInstance.get();
}

// @brief �R���X�g���N�^
CMovePointManager::CMovePointManager()
{

}

// @brief �f�X�g���N�^
CMovePointManager::~CMovePointManager()
{

}

// @brief �f�o�b�N�`�揈��
void CMovePointManager::DebugDraw(void)
{
#ifdef _DEBUG
	SetRender3D();
	for (int i = 0; i < m_pMovePointModels.size(); i++)
	{
		CreateObject(
			m_MovePoints[i],			// �ʒu
			StructMath::FtoF3(5.0f),// �X�P�[��
			StructMath::FtoF3(0.0f),// ��]
			m_pMovePointModels[i].get(),			// ���f���|�C���^
			Camera::GetInstance(),	// �J�����|�C���^
			true,					// ���邭���邩�ǂ���
			XMFLOAT3(0.5f, 0.5f, 0.5f) // ���C�e�B���O�F
		);
	}
#endif // _DEBUG
}

// @brief �߂��̈ړ��|�C���g���擾
// @param In_Point �w��ʒu
// @return �w��ʒu�̋߂��̈ړ��|�C���g
XMFLOAT3 CMovePointManager::NearMovePoint(const XMFLOAT3& In_Point) const
{
	// �ŏ�������������
	float minDistance = -1.0f;

	// �ł��߂��ړ��|�C���g��������
	XMFLOAT3 nearestPoint = XMFLOAT3();

	// �ړ��|�C���g�̃��X�g�𑖍����čł��߂��|�C���g��T��
	for (const auto& point : m_MovePoints)
	{
		// �w��ʒu�ƈړ��|�C���g�̋������v�Z
		float distance = StructMath::Abs(StructMath::Distance(In_Point, point));

		// �ŏ����������������ꍇ�͍X�V
		// 0��菬�����ꍇ�͏���Ȃ̂ōX�V
		if (distance < minDistance || minDistance < 0.0f)
		{
			// �ŏ������ƍł��߂��ړ��|�C���g���X�V
			minDistance = distance;
			nearestPoint = point;
		}
	}

	return nearestPoint;
}

// @brief �w������Ɍ��肵���߂��̈ړ��|�C���g���擾
// @param In_Point �w��ʒu
// @param In_Dir �w�����
// @return �w������Ɍ��肵���߂��̈ړ��|�C���g
XMFLOAT3 CMovePointManager::NearMovePointDir(const XMFLOAT3& In_Point, const XMFLOAT3& In_Dir) const
{
	// �ŏ�������������
	float minDistance = -1.0f;

	// �ł��߂��ړ��|�C���g��������
	XMFLOAT3 nearestPoint = XMFLOAT3();

	// �ړ��|�C���g�̃��X�g�𑖍����čł��߂��|�C���g��T��
	for (const auto& point : m_MovePoints)
	{
		// �ړ��|�C���g���w������ɂ��邩�ǂ����𔻒�
		XMFLOAT3 dirToPoint = StructMath::Sub(point, In_Point);
		if (StructMath::Dot(dirToPoint, In_Dir) < 0.0f)continue;

		// �w��ʒu�ƈړ��|�C���g�̋������v�Z
		float distance = StructMath::Abs(StructMath::Distance(In_Point, point));

		// �ŏ����������������ꍇ�͍X�V
		// 0��菬�����ꍇ�͏���Ȃ̂ōX�V
		if (distance < minDistance || minDistance < 0.0f)
		{
			// �ŏ������ƍł��߂��ړ��|�C���g���X�V
			minDistance = distance;
			nearestPoint = point;
		}
	}

	return nearestPoint;
}

// @brief �ړ����[�g�̍쐬
// @param In_CurrentPoint ���݂̈ʒu
// @param In_TargetPoint �ړI�n
// @return ���݈ʒu����ړI�n�܂ł̈ړ����[�g
std::vector<XMFLOAT3> CMovePointManager::CreateMoveRoute(const XMFLOAT3& In_CurrentPoint, const XMFLOAT3& In_TargetPoint) const
{
	// ���O��Ԃ̎g�p
	using namespace StructMath;
	using namespace GameValue::MoveSystem;

	std::vector<XMFLOAT3> newMovePointRoute = std::vector<XMFLOAT3>();

	// ���݈ʒu�ɋ߂��ړ��|�C���g���擾
	XMFLOAT3 currentPointnear = NearMovePoint(In_CurrentPoint);

	// �ړI�n�ɋ߂��ړ��|�C���g���擾
	XMFLOAT3 targetPointnear = NearMovePoint(In_TargetPoint);

	//(��)���������܂ł̌q��
	newMovePointRoute.push_back(currentPointnear);
	newMovePointRoute.push_back(targetPointnear);
	return newMovePointRoute;

	// ��������
	// 
	// �P�D���݈ʒu���Q�ƈʒu�Ƃ��ď����ۑ�
	// �Q�D�Q�ƈʒu�ƖړI�n�����Ԑ������쐬
	// �R�D������ɏ�Q��������Ă��邩�ǂ������`�F�b�N
	//  ���� ��Q���̓����蔻����擾���ē����蔻��ɐ���������Ă��邩�ǂ������`�F�b�N
	// �S�D����Ă��Ȃ��ꍇ�͖ړI�n�����[�g�ɒǉ����ďI��
	// �T�D����Ă���ꍇ�͏�Q���������悤�Ɉړ��|�C���g�����[�g�ɒǉ�
	//	���� DistancePointSegment(A,B,C); // A���_�AB��C�������̗��[
	//		 ���� �߂�l���_�Ɛ����̋���
	// �U�D�ǉ������ړ��|�C���g���Q�ƈʒu�Ƃ��čēx�Q�ɖ߂�

}

// @brief �_�Ɛ����̋������v�Z
// @param In_Point �_
// @param In_SegmentStart �����̊J�n�_
// @param In_SegmentEnd �����̍ŏI�_
float CMovePointManager::DistancePointSegment(const XMFLOAT3& In_Point, const XMFLOAT3& In_SegmentStart, const XMFLOAT3& In_SegmentEnd) const
{
	// ���O��Ԃ̎g�p
	using namespace StructMath;

	// �����̃x�N�g��
	XMFLOAT3 segVec = Sub(In_SegmentEnd, In_SegmentStart);
	XMFLOAT3 StartToPoint = Sub(In_Point, In_SegmentStart);

	float ab2 = Dot(segVec, segVec);
	// A��B�������_
	if (ab2 == 0.0f)return Length(StartToPoint);

	float t = Dot(StartToPoint, segVec) / ab2;

	if (t < 0.0f)
	{
		// �����̊J�n�_���ł��߂��ꍇ
		return Length(StartToPoint);
	}
	else if (t > 1.0f)
	{
		// �����̏I���_���ł��߂��ꍇ
		return Length(Sub(In_Point, In_SegmentEnd));
	}


	// ������̓_���ł��߂��ꍇ
	XMFLOAT3 projection = Add(In_SegmentStart, Mul(segVec, FtoF3(t)));
	return Length(Sub(In_Point, projection));
}
