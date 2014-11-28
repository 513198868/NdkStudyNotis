#include "GraphicsService.hpp"
#include "Log.hpp"

#include <GLES/gl.h>
#include <GLES/glext.h>

namespace packt
{
    GraphiceService::GraphicsService(android_app* pApplication,
    		                     TimeService* pTimeService) :
        mApplication(pApplication),
        mTimeService(pTimeService),
        mWidth(0),mHeight(0),
        mDisplay(EGL_NO_DISPLAY),
        mSurface(EGL_NO_CONTEXT),
        mContext(EGL_NO_SURFACE)
    {}

    int32_t GraphicsService::getPath() {
    	return mResource.getPath();
    }

    const int32_t& GraphicsService::getHeight() {
    	return mHeight;
    }

    const int32_t& GraphicsService::getWidth() {
    	return mWidth;
    }

    status GraphicsService::start() {
    	EGLint lFormat, lNumConfigs, lErrorResult;
    	EGLConfig lConfig;
    	const EGLint lAttributes[] = {
    			EGL_RENDERABLE_TYPE,EGL_OPENGL_ES_BIT,
    			EGL_BLUE_SIZE, 5,EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
    			EGL_SURFACE_TYPE,EGL_WINDOW_BIT,
    			EGL_NONE
    	};
    	mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    	if(mDisplay == EGL_NO_DISPLAY) goto ERROR;
    	if(!eglinitialize(mDisplay,NULL,NULL)) goto ERROR;

    	if(!eglChooseConfig(mDisplay,lAttributes,&lConfig,1,
    			&lNumConfigs) || (lNumConfigs<= 0)) goto ERROR;
    	ANativeWindow_setBuffersGeometry(mApplication->window, 0, 0,
    			lFormat);

    	mSurface = eglCreateWindowSurface(mDisplay,lConfig,
    			mApplication->window,NULL);
    	if(mSurface == EGL_NO_SURFACE) goto ERROR;
    	mContext = eglCreateContext(mDisplay,lConfig,
    			EGL_NOCONTEXT,NULL);
    	if(mContext == EGL_NO_CONTEXT) goto ERROR;

    	if(!eglMakeCurrent (mDisplay,mSurface,mSurface,mContext)
    			|| !eglQuerySurface (mDisplay,mSurface,EGL_WIDTH,&mWidth)
    			|| !eglQuerySurface (mDisplay,mSurface,EGL_HEIGHT,&mHeight)
    			|| (mWidth <= 0) || (mHeight <= 0)) goto ERROR;
    	    glViewport(0, 0, mWidth, mHeight);

    	    return STATUS_OK;

    	ERROR:
    	    Log::error("Error while starting GraphicsService");
    	    stop();
    	    return STATUS_KO;
    }

    void GraphicsService::stop() {
    	if(mDisplay != EGL_NO_DISPLAY){
    		eglMakeCurrent(mDisplay, EGL_NO_SURFACE,EGL_NO_SURFACE,
    				EGL_NO_CONTEXT);
    		if(mContext != EGL_NO_CONTEXT) {
    			eglDestroyContext(mDisplay,mContext);
    			mContext = EGL_NO_CONTEXT;
    		}
    		if(mSurface != EGL_NO_SURFACE) {
    			eglDestroySurface(mDisplay,mSurface);
    			mSurface = EGL_NO_SURFACE;
    		}
    		eglTerminate(mDisplay);
    		mDisplay = EGL_NO_DISPLAY;
    	}

    	status GraphicsService::update() {
    		float lTimeStop = mTimeService->elapsed();

    		statc float lClearColor = 0.0f;
    		lClearColor += lTimeStep * 0.01f;
    		glClearColor(lClearColor,lClearColor,lClearColor,1.0f);
    		glClear(GL_COLOR_BUFFER_BIT);

    		if (eglSwapBuffers(mDisplay, mSurface) != EGL_TRUE) {
    			Log::error("Error %d swapping buffers.", eglGetError());
    			return STATUS_KO;
    		}
    		return STATUS_OK;
    	}
    }
}
