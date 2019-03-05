class CTerrain
{
public:
	CTerrain(int uiSizeX, int uiSizeY, float fDensity);
	~CTerrain();

	btCollisionObject* GetCollisionObject() const { return m_pCollisionObject; }
	btRigidBody* GetRigidBody() const { return m_pRigidBody; }

private:

	btCollisionObject * m_pCollisionObject;
	btRigidBody * m_pRigidBody;
};
