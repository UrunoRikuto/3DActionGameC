/*=====================================================================
* @file Sword.h
* @brief ���N���X��`�t�@�C��
=====================================================================*/
#pragma once

/* ���N���X�̃C���N���[�h */
#include "Weapon.h"

//@brief ���N���X
class CSword : public CWeapon
{
public:
	// @brief �R���X�g���N�^
	CSword();

	// @brief �f�X�g���N�^
	virtual ~CSword();

	// @brief �X�V
	// @param In_Position �L�����N�^�[�̈ʒu
	void Update(XMFLOAT3 In_Position) override;

protected:

	// @brief �p�����[�^�̐ݒ�
	void SetParam(void) override;
};

