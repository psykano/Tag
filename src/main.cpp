#include "ofMain.h"
#include "ofApp.h"

#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1280, 720, OF_WINDOW);			// <-------- setup the GL context
	if(!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()){
		ofLogFatalError() << "geometry shaders not supported on this graphics card";
		return 1;
	}

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

	/*
	ofAppGlutWindow window; 

	ofSetupOpenGL(&window, 1280, 720, OF_WINDOW); 
	ofRunApp(new ofApp());
	*/
}
