#pragma once
#include "SceneBase.h"
#include "Enums.h"
#include "Camera.h"

/*
* @brief �Q�[���V�[���N���X
*/
class CSceneGame : public CSceneBase
{
public:
	//�R���X�g���N�^
	CSceneGame();
	//�f�X�g���N�^
	~CSceneGame();
	//�X�V����
	void Update(void)override;
	//�`�揈��
	void Draw(void)override;
private:
	//�ʏ탂�[�h�̍X�V����
	void NormalUpdate(void);
	//�ʏ탂�[�h�̕`�揈��
	void NormalDraw(void);

private:
};

