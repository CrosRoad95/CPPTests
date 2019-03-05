#include "StdInc.h"


CCollision::CCollision(uint uiID) :
	m_uiID(uiID)
{
	m_pCollisionObject = new btCollisionObject();
	pGame->GetWorld()->RegisterCollision(this);
};

CCollision::~CCollision()
{

};

void CCollision::Set(btCollisionShape* pShape)
{
	GetCollisionObject()->setCollisionShape(pShape);
};

void CCollision::SetRotation(const btVector3 vecRotation)
{
	btTransform& pTransform = GetCollisionObject()->getWorldTransform();
	btQuaternion quaterion;
	quaterion.setRotation(vecRotation, 1);
	pTransform.setRotation(quaterion);
	GetCollisionObject()->setWorldTransform(pTransform);
};

void CCollision::SetPosition(const btVector3 vecPosition)
{
	btTransform& pTransform = GetCollisionObject()->getWorldTransform();
	pTransform.setOrigin(vecPosition);
	GetCollisionObject()->setWorldTransform(pTransform);
};

CPhysical::CPhysical(CCollision* pCollision)
{
	btCollisionObject* btCollision = pCollision->GetCollisionObject();
	m_pCollision = pCollision;
	btCollisionShape* pColShape = btCollision->getCollisionShape();
	if (pColShape)
	{
		btScalar mass = 10;
		btVector3 localInertia;
		pColShape->calculateLocalInertia(mass, localInertia);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, 0, pColShape, localInertia);
		rbInfo.m_startWorldTransform.setOrigin(btVector3(-8, 1, 20));
		m_pRigidBody = new btRigidBody(rbInfo);
		m_pRigidBody->setCollisionFlags(m_pRigidBody->getCollisionFlags() & (btCollisionObject::CF_STATIC_OBJECT | btCollisionObject::CF_KINEMATIC_OBJECT));

		pGame->GetWorld()->AddPhysical(this);
		pGame->GetWorld()->RegisterPhysical(this);
	}
}

void CPhysical::SetRotation(const btVector3 vecRotation)
{
	btTransform& pTransform = m_pRigidBody->getWorldTransform();
	btQuaternion quaterion;
	quaterion.setRotation(vecRotation, 1);
	pTransform.setRotation(quaterion);
	m_pRigidBody->setWorldTransform(pTransform);
};

void CPhysical::SetPosition(const btVector3 vecPosition)
{
	btTransform& pTransform = m_pRigidBody->getWorldTransform();
	pTransform.setOrigin(vecPosition);
	m_pRigidBody->setWorldTransform(pTransform);
};