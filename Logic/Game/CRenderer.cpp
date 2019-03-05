#include "StdInc.h"

extern sf::RenderWindow* g_pWindow;

CRendererDebug::CRendererDebug()
{
};


CRenderer::CRenderer(uint id) :
	m_uiID(id)
{
	m_mapRenderers[id] = this;
	vecBBoxMin = new Vector3D(0, 0, 0);
	vecBBoxMax = new Vector3D(0, 0, 0);
};

CRenderer::~CRenderer()
{

};

void CRenderer::DrawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void CRenderer::RenderBoundingBox()
{
	glColor4ub(255, 0, 0, 255);
	glLineWidth(3);

	DrawLine(vecBBoxMin->x, vecBBoxMax->y, vecBBoxMin->z, vecBBoxMin->x, vecBBoxMax->y, vecBBoxMax->z);
	DrawLine(vecBBoxMin->x, vecBBoxMin->y, vecBBoxMin->z, vecBBoxMin->x, vecBBoxMin->y, vecBBoxMax->z);
	DrawLine(vecBBoxMax->x, vecBBoxMin->y, vecBBoxMin->z, vecBBoxMax->x, vecBBoxMin->y, vecBBoxMax->z);
	DrawLine(vecBBoxMax->x, vecBBoxMax->y, vecBBoxMin->z, vecBBoxMax->x, vecBBoxMax->y, vecBBoxMax->z);
	
	DrawLine(vecBBoxMax->x, vecBBoxMax->y, vecBBoxMin->z, vecBBoxMax->x, vecBBoxMin->y, vecBBoxMin->z);
	DrawLine(vecBBoxMax->x, vecBBoxMax->y, vecBBoxMin->z, vecBBoxMin->x, vecBBoxMax->y, vecBBoxMin->z);
	DrawLine(vecBBoxMin->x, vecBBoxMin->y, vecBBoxMin->z, vecBBoxMin->x, vecBBoxMax->y, vecBBoxMin->z);
	DrawLine(vecBBoxMin->x, vecBBoxMin->y, vecBBoxMin->z, vecBBoxMax->x, vecBBoxMin->y, vecBBoxMin->z);
	
	DrawLine(vecBBoxMax->x, vecBBoxMax->y, vecBBoxMax->z, vecBBoxMax->x, vecBBoxMin->y, vecBBoxMax->z);
	DrawLine(vecBBoxMax->x, vecBBoxMax->y, vecBBoxMax->z, vecBBoxMin->x, vecBBoxMax->y, vecBBoxMax->z);
	DrawLine(vecBBoxMin->x, vecBBoxMin->y, vecBBoxMax->z, vecBBoxMin->x, vecBBoxMax->y, vecBBoxMax->z);
	DrawLine(vecBBoxMin->x, vecBBoxMin->y, vecBBoxMax->z, vecBBoxMax->x, vecBBoxMin->y, vecBBoxMax->z);
};

bool CRenderer::Render()
{
	for (auto pMesh : m_vecMeshes)
	{
		pMesh->Draw();
	}
	return true;
};

void CRenderer::RecalculateBoundingBox()
{
	vecBBoxMax->Reset();
	vecBBoxMin->Reset();
	for( std::vector<CMeshVertex*>::iterator it = m_vecMeshVertices.begin(); it != m_vecMeshVertices.end(); ++it)
	{
		vecBBoxMax->x = std::max(vecBBoxMax->x, (*it)->x);
		vecBBoxMax->y = std::max(vecBBoxMax->y, (*it)->y);
		vecBBoxMax->z = std::max(vecBBoxMax->z, (*it)->z);

		vecBBoxMin->x = std::min(vecBBoxMin->x, (*it)->x);
		vecBBoxMin->y = std::min(vecBBoxMin->y, (*it)->y);
		vecBBoxMin->z = std::min(vecBBoxMin->z, (*it)->z);
	}
};



bool CRenderer::AddMesh(CMesh* pMesh)
{
	pMesh->SetRenderer(this);
	m_vecMeshes.push_back(pMesh);
	return true;
};

bool CRenderer::StaticRender(uint uiID)
{
	auto pRenderer = CRenderer::m_mapRenderers.find(uiID);
	if (pRenderer != CRenderer::m_mapRenderers.end())
	{
		return pRenderer->second->Render();
	}
	return false;
};

bool CRenderer::StaticRenderBoundingBox(uint uiID)
{
	auto pRenderer = CRenderer::m_mapRenderers.find(uiID);
	if (pRenderer != CRenderer::m_mapRenderers.end())
	{
		pRenderer->second->RenderBoundingBox();
		return true;
	}
	return false;
};

CRenderer* CRenderer::GetByID(uint uiID)
{
	auto pRenderer = CRenderer::m_mapRenderers.find(uiID);
	if (pRenderer != CRenderer::m_mapRenderers.end())
	{
		return pRenderer->second;
	}
	return nullptr;
};

void CMesh::SetRenderer(CRenderer* pRenderer)
{
	m_pParentRenderer = pRenderer;
}

CMesh::CMesh()
{
}

void CMesh::Draw()
{
	if (m_vecMeshTriangles.size() > 0)
	{
		CMeshVertex* vecVertex[3];
		CMeshTriangle* pTriangle;

		if (m_strTexture)
		{
			pGame->UseTexture(m_strTexture);
			for (uint ui_vertex : m_vecMeshTriangles)
			{
				pTriangle = m_pParentRenderer->GetTriangleByID(ui_vertex);
				vecVertex[0] = m_pParentRenderer->GetVertexByID(pTriangle->vertex1);
				vecVertex[1] = m_pParentRenderer->GetVertexByID(pTriangle->vertex2);
				vecVertex[2] = m_pParentRenderer->GetVertexByID(pTriangle->vertex3);
				glBegin(GL_TRIANGLES);
				for (CMeshVertex* pVertex : vecVertex)
				{
					glColor4ub(pVertex->r, pVertex->g, pVertex->b, pVertex->a);
					glTexCoord2f(pVertex->u, pVertex->v);
					glVertex3f(pVertex->x, pVertex->y, pVertex->z);
				}
				glEnd();
			}
		}
		else
		{
			for (uint ui_vertex : m_vecMeshTriangles)
			{
				pTriangle = m_pParentRenderer->GetTriangleByID(ui_vertex);
				vecVertex[0] = m_pParentRenderer->GetVertexByID(pTriangle->vertex1);
				vecVertex[1] = m_pParentRenderer->GetVertexByID(pTriangle->vertex2);
				vecVertex[2] = m_pParentRenderer->GetVertexByID(pTriangle->vertex3);
				glBegin(GL_TRIANGLES);
				for (CMeshVertex* pVertex : vecVertex)
				{
					glColor4ub(pVertex->r, pVertex->g, pVertex->b, pVertex->a);
					glVertex3f(pVertex->x, pVertex->y, pVertex->z);
				}
				glEnd();
			}
		}

	}
}

uint CRenderer::AddVertex(CMeshVertex* pVertex)
{
	m_vecMeshVertices.push_back(pVertex);
	return m_vecMeshVertices.size()-1;
}

uint CRenderer::AddVertex(float x, float y, float z, uchar r, uchar g, uchar b, uchar a, float u, float v)
{
	CMeshVertex* pVertex = new CMeshVertex(x, y, z, r, g, b, a, u, v);
	m_vecMeshVertices.push_back(pVertex);
	return m_vecMeshVertices.size()-1;
}
uint CRenderer::CreateTriangle(uint v1, uint v2, uint v3)
{
	CMeshTriangle* pTriangle = new CMeshTriangle(v1, v2, v3);
	m_vecMeshTriangles.push_back(pTriangle);
	return m_vecMeshTriangles.size()-1;
}

CMeshVertex* CRenderer::GetVertexByID(uint uiVertexID)
{
	return m_vecMeshVertices.at(uiVertexID);
}

CMeshTriangle* CRenderer::GetTriangleByID(uint uiTriangleID)
{
	return m_vecMeshTriangles.at(uiTriangleID);
}

int CMesh::CreateTriangle(uint v1, uint v2, uint v3)
{
	uint uiTriangle = m_pParentRenderer->CreateTriangle(v1, v2, v3);
	m_vecMeshTriangles.push_back(uiTriangle);
	return m_vecMeshTriangles.size() - 1;
}

void CRendererDebug::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	CRenderer::DrawLine(from.getX(), from.getY(), from.getZ(), to.getX(), to.getY(), to.getZ());
}