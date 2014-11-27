#include "Log.hpp"

#include <stdarg.h>
#include <android/log.h>

namespace packt{
    void Log::info(const char* pMessage, ...){
    	va_list lVarArgs;
    	va_start (lVarArgs, pMessage);
    	__android_log_vprint(ANDROID_LOG_INFO,"PACKT",pMessage,
    			lVarArgs);
    	__android_log_print(ANDROID_LOG_INFO,"PACKT","\n");
    	va_end(lVarArgs);
    }
}
