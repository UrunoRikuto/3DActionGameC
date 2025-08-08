/*
* @file Ray.cpp
* @brief ���C�̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 ���C�L���X�g�̃N���X�̎���
*/

/* �w�b�_�[�̃C���N���[�h */
#include "Ray.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include <math.h>
#include <utility>

// @brief �R���X�g���N�^
CRay::CRay()
	: m_tOrigin(0.0f, 0.0f, 0.0f) // ���C�̎n�_�̏�����
	, m_tDirection(0.0f, 0.0f, 0.0f) // ���C�̕����̏�����
{

}

// @brief �f�X�g���N�^
CRay::~CRay()
{

}

// @brief ���C�L���X�g�̎��s
// @param InTarget �^�[�Q�b�g�I�u�W�F�N�g(Box)
bool CRay::Cast(CRayCastTarget* InTarget)
{
	//// ���C�̎n�_�ƕ������擾
	//XMFLOAT3 origin = m_tOrigin;         // ���C�̎n�_
	//XMFLOAT3 direction = StructMath::Normalize(m_tDirection); // ���C�̕����i���K���j

	//// �^�[�Q�b�g�̈ʒu�ƃX�P�[�����擾
	//XMFLOAT3 targetPosition = InTarget->GetPosition(); // �^�[�Q�b�g�̈ʒu
	//XMFLOAT3 targetScale = InTarget->GetScale();       // �^�[�Q�b�g�̃X�P�[��

	//// AABB�̍ŏ�/�ő�_���v�Z
	//XMFLOAT3 boxMin = StructMath::Sub(targetPosition, StructMath::Div(targetScale, 2.0f));
	//XMFLOAT3 boxMax = StructMath::Add(targetPosition, StructMath::Div(targetScale, 2.0f));

	//// �e����tMin, tMax���v�Z�i�X���u�@�j
	//float tMin = -FLT_MAX;
	//float tMax = FLT_MAX;

	//auto checkAxis = [&](float origin, float direction, float minB, float maxB) -> bool {
	//	if (fabsf(direction) < 1e-6f) {
	//		// �����Ȃ����Ȃ̂ɔ͈͊O�Ȃ� false�i�����I�Ɂj
	//		if (origin < minB || origin > maxB)
	//			return false;
	//		// �͈͓��Ȃ�X�L�b�v�Ώ�
	//		return true;
	//	}
	//	float t1 = (minB - origin) / direction;
	//	float t2 = (maxB - origin) / direction;
	//	if (t1 > t2) std::swap(t1, t2);
	//	tMin = std::max(tMin, t1);
	//	tMax = std::min(tMax, t2);
	//	return tMin <= tMax;
	//	};

	//bool hitX = checkAxis(origin.x, direction.x, boxMin.x, boxMax.x);
	//bool hitY = checkAxis(origin.y, direction.y, boxMin.y, boxMax.y);
	//bool hitZ = checkAxis(origin.z, direction.z, boxMin.z, boxMax.z);

	//// �S�Ă̎��Ō������Ă���Γ�����
	//if (hitX && hitY && hitZ) {
	//	return true;
	//}

	// ���C�̎n�_���^�[�Q�b�g��Box��X����Z���͈͓̔��ɂ��邩�`�F�b�N
	if (m_tOrigin.x >= InTarget->GetPosition().x - InTarget->GetScale().x / 2.0f &&
		m_tOrigin.x <= InTarget->GetPosition().x + InTarget->GetScale().x / 2.0f &&
		m_tOrigin.z >= InTarget->GetPosition().z - InTarget->GetScale().z / 2.0f &&
		m_tOrigin.z <= InTarget->GetPosition().z + InTarget->GetScale().z / 2.0f)
	{
		return true; // ���C���^�[�Q�b�g�ɓ�������
	}


	return false;
}

// @brief �p�����[�^�[�̐ݒ�
// @param origin ���C�̎n�_
// @param direction ���C�̕���
void CRay::SetParam(const XMFLOAT3& origin, const XMFLOAT3& direction)
{
	m_tOrigin = origin; // ���C�̎n�_��ݒ�
	m_tDirection = direction; // ���C�̕�����ݒ�
}
