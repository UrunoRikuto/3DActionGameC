/*=====================================================================
* @file Enums.h
* @brief �񋓌^�̒�`�t�@�C��
=====================================================================*/
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
* @brief �ړ��V�X�e���̎��
* @param 0�F���ړ�
* ...�ŏI�|�C���g�܂ōs������~�܂�
* @param 1�F���[�v�ړ�
* ...�ŏI�|�C���g�܂ōs������ŏI�|�C���g����ŏ��̃|�C���g�܂ňړ����čēx�ړ� 
* @param 2�F���]�ړ�
* ...�ŏI�|�C���g�܂ōs�����甽�]���čŏ��̃|�C���g�܂ňړ����Ĉړ�
*/
enum class MoveSystemType
{
	Once,
	Loop,
	Reverse,
};

/*
* @brief �t�B�[���h�̎��
* @param 0�F����
*/
enum class FieldType
{
	Plain,	// ����
	MAX,
};

/*
* @brief ���o���G�̏��
* @param 0�F�ُ�Ȃ�
* @param 1�F�^��
* @param 2: ������
* @param 3�F����
*/
enum class VisionSearchState
{
	None,		// �ُ�Ȃ�
	Doubt,		// �^��
	Lost,		// ������
	Discovery,	// ����
	MAX,
};

/*
* @brief �v���C���[�̎p���̎��
* @param 0�F����
* @param 1�F���Ⴊ��
* @param 2�F����
* @param 3�F����
*/
enum class PlayerPosture
{
	Stand,		// ����
	Crouch,		// ���Ⴊ��
	Prone,		// ����
	Hide,		// ����
	MAX,
};

/*
* @brief NPC�̎��
* @param 0�F�ʏ�NPC
*/
enum class NpcType
{
	Normal,		// �ʏ�NPC
	MAX,
};

/*
* @brief �U���̎��
* @param 0�F�Ō�
* @param 1�F�a��
* @param 2�F����
* @param 3�F�h��
*/
enum class AttackType
{
	Blow,		// �Ō�
	Slash,		// �a��
	Blast,		// ����
	Pierce,		// �h��
};

/*
* @brief �Q�[�W�̎��
* @param 0�F�̗�
* @param 1�F���G
*/
enum class GaugeType
{
	Health,			// �̗�
	Detection,		// ���G
	MAX,
};

/*
* @brief �t�B�[���h�I�u�W�F�N�g�̎��
* @param 0�F��
* @param 1�F�n��
*/
enum class FieldObjectType
{
	Wall,		// ��
	Ground,		// �n��
	MAX,
};