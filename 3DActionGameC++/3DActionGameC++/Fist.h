/*=====================================================================
* @file Fist.h
* @brief ���N���X�w�b�_�[�t�@�C��
=====================================================================*/
#pragma once

/* ���N���X�̃C���N���[�h */
#include "Weapon.h"

//@brief ���N���X
class CFist : public CWeapon
{
public:
	// @brief �R���X�g���N�^
	CFist();

	// @brief �f�X�g���N�^
	virtual ~CFist();

	// @brief �X�V
	// @param In_Position �L�����N�^�[�̈ʒu
	void Update(XMFLOAT3 In_Position) override;

protected:

	// @brief �p�����[�^�̐ݒ�
	void SetParam(void) override;
};

