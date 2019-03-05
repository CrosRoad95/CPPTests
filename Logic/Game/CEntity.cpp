#include "StdInc.h"

CEntity::CEntity(uint uiID, int& iFreeID)
{
	m_uiID = uiID;
	MAP_FIND_FIRST_FREE_KEY(iFree, m_pEntities);
	m_pEntities.insert({ iFree, this });

	iFreeID = iFree;
}

void CEntity::StaticPulseAll()
{
	for (auto entity : m_pEntities)
	{
		entity.second->DoPulse();
	}
}

void CEntity::DoPulse()
{
	Render();
}

void CEntity::ApplyPreRenderTransformation()
{
	glPushMatrix();
	glTranslatef(m_pPosition->x, m_pPosition->y, m_pPosition->z);
	glRotatef(m_pRotation->x, 1, 0, 0);
	glRotatef(m_pRotation->y, 0, 1, 0);
	glRotatef(m_pRotation->z, 0, 0, 1);
}

void CEntity::ApplyPostRenderTransformation()
{
	glPopMatrix();
}

bool CEntity::IsVisible()
{
	if (!m_bVisible)
	{
		return false;
	}
	if (m_ucAlpha == 0)
	{
		return false;
	}
	return true;
}
void CEntity::Render()
{
	if (IsVisible())
	{
		ApplyPreRenderTransformation();
		CRenderer::StaticRender(m_uiID);
		ApplyPostRenderTransformation();
	}
}

void CEntity::RenderBoundingBox()
{
	if (IsVisible())
	{
		ApplyPreRenderTransformation();
		CRenderer::StaticRenderBoundingBox(m_uiID);
		ApplyPostRenderTransformation();
	}
}

CEntity::~CEntity()
{

}
