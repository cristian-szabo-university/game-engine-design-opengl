#pragma once

#include "ZenoInterface.h"

class Entity : public IEntity
{
public:
	Entity(IRenderTarget* pObject, const char* pCategory);

	virtual ~Entity();

	virtual void vUpdate();

	virtual void vRender();

	virtual tinyxml2::XMLElement* vToXML(tinyxml2::XMLDocument* pDoc);

	void setComponent(IEntityComponent* pComponent);

	void setName(const char* pName);

	void setPosition(int nPosX, int nPosY);

	void setDirection(int nDirX, int nDirY);

	virtual int vGetWidth();

	virtual int vGetHeight();

	virtual int vGetPosX();

	virtual int vGetPosY();

	virtual const char* vGetName();

	virtual const char* vGetCategory();

	virtual IEntityComponent* vGetComponent(const char* pName);

private:
	std::string m_szName;

	std::string m_szCategory;

	IRenderTarget* m_pObject;

	std::vector<IEntityComponent*> m_vecComponent;

	int m_nPosX;

	int m_nPosY;

};

class EntityComponent : public IEntityComponent
{
public:
	EntityComponent(const char* pName, int nValue);

	virtual ~EntityComponent();

	virtual const char* vGetName();

	virtual int vGet();

	virtual void vSet(int nValue);

	virtual void vChange(int nValue);

private:
	std::string m_szName;

	int m_nValue;

};

class EntityCategory : public IEntityCategory
{
public:
	EntityCategory(const char* pName, const char* pType, int nResourceIndex);

	virtual ~EntityCategory();

	virtual const char* vGetName();

	virtual const char* vGetType();

	virtual int vGetResourceIndex();

private:
	std::string m_szName;

	std::string m_szType;

	int m_nResourceIndex;

};
