/*
* @file SceneGame.cpp
* @brief �Q�[���V�[���̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/

/* �w�b�_�[�ŗ��p����V�X�e���̃C���N���[�h */
#include <memory>
/* �Q�[���I�u�W�F�N�g�̃C���N���[�h */
#include "FieldObject.h"
#include "Player.h"
#include "TargetNpc.h"
#include "GuardNpc.h"
/* �w�b�_�[�̃C���N���[�h */
#include "SceneGame.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Camera.h"
#include "Defines.h"
#include "GameValues.h"
#include "MovePointManager.h"
#include "Quest.h"
#include "Timer.h"

/* �O���[�o���ϐ� */
std::list<CGameObject*> g_vNullCheckList; // Null�`�F�b�N�p�̃Q�[���I�u�W�F�N�g�̃��X�g
std::list<CGameObject*> g_vAttackObjects; // �U���p�̃Q�[���I�u�W�F�N�g�̃��X�g

// @brief ���Z��X�e�[�W�̏�����
void CSceneGame::InitArenaStage(void)
{
	// �t�B�[���h�̐���
	// �n�ʂ̐���
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(400.0f, 1.0f, 400.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, 0.0f));

	// �ǂ̐���
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(400.0f, 20.0f, 1.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 20.0f, 99.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, 200.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(400.0f, 20.0f, 1.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 20.0f, 99.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, -200.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(0.0f, 20.0f, 400.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetRotation(XMFLOAT3(0.0f, 90.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(400.0f, 20.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(200.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, 0.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Wall));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(0.0f, 20.0f, 400.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetRotation(XMFLOAT3(0.0f, 90.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(400.0f, 20.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(-200.0f, m_pFieldObject[m_pFieldObject.size() - 1]->GetScale().y / 2.0f, 0.0f));

	// �ړ��|�C���g�̐���
	CMovePointManager::GetInstance()->CreateData(CQuest::GetInstance()->GetQuestData().stageType);
	//- �ړ��|�C���g�}�l�[�W���[�̃C���X�^���X���擾
	std::vector<XMFLOAT3> pMovePointManager = CMovePointManager::GetInstance()->GetMovePoints();

	// NPC�̐����i�^�[�Q�b�gNPC�j
	m_pNpc.push_back(std::make_unique<CTargetNpc>(pMovePointManager[0], NpcType::ArenaTarget));
	m_pNpc[m_pNpc.size() - 1]->GetMoveSystem()->AddMovePoint(pMovePointManager[1]);
	m_pNpc[m_pNpc.size() - 1]->GetMoveSystem()->AddMovePoint(pMovePointManager[2]);
	m_pNpc[m_pNpc.size() - 1]->GetMoveSystem()->AddMovePoint(pMovePointManager[3]);
	m_pNpc[m_pNpc.size() - 1]->GetMoveSystem()->AddMovePoint(pMovePointManager[4]);

	// �v���C���[�̈ʒu�ݒ�
	m_pPlayer->SetPosition(GameValue::Field::PLAYER_SPOWN_POINT[static_cast<int>(StageType::Arena)]);
}

// @brief �����X�e�[�W�̏�����
void CSceneGame::InitPlainStage(void)
{
	// �t�B�[���h�̐���
	// �n�ʂ̐���
	float height = 0.0f; // �n�ʂ̍���
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, height, 0.0f));
	height = 1.0f;
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(200.0f, height, 0.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(-200.0f, height, 0.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, height, 200.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(0.0f, height, -200.0f));
	height = 2.0f;
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(200.0f, height, 200.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(200.0f, height, -200.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(-200.0f, height, 200.0f));
	m_pFieldObject.push_back(std::make_unique<CFieldObject>(FieldObjectType::Ground));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetScale(XMFLOAT3(200.0f, 1.0f, 200.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetModelScaleAjast(XMFLOAT3(0.0f, 99.0f, 0.0f));
	m_pFieldObject[m_pFieldObject.size() - 1]->SetPosition(XMFLOAT3(-200.0f, height, -200.0f));


	// ���ׂẴt�B�[���h�̃��f���T�C�Y�ɂ�鍂���␳
	for (auto& field : m_pFieldObject)
	{
		field->SetPosition(StructMath::Add(field->GetPosition(), XMFLOAT3(0.0f, field->GetScale().y / 2.0f, 0.0f)));
	}

	// �ړ��|�C���g�̐���
	CMovePointManager::GetInstance()->CreateData(StageType::Arena);
	// �ړ��|�C���g�}�l�[�W���[�̃C���X�^���X���擾
	std::vector<XMFLOAT3> pMovePointManager = CMovePointManager::GetInstance()->GetMovePoints();

	// NPC�̐����i�^�[�Q�b�gNPC�j
	m_pNpc.push_back(std::make_unique<CTargetNpc>(pMovePointManager[0], NpcType::ArenaTarget));
	m_pNpc[m_pNpc.size() - 1]->GetMoveSystem()->AddMovePoint(pMovePointManager[1]);

	// NPC�̐����i��qNPC�j
	m_pNpc.push_back(std::make_unique<CGuardNpc>(pMovePointManager[2], NpcType::ArenaTarget));
	m_pNpc[m_pNpc.size() - 1]->GetMoveSystem()->AddMovePoint(pMovePointManager[3]);
	m_pNpc[m_pNpc.size() - 1]->GetMoveSystem()->AddMovePoint(pMovePointManager[4]);

	// �v���C���[�̈ʒu�ݒ�
	m_pPlayer->SetPosition(GameValue::Field::PLAYER_SPOWN_POINT[static_cast<int>(StageType::Plain)]);
}

// @brief �R���X�g���N�^
CSceneGame::CSceneGame()
	:CSceneBase()
{
	// �v���C���[�̐���
	m_pPlayer = std::make_unique<CPlayer>();

	switch (CQuest::GetInstance()->GetQuestData().stageType)
	{
	case StageType::Arena:
		InitArenaStage(); // ���Z��X�e�[�W�̏�����
		break;
	case StageType::Plain:
		InitPlainStage(); // �����X�e�[�W�̏�����
		break;
	}

	// ���o���G�����̃^�[�Q�b�g�ݒ�
	for (auto& npc : m_pNpc)
	{
		npc->SetTarget(m_pPlayer.get());
	}

	// Null�`�F�b�N�p���X�g�ɒǉ�
	for (auto& field : m_pFieldObject)
	{
		g_vNullCheckList.push_back(field.get()); // �t�B�[���h
	}
	g_vNullCheckList.push_back(m_pPlayer.get()); // �v���C���[
	g_vAttackObjects.push_back(m_pPlayer.get()); // �U���p���X�g�Ƀv���C���[��ǉ�
	for (auto& npc : m_pNpc)
	{
		g_vNullCheckList.push_back(npc.get()); // NPC
		g_vAttackObjects.push_back(npc.get()); // �U���p���X�g��NPC��ǉ�
	}
}

// @brief �f�X�g���N�^
CSceneGame::~CSceneGame()
{
	g_vNullCheckList.clear(); // Null�`�F�b�N�p���X�g�̃N���A
	g_vAttackObjects.clear(); // �U���p���X�g�̃N���A
}

// @brief �X�V����
void CSceneGame::Update(void)
{
	// �e���b�v�����݂���ꍇ�̓e���b�v�̍X�V���s��
	if (!m_pGameTelop.empty())
	{
		// ��ԑO�̗v�f�̃e���b�v�̍X�V����
		// �X�V�������I�������폜����
		if (m_pGameTelop[0]->Update())
		{
			// �e���b�v�̍폜����
			m_pGameTelop.erase(m_pGameTelop.begin());
		}
	}
	else
	{
		if (!CTimer::GetInstance()->Update())
		{
			for (auto& obj : g_vNullCheckList)
			{
				if (SafeNullCheck(obj))
				{
					obj->Update(); // Null�`�F�b�N���s���A�I�u�W�F�N�g���L���ȏꍇ�̂ݍX�V�������Ăяo��
				}
			}

			CollisionCheck(); // �����蔻��̏Փ˃`�F�b�N

			RayCastCheck(); // ���C�L���X�g�̃`�F�b�N

			AttackCollisionCheck(); // �U���̓����蔻��`�F�b�N
		}
		else
		{
			// �^�C���A�b�v���̏���
			// �Q�[���I�[�o�[�e���b�v��\�����āA�N�G�X�g�I���V�[���֑J��
			ChangeScene(SceneType::QuestSelect, TransitionType::Fade);
		}
	}
}

// @brief �`�揈��
void CSceneGame::Draw(void)
{
	SetRender3D();

	if (!m_pGameTelop.empty())
	{
		// ��ԑO�̗v�f�̃e���b�v�̍X�V����
		m_pGameTelop[0]->Draw();
	}

	// �^�C�}�[�̕`��
	CTimer::GetInstance()->Draw();

	// �ړ��|�C���g�̃f�o�b�O�`��
	CMovePointManager::GetInstance()->DebugDraw();

	// �U���̓����蔻��̃f�o�b�O�`��
	for (const auto& attack : m_vAttackCollisionInfos)
	{
		Collision::DrawCollision(attack.CollisionInfo);
	}

	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Draw(); // Null�`�F�b�N���s���A�I�u�W�F�N�g���L���ȏꍇ�̂ݕ`�揈�����Ăяo��
		}
	}
}

// @brief ���ׂẴt�B�[���h�I�u�W�F�N�g���擾����
// @return ���ׂẴt�B�[���h�I�u�W�F�N�g�̃��X�g
std::vector<CGameObject*> CSceneGame::GetAllFieldObjects(void)
{
	// �i�[���郊�X�g���쐬
	std::vector<CGameObject*> fieldObjects;

	for (auto& obj : g_vNullCheckList)
	{
		// Null�`�F�b�N���s��
		if (SafeNullCheck(obj))
		{
			// �����蔻��𑖍�
			if (!obj->GetCollisionInfo(Collision::Tag::FieldObject).empty())
			{
				fieldObjects.push_back(obj); // �����蔻�肪���݂���ꍇ�A���X�g�ɒǉ�
			}
		}
	}

	// ���X�g��Ԃ�
	return fieldObjects;
}

// @brief �����蔻��̏Փ˃`�F�b�N
void CSceneGame::CollisionCheck(void)
{
	// ���ׂẴQ�[���I�u�W�F�N�g�̓����蔻������擾���A�Փ˃`�F�b�N���s��
	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			auto collisionInfo = obj->GetCollisionInfo(Collision::Tag::All);
			for (const auto& info : collisionInfo)
			{
				for (auto& targetObj : g_vNullCheckList)
				{
					if (targetObj == obj) continue; // �������g�͏��O

					auto targetCollisionInfo = targetObj->GetCollisionInfo(Collision::Tag::All);

					for (const auto& targetInfo : targetCollisionInfo)
					{
						Collision::Result result = Collision::Hit(info, targetInfo);
						if (result.isHit)
						{
							obj->Hit(targetInfo); // �Փˎ��̏������Ăяo��
						}
					}
				}
			}
		}
	}

	// �y�ʉ�����ۂ̏������(�u���[�h�ƃi���[)
}

// @brief ���C�L���X�g�̃`�F�b�N
void CSceneGame::RayCastCheck(void)
{
	float SetUnderHeight = 0.0f; // �v���C���[�̐^���̒n�ʂ̍�����ݒ肷��ϐ�

	for (auto& obj : m_pFieldObject)
	{
		if (m_pPlayer->GetRay()->Cast(obj->GetCollisionInfo(Collision::Tag::FieldGround)))
		{
			if (SetUnderHeight < obj->GetPosition().y + obj->GetScale().y / 2.0f)
			{
				// ���C�L���X�g�����������ꍇ�A�v���C���[�̐^���̒n�ʂ̍�����ݒ�
				SetUnderHeight = obj->GetPosition().y + obj->GetScale().y / 2.0f;
			}
		}
	}
	m_pPlayer->SetUnderHeight(SetUnderHeight);

	SetUnderHeight = 0.0f;

	for (auto& npc : m_pNpc)
	{
		for (auto& obj : m_pFieldObject)
		{
			if (npc->GetRay()->Cast(obj->GetCollisionInfo(Collision::Tag::FieldGround)))
			{
				if (SetUnderHeight < obj->GetPosition().y + obj->GetScale().y / 2.0f)
				{
					// ���C�L���X�g�����������ꍇ�ANPC�̐^���̒n�ʂ̍�����ݒ�
					SetUnderHeight = obj->GetPosition().y + obj->GetScale().y / 2.0f;
				}
			}
		}
		npc->SetUnderHeight(SetUnderHeight); // NPC�̐^���̒n�ʂ̍�����ݒ�
	}
}

// @brief �U���̓����蔻��`�F�b�N
void CSceneGame::AttackCollisionCheck(void)
{
	for (auto& attackInfo : m_vAttackCollisionInfos)
	{
		for (auto& obj : g_vAttackObjects)
		{
			if (SafeNullCheck(obj))
			{
				// �������g�͏��O
				// �w��̃^�O���܂܂�Ă���ꍇ�͏��O
				std::vector<Collision::Info>SkipTagCollision;
				int EntityID = -1;

				for (auto& tag : attackInfo.CollisionInfo.tag)
				{
					switch (tag)
					{
					case Collision::Tag::Npc:
						SkipTagCollision = obj->GetCollisionInfo(Collision::Tag::Npc);
						EntityID = static_cast<CNpcBase*>(obj)->GetEntityID();
						break;
					case Collision::Tag::Player:
						SkipTagCollision = obj->GetCollisionInfo(Collision::Tag::Player);
						EntityID = static_cast<CPlayer*>(obj)->GetEntityID();
						break;
					}
				}
				// �w��̃^�O���܂܂�Ă���ꍇ�͏��O
				if (!SkipTagCollision.empty()) continue;

				bool IsHited = false;

				// ���łɓ����������Ƃ̂���G�͏��O
				if (!attackInfo.HitEntityIDList.empty())
				{
					for (int id : attackInfo.HitEntityIDList)
					{
						if (id == EntityID) IsHited = true;
					}
				}
				if (IsHited) continue;

				// �����蔻��̃`�F�b�N
				auto targetCollisionInfo = obj->GetCollisionInfo(Collision::Tag::All);
				for (const auto& targetInfo : targetCollisionInfo)
				{
					Collision::Result result = Collision::Hit(attackInfo.CollisionInfo, targetInfo);
					if (result.isHit)
					{
						obj->Hit(attackInfo.CollisionInfo, attackInfo.AttackPower); // �Փˎ��̏������Ăяo��

						// NPC���U�����󂯂��ꍇ�A���̍U���ɓ�������NPC��ID���U�����ɒǉ�
						attackInfo.HitEntityIDList.push_back(EntityID);
						break;
					}
				}
			}
		}

		// �U���̎������Ԃ�����
		attackInfo.DurationFrame -= 1.0f / fFPS;

	}

	// �������Ԃ�0�ȉ��ɂȂ�����폜
	for (auto itr = m_vAttackCollisionInfos.begin(); itr != m_vAttackCollisionInfos.end();)
	{
		if (itr->DurationFrame <= 0)
		{
			itr = m_vAttackCollisionInfos.erase(itr); // �������Ԃ�0�ȉ��̏ꍇ�A�U�������폜
		}
		else
		{
			++itr;
		}
	}
}

// @brief �U���̐���
// @param In_CollisionInfo �ՓˑΏ�
void CSceneGame::AttackCreate(AttackCollision In_CollisionInfo)
{
	// �U���̐���
	m_vAttackCollisionInfos.push_back(In_CollisionInfo);
}

// @brief �e���b�v�̒ǉ�
// @param In_Telop �ǉ�����e���b�v
void CSceneGame::AddTelop(CTelopEffect* In_Telop)
{
	m_pGameTelop.push_back(In_Telop);
}
