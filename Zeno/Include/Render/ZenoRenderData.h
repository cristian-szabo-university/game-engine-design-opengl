#pragma once

#include "ZenoInterface.h"

/* ------------------------------------------------------------------------- */

class GraphicObject : public IRenderTarget
{
public:
	GraphicObject();

	virtual ~GraphicObject();

	virtual bool vSetup(IResource* pResource);

	virtual void vRender(int nPosX, int nPosY);

	virtual void vClean();

	virtual int vGetWidth();

	virtual int vGetHeight();

protected:
	GLuint m_nTextureIndex;

    int m_nWidth;

	int m_nHeight;

};

/* ------------------------------------------------------------------------- */

class StringObject : public IRenderTarget
{
public:
	StringObject();

	virtual ~StringObject();

	virtual bool vSetup(IResource* pResource);

	virtual void vRender(int nPosX, int nPosY);

	virtual void vClean();

	void setText(const char* pText);

	virtual int vGetWidth();

	virtual int vGetHeight();

	const char* getText();

protected:
	std::string m_szText;

	GLuint m_nTextureIndex;

    int m_nWidth;

	int m_nHeight;

};

class RenderListener : public IRenderListener
{
public:
	RenderListener();

	virtual ~RenderListener();

	virtual void vOnClose();

	virtual void vOnResize(int nWidth, int nHegiht);

	virtual IRenderManager* vGetContext();

	virtual IGameOptions* vGetOption();

private:
	friend class RenderManager;

	friend class GameManager;

	IRenderManager* m_pContext;

	IGameOptions* m_pOptions;

};

/* ------------------------------------------------------------------------- */
