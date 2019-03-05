#include "StdInc.h"
CWorld::CWorld()
{
	InitializeCollisions();
}

void CWorld::Initialize()
{
	m_pWorldCollision->setDebugDrawer(pGame->GetRendererDebug());

	//fallShape = new btBoxShape(btVector3(5,5,5)); /* Old falling shape */

	static btScalar vertexes[] = { 0,0,0, 10,0,0, 10,10,0, 10,10,10, 0,10,10, 0,-10,0 };
	size_t vertexesSize = sizeof(vertexes) / 3 / sizeof(btScalar);
	btCollisionShape* fallShape = new btConvexHullShape(vertexes, vertexesSize); /* New falling shape */

	btQuaternion qtn;
	static btScalar matrix[16];
	static btTransform trans;

	static btDefaultMotionState* fallMotionState;
	trans.setIdentity();
	trans.setRotation(qtn);
	fallMotionState = new btDefaultMotionState(trans);

	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);

	CCollision* pCollision1 = new CCollision(1);
	pCollision1->Set(fallShape);
	CCollision* pCollision2 = new CCollision(2);
	pCollision2->Set(new btCapsuleShape(1,5));
	CCollision* pCollision3 = new CCollision(3);
	pCollision3->Set(new btBoxShape(btVector3(1,1,1)));


	for (int i = 0; i < 3; i++)
	{
		CPhysical* physical = new CPhysical(pCollision1);
		physical->SetPosition(btVector3(-10, i * 0.1, i * 15 + 60));

		CPhysical* physical2 = new CPhysical(pCollision2);
		physical2->SetPosition(btVector3(10, i * 0.1, i * 7 + 60));

		CPhysical* physical3 = new CPhysical(pCollision3);
		physical3->SetPosition(btVector3(0, i * 0.1, i * 7 + 60));

	}
}

void CWorld::AddCollision(CCollision* pCollision)
{
	btCollisionObject* btCollision = pCollision->GetCollisionObject();
	if (btCollision->getCollisionShape())
	{
		m_pWorldCollision->addCollisionObject(btCollision);
	}
}

void CWorld::AddPhysical(CPhysical* pPhysical)
{
	m_pWorldCollision->addRigidBody(pPhysical->GetRigidBody());
}


void CWorld::AddTerrain(CTerrain* pTerrain)
{
	m_pWorldCollision->addRigidBody(pTerrain->GetRigidBody());
}

void CWorld::DoPulse() {
	if (!m_pWorldCollision)return;

	m_pWorldCollision->stepSimulation(1);
	for (auto v : CDummies)
	{
		v->DoPulse();
	}

	btCollisionShape* pCollisionShape;
	btTransform transform;

	//glColor4ub(255,255,255, 255);
	//glLineWidth(20);
	//for (auto v : m_vecCollisions)
	//{
	//	pCollisionShape = v->GetCollisionObject()->getCollisionShape();
	//	transform = v->GetCollisionObject()->getWorldTransform();
	//	if(pCollisionShape)
	//		m_pWorldCollision->debugDrawObject(transform, pCollisionShape, btVector3(10, 255, 10));
	//}

	glColor4ub(0,255,0, 255);
	glLineWidth(0.5);

	btRigidBody* pRigidBody;
	for (auto v : m_vecPhysicals)
	{
		if (v->GetCollision() && v->GetCollision()->GetCollisionObject())
		{
			pRigidBody = v->GetRigidBody();
			pCollisionShape = v->GetCollision()->GetCollisionObject()->getCollisionShape();
			transform = pRigidBody->getWorldTransform();
			if (pCollisionShape)
				m_pWorldCollision->debugDrawObject(transform, pCollisionShape, btVector3(10, 255, 10));
		}
	}

	glColor4ub(255, 0, 0, 255);
	glLineWidth(2);
	for (auto v : m_vecTerrains)
	{
		pCollisionShape = v->GetCollisionObject()->getCollisionShape();
		transform = v->GetCollisionObject()->getWorldTransform();
		if (pCollisionShape)
			m_pWorldCollision->debugDrawObject(transform, pCollisionShape, btVector3(10, 255, 10));
	}

	glm::vec3 from;
	glm::vec3 to;
	pGame->GetCamera()->GetCameraPosition(from);
	pGame->GetCamera()->GetCameraLookAt(to);
	to.x = 0;
	to.y = 0;
	to.z = 0;
	rayResult rayRes = rayTest(btVector3(from.x, from.y, from.z), btVector3(to.x, to.y, to.z));

	glColor4ub(0,255,0, 255);
	glLineWidth(3);
	if (rayRes.hasHit())
	{
		if (rayRes.m_hitPointWorld.size() > 0)
		{
			btVector3 hitPoint = rayRes.m_hitPointWorld.at(0);
			btVector3 hitNormal = rayRes.m_hitNormalWorld.at(0);
			hitNormal *= 50;
			//CRenderer::DrawLine(hitPoint.getX(), hitPoint.getY(), hitPoint.getZ(), hitNormal.getX(), hitNormal.getY(), hitNormal.getZ());

		}
		//printf("result 1 %.2f, %.2f, %.2f\n", hitpoint.getX(), hitpoint.getY(), hitpoint.getZ());

	}
	
	//btVector3 hitpoint = asdf.m_hitPointWorld.at(0);
	//printf("result 1 %.2f, %.2f, %.2f\n", hitpoint.getX(), hitpoint.getY(), hitpoint.getZ());
	//printf("hasHit 1 %s\n", asdf.hasHit() ? "true" : "false");
	//printf("hasHit 2 %s\n", asdf2.hasHit() ? "true" : "false");
};

void CWorld::Do1SecPulse() {
	for (auto v : CDummies)
	{
		v->Do1SecPulse();
	}
};

void CWorld::RegisterDummy(CDummy* pDummy) {
	CDummies.push_back(pDummy);
};

void CWorld::UnregisterDummy(CDummy* pDummy) {
	VECTOR_REMOVE(CDummies, pDummy);
};

void CWorld::RegisterCollision(CCollision* pCollision) {
	m_vecCollisions.push_back(pCollision);
};

void CWorld::UnregisterCollision(CCollision* pCollision) {
	VECTOR_REMOVE(m_vecCollisions, pCollision);
};

void CWorld::RegisterTerrain(CTerrain* pTerrain) {
	m_vecTerrains.push_back(pTerrain);
};

void CWorld::UnregisterTerrain(CTerrain* pTerrain) {
	VECTOR_REMOVE(m_vecTerrains, pTerrain);
};

void CWorld::RegisterPhysical(CPhysical* pPhysical) {
	m_vecPhysicals.push_back(pPhysical);
};

void CWorld::UnregisterPhysical(CPhysical* pPhysical) {
	VECTOR_REMOVE(m_vecPhysicals, pPhysical);
};

rayResult CWorld::rayTest(const btVector3& rayFromWorld, const btVector3& rayToWorld) const{

	rayResult result(rayFromWorld, rayToWorld);
	m_pWorldCollision->rayTest(rayFromWorld, rayToWorld, result);
	return result;
};


void CWorld::InitializeCollisions()
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	m_pWorldCollision = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	m_pWorldCollision->setGravity(btVector3(0, 0, -10));
}

void CWorld::DrawDebug()
{
	if (pGame->GetDebugEnabled(DEBUG_GRID))
	{
		glColor4ub(255, 255, 255, 255);
		int iGridLineCount = 10;
		int iGridSpacing = 50;
		glLineWidth(1);
		for (int x = -iGridLineCount; x <= iGridLineCount; x++)
		{
			glLineWidth(x == 0?10:1);
			glColor4ub(255, x == 0 ? 0 : 255, x == 0 ? 0 : 255, 255);
			CRenderer::DrawLine(x * iGridSpacing, -iGridSpacing * 2 * iGridLineCount, 0.0, x * iGridSpacing, iGridSpacing * 2 * iGridLineCount, 0.0f);
		}
		for (int y = -iGridLineCount; y <= iGridLineCount; y++)
		{
			glLineWidth(y == 0 ? 10 : 1);
			glColor4ub(255, y == 0 ? 0 : 255, y == 0 ? 0 : 255, 255);
			CRenderer::DrawLine(-iGridSpacing * 2 * iGridLineCount, y * iGridSpacing, 0.0f, iGridSpacing * 2 * iGridLineCount, y * iGridSpacing, 0.0f);
		}
	}
	if (pGame->GetDebugEnabled(DEBUG_ENTITY_BOUNDING_BOX))
	{
		glColor4ub(255, 255, 255, 255);
		for (auto it : CEntity::m_pEntities)
		{
			it.second->RenderBoundingBox();
		}
	}
};