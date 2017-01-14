#include "ZenoInterface.h"

MemoryTracker* MemoryTracker::getInst()
{
	static MemoryTracker memoryTracker;

	return &memoryTracker;
}

MemoryTracker::~MemoryTracker()
{
	std::ofstream fileDump;

	fileDump.open("MemoryLeaks.txt", std::ios::app | std::ios::out);

	if (m_mapData.size() == 0)
	{
		fileDump << "No memory leaks detected !" << std::endl;
	}
	else
	{
		fileDump << "Detected memory leaks ! " << __TIMESTAMP__ << std::endl;
		fileDump << "Status: (" << m_mapData.size() << ") allocation(s) with total " << m_nTotalMemAlloc << " bytes." << std::endl;
		fileDump << "Dumping allocations --->" << std::endl;

		for (auto iterData = m_mapData.begin();
			iterData != m_mapData.end();
			iterData++)
		{
			fileDump << iterData->second.szFileName << " (" << iterData->second.nLineNum << ") : { " << iterData->second.nSize << " bytes } in function " << iterData->second.szFuncName << std::endl;
		}
	}

	fileDump.close();
}

void MemoryTracker::record(void* ptr, MemoryData data)
{
	m_nTotalMemAlloc += data.nSize;

	m_mapData.insert(std::make_pair(ptr, data));
}

void MemoryTracker::release(void* ptr)
{
	auto iterData = m_mapData.find(ptr);

	if (iterData != m_mapData.end())
	{
		m_nTotalMemAlloc -= iterData->second.nSize;

		m_mapData.erase(iterData);
	}	
}

MemoryTracker::MemoryTracker()
{
	m_nTotalMemAlloc = 0;
}

MemoryObject::~MemoryObject()
{

}

void* MemoryObject::operator new(size_t nSize, const char* pFileName, int nLineNum, const char* pFuncName)
{
	void* pPtr = malloc(nSize);

	MemoryData data;

	data.nLineNum = nLineNum;

	data.nSize = nSize;

	data.szFileName = pFileName;

	data.szFuncName = pFuncName;

	MemoryTracker::getInst()->record(pPtr, data);

	return pPtr;
}

void MemoryObject::operator delete(void* pPtr, const char* pFileName, int nLineNum, const char* pFuncName)
{
	MemoryTracker::getInst()->release(pPtr);

	free(pPtr);
}

void MemoryObject::operator delete(void* pPtr)
{
	MemoryTracker::getInst()->release(pPtr);

	free(pPtr);
}

IGameOptions::~IGameOptions()
{

}

IGameManager::~IGameManager()
{

}

IResourceManager::~IResourceManager()
{

}

IResource::~IResource()
{

}

IRenderManager::~IRenderManager()
{

}

IRenderListener::~IRenderListener()
{

}

IRenderTarget::~IRenderTarget()
{

}

ISceneManager::~ISceneManager()
{

}

ISceneListener::~ISceneListener()
{

}

ISceneLayer::~ISceneLayer()
{

}

IEntity::~IEntity()
{

}

IEntityCategory::~IEntityCategory()
{

}

IEntityComponent::~IEntityComponent()
{

}

IEntityFactory::~IEntityFactory()
{

}
