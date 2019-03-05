#include "StdInc.h"

CLuaMain::CLuaMain(const char* cName) : m_cName(cName)
{
	luaVM = luaL_newstate();
	luaL_openlibs(luaVM);
	pGame->RegisterLuaMachine(this);
	RegisterFunctions();
	luaL_dofile(luaVM, "init.lua");
};

CLuaMain::~CLuaMain()
{
	pGame->RegisterLuaMachine(this);
};

// Called once per second
void CLuaMain::DoPulse()
{

};

void CLuaMain::DoMouseEvent(int button, int state, int x, int y)
{
	CLuaArguments Arguments;
	Arguments.PushNumber(button);
	Arguments.PushNumber(state);
	Arguments.PushNumber(x);
	Arguments.PushNumber(y);
	Arguments.Call(luaVM, "onMouseClick");
};

void CLuaMain::DoKeyBoardEvent(uchar key, int x, int y)
{

	CLuaArguments Arguments;
	Arguments.PushNumber(key);
	Arguments.PushNumber(x);
	Arguments.PushNumber(y);
	Arguments.Call(luaVM, "onKeyBoard");
};

void CLuaMain::RegisterFunctions()
{
	CLuaDefsMain::RegisterFunctions("Main", this);
	CLua2DDrawDefs::RegisterFunctions("Draw2D", this);
};

void CLuaMain::RegisterFunction(const char* cName, int(*cb)(lua_State* L))
{
	lua_pushstring(luaVM, cName);
	lua_pushcfunction(luaVM, cb);
	lua_rawset(luaVM, -3);
};

void CLuaMain::StartClass(const char* cName)
{
	lua_newtable(luaVM);
	m_cClassName = cName;
};

void CLuaMain::EndClass()
{
	lua_setglobal(luaVM, m_cClassName);
	m_cClassName = nullptr;
};
void CLuaMain::LoadCode(const char* cName)
{
	luaL_dostring(luaVM, cName);
};

bool CLuaMain::SetGlobal(const char* cName, const char* value)
{
	lua_pushstring(luaVM, value);
	lua_setglobal(luaVM, cName);
	return true;
};

bool CLuaMain::SetGlobal(const char* cName, lua_Number value)
{
	lua_pushnumber(luaVM, value);
	lua_setglobal(luaVM, cName);
	return true;
};

bool CLuaMain::GetGlobal(const char* cName, const char* &value)
{
	lua_getglobal(luaVM, cName);
	value = lua_tostring(luaVM, 1);
	return true;
};

bool CLuaMain::GetGlobal(const char* cName, lua_Number &value)
{
	lua_getglobal(luaVM, cName);
	value = lua_tonumber(luaVM, 1);
	return true;
};
