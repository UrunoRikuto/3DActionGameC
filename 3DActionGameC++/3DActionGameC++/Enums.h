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
* @param 1�F�^�[�Q�b�gNPC
* @param 2�F�X�i�C�p�[NPC
* @param 3�F����NPC
*/
enum class NpcType
{
	Normal,		// �ʏ�NPC
	Target,		// �^�[�Q�b�gNPC
	Sniper,		// �X�i�C�p�[NPC
	Patrol,		// ����NPC
	MAX,
};

/*
* @brief �X�e�[�^�X�p�����[�^�̎��
* @param 0�F������
* @param 1�F�ؗ�
* @param 2�F���_��
* @param 3�F���v��
* @param 4�F�Z��
*/
enum class StatusParameterType
{
	Vitality,	// ������
	Muscle,		// ��  ��
	Mental,		// ���_��
	Endurance,	// ���v��
	Skill,		// �Z  ��
	MAX,
};

/*
* @brief �U���̎��
* @param 0�F�a��
* @param 1�F�h��
* @param 2�F�ł�
* @param 3�F����
*/
enum class AttackType
{
	Slash,	// �a��
	Stab,	// �h��
	Blow,	// �ł�
	Shoot,	// ����
};