#pragma once
#include "DirectXTex/DirectXTex.h"

class Collision
{
public:
	enum Type
	{
		eNone,
		eBox,
		eSphere,
		ePlane,
		eRay,
		eLine,
		ePoint,
		eTriangle
	};

	enum class Tag
	{
		Player,
		Enemy,
		Field,
		Object,
		Attack,
	};

	//--- �����蔻��̌`�� 
	struct Box	// �l�p 
	{
		DirectX::XMFLOAT3  center;  // ���S���W 
		DirectX::XMFLOAT3  size;	// �T�C�Y
	};

	struct Sphere	// �� 
	{
		DirectX::XMFLOAT3  center;  // ���S���W 
		float			   radius;  // ���a 
	};

	struct Plane	// ����
	{
		DirectX::XMFLOAT3  pos;		// ���ʏ�̈�_ 
		DirectX::XMFLOAT3  normal;	// ���ʂ̖@��
	};

	struct Ray	// �����̒���
	{
		DirectX::XMFLOAT3 origin;	// �n�_
		DirectX::XMFLOAT3 dir;		// ���C�̌���
	};

	struct Line	// ����
	{
		DirectX::XMFLOAT3 start;	// �����̎n�_
		DirectX::XMFLOAT3 end;		// �����̏I�_
	};

	struct Point // �_
	{
		DirectX::XMFLOAT3 pos;	// ���W
	};

	struct Triangle // �O�p�`
	{
		DirectX::XMFLOAT3 point[3];	// �e���_
	};

	//--- �����蔻��̓������
	struct Info
	{
		Type type;					// �����蔻��̎��
		Tag tag;
		union
		{
			Box box;
			Sphere sphere;
			Plane plane;
			Ray ray;
			Line line;
			Point point;
			Triangle triangle;
		};

	};

	//--- �����蔻��̌��� 
	struct Result
	{
		bool isHit;					// �����������ǂ��� 
		DirectX::XMFLOAT3  point;	// �q�b�g�ʒu 
		DirectX::XMFLOAT3  normal;	// �q�b�g���� 
		Info other;					// �����蔻��I�u�W�F�N�g]
		float u;					// �o���Z�����Wu
		float v;					// �o���Z�����Wv
		float t;					// �n�_�����_�܂ł̋���
	};

	// 2D
	enum Type2D
	{
		eSquare,
		eCircle
	};

	struct Square	// �Z�`
	{
		DirectX::XMFLOAT2 pos;
		DirectX::XMFLOAT2 size;
	};

	struct Circle	// �~�^
	{
		DirectX::XMFLOAT2 pos;
		float radius;
	};

	//--- �����蔻��̓������
	struct Info2D
	{
		Type2D type;
		Square square;
		Circle circle;
	};

	//--- 2D�����蔻��̌��� 
	struct Result2D 
	{
		bool isHit;	// �����������ǂ��� 
		DirectX::XMFLOAT2 posAtoB;
		DirectX::XMFLOAT2 posBtoA;
		DirectX::XMFLOAT2 distance;
	};
public:
	// Info�^�ł̓����蔻��
	static Result Hit(Info a, Info b);
	// �l�p���m�̓����蔻��
	static Result Hit(Box a, Box b);
	// �����m�ł̓����蔻��
	static Result Hit(Sphere a, Sphere b);
	static Result Hit(Plane plane, Line line);
	static Result Hit(Plane plane, Ray ray, float lenght);
	static Result Hit(Point point, Triangle triangle);
	static Result Hit(Ray ray, Triangle triangle);
	static Result Hit(Line line, Triangle triangle);
	static Result2D Hit2D(Info2D a, Info2D b);
	static Result2D Hit2D(Square a,Square b);
	static Result2D Hit2D(Circle a, Circle b);
	static void DrawCollision(Collision::Info collision);
};