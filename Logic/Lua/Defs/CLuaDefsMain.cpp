#include "StdInc.h"

void CLuaDefsMain::RegisterFunctions(const char* pName, CLuaMain* pLua)
{
	pLua->StartClass(pName);
	pLua->RegisterFunction("getAll", GetAll);
};

int CLuaDefsMain::GetAll(lua_State* luaVM)
{
	CScriptArgReader argStream(luaVM);
	SString strType;
	argStream.ReadString(strType);

	lua_pushstring(luaVM, strType);
	return 1;
};