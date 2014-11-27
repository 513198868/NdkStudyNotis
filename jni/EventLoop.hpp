#ifndef _PACKT_EVENTLOOP_HPP_
#define _PACKT_EVENTLOOP_HPP_

#include "ActivityHandler.hpp"
#include "Types.hpp"

#include <android_native_app_glue.h>

namespace packt {
    class EventLoop{
    public:
    	EventLoop(android_app* pApplication);

    	void run(EventHandler& pEventHandler);

    protected:
    	void activate();
    	void deactivate();

    	void processActivityEvent(int32_t pCommand);

    private:
    	static void activityCallback(android_app* pApplication,
    			int32_t pCommand);

    private:
    	bool mEnabled; bool mQuit;
    	EventHandler* mActivityHandler;
    	android_app* mApplication;
    };
}
#endif
