#pragma once

enum ECameraMode
{
	CAMERA_MODE_ROTATING,
	CAMERA_MODE_POINTED,
	CAMERA_MODE_FREECAM,
};


class CCamera
{
public:
	CCamera() :
		NEAR_PLANE(0.1f), FAR_PLANE(200.0f),
		Position(0.0f, 0.0f, 0.0f),
		mouseFocus(false),
		XRotation(0), ZRotation(0)
	{
		SetCameraPosition(sin(5) * 70.0f, cos(5) * 70.0f, 75);
		SetCameraLookAt(0, 0, 0);
		SetCameraMode(CAMERA_MODE_FREECAM);
	}

	~CCamera()
	{
	}

	void DoPulse();

	void GetCameraPosition(glm::vec3& position) const { position = m_pCameraPosition; }
	void GetCameraLookAt(glm::vec3& position) const { position = m_pCameraLookAt; }

	void SetCameraPosition(glm::vec3& pPosition) { m_pCameraPosition = pPosition; }
	void SetCameraLookAt(glm::vec3& pPosition) { m_pCameraLookAt = pPosition; }

	void SetCameraPosition(float x, float y, float z)
	{
		m_pCameraPosition.x = x;
		m_pCameraPosition.y = y;
		m_pCameraPosition.z = z;
	}
	void SetCameraLookAt(float x, float y, float z)
	{
		m_pCameraLookAt.x = x;
		m_pCameraLookAt.y = y;
		m_pCameraLookAt.z = z;
	}

	void SetCameraMatrix(float px, float py, float pz, float lx, float ly, float lz)
	{
		m_pCameraPosition.x = lx;
		m_pCameraPosition.y = ly;
		m_pCameraPosition.z = lz;
		m_pCameraLookAt.x = lx;
		m_pCameraLookAt.y = ly;
		m_pCameraLookAt.z = lz;
	}

	void MoveCameraPosition(float x, float y, float z) {
		m_pCameraPosition.x += x;
		m_pCameraPosition.y += y;
		m_pCameraPosition.z += z;
	}
	void MoveCameraLookAt(float x, float y, float z) {
		m_pCameraLookAt.x += x;
		m_pCameraLookAt.y += y;
		m_pCameraLookAt.z += z;
	}

	void MoveCameraPosition(Vector3D& vecMove) {
		m_pCameraPosition.x += vecMove.x;
		m_pCameraPosition.y += vecMove.y;
		m_pCameraPosition.z += vecMove.z;
	}

	void MoveCameraLookAt(Vector3D& vecMove) {
		m_pCameraLookAt.x += vecMove.x;
		m_pCameraLookAt.y += vecMove.y;
		m_pCameraLookAt.z += vecMove.z;
	}
	void SetCameraMode(ECameraMode eCameraMode) { m_eCameraMode = eCameraMode; }

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetTransformMatrix();
	glm::vec3 GetViewDirection();
	glm::vec3 Position;
	float XRotation;
	float ZRotation;
	float FieldOfView;
	void ResizedWindow(int windowWidth, int windowHeight);
	const float NEAR_PLANE;
	const float FAR_PLANE;
private:
	ECameraMode m_eCameraMode;
	glm::vec3 m_pCameraPosition;
	glm::vec3 m_pCameraLookAt;
	float aspectRatio;
	bool mouseFocus;
};
