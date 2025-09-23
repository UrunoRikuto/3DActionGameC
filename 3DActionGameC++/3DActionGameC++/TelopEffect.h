/*������������������������������������������������������������������������������������������������������������������������������
*
* file�FTelopEffect.h
*
* �T�v�F�e���b�v�G�t�F�N�g�̊��N���X���Ǘ�����t�@�C��
*
������������������������������������������������������������������������������������������������������������������������������*/

#pragma once
#include "DirectX.h"

/// <summary>
/// �e���b�v�G�t�F�N�g�̊��N���X
/// </summary>
class CTelopEffect
{
public:
	// �R���X�g���N�^
	CTelopEffect() = default;
	// �f�X�g���N�^
	virtual ~CTelopEffect() = default;
	// �X�V����
	virtual bool Update() = 0;
	// �`�揈��
	virtual void Draw() = 0;
protected:
	// ���_�o�b�t�@
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	// �e�N�X�`��
	ID3D11ShaderResourceView* m_pTexture = nullptr;
	// �e���b�v�̕\������
	float m_fDisplayTime = 0.0f; // �b�P��
	// �e���b�v�̌o�ߎ���
	float m_fElapsedTime = 0.0f; // �b�P��
};

