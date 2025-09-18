/*������������������������������������������������������������������������������������������������������������������������������
*
* file�FFade.h
*
* �T�v�F�t�F�[�h�������Ǘ�����t�@�C��
*
������������������������������������������������������������������������������������������������������������������������������*/

#pragma once
#include "Transition.h"

/// <summary>
/// �t�F�[�h�������Ǘ�����N���X
/// </summary>
class CFade : public CTransition
{
public:
	// �R���X�g���N�^
	CFade(float In_MaxFadeTime);
	// �f�X�g���N�^
	~CFade() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
private:
	// �A���t�@�l
	float m_fAlpha;
	// �t�F�[�h�C���A�E�g�̎���
	float m_fTime;
	// �t�F�[�h�A�E�g�t���O
	bool m_bFadeOut; // true�Ȃ�t�F�[�h�A�E�g�Afalse�Ȃ�t�F�[�h�C��
};

