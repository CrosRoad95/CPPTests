class CCollision
{
public:
	CCollision(uint uiID);
	~CCollision();

	void Set(btCollisionShape* pShape);

	btCollisionObject* GetCollisionObject() const { return m_pCollisionObject; }
	void SetRotation(const btVector3 vecRotation);
	void SetPosition(const btVector3 vecPosition);

private:
	uint m_uiID;
	btCollisionObject* m_pCollisionObject;
};

class CPhysical
{
public:
	CPhysical(CCollision* pCollision);
	btRigidBody* GetRigidBody() { return m_pRigidBody; }
	CCollision* GetCollision() { return m_pCollision; }
	void SetRotation(const btVector3 vecRotation);
	void SetPosition(const btVector3 vecPosition);

private:
	CCollision* m_pCollision;
	btRigidBody* m_pRigidBody;
};