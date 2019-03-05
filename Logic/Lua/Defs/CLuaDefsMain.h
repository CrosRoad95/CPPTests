class CLuaDefsMain
{
public:
	static void RegisterFunctions(const char* pName, CLuaMain* luaVM);
	LUA_FUNCTION(GetAll);
};