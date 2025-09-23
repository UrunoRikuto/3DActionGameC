/*=====================================================================
* @file ResultTelop.h
* @brief ���U���g�e���b�v��h�t�@�C��
=====================================================================*/
#pragma once

/* ���N���X�̃C���N���[�h */
#include "TelopEffect.h"

/// <summary>
/// ���U���g�e���b�v�̃N���X
/// </summary>
class CResultTelop : public CTelopEffect
{
public:
	// �R���X�g���N�^
	CResultTelop(bool IsWin);
	// �f�X�g���N�^
	~CResultTelop() override;
	// �X�V����
	bool Update() override;
	// �`�揈��
	void Draw() override;
};

