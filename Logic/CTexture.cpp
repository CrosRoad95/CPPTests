#include "StdInc.h"

CTexture::CTexture(SString path, SString name)
{
	glEnable(GL_TEXTURE_2D);
	Load(path);
	m_strName = name;
	pGame->RegisterTexture(name, this);
}

void CTexture::Load(const SString& path)
{
	sf::Image image;
	if (!image.loadFromFile(path))
		return;

	glGenTextures(1, &m_textureID);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D, 0);
}

CTexture::~CTexture()
{
}

void CTexture::StaticSelect(CTexture* pTexture)
{
	pTexture->Select();
}

void CTexture::Select()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void CTexture::InitializeDefault()
{
	CTexture* pTexture = new CTexture("image.png", "test");
	CTexture* pTexture2 = new CTexture("image2.png", "test2");
}
