#include "KGE.hpp"
#include "Core/Components/Basic/ComponentWindowLayer.hpp"

namespace KGE
{
	unordered_set<ComponentWindowLayer*, ComponentWindowLayer::Hasher> ComponentWindowLayer::s_xAllWindows;

	void ComponentWindowLayer::HandleInputAll()
	{
		FOREACH_R(xIt, s_xAllWindows)
		{
			(*xIt)->HandleInput();
		}
	}
	void ComponentWindowLayer::RenderAll()
	{
		FOREACH(xIt, s_xAllWindows)
		{
			(*xIt)->Render();
		}
	}

	void ComponentWindowLayer::HandleInput()
	{
		sf::Event xEvent;
		while (m_pxWindow && m_pxWindow->pollEvent(xEvent))
		{
			if (parent_t::HandleInput(xEvent, m_pxWindow))
			{
				// handled by game, ignore default events...
			}
			else if (xEvent.type == sf::Event::KeyReleased && xEvent.key.code == sf::Keyboard::F12)
			{
				m_bFullscreen = !m_bFullscreen;
				sf::VideoMode xVideoMode = m_bNativeResolution
					? sf::VideoMode::getDesktopMode()
					: sf::VideoMode(m_iXResolution, m_iYResolution);
				m_pxWindow->create(xVideoMode, "KGE", m_bFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
			}
			else if (xEvent.type == sf::Event::Closed)
			{
				// "close requested" event: we close the window
				m_pxWindow->close();
				eventparams_t xBlankParams;
				if (m_pxParent && m_pxParent->IsComposite())
				{
					m_pxParent->OnEvent(g_xHASH_ONDESTROY, xBlankParams);
				}
				else
				{
					OnEvent(g_xHASH_ONDESTROY, xBlankParams);
				}
			}
		}
	}

	void ComponentWindowLayer::Render()
	{
		if (m_pxWindow)
		{
			m_pxWindow->clear(sf::Color::Black);
			parent_t::Render(*m_pxWindow);
		}
	}

	void ComponentWindowLayer::OnActivate(eventparams_t& xEventParameters)
	{
		Component::OnActivate(xEventParameters); // deliberately skip parent_t
		s_xAllWindows.insert(this);

		sf::VideoMode xVideoMode = m_bNativeResolution 
			? sf::VideoMode::getDesktopMode()
			: sf::VideoMode(m_iXResolution, m_iYResolution);
		m_pxWindow = new sf::RenderWindow(xVideoMode, "KGE", m_bFullscreen ? sf::Style::Fullscreen : sf::Style::Default );
	}
	void ComponentWindowLayer::OnDeactivate(eventparams_t& xEventParameters)
	{
		Component::OnDeactivate(xEventParameters); // deliberately skip parent_t
		s_xAllWindows.erase(this);

		delete m_pxWindow;
		m_pxWindow = NULL;
	}

	void ComponentWindowLayer::ProcessFullscreen(xml_attribute<char>& xFullscreen)
	{
		m_bFullscreen = (strcmp(xFullscreen.value(), "true") == 0) 
					|| (strcmp(xFullscreen.value(), "1") == 0);
	}
	void ComponentWindowLayer::ProcessXResolution(xml_attribute<char>& xX)
	{
		stringstream xStream(xX.value());
		xStream >> m_iXResolution;
		m_bNativeResolution = false;
	}
	void ComponentWindowLayer::ProcessYResolution(xml_attribute<char>& xY)
	{
		stringstream xStream(xY.value());
		xStream >> m_iXResolution;
		m_bNativeResolution = false;
	}

};