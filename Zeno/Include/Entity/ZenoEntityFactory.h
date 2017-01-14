#pragma once

#include "ZenoInterface.h"

#include "ZenoEntityData.h"

class EntityFactory : public IEntityFactory
{
public:
	EntityFactory();

	virtual ~EntityFactory();

	virtual bool vLoad(const char* pFileName);

	virtual void vRegister(const char* pCategory, CreateFunc pFunc);

	virtual IEntityComponent* vFind(const char* pCategory, const char* pComponent);

	virtual IEntity* vCreate(tinyxml2::XMLElement* pElement);

private:
	std::map<IEntityCategory*, std::vector<IEntityComponent*>> m_mapEntityComp;

	std::map<IEntityCategory*, CreateFunc> m_mapEntityFunc;

};
