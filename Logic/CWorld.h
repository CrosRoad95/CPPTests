#pragma once

using rayResult = btCollisionWorld::AllHitsRayResultCallback;

class CWorld
{
public:
	CWorld();

	void RegisterDummy(CDummy* pDummy);
	void UnregisterDummy(CDummy* pDummy);
	void RegisterCollision(CCollision* pCollision);
	void UnregisterCollision(CCollision* pCollision);
	void RegisterTerrain(CTerrain* pTerrain);
	void UnregisterTerrain(CTerrain* pTerrain);
	void RegisterPhysical(CPhysical* pPhysical);
	void UnregisterPhysical(CPhysical* pPhysical);
	void DoPulse();
	void Do1SecPulse();
	void InitializeCollisions();
	rayResult rayTest(const btVector3& rayFromWorld, const btVector3& rayToWorld) const;

	void DrawDebug();
	void Initialize();
	void AddCollision(CCollision* pCollision);
	void AddPhysical(CPhysical* pPhysical);
	void AddTerrain(CTerrain* pTerrain);

	btDiscreteDynamicsWorld* GetWorldCollision() const { return m_pWorldCollision;  }
private:
	std::vector<CDummy*>		CDummies;
	std::vector<CCollision*>	m_vecCollisions;
	std::vector<CPhysical*> 	m_vecPhysicals;
	std::vector<CTerrain*>	    m_vecTerrains;

	btDiscreteDynamicsWorld* m_pWorldCollision;
};