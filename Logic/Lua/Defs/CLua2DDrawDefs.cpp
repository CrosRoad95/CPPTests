#include "StdInc.h"

void CLua2DDrawDefs::RegisterFunctions(const char* pName, CLuaMain* pLua)
{
	pLua->StartClass(pName);
	pLua->RegisterFunction("createVertex", CreateVertex);
	pLua->RegisterFunction("setVertexPosition", SetVertexPosition);
	pLua->RegisterFunction("getVertexPosition", GetVertexPosition);
	pLua->RegisterFunction("setVertexColor", SetVertexColor);
	pLua->RegisterFunction("getVertexColor", GetVertexColor);
	pLua->RegisterFunction("createTriangle", CreateTriangle);
	pLua->EndClass();
};

int CLua2DDrawDefs::CreateVertex(lua_State* luaVM)
{
	CScriptArgReader argStream(luaVM);
	int iPos[2];
	char cColor[4];
	float u, v;
	argStream.ReadNumber(iPos[0]);
	argStream.ReadNumber(iPos[1]);
	argStream.ReadNumber(cColor[0], 255);
	argStream.ReadNumber(cColor[1], 255);
	argStream.ReadNumber(cColor[2], 255);
	argStream.ReadNumber(cColor[3], 255);
	argStream.ReadNumber(u, iPos[0]/100);
	argStream.ReadNumber(v, iPos[1]/100);
	if (!argStream.HasErrors())
	{
		ColorRGBA* pColor = new ColorRGBA(cColor[0], cColor[1], cColor[2]);
		Vertex2DUVColor* pVertex = new Vertex2DUVColor(iPos[0], iPos[1], u, v, pColor);
		lua_pushlightuserdata(luaVM, pVertex);
		return 1;
	}
	lua_pushboolean(luaVM, false);
	return 1;
};

int CLua2DDrawDefs::GetVertexPosition(lua_State* luaVM)
{
	CScriptArgReader argStream(luaVM);
	Vertex2DUVColor* pVertex;
	argStream.ReadUserData(pVertex);
	if (!argStream.HasErrors())
	{
		lua_pushnumber(luaVM, pVertex->x);
		lua_pushnumber(luaVM, pVertex->y);
		return 2;
	}
	lua_pushboolean(luaVM, false);
	return 1;
};

int CLua2DDrawDefs::SetVertexPosition(lua_State* luaVM)
{
	CScriptArgReader argStream(luaVM);
	Vertex2DUVColor* pVertex;
	int x, y;
	argStream.ReadUserData(pVertex);
	argStream.ReadNumber(x);
	argStream.ReadNumber(y);
	if (!argStream.HasErrors() && pVertex)
	{
		pVertex->x = x;
		pVertex->y = y;
		lua_pushboolean(luaVM, true);
		return 1;
	}
	lua_pushboolean(luaVM, false);
	return 1;
};

int CLua2DDrawDefs::GetVertexColor(lua_State* luaVM)
{
	CScriptArgReader argStream(luaVM);
	Vertex2DUVColor* pVertex;
	argStream.ReadUserData(pVertex);
	if (!argStream.HasErrors())
	{
		lua_pushnumber(luaVM, pVertex->color->r);
		lua_pushnumber(luaVM, pVertex->color->g);
		lua_pushnumber(luaVM, pVertex->color->b);
		lua_pushnumber(luaVM, pVertex->color->a);
		return 4;
	}
	lua_pushboolean(luaVM, false);
	return 1;
};

int CLua2DDrawDefs::SetVertexColor(lua_State* luaVM)
{
	CScriptArgReader argStream(luaVM);
	Vertex2DUVColor* pVertex;
	char r, g, b, a;
	argStream.ReadUserData(pVertex);
	argStream.ReadNumber(r);
	argStream.ReadNumber(g);
	argStream.ReadNumber(b);
	argStream.ReadNumber(a, 255);
	if (!argStream.HasErrors() && pVertex)
	{
		pVertex->color->r = r;
		pVertex->color->g = g;
		pVertex->color->b = b;
		pVertex->color->a = a;
		lua_pushboolean(luaVM, true);
		return 1;
	}
	lua_pushboolean(luaVM, false);
	return 1;
};

int CLua2DDrawDefs::CreateTriangle(lua_State* luaVM)
{
	CScriptArgReader argStream(luaVM);
	Vertex2DUVColor* pVertex[3];
	SString strTextureName;
	argStream.ReadUserData(pVertex[0]);
	argStream.ReadUserData(pVertex[1]);
	argStream.ReadUserData(pVertex[2]);
	argStream.ReadString(strTextureName, "");
	if (!argStream.HasErrors())
	{
		//CTriangle* pTriangle = new CTriangle(pVertex[0], pVertex[1], pVertex[2], strTextureName);
		//lua_pushlightuserdata(luaVM, pVertex);
		return 1;
	}
	lua_pushboolean(luaVM, false);
	return 1;
};