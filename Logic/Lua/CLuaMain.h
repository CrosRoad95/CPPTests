#pragma once

#define LUA_FUNCTION(name) static int name(lua_State* luaVM);

class CLuaMain
{
public:
	CLuaMain(const char* cName);
	~CLuaMain();

	void LoadCode(const char* cName);

	bool SetGlobal(const char* cName, const char* value);
	bool SetGlobal(const char* cName, lua_Number value);

	bool GetGlobal(const char* cName, const char* &value);
	bool GetGlobal(const char* cName, lua_Number &value);

	void RegisterFunctions();

	void StartClass(const char* cName);
	void EndClass();
	void RegisterFunction(const char* cName, int(*cb)(lua_State* L));

	void DoPulse();

	void DoKeyBoardEvent(uchar key, int x, int y);
	void DoMouseEvent(int button, int state, int x, int y);
private:
	const char* m_cName;
	const char* m_cClassName = "";
	lua_State* luaVM;
};