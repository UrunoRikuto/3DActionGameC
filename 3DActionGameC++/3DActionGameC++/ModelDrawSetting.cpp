#include "ModelDrawSetting.h"
#include "ShaderList.h"
#include "Defines.h"
#include "Geometory.h"
#include "Model.h"
#include "Camera.h"
#include "Setting.h"

void ShaderSetting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Model* Model);
void ShaderCameraSetting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Model* Model, Camera* Camera);
void ShaderCameraAnimationSetting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Model* Model, Camera* Camera);


void ShaderSetting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Model* Model)
{
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world, view, proj;
	world = Setting(pos, Scale, Rotate);
	view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, METER(1.0f), METER(-1.0f), 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	);
	proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f,
		CMETER(5.0f), METER(1000.0f)
	);

	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&wvp[1], DirectX::XMMatrixTranspose(view));
	DirectX::XMStoreFloat4x4(&wvp[2], DirectX::XMMatrixTranspose(proj));

	ShaderList::SetWVP(wvp);

	Model->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	Model->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));
}

void ShaderCameraSetting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate,Model* Model, Camera* Camera)
{
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world;
	world = Setting(pos, Scale, Rotate);

	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(world));
	wvp[1] = Camera->GetViewMatrix();
	wvp[2] = Camera->GetProjectionMatrix();

	Geometory::SetView(wvp[1]);
	Geometory::SetProjection(wvp[2]);

	ShaderList::SetWVP(wvp);

	Model->SetVertexShader(ShaderList::GetVS(ShaderList::VS_WORLD));
	Model->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));
}

void CreateObject(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Model* Model, Camera* Camera,bool IsLighting, DirectX::XMFLOAT3 LightingColor)
{
	ShaderCameraSetting(pos, Scale, Rotate, Model, Camera);
	for (int i = 0; i < Model->GetMeshNum(); ++i)
	{
	
		Model::Material material = *Model->GetMaterial(Model->GetMesh(i)->materialID);
		if (IsLighting)
		{
			material.ambient.x = LightingColor.x; // x (r) 
			material.ambient.y = LightingColor.y; // y (g) 
			material.ambient.z = LightingColor.z; // z (b) 
		}
		ShaderList::SetMaterial(material);

		if (Model) {
			Model->Draw(i);
		}
	}
}

void ShaderCameraAnimationSetting(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Model* Model, Camera* Camera)
{
	DirectX::XMFLOAT4X4 wvp[3];
	DirectX::XMMATRIX world;
	world = Setting(pos, Scale, Rotate);

	DirectX::XMStoreFloat4x4(&wvp[0], DirectX::XMMatrixTranspose(world));
	wvp[1] = Camera->GetViewMatrix();
	wvp[2] = Camera->GetProjectionMatrix();

	Geometory::SetView(wvp[1]);
	Geometory::SetProjection(wvp[2]);

	ShaderList::SetWVP(wvp);

	Model->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));
	Model->SetPixelShader(ShaderList::GetPS(ShaderList::PS_LAMBERT));
}

void CreateAnimationObject(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 Scale, DirectX::XMFLOAT3 Rotate, Model* Model, Camera* Camera, bool IsLighting , DirectX::XMFLOAT3 LightingColor)
{
	ShaderCameraAnimationSetting(pos, Scale, Rotate, Model, Camera);
	const Model::Mesh* tMesh;

	for (int i = 0; i < Model->GetMeshNum(); ++i)
	{
		tMesh = Model->GetMesh(i);
		Model::Material material = *Model->GetMaterial(tMesh->materialID);
		material.ambient.x = 0.85f; // x (r) 
		material.ambient.y = 0.85f; // y (g) 
		material.ambient.z = 0.85f; // z (b) 
		ShaderList::SetMaterial(material);

		// ボーンの情報をシェーダーに送る
		DirectX::XMFLOAT4X4 bones[200];
		for (int j = 0; j < tMesh->bones.size(); ++j)
		{
			DirectX::XMStoreFloat4x4(&bones[j], DirectX::XMMatrixTranspose(
				tMesh->bones[j].invOffset * Model->GetBoneMatrix(tMesh->bones[j].nodeIndex)
			));
		}
		ShaderList::SetBones(bones);

		if (Model) {
			Model->Draw(i);
		}
	}

}