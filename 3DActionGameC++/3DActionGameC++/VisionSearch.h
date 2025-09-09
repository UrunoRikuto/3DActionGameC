/*=====================================================================
* @file VisionSearch.h
* @brief ���o���G�̃w�b�_�[�t�@�C��
=====================================================================*/
#pragma once

/* �V�X�e���E�v�f�̃C���N���[�h */
#include "StructMath.h"
#include "Enums.h"
#include "GaugeUI.h"

/* �O���錾 */
class CNpcBase;
class CRay;

/// <summary>
/// ���o���G�N���X
/// </summary>
class CVisionSearch
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="In_Self">���g�̃I�u�W�F�N�g</param>
	CVisionSearch(CNpcBase* In_Self);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CVisionSearch();

	/// <summary>
	/// ���G����
	/// </summary>
	/// <param name="In_SelfPosition">���g�̈ʒu</param>
	/// <param name="In_CurrentSearchState">���݂̍��G���</param>
	/// <returns>�X�V��̍��G���</returns>
	VisionSearchState Search(const XMFLOAT3& In_SelfPosition, VisionSearchState In_CurrentSearchState);

	/// <summary>
	/// ���o���G�̕`�揈��
	/// </summary>
	void DebugDraw(void);

private:
	/// <summary>
	/// ����p�̍X�V
	/// </summary>
	void UpdateViewAngle(void);

	/// <summary>
	///�^�[�Q�b�g�Ƃ̊Ԃɏ�Q�������邩�ǂ����̃`�F�b�N
	/// </summary>
	/// <returns>�������ꍇtrue�Ȃ������ꍇfalse</returns>
	bool CheckObstacle(void) const;

	/// <summary>
	/// ����p�͈͓̔��Ƀ^�[�Q�b�g�����邩�ǂ����̃`�F�b�N
	/// </summary>
	/// <returns>�����ꍇtrue���Ȃ������ꍇ�ꍇfalse</returns>
	bool CheckTargetInViewAngle(void) ;

	/// <summary>
	/// ����p�͈͓̔��Ƀ|�C���g�����邩�ǂ����̃`�F�b�N
	/// </summary>
	/// <param name="P">�m�F����|�C���g</param>
	/// <returns>����ꍇtrue,�Ȃ��ꍇfalse</returns>
	bool CheckPointInTriangle(const XMFLOAT3& Point) const;
private:
	
	/// <summary>
	/// ���C(����)
	/// </summary>
	CRay* m_pRay;

	/// <summary>
	/// ���Ă������
	/// </summary>
	XMFLOAT3 m_tDirection;

	/// <summary>
	/// �O�p�`�̒��_�|�C���g
	/// </summary>
	XMFLOAT3 m_TrianglePoint[3];

	/// <summary>
	/// ���F����
	/// </summary>
	float m_fViewDistance;

	/// <summary>
	/// �����l
	/// </summary>
	float m_fDetectionValue;

	/// <summary>
	/// �����l�̃Q�[�WUI
	/// </summary>
	CGaugeUI* m_pDetectionGauge;

	/// <summary>
	/// ��������ԂɂȂ�܂ł̌o�ߎ���
	/// </summary>
	float m_fLostTimer;

	/// <summary>
	/// ���G���s���Q�[���I�u�W�F�N�g
	/// </summary>
	CNpcBase* m_pSelfObject;

public:// �A�N�Z�T
	/// <summary>
	/// ���Ă�������̐ݒ�
	/// </summary>
	/// <param name="direction">���Ă������</param>
	void SetDirection(const XMFLOAT3& direction) { m_tDirection = direction; }
	/// <summary>
	/// ���Ă�������̎擾
	/// </summary>
	/// <returns>���Ă������</returns>
	const XMFLOAT3& GetDirection(void) const { return m_tDirection; }
	/// <summary>
	/// �����l�̎擾
	/// </summary>
	/// <returns>�����l</returns>
	float GetDetectionValue(void) const { return m_fDetectionValue; }

	/// <summary>
	/// ���G�l�̃Q�[�WUI�̎擾
	/// </summary>
	/// <returns>���G�l�̃Q�[�WUI</returns>
	CGaugeUI* GetDetectionGauge(void) const { return m_pDetectionGauge; }
};

