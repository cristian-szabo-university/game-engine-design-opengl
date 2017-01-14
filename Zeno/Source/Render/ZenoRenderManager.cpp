#include "Render/ZenoRenderManager.h"

RenderManager::~RenderManager()
{
	for (auto iterListener = m_mapListener.begin();
		iterListener != m_mapListener.end();
		iterListener++)
	{
		ZENO_DELETE iterListener->second;
	}

	m_mapListener.clear();

	// Release context
	SDL_GL_DeleteContext(m_pContext);

	// Quit video subsystem
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool RenderManager::vInit()
{
	if (m_bReady)
	{
		return false;
	}

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}

	m_bReady = true;

	return true;
}

int RenderManager::vCreate(int nWndWidth, int nWndHeight, const char* pWndTitle)
{
	SDL_Window* pWindow;

	// Set the window OpenGL context to 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Enable double buffering with 8 bits for alpha channel
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// Turn on x4 multisampling anti-aliasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
 
	// Create the new window at the specific coordinates
	pWindow = SDL_CreateWindow(pWndTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		nWndWidth, nWndHeight, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

	// Check window handle
	if (!pWindow)
	{
        return false;
	}
	
	if (!m_pContext)
	{
		m_pContext = SDL_GL_CreateContext(pWindow);
	}

	// Enable VSync
    SDL_GL_SetSwapInterval(1);

	// Set viewport to the full window size
	glViewport(0, 0, nWndWidth, nWndHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, nWndWidth,
		nWndHeight, 0.0, 
		-1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return SDL_GetWindowID(pWindow);
}

void RenderManager::vAttach(IRenderListener* pListener, int nIndex)
{
	SDL_Window* pWindow = SDL_GetWindowFromID(nIndex);

	if (pWindow)
	{
		m_mapListener.insert(std::make_pair(nIndex, pListener));
	}
}

void RenderManager::vMakeCurrent(int nIndex)
{
	SDL_Window* pWindow = SDL_GetWindowFromID(nIndex);

	if (pWindow)
	{
		// Make current context on window
		SDL_GL_MakeCurrent(pWindow, m_pContext);
	}
}

void RenderManager::vSwapBuffer(int nIndex)
{
	SDL_Window* pWindow = SDL_GetWindowFromID(nIndex);

	if (pWindow)
	{
		// Swap window buffers
		SDL_GL_SwapWindow(pWindow);
	}
}

void RenderManager::vOnEvent(SDL_WindowEvent* pEvent)
{
	auto iterListener = m_mapListener.find(pEvent->windowID);

	if (iterListener != m_mapListener.end())
	{
		switch (pEvent->event)
		{
		case SDL_WINDOWEVENT_CLOSE :
			{			
				iterListener->second->vOnClose();

				vDestroy(pEvent->windowID);

				break;
			}
		case SDL_WINDOWEVENT_RESIZED :
			{
				iterListener->second->vOnResize(pEvent->data1, pEvent->data2);

				break;
			}
		}
	}
}

void RenderManager::vDestroy(int nIndex)
{
	SDL_Window* pWindow = SDL_GetWindowFromID(nIndex);

	if (pWindow)
	{
		// Destroy window
		SDL_DestroyWindow(pWindow);

		auto iterListener = m_mapListener.find(nIndex);

		if (iterListener != m_mapListener.end())
		{
			ZENO_DELETE iterListener->second;

			// Erase the window listener
			m_mapListener.erase(nIndex);
		}
	}
}

int RenderManager::vGetWndNum()
{
	return m_mapListener.size();
}

RenderManager::RenderManager()
{
	m_pContext = NULL;

	m_bReady = false;
}