#include "Entity/ZenoEntityData.h"

#include "Render/ZenoRenderData.h"

Entity::Entity(IRenderTarget* pObject, const char* pCategory)
{
	m_szName.assign("Unknown");

	if (pCategory)
	{
		m_szCategory.assign(pCategory);
	}
	else
	{
		m_szCategory.assign("Unknown");
	}

	m_nPosX = 0;

	m_nPosY = 0;

	m_pObject = pObject;
}

Entity::~Entity()
{
	for (auto iterComp = m_vecComponent.begin();
		iterComp != m_vecComponent.end();
		iterComp++)
	{
		ZENO_DELETE (*iterComp);
	}

	m_vecComponent.clear();

	m_pObject->vClean();

	ZENO_DELETE m_pObject;
}

void Entity::vUpdate()
{
	
}

void Entity::vRender()
{
	m_pObject->vRender(m_nPosX, m_nPosY);
}

tinyxml2::XMLElement* Entity::vToXML(tinyxml2::XMLDocument* pDoc)
{
	tinyxml2::XMLElement* pElem = pDoc->NewElement("Object");

	pElem->SetAttribute("Name", m_szName.c_str());

	pElem->SetAttribute("PosX", m_nPosX);

	pElem->SetAttribute("PosY", m_nPosY);

	StringObject* pCastObject = dynamic_cast<StringObject*>(m_pObject);

	if (pCastObject)
	{
		pElem->SetAttribute("Text", pCastObject->getText());
	}

	pElem->SetAttribute("Category", m_szCategory.c_str());

	return pElem;
}

void Entity::setComponent(IEntityComponent* pComponent)
{
	m_vecComponent.push_back(pComponent);
}

void Entity::setName(const char* pName)
{
	if (pName)
	{
		m_szName.assign(pName);
	}
}

void Entity::setPosition(int nPosX, int nPosY)
{
	m_nPosX = nPosX;

	m_nPosY = nPosY;
}

void Entity::setDirection(int nDirX, int nDirY)
{
	m_nPosX += nDirX;

	m_nPosY += nDirY;
}

int Entity::vGetWidth()
{
	return m_pObject->vGetWidth();
}

int Entity::vGetHeight()
{
	return m_pObject->vGetHeight();
}

int Entity::vGetPosX()
{
	return m_nPosX;
}

int Entity::vGetPosY()
{
	return m_nPosY;
}

const char* Entity::vGetName()
{
	return m_szName.c_str();
}

const char* Entity::vGetCategory()
{
	return m_szCategory.c_str();
}

IEntityComponent* Entity::vGetComponent(const char* pName)
{
	for (auto iterComp = m_vecComponent.begin();
		iterComp != m_vecComponent.end();
		iterComp++)
	{
		if (_stricmp((*iterComp)->vGetName(), pName) == NULL)
		{
			return (*iterComp);
		}
	}

	return NULL;
}

EntityComponent::EntityComponent(const char* pName, int nValue)
{
	if (pName)
	{
		m_szName.assign(pName);
	}
	else
	{
		m_szName.assign("Unknown");
	}

	m_nValue = nValue;
}

EntityComponent::~EntityComponent()
{

}

const char* EntityComponent::vGetName()
{
	return m_szName.c_str();
}

int EntityComponent::vGet()
{
	return m_nValue;
}

void EntityComponent::vSet(int nValue)
{
	m_nValue = nValue;
}

void EntityComponent::vChange(int nValue)
{
	m_nValue += nValue;
}

EntityCategory::EntityCategory(const char* pName, const char* pType, int nResourceIndex)
{
	if (pName)
	{
		m_szName.assign(pName);
	}
	else
	{
		m_szName.assign("Unknown");
	}

	if (pType)
	{
		m_szType.assign(pType);
	}
	else
	{
		m_szType.assign("Unknown");
	}

	m_nResourceIndex = nResourceIndex;
}

EntityCategory::~EntityCategory()
{

}

const char* EntityCategory::vGetName()
{
	return m_szName.c_str();
}

const char* EntityCategory::vGetType()
{
	return m_szType.c_str();
}

int EntityCategory::vGetResourceIndex()
{
	return m_nResourceIndex;
}
