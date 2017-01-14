#include "Resource/ZenoResourceManager.h"

#include "TinyXML2/TinyXML2.h"

ResourceManager::~ResourceManager()
{
	for (auto iterResource = m_vecResource.begin();
		iterResource != m_vecResource.end();
		iterResource++)
	{
		(*iterResource)->vClean();

		ZENO_DELETE (*iterResource);
	}

	m_vecResource.clear();

	IMG_Quit();

	TTF_Quit();
}

bool ResourceManager::vInit()
{
	if (m_bReady)
	{
		return false;
	}

	// Prepare flags for SDL_Image library.
	int nFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

	// Initialize SDL_Image library for reading .jpg, .png and .tif files
	int nResult = IMG_Init(nFlags);

	// Check if process succeeded or failed
	if((nResult & nFlags) != nFlags) 
	{
		return false;
	}

	// Initialize SDL_ttf library
	if (TTF_Init() < 0)
	{
		return false;
	}

	m_bReady = true;

	return true;
}

bool ResourceManager::vLoad(const char* pFileName)
{
	std::string szFileName(pFileName);

	if (szFileName.empty() || !szFileName.find(".xml"))
	{
		return false;
	}

	// Create an xml document wrapper pointer to store the data
	tinyxml2::XMLDocument pDocument;

	// Try to open the .xml file
	pDocument.LoadFile(szFileName.c_str());

	// Check if file was loaded in document successfully
	if (pDocument.ErrorID() == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		return false;
	}

	// Get the root element fo the document
	tinyxml2::XMLElement* pRoot = pDocument.FirstChildElement("Resources");

	// Check if it was found
	if (!pRoot)
	{
		return false;
	}

	// Loop through all resources
	for (tinyxml2::XMLNode* pNode = pRoot->FirstChild();
		pNode;
		pNode = pNode->NextSibling())
	{
		// Convert the xml node to xml element
		tinyxml2::XMLElement* pElement = pNode->ToElement();

		IResource* pResource;

		// Check element name
		if (_stricmp(pElement->Name(), "Graphic") == NULL)
		{
			// Find the resource index attribute
			int nIndex = pElement->IntAttribute("Index");

			// Find the resource file path attribute
			const char* pFileName = pElement->Attribute("File");

			// Check if all required atributes are found 
			if (!nIndex || !pFileName)
			{
				continue;
			}

			// Create the graphical resource with the information 
			// gathered from element information
			pResource = ZENO_NEW GraphicResource(nIndex, pFileName);		
		}
		// Check if resource is part of font category
		else if (_stricmp(pElement->Name(), "Font") == NULL)
		{
			// Find the resource index attribute
			int nIndex = pElement->IntAttribute("Index");

			// Find the resource file path attribute
			const char* pFileName = pElement->Attribute("File");

			// Fint the resource size attribute
			int nSize = pElement->IntAttribute("Size");

			// Check if all required atributes are found 
			if (!nIndex || !pFileName || !nSize)
			{
				continue;
			}

			// Create the font resource with the information 
			// gathered from element information
			pResource = ZENO_NEW FontResource(nIndex, pFileName, nSize);	
		}
		else
		{
			continue;
		}

		m_vecResource.push_back(pResource);
	}

	// Loop through resources
	for(auto iterResource = m_vecResource.begin();
		iterResource != m_vecResource.end();
		iterResource++)
	{
		// Load resource in memory
		(*iterResource)->vLoad();
	}

	return true;
}

IResource* ResourceManager::vFind(int nIndex)
{
	// Loop through resources
	for(auto iterResource = m_vecResource.begin();
		iterResource != m_vecResource.end();
		iterResource++)
	{
		// Check if resource index exists
		if ((*iterResource)->vGetIndex() == nIndex)
		{
			return (*iterResource);
		}
	}

	return NULL;
}

ResourceManager::ResourceManager()
{
	m_bReady = false;
}
