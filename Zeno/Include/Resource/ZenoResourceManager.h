#pragma once

#include "ZenoInterface.h"

#include "ZenoResourceData.h"

class ResourceManager : public IResourceManager
{
public:
	virtual ~ResourceManager();

	virtual bool vInit();

	virtual bool vLoad(const char* pFileName);

	virtual IResource* vFind(int nIndex);

private:
	template<class T> friend class Global;

	std::vector<IResource*> m_vecResource;

	bool m_bReady;

	ResourceManager();

};
