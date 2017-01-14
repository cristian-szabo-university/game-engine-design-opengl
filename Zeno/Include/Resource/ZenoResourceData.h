#pragma once

#include "ZenoInterface.h"

/* ------------------------------------------------------------------------- */

class FontResource : public IResource
{
public:
	FontResource(int nIndex, const char* pFileName, int nSize);

	virtual ~FontResource();

	virtual void vLoad();

	virtual void vClean();

	virtual bool vIsLoaded();

	virtual int vGetIndex();

	virtual ResourceType vGetType();

	virtual const char* vGetFileName();

	TTF_Font* getFont();

protected:
	TTF_Font* m_pFont;

	int m_nIndex;

	int m_nSize;
        
	std::string m_szFileName;
        
	bool m_bLoaded;

};

/* ------------------------------------------------------------------------- */

class GraphicResource : public IResource
{
public:
	GraphicResource(int nIndex, const char* pFileName);

	virtual ~GraphicResource();

	virtual void vLoad();

	virtual void vClean();

	virtual bool vIsLoaded();

	virtual int vGetIndex();

	virtual ResourceType vGetType();

	virtual const char* vGetFileName();

	SDL_Surface* getSurface();

protected:
	SDL_Surface* m_pSurface;

	int m_nIndex;
        
	std::string m_szFileName;
        
	bool m_bLoaded;

};

/* ------------------------------------------------------------------------- */
