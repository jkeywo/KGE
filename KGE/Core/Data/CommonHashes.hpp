#pragma once

namespace KGE
{
	// event parameter names
	const Hash g_xHASH_SOURCE("Source");	// component that called the event

	// events
	const Hash g_xHASH_ONCREATE("OnCreate");
	const Hash g_xHASH_ONACTIVATE("OnActivate");
	const Hash g_xHASH_ONDEACTIVATE("OnDeactivate");
	const Hash g_xHASH_ONDESTROY("OnDestroy");

	const Hash g_xHASH_ONUPDATE("OnUpdate");
	const Hash g_xHASH_ONRENDER("OnRender");
	const Hash g_xHASH_ONHANDLEINPUT("OnHandleInput");

}
