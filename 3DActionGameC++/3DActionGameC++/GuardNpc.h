/*
* @file GuardNpc.h
* @brief ��qNPC�̃N���X�̃w�b�_�[�t�@�C��
* @author �F���엤�l
* @date 2025/08/14 ��qNPC�̃N���X�̒�`
*/

#pragma once

/* ���N���X�̃C���N���[�h */
#include "NpcBase.h"

/// <summary>
/// ��qNPC�̃N���X
/// </summary>
class CGuardNpc : public CNpcBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CGuardNpc(int PointIndex);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~CGuardNpc();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(void) override;


};

