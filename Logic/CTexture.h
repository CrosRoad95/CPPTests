#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "lua/SString.h"

class CTexture {
public:
	CTexture(SString path, SString name);
	~CTexture();
	static void InitializeDefault();
	static void StaticSelect(CTexture*);
	void Select();
	void Load(const SString& path);
private:
	SString m_strFilePath;
	SString m_strName;
	uint m_uiWidth, m_uiHeigth;
	GLuint m_textureID;
};
