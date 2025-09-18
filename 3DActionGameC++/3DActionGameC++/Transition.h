/*������������������������������������������������������������������������������������������������������������������������������
*
* file�FTransition.h
*
* �T�v�F�g�����W�V�����̊��N���X���Ǘ�����t�@�C��
*
������������������������������������������������������������������������������������������������������������������������������*/

#pragma once
#include "SpriteDrawer.h"

/// <summary>
/// �g�����W�V�����̊��N���X
/// </summary>
class CTransition
{
public:
	// �R���X�g���N�^
	CTransition() = default;
	// �f�X�g���N�^
	virtual ~CTransition() = default;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;
protected:
	// 2D�`��ɕK�v�ȃf�[�^
	ID3D11Buffer* m_pVtx;
	ID3D11ShaderResourceView* m_pTex;
	// �t�F�[�h�����t���O
	bool m_bEnd = false;
	// �`�F���W�t���O(�؂�ւ����̃^�C�~���O)
	bool m_bChange = false;
public:
	// �t�F�[�h�����t���O�̎擾
	bool IsEnd() const { return m_bEnd; }
	// �`�F���W�t���O�̎擾
	bool IsChange() const { return m_bChange; }
	// �`�F���W�t���O�̐ݒ�
	void SetChange(bool change) { m_bChange = change; }
};

