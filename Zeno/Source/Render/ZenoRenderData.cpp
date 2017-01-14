#include "Render/ZenoRenderData.h"

#include "Resource/ZenoResourceData.h"

/* ------------------------------------------------------------------------- */

GraphicObject::GraphicObject()
{
	m_nWidth = 32;
    
	m_nHeight = 32;

	m_nTextureIndex = 0;
}

GraphicObject::~GraphicObject()
{
	
}

bool GraphicObject::vSetup(IResource* pResource)
{
	// Check if resource is not null
	if (!pResource)
	{
		return false;
	}

	// Check if the resource is loaded
	if (!pResource->vIsLoaded())
	{
		return false;
	}

	GraphicResource* pCastResource = dynamic_cast<GraphicResource*>(pResource);

	// Check the casting status
	if (pCastResource)
	{
		m_nWidth = pCastResource->getSurface()->w;
    
		m_nHeight = pCastResource->getSurface()->h;
	
		// Generate a new OpenGL texture index
		glGenTextures(1, &m_nTextureIndex);
		glBindTexture(GL_TEXTURE_2D, m_nTextureIndex); 

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Create the new texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, pCastResource->getSurface()->pixels);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}

	return true;
}

void GraphicObject::vRender(int nPosX, int nPosY)
{
	// Draw texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_nTextureIndex);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
		// First corner
		glTexCoord2d(0, 0);
		glVertex3f((float)nPosX, (float)nPosY, 0.0f);

		// Second corner
		glTexCoord2d(0, 1);
		glVertex3f((float)nPosX, (float)nPosY + (float)m_nHeight, 0.0f);

		// Third corner
		glTexCoord2d(1, 1);
		glVertex3f((float)nPosX + (float)m_nWidth, (float)nPosY + (float)m_nHeight, 0.0f);

		// Fourth corner
		glTexCoord2d(1, 0);
		glVertex3f((float)nPosX + (float)m_nWidth, (float)nPosY, 0.0f);
    glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void GraphicObject::vClean()
{
	glDeleteTextures(1, &m_nTextureIndex);

	m_nTextureIndex = 0;
}

int GraphicObject::vGetWidth()
{
	// Return the object width
	return m_nWidth;
}

int GraphicObject::vGetHeight()
{
	// Return the object height
	return m_nHeight;
}

/* ------------------------------------------------------------------------- */

StringObject::StringObject()
{
	m_szText.assign("Unknown");

	m_nWidth = 128;
    
	m_nHeight = 16;

	m_nTextureIndex = 0;
}

StringObject::~StringObject()
{
	
}

bool StringObject::vSetup(IResource* pResource)
{
	// Check if resource is not null
	if (!pResource)
	{
		return false;
	}

	// Check if the resource is loaded
	if (!pResource->vIsLoaded())
	{
		return false;
	}

	FontResource* pCastResource = dynamic_cast<FontResource*>(pResource);

	SDL_Surface* pSurface = NULL;

	if (pCastResource)
	{
		SDL_Color sColor = {0, 0, 0};

		pSurface = TTF_RenderText_Blended(pCastResource->getFont(), m_szText.c_str(), sColor);
	}

	// Check the casting status
	if (pSurface)
	{
		m_nWidth = pSurface->w;
    
		m_nHeight = pSurface->h;
	
		// Generate a new OpenGL texture index
		glGenTextures(1, &m_nTextureIndex);
		glBindTexture(GL_TEXTURE_2D, m_nTextureIndex); 

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Create the new texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, pSurface->pixels);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		SDL_FreeSurface(pSurface);
	}

	return true;
}

void StringObject::vRender(int nPosX, int nPosY)
{
	// Draw texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_nTextureIndex);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
		// First corner
		glTexCoord2d(0, 0);
		glVertex3f((float)nPosX, (float)nPosY, 0.0f);

		// Second corner
		glTexCoord2d(0, 1);
		glVertex3f((float)nPosX, (float)nPosY + (float)m_nHeight, 0.0f);

		// Third corner
		glTexCoord2d(1, 1);
		glVertex3f((float)nPosX + (float)m_nWidth, (float)nPosY + (float)m_nHeight, 0.0f);

		// Fourth corner
		glTexCoord2d(1, 0);
		glVertex3f((float)nPosX + (float)m_nWidth, (float)nPosY, 0.0f);
    glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void StringObject::vClean()
{
	glDeleteTextures(1, &m_nTextureIndex);

	m_nTextureIndex = 0;
}

void StringObject::setText(const char* pText)
{
	if (pText)
	{
		m_szText.assign(pText);
	}
}

int StringObject::vGetWidth()
{
	// Return the object width
	return m_nWidth;
}

int StringObject::vGetHeight()
{
	// Return the object height
	return m_nHeight;
}

const char* StringObject::getText()
{
	return m_szText.c_str();
}

/* ------------------------------------------------------------------------- */

RenderListener::RenderListener()
{
	
}

RenderListener::~RenderListener()
{

}

void RenderListener::vOnClose()
{

}

void RenderListener::vOnResize(int nWidth, int nHegiht)
{

}

IRenderManager* RenderListener::vGetContext()
{
	return m_pContext;
}

IGameOptions* RenderListener::vGetOption()
{
	return m_pOptions;
}

/* ------------------------------------------------------------------------- */
