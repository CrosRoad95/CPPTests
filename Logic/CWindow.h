#pragma once

#include <SFML/Graphics.hpp>

class CWindow
{
public:
	CWindow(const char* strName, uint width, uint heigth);

	sf::RenderWindow* GetWindow() { return m_pWindow; }
	bool IsWindowReady() { return m_pWindow != nullptr; }

	sf::Vector2u GetSize() const { return m_pWindow->getSize(); }
	sf::Vector2i GetPosition() const { return m_pWindow->getPosition(); }
	const char* GetName() const { return m_cName; }
	void CenterMouse();

	void SetWindow(sf::RenderWindow* pWindow){ m_pWindow = pWindow; }
private:
	sf::RenderWindow* m_pWindow;
	const char* m_cName;
};