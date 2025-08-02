#ifndef ___VERTEXBUFFER_H___
#define ___VERTEXBUFFER_H___

#include "DirectX.h"

struct Vertex {
	float pos[3];
	float uv[2];
};


ID3D11Buffer* CreateVertexBuffer(void* vtxData, UINT vtxNum);

#endif //- !___VERTEXBUFFER_H___