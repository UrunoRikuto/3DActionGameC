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

/* �O���[�o���ϐ� */
std::list<CGameObject*> g_vNullCheckList; // Null�`�F�b�N�p�̃Q�[���I�u�W�F�N�g�̃��X�g
std::list<CGameObject*> g_vAttackObjects; // �U���p�̃Q�[���I�u�W�F�N�g�̃��X�g

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
	m_pPlayer->SetPosition(XMFLOAT3(0.0f, 0.0f, -180.0f));
}

void CSceneGame::InitPlainStage(void)
{
	//// �ړ��|�C���g�̐���
	//CMovePointManager::GetInstance()->CreateData(FieldType::Plain);
	////- �ړ��|�C���g�}�l�[�W���[�̃C���X�^���X���擾
	//std::vector<XMFLOAT3> pMovePointManager = CMovePointManager::GetInstance()->GetMovePoints();

	//// NPC�̐����i�^�[�Q�b�gNPC�j
	//m_pNpc.push_back(std::make_unique<CTargetNpc>(pMovePointManager[0], NpcType::Normal));
	//m_pNpc[0]->GetMoveSystem()->AddMovePoint(pMovePointManager[1]);

	//// NPC�̐����i��qNPC�j
	//m_pNpc.push_back(std::make_unique<CGuardNpc>(pMovePointManager[2], NpcType::Normal));
	//m_pNpc[1]->GetMoveSystem()->AddMovePoint(pMovePointManager[3]);
	//m_pNpc[1]->GetMoveSystem()->AddMovePoint(pMovePointManager[4]);
}

// @brief �R���X�g���N�^
CSceneGame::CSceneGame()
	:CSceneBase()
{
	// ���O��Ԃ̎g�p
	using namespace GameValue;

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

}

// @brief �X�V����
void CSceneGame::Update(void)
{
	for(auto& obj : g_vNullCheckList)
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

// @brief �`�揈��
void CSceneGame::Draw(void)
{
	// �ړ��|�C���g�̃f�o�b�O�`��
	CMovePointManager::GetInstance()->DebugDraw(); // �ړ��|�C���g�̃f�o�b�O�`��

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
	/*
	using namespace GameValue::Collision;

	/// �u���[�h�t�F�[�Y
	// �Փ˂���\���̂��铖���蔻������X�g�A�b�v���鏈��

	// �i�[���X�g
	std::vector<CollisionCheckInfo> collisionList;

	// Null�`�F�b�N���s���A�I�u�W�F�N�g���L���ȏꍇ�̂ݏ������s��
	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			// �e�I�u�W�F�N�g�̓����蔻������擾
			auto collisionInfo = obj->GetCollisionInfo(Collision::Tag::All);
			
			for (const auto& info : collisionInfo)
			{
				CollisionCheckInfo checkInfo;
				checkInfo.SelfInfo = info; // �I�u�W�F�N�g��ݒ�

				for (auto& TargetObject : g_vNullCheckList)
				{
					if (TargetObject == obj) continue; // �������g�͏��O

					auto TargetCollisionInfo = TargetObject->GetCollisionInfo(Collision::Tag::All);

					for (const auto& Targetinfo : TargetCollisionInfo)
					{
						switch (info.type)
						{
						case Collision::Type::eNone:
							break;
						case Collision::Type::eBox:
							if (StructMath::Distance(Targetinfo.box.center,info.box.center) <= DETECT_DISTANCE)
							{
								checkInfo.TargetInfo.push_back(Targetinfo); // �Ώۂ̓����蔻�����ݒ�
							}
							break;
						case Collision::Type::eSphere:
							break;
						case Collision::Type::ePlane:
							break;
						case Collision::Type::eRay:
							break;
						case Collision::Type::eLine:
							break;
						case Collision::Type::ePoint:
							break;
						case Collision::Type::eTriangle:
							break;
						}
					}
				}

				if (!checkInfo.TargetInfo.empty()) // �Ώۂ̓����蔻���񂪂���ꍇ
				{
					collisionList.push_back(checkInfo); // ���X�g�ɒǉ�
				}
			}
		}
	}



	/// �i���[�t�F�[�Y
	// ���X�g�A�b�v�����I�u�W�F�N�g���m�̏ڍׂȏՓ˔���
	for (const auto& checkInfo : collisionList)
	{
		for (const auto& targetInfo : checkInfo.TargetInfo)
		{
			Collision::Result result = Collision::Hit(checkInfo.SelfInfo, targetInfo);
			if (result.isHit)
			{
				int a = 0;
			}
		}
	}
	*/
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
