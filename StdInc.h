#pragma message("Compiling precompiled header.\n")

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

class CTexture;
class CCamera;
class CWindow;
class CDummy;
class CLuaMain;
class ConvertableEnum;
class SString;
class CCollision;
class CWorld;
class CTerrain;
class CMesh;
class CPhysical;
class CRendererDebug;
struct ColorRGBA;
struct EEntityPreset;
struct Vector3D;

#include <cstdio>
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <sstream>
#include <thread>

#include "btBulletDynamicsCommon.h"

#include "BulletDynamics/MLCPSolvers/btDantzigSolver.h"
#include "BulletDynamics/MLCPSolvers/btLemkeSolver.h"
#include "BulletDynamics/MLCPSolvers/btSolveProjectedGaussSeidel.h"

#include "BulletDynamics/Featherstone/btMultiBody.h"
#include "BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h"
#include "BulletDynamics/Featherstone/btMultiBodyMLCPConstraintSolver.h"
#include "BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h"
#include "BulletDynamics/Featherstone/btMultiBodyLinkCollider.h"
#include "BulletDynamics/Featherstone/btMultiBodyLink.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.h"
#include "BulletDynamics/Featherstone/btMultiBodyJointMotor.h"
#include "BulletDynamics/Featherstone/btMultiBodyPoint2Point.h"
#include "BulletDynamics/Featherstone/btMultiBodyFixedConstraint.h"
#include "BulletDynamics/Featherstone/btMultiBodySliderConstraint.h"
#include "BulletCollision/Gimpact/btTriangleShapeEx.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"

#define VECTOR_REMOVE(vec,val) vec.erase(std::remove(vec.begin(), vec.end(), val), vec.end());
#define GLM_ENABLE_EXPERIMENTAL
#define PI 3.14159f

extern "C" {
#include "vendor/lua/lua.h"
#include "vendor/lua/lauxlib.h"
#include "vendor/lua/lualib.h"
}

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include <GLEW/include/GL/glew.h>

#include <SFML/Graphics.hpp>

#include <glut.h>

#include "Logic/CStructs.h"

#include "Main.h"
#include "CGame.h"

extern CGame* pGame;

#include "Logic/Lua/SString.h"
#include "Logic/Lua/CScriptArgReader.h"
#include "Logic/Lua/extra/StringToEnumToString.h"

#include "Logic/CDummy.h"
#include "Logic/C2DDraw.h"
#include "Logic/Lua/CLuaMain.h"
#include "Logic/CTexture.h"
#include "Logic/CWindow.h"
#include "Logic/CWorld.h"
#include "Logic/Game/CTerrain.h"
#include "Logic/Game/CRenderer.h"
#include "Logic/Game/CEntity.h"
#include "Logic/Game/CCamera.h"
#include "Logic/Game/CCollision.h"

#include "Logic/C2DDraw/CRectangle.h"
#include "Logic/Lua/Defs/CLuaDefsMain.h"
#include "Logic/Lua/Defs/CLua2DDrawDefs.h"
