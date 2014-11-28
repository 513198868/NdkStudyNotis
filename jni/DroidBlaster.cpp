#include "DroidBlaster.hpp"
#include "Log.hpp"

#include <unistd.h>

namespace dbs {
    DroidBlaster::DroidBlaster(packt::Context& pContext,
    		android_app* pApplication):
    		mApplication(pApplication),
    		mTimeService(pContext.mTimeService),
    		mInitialized(false),
    		mPosX(0),mPosY(0),mSize(24),mSpeed(100.0f){
    	packt::Log::info("Ceateing DroidBlaster");
    }

    DroidBlaster::~DroidBlaster() {
    	packt::Log::info("Destructing DroidBlaster");
    }

    status DroidBlaster::onActivate() {
    	packt::Log::info("Activating DroidBlaster");

    	mTimeService->reset();

    	ANativeWindow* lWindow = mApplication->window;
    	if(ANativeWindow_setBuffersGeometry(lWindow,0,0,
    			WINDOW_FORMAT_RGBX_8888) < 0){
    		return STATUS_KO;
    	}
    	if(ANativeWindow_lock
    			(lWindow,&mWindowBuffer,NULL) >= 0) {
    		ANativeWindow_unlockAndPost(lWindow);
    	}else {
    		return STATUS_KO;
    	}
    	if(!mInitialized) {
    		mPosX = mWindowBuffer.width / 2;
    		mPosY = mWindowBuffer.height /2;
    		mInitialized = true;
    	}
    	return STATUS_OK;
    }

    void DroidBlaster::onDeactivate() {
    	packt::Log::info("Deactivating DroidBlaster");
    }

    status DroidBlaster::onStep() {
    	mTimeService->update();
    	mPosX = fmod(mPosX + mSpeed * mTimeService->elapsed(),
    			     mWindowBuffer.width);
    	ANativeWindow* lWindow = mApplication->window;
    	if(ANativeWindow_lock(lWindow, &mWindowBuffer, NULL) >= 0) {
    		clear();
    		drawCursor(mSize, mPosX,mPosY);
    		ANativeWindow_unlockAndPost(lWindow);
    		return STATUS_OK;
    	}else{
    		return STATUS_KO;
    	}
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

    void DroidBlaster::clear() {
    	memset(mWindowBuffer.bits,0,mWindowBuffer.stride * mWindowBuffer.height * sizeof(uint32_t*));
    }

    void DroidBlaster::drawCursor(int pSize, int pX,int pY) {
    	const int lHalfSize = pSize /2;

    	const int lUpLeftX = pX - lHalfSize;
    	const int lUpLeftY = pY - lHalfSize;
    	const int lDownRightX = pX + lHalfSize;
    	const int lDownRightY = pY + lHalfSize;

    	int32_t* lLine =
    			reinterpret_cast<int32_t*> (mWindowBuffer.bits) +
    			            (mWindowBuffer.stride * lUpLeftY);
    	for(int iY = lUpLeftY;iY <= lDownRightY;iY ++) {
    		for (int iX = lUpLeftX;iX <= lDownRightX;iX++) {
    			lLine[iX] =255;
    		}
    		lLine = lLine + mWindowBuffer.stride;
    	}
    }
}
