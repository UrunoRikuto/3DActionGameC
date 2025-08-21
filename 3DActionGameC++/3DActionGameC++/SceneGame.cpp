/*
* @file SceneGame.cpp
* @brief �Q�[���V�[���̃N���X��Cpp�t�@�C��
* @author �F���엤�l
* @date 2025/08/04 �N���X�̎���
*/

/* �w�b�_�[�ŗ��p����V�X�e���̃C���N���[�h */
#include <memory>
/* �Q�[���I�u�W�F�N�g�̃C���N���[�h */
#include "Field.h"
#include "Player.h"
#include "TargetNpc.h"
#include "GuardNpc.h"
/* �w�b�_�[�̃C���N���[�h */
#include "SceneGame.h"
/* �V�X�e���E�v�f�̃C���N���[�h */
#include "Camera.h"
#include "Defines.h"
#include "MovePointManager.h"

/* �O���[�o���ϐ� */
std::vector<CGameObject*> g_vNullCheckList; // Null�`�F�b�N�p�̃Q�[���I�u�W�F�N�g�̃��X�g

// @brief �R���X�g���N�^
CSceneGame::CSceneGame()
	:CSceneBase()
{
	CMovePointManager::GetInstance()->CreateData(FieldType::Plain); // �ړ��|�C���g�̐���

	// �t�B�[���h�̐���
	m_pField.resize(2);
	m_pField[0] = std::make_unique<CField>();
	m_pField[0]->SetScale(XMFLOAT3(1000.0f, 1.0f, 1000.0f));
	m_pField[1] = std::make_unique<CField>();
	m_pField[1]->SetPosition(XMFLOAT3(0.0f, 1.0f, 1000.0f)); // 2�ڂ̃t�B�[���h��z�u
	m_pField[1]->SetScale(XMFLOAT3(1000.0f, 1.0f, 1000.0f));

	// �v���C���[�̐���
	m_pPlayer = std::make_unique<CPlayer>();

	//- �ړ��|�C���g�}�l�[�W���[�̃C���X�^���X���擾
	std::vector<XMFLOAT3> pMovePointManager = CMovePointManager::GetInstance()->GetMovePoints();

	// NPC�̐����i�^�[�Q�b�gNPC�j
	m_pNpc.push_back(std::make_unique<CTargetNpc>(0));
	m_pNpc[0]->GetMoveSystem()->AddMovePoint(pMovePointManager[1]);

	// NPC�̐����i��qNPC�j
	m_pNpc.push_back(std::make_unique<CGuardNpc>(2));
	m_pNpc[1]->GetMoveSystem()->AddMovePoint(pMovePointManager[3]);
	m_pNpc[1]->GetMoveSystem()->AddMovePoint(pMovePointManager[4]);


	for (auto& field : m_pField)
	{
		g_vNullCheckList.push_back(field.get()); // �t�B�[���h��Null�`�F�b�N�p���X�g�ɒǉ�
	}
	g_vNullCheckList.push_back(m_pPlayer.get()); // �v���C���[��Null�`�F�b�N�p���X�g�ɒǉ�
	for (auto& npc : m_pNpc)
	{
		g_vNullCheckList.push_back(npc.get()); // NPC��Null�`�F�b�N�p���X�g�ɒǉ�
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
}

// @brief �`�揈��
void CSceneGame::Draw(void)
{
	// �ړ��|�C���g�̃f�o�b�O�`��
	CMovePointManager::GetInstance()->DebugDraw(); // �ړ��|�C���g�̃f�o�b�O�`��

	for (auto& obj : g_vNullCheckList)
	{
		if (SafeNullCheck(obj))
		{
			obj->Draw(); // Null�`�F�b�N���s���A�I�u�W�F�N�g���L���ȏꍇ�̂ݕ`�揈�����Ăяo��
		}
	}
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
				// ���̃I�u�W�F�N�g�Ƃ̏Փ˃`�F�b�N
				for (auto& tag : info.tag)
				{
					// ���C�L���X�g�̃^�O���������珈�����X�L�b�v����
					if (tag == Collision::Tag::RayCast)
					{
						continue; // ���C�L���X�g�̃^�O���������珈�����X�L�b�v
					}
				}

				for (auto& targetObj : g_vNullCheckList)
				{
					if (targetObj == obj) continue; // �������g�͏��O

					auto targetCollisionInfo = targetObj->GetCollisionInfo(Collision::Tag::All);

					for (const auto& targetInfo : targetCollisionInfo)
					{
						bool IsSkip = false; // ���C�L���X�g�̃^�O���������珈�����X�L�b�v����t���O
						for (const auto& tag : targetInfo.tag)
						{
							// ���C�L���X�g�̃^�O���������珈�����Ȃ�
							if (tag == Collision::Tag::RayCast)
							{
								IsSkip = true; // ���C�L���X�g�̃^�O���������珈�����X�L�b�v����
								break; // ���[�v�𔲂���
							}
						}

						if (IsSkip) continue; // ���C�L���X�g�̃^�O���������珈�����X�L�b�v

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
	for (auto& obj : m_pField)
	{
		if (m_pPlayer->GetRay()->Cast(obj->GetCollisionInfo()))
		{
			// ���C�L���X�g�����������ꍇ�A�v���C���[�̐^���̒n�ʂ̍�����ݒ�
			m_pPlayer->SetUnderHeight(obj->GetPosition().y + obj->GetScale().y / 2.0f);
			return;
		}
	}
	m_pPlayer->SetUnderHeight(-3.0f); // ���C�L���X�g��������Ȃ������ꍇ�A-3.0f��ݒ�
}
