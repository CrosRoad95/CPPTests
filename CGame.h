#pragma once

enum EDebug
{
	DEBUG_GRID = 1 << 0,
	DEBUG_MESH_BOUNDING_BOX = 1 << 1,
	DEBUG_ENTITY_BOUNDING_BOX = 1 << 2,
};

class CGame {
public:

	CGame(int& iResult, std::string strWindowName);
	~CGame();

	void RegisterLuaMachine(CLuaMain* pDummy);
	void UnregisterLuaMachine(CLuaMain* pDummy);

	void RegisterTexture(SString name, CTexture* pTexture);
	void UseTexture(SString name);

	void EventMouse(int button, int state, int x, int y);
	void EventKeyBoard(uchar key, int x, int y);

	static void StaticDoPulse();

	static void StaticDisplay();
	static void StaticIdle();

	static void StaticEventKeyBoard(uchar key, int x, int y);
	static void StaticEventMouse(int button, int state, int x, int y);

	ColorRGBA* gColor;

	static const int screenX = 800;
	static const int screenY = 600;

	std::map<SString, ConvertableEnum*> mEnums;

	void SetDebugEnabled(uint uiDebug) { m_uiDebug = uiDebug; }
	bool GetDebugEnabled(EDebug eDebug) { return m_uiDebug & eDebug; }

	CCamera* GetCamera() const { return m_pCamera; }
	CWindow* GetWindow() const { return m_pMainWindow; }
	CWorld* GetWorld() const { return m_pWorld; }
	CRendererDebug* GetRendererDebug() const { return m_pRendererDebug; }

	void SetElapsedTime(float& fElapsedTime) { m_fElapsedTime = fElapsedTime; }
	float GetElapsedTime() const { return m_fElapsedTime; }
	uint GetFrameLimit() const { return m_uiFrameLimit; }
private:
	void DoPulse();
	void Do1SecPulse();

	void Render();

	std::vector<CLuaMain*>		  vecLua;
	std::map<SString, CTexture*>  m_Textures;

private:

	uint m_uiDebug = 0;

	uint m_uiFPS;
	float m_fElapsedTime;
	int m_iDeltaTime;
	const char* m_cTitle = "FPS: %i";
	uint m_uiFrameLimit = 60;
	CLuaMain* m_pRootLua;
	CWindow* m_pMainWindow;
	CCamera* m_pCamera;
	CWorld* m_pWorld;
	CTerrain* m_pTerrainRoot;
	CRendererDebug* m_pRendererDebug;

	//btDiscreteDynamicsWorld* m_pCollisions;
};
