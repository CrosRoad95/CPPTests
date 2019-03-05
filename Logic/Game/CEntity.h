enum EEntityType
{
	ENTITY_TYPE_OBJECT,
};

class CEntity : CDummy
{
public:
	CEntity(uint uiID, int& iFreeID);
	~CEntity();

	EDummyType DummyType() { return EDummyType::DUMMY_TYPE_ENTITY; }

	static void StaticPulseAll();

	void DoPulse();
	void Render();
	void RenderBoundingBox();
	void ApplyPreRenderTransformation();
	void ApplyPostRenderTransformation();
	bool IsVisible();

	void SetPosition(float x, float y, float z) {
		m_pPosition->x = x;
		m_pPosition->y = y;
		m_pPosition->z = z;
	}
	void SetRotation(float x, float y, float z) {
		m_pRotation->x = x;
		m_pRotation->y = y;
		m_pRotation->z = z;
	}

	static std::map<uint, CEntity*> m_pEntities;
private:
	Position3D* m_pPosition = new Position3D(0,0,0);
	Rotation3D* m_pRotation = new Rotation3D(0,0,0);
	uint m_uiID;

	bool m_bVisible = true;
	uchar m_ucAlpha = 255;
	bool m_bStatic = true;

};