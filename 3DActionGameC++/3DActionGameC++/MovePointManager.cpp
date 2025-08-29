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

// @brief �ړ����[�g�̍쐬
// @param In_CurrentPoint ���݂̈ʒu
// @param In_TargetPoint �ړI�n
// @return ���݈ʒu����ړI�n�܂ł̈ړ����[�g
std::vector<XMFLOAT3> CMovePointManager::CreateMoveRoute(const XMFLOAT3& In_CurrentPoint, const XMFLOAT3& In_TargetPoint) const
{
	std::vector<XMFLOAT3> newMovePointRoute = std::vector<XMFLOAT3>();

	// ���݈ʒu�ɋ߂��ړ��|�C���g���擾
	XMFLOAT3 currentPointnear = NearMovePoint(In_CurrentPoint);

	// �ړI�n�ɋ߂��ړ��|�C���g���擾
	XMFLOAT3 targetPointnear = NearMovePoint(In_TargetPoint);

	// ���݈ʒu����ړI�n�̕����x�N�g�����v�Z
	XMFLOAT3 direction = StructMath::Direction(currentPointnear, targetPointnear);

	// ���ݒn����ړI�n�����Ԓ�����ɂ���ړ��|�C���g�����ׂĎ擾
	for (const auto& point : m_MovePoints)
	{

	}

	// ���݈ʒu�̋߂��̈ړ��|�C���g�����[�g�̍ŏ��ɒǉ�
	newMovePointRoute.push_back(currentPointnear);


	// �ړI�n�̋߂��̈ړ��|�C���g�����[�g�̍Ō�ɒǉ�
	newMovePointRoute.push_back(targetPointnear);

	return newMovePointRoute;
}
