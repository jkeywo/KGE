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
	KGE::TUID<KGE::Component>::CachedReference xNULL;
	KGE::Component* pxRootObject = KGE::Component::Create(*xDoc.first_node(), xNULL);

	// run game
	if (pxRootObject)
	{
		KGE::eventparams_t xBlankParams;
		pxRootObject->OnActivate(xBlankParams);
		sf::Clock xClock;
		while (pxRootObject->GetState() == KGE::Component::Active)
		{
			KGE::Component::DeleteDestroyed();

			float fDT = xClock.restart().asSeconds();

			KGE::ComponentWindowLayer::HandleInputAll();
			KGE::ComponentUpdater::UpdateAll(fDT);
			KGE::ComponentWindowLayer::RenderAll();
		}
		KGE::Component::DeleteDestroyed();
	}

	return 0;
}