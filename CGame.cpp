#include "StdInc.h"

int oldTimeSinceStart = 0;
int iFrames = 0;
int iDeltaTimeSum = 0;
int FPS = 0;

CGame* pGame;
btDiscreteDynamicsWorld* dynamicsWorld;

std::map<uint, CRenderer*> CRenderer::m_mapRenderers;
std::map<uint, CEntity*> CEntity::m_pEntities;

CGame::CGame(int& iResult, std::string strWindowName) {
	pGame = this;
	m_pCamera = new CCamera();
	ConvertableEnum::InitializeEnums();
	m_pRootLua = new CLuaMain("root");

	CRenderer::m_mapRenderers = {};
	m_pMainWindow = new CWindow("Hi", 1024, 768);
	m_pWorld = new CWorld();
	m_pRendererDebug = new CRendererDebug();
	m_pWorld->Initialize();
	m_pTerrainRoot = new CTerrain(100, 100, 25);

	//pGame->SetDebugEnabled(DEBUG_GRID | DEBUG_MESH_BOUNDING_BOX | DEBUG_ENTITY_BOUNDING_BOX);

	CMesh* pMesh = new CMesh();
	CRenderer* pRenderer = new CRenderer(1);
	pRenderer->AddMesh(pMesh);
	uint a = pRenderer->AddVertex(-50, -50, 10,0,0,255,0, -1, -1);
	uint b = pRenderer->AddVertex(-50,50, -10, 0,255,0, 0, -1,1);
	uint c = pRenderer->AddVertex(100,100, 10, 255,0,0, 0, 2,2);
	uint d = pRenderer->AddVertex(50,-50, -10, 0,255,0, 0, 1,-1);
	pMesh->CreateTriangle(a, b, c);
	pMesh->CreateTriangle(a, c, d);

	pMesh->SetTexture("test");
	pRenderer->RecalculateBoundingBox();

	int iEntityID = 0;
	CEntity* ea = new CEntity(1, iEntityID);
	CEntity* eb = new CEntity(1, iEntityID);
	CEntity* ec = new CEntity(1, iEntityID);
	ea->SetPosition(-500, 500, 0);
	eb->SetPosition(500, -500, 0);
	ec->SetPosition(-500, -500, 0);
	ec->SetRotation(45, 21, 30);
	eb->SetRotation(0, 45, 45);

	//HWND consoleWindowHandle = GetConsoleWindow();
	//SetConsoleTitle("test");
	//ShowWindow(consoleWindowHandle, SW_HIDE);
	//ShowWindow(consoleWindowHandle, SW_RESTORE);

	//printf("consoleWindowHandle %x\n", consoleWindowHandle);

	Do1SecPulse();

	while (true)
	{
		
	}
	iResult = EXIT_SUCCESS;
};

CGame::~CGame()
{

};

void CGame::StaticDoPulse()
{
	pGame->Render();
	pGame->DoPulse();
	//CRenderer::StaticRender(1);
	//pGame->DoPulse();
	//printf("do pulse\n");

};

void CGame::Render()
{
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	m_iDeltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	m_uiFPS += 1;
	iDeltaTimeSum += m_iDeltaTime;
	if (iDeltaTimeSum > 1000)
	{
		iDeltaTimeSum = 0;
		Do1SecPulse();
		m_uiFPS = 0;
	}
	iFrames++;

	pGame->GetWorld()->DrawDebug();

	pGame->DoPulse();
}

void CGame::DoPulse()
{
	m_pWorld->DoPulse();
};

void CGame::Do1SecPulse()
{
	char buffer[60];
	sprintf_s(buffer, sizeof(buffer), m_cTitle, m_uiFPS);
	SetConsoleTitle(buffer);

	for (auto v : vecLua)
	{
		v->DoPulse();
	}

	m_pWorld->Do1SecPulse();
};

void CGame::StaticDisplay()
{

};

void CGame::StaticIdle()
{

};

void CGame::EventMouse(int button, int state, int x, int y)
{
	for (auto v : vecLua)
	{
		v->DoMouseEvent(button, state, x, y);
	}
};

void CGame::EventKeyBoard(uchar key, int x, int y)
{
	for (auto v : vecLua)
	{
		v->DoKeyBoardEvent(key, x, y);
	}
};

void CGame::StaticEventMouse(int button, int state, int x, int y)
{
	pGame->EventMouse(button, state, x, y);
}

void CGame::StaticEventKeyBoard(uchar key, int x, int y)
{
	pGame->EventKeyBoard(key, x, y);
};

void CGame::RegisterTexture(SString name, CTexture* pTexture) {
	m_Textures.insert({ name, pTexture });
};

void CGame::UseTexture(SString name) {
	auto search = m_Textures.find(name);
	if (search != m_Textures.end()) {
		CTexture::StaticSelect(search->second);
		return;
	}
	CTexture::StaticSelect(nullptr);
};

void CGame::RegisterLuaMachine(CLuaMain* cLua)
{
	vecLua.push_back(cLua);
};

void CGame::UnregisterLuaMachine(CLuaMain* cLua){
	VECTOR_REMOVE(vecLua, cLua);
};
