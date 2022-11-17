#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();
	 VertexBuffer* getVertexBuffer();
	 IndexBuffer* getIndexBuffer();
private:
	VertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;
private:
	friend class DeviceContext;
};