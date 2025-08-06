/*
* @file Enums.h
* @brief �񋓌^�̒�`�t�@�C��
* @author �F���엤�l
*/
#pragma once

/*
* @brief �V�[���̎��
* @param 0�F�^�C�g��
* @param 1�F�Q�[��
*/
enum class SceneType
{
	Title,
	Game,
	MAX,
};

/*
* @brief �v���C���[�̍s�����[�h
* @param 0�F�ړ����[�h
* @param 1�F�_�����[�h
*/
enum class PlayerActionMode
{
	Move,		// �ړ����[�h
	Sniping,	// �_�����[�h
	MAX,
};