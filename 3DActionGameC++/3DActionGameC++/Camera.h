#pragma once
#include <DirectXMath.h> 
#include "Structs.h"

class Camera 
{
protected:
	//コンストラクタ
	Camera();
public:
	//アドレス作成
	static void CreateCamera(void);
	//デストラクタ
	virtual ~Camera();
 
	virtual void Update(void) = 0;
	virtual void Update(DirectX::XMFLOAT3 PlayerPos, DirectX::XMFLOAT3 PlayerRot) = 0;
	
	DirectX::XMFLOAT4X4 GetViewMatrix(bool transpose = true);

	DirectX::XMFLOAT4X4 GetProjectionMatrix(bool transpose = true);
 
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
 
	DirectX::XMFLOAT3 GetLook() { return m_look; }
	void SetCameraPos(float fX, float fY, float fZ) { m_look = { fX, fY, fZ }; }

	float GetRadY() { return m_radY; }

	void SetFov(float Add){ m_radius = Add; }

	DirectX::XMFLOAT3 MoveVector(void);

	static Camera* GetInfo() { return m_pCamera; }
protected:
	static Camera* m_pCamera;

	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_look;
	DirectX::XMFLOAT3 m_up;
	float m_fovy;
	float m_aspect;
	float m_near;
	float m_far;

	float m_radius;
	float m_radY;
};

class CameraDebug : public Camera {
public:
	CameraDebug();
	~CameraDebug();
	void Update(DirectX::XMFLOAT3 PlayerPos = { 0.0f,0.0f,0.0f }, DirectX::XMFLOAT3 PlayerRot = { 0.0f,0.0f,0.0f }) final;
	void Update(void) final;
private:
	float m_radXZ;
	float m_fMovePosXZ;
};