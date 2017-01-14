#include "Entity/ZenoEntityFactory.h"

#include "ZenoTemplate.h"
#include "Resource/ZenoResourceManager.h"

EntityFactory::EntityFactory()
{

}

EntityFactory::~EntityFactory()
{
	for (auto iterCategory = m_mapEntityComp.begin();
		iterCategory != m_mapEntityComp.end();
		iterCategory++)
	{
		ZENO_DELETE iterCategory->first;

		for (auto iterComp = iterCategory->second.begin();
			iterComp != iterCategory->second.end();
			iterComp++)
		{
			ZENO_DELETE (*iterComp);
		}

		iterCategory->second.clear();
	}

	m_mapEntityComp.clear();
}

bool EntityFactory::vLoad(const char* pFileName)
{
	std::string szFileName(pFileName);

	if (szFileName.empty() || !szFileName.find(".xml"))
	{
		return false;
	}

	tinyxml2::XMLDocument pDocument;

	if (pDocument.LoadFile(szFileName.c_str()) == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		return false;
	}

	tinyxml2::XMLElement* pRoot = pDocument.FirstChildElement("Categories");

	if (!pRoot)
	{
		return false;
	}

	for (tinyxml2::XMLNode* pNode = pRoot->FirstChild();
		pNode;
		pNode = pNode->NextSibling())
	{
		tinyxml2::XMLElement* pElement = pNode->ToElement();

		if (_stricmp(pElement->Name(), "Category") != NULL)
		{
			continue;
		}

		const char* pName = pElement->Attribute("Name");

		const char* pType = pElement->Attribute("Type");

		int nResourceIndex = pElement->IntAttribute("ResourceIndex");

		if (!pName || !pType)
		{
			continue;
		}

		IEntityCategory* pCategory = ZENO_NEW EntityCategory(pName, pType, nResourceIndex);

		std::vector<IEntityComponent*> vecEntityComponent;

		for (tinyxml2::XMLNode* pNode2 = pElement->FirstChild();
			pNode2;
			pNode2 = pNode2->NextSibling())
		{
			tinyxml2::XMLElement* pElemNode = pNode2->ToElement();

			const char* pKey = pElemNode->Attribute("Key");

			int pValue = pElemNode->IntAttribute("Value");

			if (!pKey)
			{
				continue;
			}

			IEntityComponent* pComponent = ZENO_NEW EntityComponent(pKey, pValue);

			vecEntityComponent.push_back(pComponent);
			
		}

		m_mapEntityComp.insert(std::make_pair(pCategory, vecEntityComponent));
	}

	return true;
}

void EntityFactory::vRegister(const char* pType, CreateFunc pFunc)
{
	for (auto iterCategory = m_mapEntityComp.begin();
		iterCategory != m_mapEntityComp.end();
		iterCategory++)
	{
		if (_stricmp(iterCategory->first->vGetType(), pType) == NULL)
		{
			m_mapEntityFunc.insert(std::make_pair(iterCategory->first, pFunc));
		}
	}
}

IEntity* EntityFactory::vCreate(tinyxml2::XMLElement* pElement)
{
	const char* pName = pElement->Attribute("Name");

	int nPosX = pElement->IntAttribute("PosX");

	int nPosY = pElement->IntAttribute("PosY");

	const char* pCategory = pElement->Attribute("Category");

	if (!pName || !pCategory)
	{
		return NULL;
	}

	IRenderTarget* pObject;

	for (auto iterCategory = m_mapEntityFunc.begin();
		iterCategory != m_mapEntityFunc.end();
		iterCategory++)
	{
		if (_stricmp(iterCategory->first->vGetName(), pCategory) == NULL)
		{
			pObject = (iterCategory->second)(pElement);
			
			IResource* pResource = Global<ResourceManager>::getInst()->vFind(iterCategory->first->vGetResourceIndex());

			if (pObject->vSetup(pResource) != true)
			{
				return NULL;
			}

			break;
		}
	}

	if (!pObject)
	{
		return NULL;
	}

	for (auto iterCategory = m_mapEntityComp.begin();
		iterCategory != m_mapEntityComp.end();
		iterCategory++)
	{
		if (_stricmp(iterCategory->first->vGetName(), pCategory) == NULL)
		{
			Entity* pEntity = ZENO_NEW Entity(pObject, pCategory);

			for (auto iterComp = iterCategory->second.begin();
				iterComp != iterCategory->second.end();
				iterComp++)
			{
				pEntity->setComponent(ZENO_NEW EntityComponent((*iterComp)->vGetName(), (*iterComp)->vGet()));
			}

			pEntity->setName(pName);

			pEntity->setPosition(nPosX, nPosY);

			return pEntity;
		}
	}

	return NULL;
}

IEntityComponent* EntityFactory::vFind(const char* pCategory, const char* pComponent)
{
	for (auto iterCategory = m_mapEntityComp.begin();
		iterCategory != m_mapEntityComp.end();
		iterCategory++)
	{
		if (_stricmp(iterCategory->first->vGetName(), pCategory) == NULL)
		{
			for (auto iterComponent = iterCategory->second.begin();
				iterComponent != iterCategory->second.end();
				iterComponent++)
			{
				if (_stricmp((*iterComponent)->vGetName(), pComponent) == NULL)
				{
					return (*iterComponent);
				}
			}
		}
	}

	return NULL;
}
