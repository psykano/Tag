#include "ofApp.h"
#include "game/TagGame.h"
#include "game/PhysicsEngineInterface.h"
#include "game/EventSystemInterface.h"

//--------------------------------------------------------------
void ofApp::setup(){
	game = new TagGame(false);
	game->setup();

	// For drawing
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(12, 12, 12);
	camera.setVFlip(true);
	camera.setPosition(ofVec3f(0, 26.0f, -30.0f)); // 10, -30       16.0f, -0.1f
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));

	// *** tmp controls
	upKey = false;
	downKey = false;
	leftKey = false;
	rightKey = false;
	prevMoveX = 0;
	prevMoveZ = 0;
}

//--------------------------------------------------------------
void ofApp::exit(){
	game->cleanup();
	delete game;
}

//--------------------------------------------------------------
void ofApp::update(){
	// *** tmp controls
	float moveX = 0;
	float moveZ = 0;

	if (upKey) {
		moveX = 1;
	} else if (downKey) {
		moveX = -1;
	} else {
		moveX = 0;
	}

	if (leftKey) {
		moveZ = 1;
	} else if (rightKey) {
		moveZ = -1;
	} else {
		moveZ = 0;
	}

	if (moveX != prevMoveX || moveZ != prevMoveZ) {
		prevMoveX = moveX;
		prevMoveZ = moveZ;
		game->getEventSystem()->playerMovementInputEvent(0, moveX, moveZ, 0); // dt should be currentTime-lastInputTime
	}

	game->step(1.0f / 60.0f);
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Frame rate in the top left corner
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);

	ofEnableDepthTest();
	camera.begin();

#ifdef DEBUG_DRAW
	ofSetLineWidth(1.0f);
	ofSetColor(255, 0, 200);
	game->getPhysicsEngine()->debugDraw();
#endif

	ofEnableLighting();
	light.enable();

	// Draw stuff here

	light.disable();
	ofDisableLighting();

	camera.end();
	ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 357) {
		upKey = true;
	} else if (key == 359) {
		downKey = true;
	} else if (key == 356) {
		leftKey = true;
	} else if (key == 358) {
		rightKey = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 357) {
		upKey = false;
	} else if (key == 359) {
		downKey = false;
	} else if (key == 356) {
		leftKey = false;
	} else if (key == 358) {
		rightKey = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
