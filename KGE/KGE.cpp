#include "KGE.hpp"

#include "Core/Components/Component.hpp"
#include "Core/Components/Basic/ComponentWindowLayer.hpp"
#include "Core/Components/Basic/ComponentUpdater.hpp"

int main()
{
	// read in game definition
	std::ifstream xFileSteam;
	xFileSteam.open("test.xml");

	char szXMLbuffer[64 * 1024];
	memset(szXMLbuffer, '\0', 64 * 1024);
	xFileSteam.read(szXMLbuffer, 64 * 1024);

	xml_document<> xDoc;    // character type defaults to char
	xDoc.parse<0>(szXMLbuffer);

	// create game from XML
	bool bFullscreen = false;
	sf::Vector2i xWindowedSize(800, 600);
	KGE::Component* pxRootObject = KGE::Component::Create(*xDoc.first_node(), NULL);
	sf::RenderWindow xWindow(sf::VideoMode(xWindowedSize.x, xWindowedSize.y), "KGL (c)2014");

	// run game
	if (pxRootObject)
	{
		KGE::eventparams_t xBlankParams;
		pxRootObject->OnActivate(xBlankParams);
		sf::Clock xClock;
		while (pxRootObject->GetState() != KGE::Component::Destroyed)
		{
			float fDT = xClock.restart().asSeconds();

			KGE::ComponentWindowLayer::HandleInputAll();
			KGE::ComponentUpdater::UpdateAll(fDT);
			KGE::ComponentWindowLayer::RenderAll();

			KGE::Component::DeleteDestroyed();
		}
		pxRootObject->OnDeactivate(xBlankParams);
	}

	return 0;
}