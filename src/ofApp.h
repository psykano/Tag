#pragma once

#include "ofMain.h"

class GameInterface;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void exit();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
	private:
		GameInterface* game;

		// For drawing
		ofCamera camera;
		ofLight light;

		// *** tmp input
		bool upKey;
		bool downKey;
		bool leftKey;
		bool rightKey;
		float prevMoveX;
		float prevMoveZ;
};
