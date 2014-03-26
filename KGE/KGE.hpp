#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <math.h>

// STL
#include <algorithm>
#include <functional>
#include <cmath>

#include <list>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <iterator>

#include <iostream>
#include <fstream>
#include <sstream>

#include <cerrno>
#include <cassert>

using namespace std;
using namespace std::tr1;

// SFML - http://www.sfml-dev.org/index.php
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

// Box2D - http://box2d.org/
#include <Box2D/Box2D.h>

// Lua
#include <lua/lua.hpp>
#include <lua/lauxlib.h>
#include <lua/lualib.h>

// Boost - http://www.boost.org/
#define BOOST_NO_MEMBER_TEMPLATE_FRIENDS
#include "boost/multi_index/ordered_index.hpp"
#include "boost/multi_index/hashed_index.hpp"
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include "boost/multi_index/sequenced_index.hpp"
#include "Boost/tuple/tuple.hpp"
#include "Boost/any.hpp"
#include "Boost/bind.hpp"
#include "Boost/function.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/multi_index_container.hpp"
#include "Boost/ref.hpp"
#include "Boost/signals2.hpp"
using namespace boost;
using namespace boost::multi_index;

// RadpiXML
#include "rapidxml/rapidxml.hpp"
using namespace rapidxml;

// typedefs
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef short s16;
typedef char s8;

// helper macros
#define FOREACH( iterator, collection ) for( auto iterator(collection.begin()); iterator != collection.end(); iterator++ )
#define FOREACH_R( iterator, collection ) for( auto iterator(collection.rbegin()); iterator != collection.rend(); iterator++ )

#define COMBINE2(a, b) a##b
#define COMBINE(a, b) COMBINE2(a,b)

#define STATIC_INITIALISE_START			private: static struct StaticInitialise { StaticInitialise()
#define STATIC_INITIALISE_END			} s_xStaticInitialise;
#define STATIC_INITIALISE_RUN( TParentClass )	TParentClass::StaticInitialise TParentClass::s_xStaticInitialise;

// Core classes
#include "Core/Data/Hash.hpp"
#include "Core/Data/TUID.hpp"
#include "Core/Data/Data.hpp"
