#pragma once

#include "ofMain.h"
#include "bullet/btBulletDynamicsCommon.h"
#include "bullet/BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDebugDrawer.h"

const int _P1_TAG = 1;
const int _BOX_TAG = 2;
const int _WALL_TAG = 3;

static const int* P1_TAG = &_P1_TAG;
static const int* BOX_TAG = &_BOX_TAG;
static const int* WALL_TAG = &_WALL_TAG;

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
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

	btCollisionShape* groundShape;
	btCollisionShape* ballShape;
	btCollisionShape* platformShape;
	btCollisionShape* boxShape;

	btDefaultMotionState* groundMotionState;
	btDefaultMotionState* ballMotionState;
	btDefaultMotionState* platformMotionState;
	btDefaultMotionState* wallMotionState;
	btDefaultMotionState* crateMotionState;

	btRigidBody* groundRigidBody;
	btRigidBody* ballRigidBody;
	btRigidBody* platformRigidBody;
	btRigidBody* wallRigidBody;
	btRigidBody* crateRigidBody;

	ofCamera camera;
	ofLight light;
	BulletDebugDrawer* bulletDebugDrawer;
		
	void initPhysics();
	void cleanupPhysics();

	bool upKey;
	bool downKey;
	bool leftKey;
	bool rightKey;
	ofVec3f mousePosition;
};
