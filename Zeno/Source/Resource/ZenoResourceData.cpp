#include <fstream>

#include "Resource/ZenoResourceData.h"

#include "ZenoTemplate.h"
#include "Resource/ZenoResourceManager.h"

/* ------------------------------------------------------------------------- */

int powerOfTwo(int nValue)
{
	int nSize = 1;

	while (nSize < nValue)
	{
		nSize *= 2;
	}
	
	return nSize;
}

/* ------------------------------------------------------------------------- */

GraphicResource::GraphicResource(int nIndex, const char* pFileName)
	:	m_nIndex(nIndex), m_szFileName(pFileName)
{
	std::ifstream checkFile;

	// Open file for reading data
	checkFile.open(m_szFileName.c_str(), std::ifstream::app | std::ifstream::in);

	// Check if file was opened and found
	if (checkFile.is_open() != true || checkFile.good() != true)
	{
		m_szFileName.assign("Resources/Test.png");
	}

	checkFile.close();

	// Set the resource status
	m_bLoaded = false;

	// Negative index not allowed
	if (m_nIndex < 0)
	{
		m_nIndex = 0;
	}

	m_pSurface = NULL;
}

GraphicResource::~GraphicResource()
{

}

void GraphicResource::vLoad()
{
	// Unload if the resource was loaded before
	vClean();

	// Load the resource using the SDL_Image library API
	m_pSurface = IMG_Load(m_szFileName.c_str());

    if (m_pSurface)
    {
		// Create a new surface in the correct format for OpenGL buffer
		SDL_Surface* pNewSurface = NULL;

		// The new texture size should be a power of two number
		int nWidth = powerOfTwo(m_pSurface->w);

		int nHeight = powerOfTwo(m_pSurface->h);
		
		// Create a new surface in format RGBA for OpenGL rendering
		pNewSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, nWidth, nHeight, 32, 
			0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		
		// Copy the new surface in the resource surface
		SDL_BlitSurface(m_pSurface, NULL, pNewSurface, NULL);

		// Release the created surface
		SDL_FreeSurface(pNewSurface);

		// Change the resource status to loaded
		m_bLoaded = true;
    }
}

void GraphicResource::vClean()
{
	// Check if the surface was created
	if (m_pSurface)
    {
		// Release surface data
        SDL_FreeSurface(m_pSurface);

        m_pSurface = NULL;
    }

	// Change the resource status to unloaded
    m_bLoaded = false;
}

bool GraphicResource::vIsLoaded()
{
	// Return the resource status
	return m_bLoaded;
}

int GraphicResource::vGetIndex()
{
	// Return the resource index
	return m_nIndex;
}

ResourceType GraphicResource::vGetType()
{
	// Return the reousrce type
	return RESOURCE_GRAPHIC;
}

const char* GraphicResource::vGetFileName()
{
	// Return the reousorce file path
	return m_szFileName.c_str();
}

SDL_Surface* GraphicResource::getSurface()
{
	// Return the resource surface
	return m_pSurface;
}

/* ------------------------------------------------------------------------- */

FontResource::FontResource(int nIndex, const char* pFileName , int nSize)	
	:	m_nIndex(nIndex), m_nSize(nSize), m_szFileName(pFileName)
{
	std::ifstream checkFile;

	// Open file for reading data
	checkFile.open(m_szFileName.c_str(), std::ifstream::app | std::ifstream::in);

	// Check if file was opened and found
	if (checkFile.is_open() != true || checkFile.good() != true)
	{
		m_szFileName.assign("Resources/Test.ttf");
	}

	checkFile.close();

	// Set the resource status
	m_bLoaded = false;

	// Negative index not allowed
	if (m_nIndex < 0)
	{
		m_nIndex = 0;
	}

	// Smaller font size not allowed
	if (m_nSize < 12)
	{
		m_nSize = 12;
	}

	m_pFont = NULL;
}

FontResource::~FontResource()
{

}

void FontResource::vLoad()
{
	// Unload if the resource was loaded before
	vClean();

	// Load the resource using the SDL_TTF library API
	// Default font size is set to 14px
	m_pFont = TTF_OpenFont(m_szFileName.c_str(), m_nSize);

	// Check the font
    if (m_pFont)
    {
		// Change the resource status to loaded
		m_bLoaded = true;
    }
}

void FontResource::vClean()
{
	// Check if the font was created
	if (m_pFont)
    {
		// Release font data
        TTF_CloseFont(m_pFont);

        m_pFont = NULL;
    }

	// Change the resource status to unloaded
    m_bLoaded = false;
}

bool FontResource::vIsLoaded()
{
	// Return the resource status
	return m_bLoaded;
}

int FontResource::vGetIndex()
{
	// Return the reousrce index
	return m_nIndex;
}

ResourceType FontResource::vGetType()
{
	// Return the reousrce type
	return RESOURCE_FONT;
}

const char* FontResource::vGetFileName()
{
	// Return the reousorce file path
	return m_szFileName.c_str();
}

TTF_Font* FontResource::getFont()
{
	// Return font handle
	return m_pFont;
}

/* ------------------------------------------------------------------------- */
