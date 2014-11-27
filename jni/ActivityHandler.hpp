#ifndef _PACKT_EVENTHANDLER_HPP_
#define _PACKT_EVENTHANDLER_HPP_

#include "Types.hpp"

namespace packt {
    class EventHandler {
    public :
    	virtual status onActivate() = 0;
    	virtual void onDeactivate() = 0;
    	virtual status onStep() = 0;

    	virtual void onStart() {};
    	virtual void onResume() {};
    	virtual void onPause() {};
    	virtual void onStop() {};
    	virtual void onDestroy() {};

    	virtual void onSaveState(void** pData,
    			uint32_t* pSize) {};
    	virtual void onConfigurationChanged() {};
    	virtual void onLowMemory() {};

    	virtual void onCreateWindow() {};
    	virtual void onDestroyWindow() {};
    	virtual void onGainFocus() {};
    	virtual void onLostFocus() {};
    };
}
#endif
