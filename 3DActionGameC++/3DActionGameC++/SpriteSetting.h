#pragma once

class CSpriteSetting
{
public:
	//�R���X�g���N�^
	CSpriteSetting();
	//�f�X�g���N�^
	~CSpriteSetting();
	//�X�V����
	void Update(float InUV[][4], int InFrameTime, int InResetFrame, int InMaxFrame);
	//�l�̃��Z�b�g
	void Reset(float InUV[][4]);
private:
	int   m_nAnimeFrame;	// �A�j���[�V�����؂�ւ��t���[��
	int	  m_nAnimeNo;		// ���݂�UV�z��̔ԍ�
	float m_fAnimeU;		// ���݂�U�l
	float m_fAnimeV;		// ���݂�V�l
public:
	//U�l��Get
	float GetU(void) { return m_fAnimeU; }
	//V�l��Get
	float GetV(void) { return m_fAnimeV; }
};