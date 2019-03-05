#include "StdInc.h"

float clip(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}

void CCamera::DoPulse()
{
	if (!pGame->GetWindow()->IsWindowReady())
		return;

	float fElapsedTime = pGame->GetElapsedTime();
	float shiftSpeedFactor, fMul;

	sf::Vector2i vecMouseOffset = sf::Mouse::getPosition() - pGame->GetWindow()->GetPosition() - static_cast<sf::Vector2i>(pGame->GetWindow()->GetSize())/2;

	pGame->GetWindow()->CenterMouse();
	switch(m_eCameraMode)
	{
	case CAMERA_MODE_ROTATING:
		SetCameraLookAt(0, 0, 0);
		SetCameraPosition(sin(fElapsedTime / 2000.0f) * 70.0f, cos(fElapsedTime / 2000.0f) * 70.0f, 75);
		break;
	case CAMERA_MODE_FREECAM:
		shiftSpeedFactor = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 80.0f : 20.0f;
		fMul = 1.0f * (shiftSpeedFactor / pGame->GetFrameLimit());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_pCameraPosition += GetViewDirection() * fMul;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_pCameraPosition -= GetViewDirection() * fMul;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_pCameraPosition -= glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::eulerAngleXZ(XRotation, ZRotation)) * fMul;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_pCameraPosition += glm::vec3(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) * glm::eulerAngleXZ(XRotation, ZRotation)) * fMul;
		}
		XRotation += (vecMouseOffset.y / 200.0f);
		ZRotation += (vecMouseOffset.x / 200.0f);
		XRotation = clip(XRotation, 0.01f, PI);
		m_pCameraLookAt = m_pCameraPosition + GetViewDirection();
		break;
	default:
		SetCameraPosition(sin(5) * 70.0f, cos(5) * 70.0f, 75);
		break;
	}
	gluLookAt(m_pCameraPosition.x, m_pCameraPosition.y, m_pCameraPosition.z, m_pCameraLookAt.x, m_pCameraLookAt.y, m_pCameraLookAt.z, 0, 0, 1);
}

glm::mat4 CCamera::GetViewMatrix()
{
	return glm::eulerAngleXZ(XRotation, ZRotation) * glm::translate(m_pCameraPosition);
}

void CCamera::ResizedWindow(int windowWidth, int windowHeight)
{
	aspectRatio = ((float)windowWidth) / ((float)windowHeight);
}

glm::mat4 CCamera::GetProjectionMatrix()
{
	return glm::perspective(
		FieldOfView,
		aspectRatio,
		0.1f,  //near clipping plane
		1000.0f //far clipping plane
	);
}
glm::mat4 CCamera::GetTransformMatrix()
{
	return GetProjectionMatrix() * GetViewMatrix();
}

glm::vec3 CCamera::GetViewDirection()
{
	return glm::vec3(glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) * glm::eulerAngleXZ(XRotation, ZRotation));
}