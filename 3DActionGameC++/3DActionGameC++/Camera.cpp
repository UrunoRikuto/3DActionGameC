#include "Camera.h"
#include "Input.h" 
#include "Defines.h"

Camera* Camera::m_pCamera = nullptr;

Camera::Camera()
	: m_pos(0.0f, 0.0f, -40.0f)
	, m_look(-19.0f,-19.0f,-40.0f)
	, m_up(0.0f, 1.0f, 0.0f)
	, m_fovy(DirectX::XMConvertToRadians(60.0f))
	, m_aspect(16.0f / 9.0f)
	, m_near(CMETER(30.0f)), m_far(METER(1000.0f)) 
	, m_radius(55.5f)
	, m_radY(3.1f)
{ 
}

void Camera::CreateCamera()
{
	if (m_pCamera == nullptr)
	{
		m_pCamera = new CameraDebug();
	}
}

Camera::~Camera()
{

}

DirectX::XMFLOAT4X4 Camera::GetViewMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),
		DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),
		DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f)
	);
	if (transpose) {
		view = DirectX::XMMatrixTranspose(view);
	}
	DirectX::XMStoreFloat4x4(&mat, view);
	return mat;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix(bool transpose)
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	proj = DirectX::XMMatrixPerspectiveFovLH(
		m_fovy,m_aspect,m_near,m_far
	);
	if (transpose) {
		proj = DirectX::XMMatrixTranspose(proj);
	}
	DirectX::XMStoreFloat4x4(&mat, proj);
	return mat;

}

DirectX::XMFLOAT3 Camera::MoveVector(void)
{
	DirectX::XMFLOAT3 F3_MoveDirections;
	DirectX::XMVECTOR CameraPos = DirectX::XMLoadFloat3(&m_pos);
	DirectX::XMVECTOR CameraLookPos = DirectX::XMLoadFloat3(&m_look);
	DirectX::XMVECTOR V_MoveDirections = DirectX::XMVectorSubtract(CameraLookPos, CameraPos);;

	V_MoveDirections = DirectX::XMVector3Normalize(V_MoveDirections);
	DirectX::XMStoreFloat3(&F3_MoveDirections, V_MoveDirections);

	return F3_MoveDirections;
}

CameraDebug::CameraDebug()
	:Camera()
	,m_radXZ(6.25f)
	, m_fMovePosXZ(0.0f)
{

}

CameraDebug::~CameraDebug()
{
	
}

void CameraDebug::Update(DirectX::XMFLOAT3 PlayerPos, DirectX::XMFLOAT3 PlayerRot)
{
	m_look = PlayerPos;

	m_radXZ = DirectX::XMConvertToRadians(PlayerRot.y);
	m_radY = DirectX::XMConvertToRadians(180) - DirectX::XMConvertToRadians(PlayerRot.x);


	m_pos.x = cosf(m_radY) * sinf(m_radXZ) * m_radius + m_look.x;
	m_pos.y = sinf(m_radY) * m_radius + m_look.y;
	m_pos.z = cosf(m_radY) * cosf(m_radXZ) * m_radius + m_look.z;
}

void CameraDebug::Update(void)
{
	m_look.x = -19.0f;
	m_look.y = -19.0f;
	m_look.z = -40.0f;

	m_pos.x = cosf(m_radY) * sinf(m_radXZ) * m_radius + m_look.x;
	m_pos.y = sinf(m_radY) * m_radius + m_look.y;
	m_pos.z = cosf(m_radY) * cosf(m_radXZ) * m_radius + m_look.z;
}