/*=====================================================================
* @file Ray.cpp
* @brief ���C��Cpp�t�@�C��
=====================================================================*/

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
// @param In_TargetInfos �^�[�Q�b�g�R���W����
// @return ���C���������Ă��邩�ǂ���
bool CRay::Cast(std::vector<Collision::Info> In_TargetInfos)
{
	/// @Todo ���C��Box�̓����蔻�����������
	/// ���݂�y���𖳎�����X����Z���͈͓̔��ɂ��邩�ǂ����Ŕ���


	// �^�[�Q�b�g�������[�v
	for (const auto& TargetInfo : In_TargetInfos) 
	{
		Collision::Box TargetBox = TargetInfo.box; // �^�[�Q�b�g��Box�����擾

		// ���C�̎n�_���^�[�Q�b�g��Box��X����Z���͈͓̔��ɂ��邩�`�F�b�N
		if (m_tOrigin.x >= TargetBox.center.x - TargetBox.size.x / 2.0f &&
			m_tOrigin.x <= TargetBox.center.x + TargetBox.size.x / 2.0f &&
			m_tOrigin.z >= TargetBox.center.z - TargetBox.size.z / 2.0f &&
			m_tOrigin.z <= TargetBox.center.z + TargetBox.size.z / 2.0f)
		{
			return true; // ���C���^�[�Q�b�g�ɓ�������
		}
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
