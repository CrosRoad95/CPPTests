class CLua2DDrawDefs
{
public:
	static void RegisterFunctions(const char* pName, CLuaMain* luaVM);
	LUA_FUNCTION(CreateVertex);
	LUA_FUNCTION(GetVertexPosition);
	LUA_FUNCTION(SetVertexPosition);
	LUA_FUNCTION(GetVertexColor);
	LUA_FUNCTION(SetVertexColor);
	LUA_FUNCTION(CreateTriangle);
};