#include "../CTexture.h"

class CMesh;
struct Vector3D;

struct CMeshVertex
{
	CMeshVertex(float x, float y, float z, uchar r = 255, uchar g = 255, uchar b = 255,
		uchar a = 255, float u = 0, float v = 0) : x(x), y(y), z(z), r(r), g(g), b(b), a(a), u(u), v(v) {
	};
	float x,y,z;
	uchar r,g,b,a;
	float u,v;
};

struct CMeshTriangle
{
	CMeshTriangle(uint v1, uint v2, uint v3) : 
		vertex1(v1), vertex2(v2), vertex3(v3) {
	};
	uint vertex1;
	uint vertex2;
	uint vertex3;
};

class CRenderer
{
public:
	CRenderer(uint id);
	~CRenderer();

	bool Render();
	bool AddMesh(CMesh* pMesh);

	static bool StaticRender(uint uiID);
	static bool StaticRenderBoundingBox(uint uiID);
	static CRenderer* GetByID(uint uiID);

	static std::map<uint, CRenderer*> m_mapRenderers;

	uint CreateTriangle(uint v1, uint v2, uint v3);

	uint AddVertex(CMeshVertex* pVertex);
	uint AddVertex(float x, float y, float z, uchar r = 255, uchar g = 255, uchar b = 255, uchar a = 255, float u = 0, float v = 0);

	CMeshVertex* GetVertexByID(uint);
	CMeshTriangle* GetTriangleByID(uint);
	void RenderBoundingBox();
	void RecalculateBoundingBox();
	static inline void DrawLine(float x1, float y1, float z1, float x2, float y2, float z2);
private:
	bool m_bHasChanged = false;

	uint m_uiID;
	std::vector<CMesh*> m_vecMeshes;
	std::vector<CMeshVertex*> m_vecMeshVertices;
	std::vector<CMeshTriangle*> m_vecMeshTriangles;

	Vector3D* vecBBoxMin;
	Vector3D* vecBBoxMax;
};

class CMesh
{
public:
	CMesh();
	~CMesh();
	void SetRenderer(CRenderer* pRenderer);
	void Draw();
	int CreateTriangle(uint v1, uint v2, uint v3);
	void SetTexture(SString strTexture) { m_strTexture = strTexture; }

private:
	std::vector<uint> m_vecMeshTriangles;
	CRenderer* m_pParentRenderer;
	SString m_strTexture;
};

class CRendererDebug : public btIDebugDraw
{
public:
	CRendererDebug();

	void drawLine(const btVector3 &, const btVector3 &, const btVector3 &);
	void drawContactPoint(const btVector3 &, const btVector3 &, btScalar, int, const btVector3 &) {};
	void reportErrorWarning(const char *) {};
	void draw3dText(const btVector3 &, const char *) {};
	void setDebugMode(int) {};
	int getDebugMode(void) const { return 1; };
};