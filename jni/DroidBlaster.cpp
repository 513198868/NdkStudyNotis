#include "DroidBlaster.hpp"
#include "Log.hpp"

#include <unistd.h>

namespace dbs {
    DroidBlaster::DroidBlaster() {
    	packt::Log::info("Ceateing DroidBlaster");
    }

    DroidBlaster::~DroidBlaster() {
    	packt::Log::info("Destructing DroidBlaster");
    }

    status DroidBlaster::onActivate() {
    	packt::Log::info("Activating DroidBlaster");
    	return STATUS_OK;
    }

    void DroidBlaster::onDeactivate() {
    	packt::Log::info("Deactivating DroidBlaster");
    }

    status DroidBlaster::onStep() {
    	packt::Log::info("Starting step");
    	usleep(300000);
    	packt::Log::info("Stepping done");
    	return STATUS_OK;
    }

    void DroidBlaster::onStart() {
    	packt::Log::info("onStart");
    }

    void DroidBlaster::onResume() {
    	packt::Log::info("onResume");
    }

    void DroidBlaster::onPause() {
       	packt::Log::info("onPause");
       }

    void DroidBlaster::onStop() {
       	packt::Log::info("onStop");
       }

    void DroidBlaster::onDestroy() {
       	packt::Log::info("onDestroy");
       }

    void DroidBlaster::onConfigurationChanged() {
       	packt::Log::info("onConfigurationChanged");
       }

    void DroidBlaster::onLowMemory() {
           	packt::Log::info("onLowMemory");
           }

    void DroidBlaster::onCreateWindow() {
           	packt::Log::info("onCreateWindow");
           }

    void DroidBlaster::onDestroyWindow() {
           	packt::Log::info("onDestroyWindow");
           }

    void DroidBlaster::onGainFocus() {
           	packt::Log::info("onGainFocus");
           }
}
