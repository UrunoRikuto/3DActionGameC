#pragma once

//�V�[���N���X�̃x�[�X�N���X
class CSceneBase
{
public:
	//�R���X�g���N�^
	CSceneBase();
	//�f�X�g���N�^
	virtual ~CSceneBase();
	//�X�V����
	virtual void Update(void) = 0;
	//�`�揈��
	virtual void Draw(void) = 0;

};