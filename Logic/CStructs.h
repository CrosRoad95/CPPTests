#include<iostream>
#include<math.h>
#include<assert.h>

#define MAP_FIND_FIRST_FREE_KEY(VAR, MAP) \
int VAR = 1; \
	for (auto it = MAP.cbegin(), end = MAP.cend(); \
it != end && VAR == it->first; ++it, ++VAR) \
{}

struct ColorRGB {
	ColorRGB() {};
	ColorRGB(uchar cR, uchar cG, uchar cB)
	{
		r = cR / 255;
		g = cG / 255;
		b = cB / 255;
	};

	uchar r;
	uchar g;
	uchar b;
};

struct ColorRGBA : ColorRGB {
	ColorRGBA() {};
	ColorRGBA(uchar cR, uchar cG, uchar cB, uchar cA = 255)
	{
		r = cR;
		g = cG;
		b = cB;
		a = cA;
	};

	uchar a;
};

struct Vertex2D {
	Vertex2D() {};
	Vertex2D(float fX, float fY) : x(fX), y(fY) {};
	float x;
	float y;
};

struct Vertex2DColor : Vertex2D {
	Vertex2DColor() {};
	Vertex2DColor(float fX, float fY, ColorRGBA* cColor)
	{
		x = fX;
		y = fY;
		color = cColor;
	};
	ColorRGBA* color = new ColorRGBA(255, 255, 255, 255);
};

struct Vertex2DUVColor : Vertex2DColor {
	Vertex2DUVColor() {};
	Vertex2DUVColor(float fX, float fY, float fU, float fV, ColorRGBA* cColor)
	{
		x = fX;
		y = fY;
		u = fU;
		v = fV;
		color = cColor;
	};
	ColorRGBA* color = new ColorRGBA(255, 255, 255, 255);
	float u, v;
};

using namespace std;
struct Vector3D
{
	float x, y, z;
	Vector3D(){
		x = 0;
		y = 0;
		z = 0;
	};

	Vector3D(float x1, float y1, float z1 = 0){
		x = x1;
		y = y1;
		z = z1;
	};

	Vector3D(const Vector3D &vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
	};

	Vector3D operator+(const Vector3D &vec){
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	};

	Vector3D &operator+=(const Vector3D &vec){
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	};

	Vector3D operator-(const Vector3D &vec) {
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	};

	Vector3D &operator-=(const Vector3D &vec){
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	};

	Vector3D operator*(float value){
		return Vector3D(x*value, y*value, z*value);
	};

	Vector3D &operator*=(float value){
		x *= value;
		y *= value;
		z *= value;
		return *this;
	};

	//scalar division
	Vector3D operator/(float value){
		assert(value != 0);
		return Vector3D(x / value, y / value, z / value);
	};

	Vector3D &operator/=(float value){
		assert(value != 0);
		x /= value;
		y /= value;
		z /= value;
		return *this;
	};

	Vector3D &operator=(const Vector3D &vec){
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	float dotProduct(const Vector3D &vec){
		return x * vec.x + vec.y*y + vec.z*z;
	};

	Vector3D crossProduct(const Vector3D &vec){
		float ni = y * vec.z - z * vec.y;
		float nj = z * vec.x - x * vec.z;
		float nk = x * vec.y - y * vec.x;
		return Vector3D(ni, nj, nk);
	};

	float magnitude(){
		return sqrt(square());
	};

	float square(){
		return x * x + y * y + z * z;
	}

	Vector3D normalize() {
		*this /= magnitude();
		return *this;
	}

	float distance(const Vector3D &vec) {
		Vector3D dist = *this - vec;
		return dist.magnitude();
	};

	float GetX() { return x; };
	float GetY() { return y; };
	float GetZ() { return z; };

	void Reset(){
		x = 0;
		y = 0;
		z = 0;
	};
};

typedef Vector3D Position3D;
typedef Vector3D Rotation3D;
typedef Vector3D Vertex3D;