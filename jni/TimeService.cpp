#include "TimeService.hpp"
#include "Log.hpp"

namespace packt {
    TimeService::TimeService():
    		mElapsed(0.0f),
    		mLastTime(0.0f)
    {}

    void TimeService::reset() {
    	Log::info("Resetting TimeService.");
    	mElapsed = 0.0f;
    	mLastTime = now();
    }

    void TimeService::update() {
    	double lCurrentTime = now();
    	mElapsed = (lCurrentTime - mLastTime);
    	mLastTime = lCurrentTime;
    }

    double TimeService::now(){
    	timespec lTimeVal;
    	clock_gettime(CLOCK_MONOTONIC,&lTimeVal);
    	return lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);
    }

    float TimeService::elapsed() {
    	return mElapsed;
    }
}
