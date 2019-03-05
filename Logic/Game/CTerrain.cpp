#include "StdInc.h"

CTerrain::CTerrain(int uiSizeX, int uiSizeY, float fDensity)
{
	btVector3 vertex1, vertex2, vertex3, vertex4;
	btTriangleMesh* triangleMeshTerrain = new btTriangleMesh();
	m_pCollisionObject = new btCollisionObject();

	for (int i = -uiSizeX / 2; i < uiSizeX / 2; i = i + fDensity) {
		for (int j = -uiSizeY / 2; j < uiSizeY / 2; j = j + fDensity) {

			vertex1 = btVector3(i, j, 0.0f);
			vertex2 = btVector3(i + fDensity, j, 0.0f);
			vertex3 = btVector3(i + fDensity, j + fDensity, 0.0f);
			vertex4 = btVector3(i, j + fDensity, 0.0f);

			vertex1.setZ(vertex1.length() / 3);
			vertex2.setZ(vertex2.length() / 3);
			vertex3.setZ(vertex3.length() / 3);
			vertex4.setZ(vertex4.length() / 3);
			triangleMeshTerrain->addTriangle(vertex1, vertex2, vertex3);
			triangleMeshTerrain->addTriangle(vertex1, vertex3, vertex4);
		}
	}

	btCollisionShape* collisionShapeTerrain = new btBvhTriangleMeshShape(triangleMeshTerrain, true);

	m_pCollisionObject->setCollisionShape(collisionShapeTerrain);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, 0, collisionShapeTerrain, btVector3(0,0,0));
	m_pRigidBody = new btRigidBody(rbInfo);
	m_pRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	m_pRigidBody->setRestitution(0.2f);
	m_pRigidBody->setFriction(btScalar(0.9));
	m_pCollisionObject->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	//pGame->GetWorld()->GetWorldCollision()->addCollisionObject(rigidBodyTerrain);
	pGame->GetWorld()->AddTerrain(this);
	pGame->GetWorld()->RegisterTerrain(this);
};

