#include "ofApp.h"

// From here, you can modify some properties (e.g. friction) of the contact point before it gets processed.
// WARNING: does not appear to work when using multithreaded solvers.
static bool ContactAddedCollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) {
	/*
	int* o1 = static_cast<int*>(colObj0Wrap->getCollisionObject()->getUserPointer());
	int* o2 = static_cast<int*>(colObj1Wrap->getCollisionObject()->getUserPointer());
	if (o1 && o2) {
		std::cout << *o1 << " with " << *o2 << std::endl;
	}
	*/

	// This return value is currently ignored, but to be on the safe side: return false if you don't calculate friction.
	return false;
}

static bool ContactProcessedCollisionCallback(btManifoldPoint& cp, void* body0, void* body1) {
	btCollisionObject* colObj0 = static_cast<btCollisionObject*>(body0);
	btCollisionObject* colObj1 = static_cast<btCollisionObject*>(body1);
	int* o1 = static_cast<int*>(colObj0->getUserPointer());
	int* o2 = static_cast<int*>(colObj1->getUserPointer());
	if (o1 && o2) {
		std::cout << *o1 << " with " << *o2 << std::endl;
	}

	// This return value is currently ignored
	return false;
}

// userPersistentData is the value of the m_userPersistentData member of the btManifoldPoint which has been destroyed (this can be set in gContactAddedCallback or gContactProcessedCallback)
// NOTE: This will not be called for any contact point unless cp.m_userPersistentData is set!
static bool ContactDestroyedCollisionCallback(void* userPersistentData) {

	// This return value is currently ignored
	return false;
}

//--------------------------------------------------------------
void ofApp::setup(){
	initPhysics();

	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	ballShape = new btSphereShape(0.5);
	platformShape = new btBoxShape(btVector3(12, 1, 12));
	boxShape = new btBoxShape(btVector3(1, 1, 1));

	// Ground
	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBodyCI.m_friction = 4.0f;
	groundRigidBodyCI.m_rollingFriction = 0.6f;
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	// Ball
	ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 24, 0)));
	{
		btScalar mass = 1.0f;
		btVector3 ballInertia(0, 0, 0);
		ballShape->calculateLocalInertia(mass, ballInertia);
		btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass, ballMotionState, ballShape, ballInertia);
		ballRigidBodyCI.m_friction = 1.4f;
		ballRigidBodyCI.m_rollingFriction = 0.6f;
		ballRigidBodyCI.m_restitution = 0.5f;
		ballRigidBodyCI.m_angularDamping = 0.6f;
		//ballRigidBodyCI.m_linearDamping = 0.3f;
		ballRigidBody = new btRigidBody(ballRigidBodyCI);
	}
	ballRigidBody->setUserPointer((void*)P1_TAG);
	ballRigidBody->setCollisionFlags(ballRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
    dynamicsWorld->addRigidBody(ballRigidBody);

	// Platform
	platformMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
	btRigidBody::btRigidBodyConstructionInfo platformRigidBodyCI(0, platformMotionState, platformShape, btVector3(0, 0, 0));
	platformRigidBodyCI.m_friction = 1.0f;
	platformRigidBodyCI.m_rollingFriction = 0.6f;
	platformRigidBodyCI.m_restitution = 0.5f;
	platformRigidBody = new btRigidBody(platformRigidBodyCI);
	dynamicsWorld->addRigidBody(platformRigidBody);

	// Wall
	wallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 12, 0)));
	btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI(0, wallMotionState, boxShape, btVector3(0, 0, 0));
	wallRigidBodyCI.m_friction = 1.0f;
	wallRigidBodyCI.m_rollingFriction = 0.6f;
	wallRigidBodyCI.m_restitution = 0.5f;
	wallRigidBody = new btRigidBody(wallRigidBodyCI);
	wallRigidBody->setUserPointer((void*)WALL_TAG);
	dynamicsWorld->addRigidBody(wallRigidBody);

	// Crate
	crateMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-4, 12, 0)));
	{
		btScalar mass = 0.5f;
		btVector3 crateInertia(0, 0, 0);
		boxShape->calculateLocalInertia(mass, crateInertia);
		btRigidBody::btRigidBodyConstructionInfo  crateRigidBodyCI(mass, crateMotionState, boxShape, crateInertia);
		crateRigidBodyCI.m_friction = 0.6f;
		wallRigidBodyCI.m_rollingFriction = 0.6f;
		crateRigidBody = new btRigidBody(crateRigidBodyCI);
	}
	crateRigidBody->setUserPointer((void*)BOX_TAG);
	dynamicsWorld->addRigidBody(crateRigidBody);

	// Drawing
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(12, 12, 12);
	camera.setVFlip(true);
	camera.setPosition(ofVec3f(0, 26.0f, -0.1f)); // 10, -30       16.0f, -0.1f
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));

	// Debug drawing
	bulletDebugDrawer = new BulletDebugDrawer();
	dynamicsWorld->setDebugDrawer(bulletDebugDrawer);
	dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);

	// Controls
	upKey = false;
	downKey = false;
	leftKey = false;
	rightKey = false;
}

void ofApp::exit(){
	cleanupPhysics();

	delete groundShape;
	delete ballShape;
	
	delete groundMotionState;
	delete ballMotionState;

	delete groundRigidBody;
	delete ballRigidBody;

	delete bulletDebugDrawer;
}

void ofApp::initPhysics() {
	// Build the broadphase
	broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// The actual physics solver
	solver = new btSequentialImpulseConstraintSolver();

	// The world
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

	gContactAddedCallback = ContactAddedCollisionCallback;
	gContactProcessedCallback = ContactProcessedCollisionCallback;
	gContactDestroyedCallback = ContactDestroyedCollisionCallback;
}

void ofApp::cleanupPhysics() {
	// Order matters
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

//--------------------------------------------------------------
void ofApp::update(){
	dynamicsWorld->stepSimulation(1 / 60.0f, 10);

	// Collision
	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; ++i) {
		btPersistentManifold* contactManifold =  dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);

		const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
		const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());

		int numContacts = contactManifold->getNumContacts();
		if (numContacts > 0) {
			int* o1 = static_cast<int*>(obA->getUserPointer());
			int* o2 = static_cast<int*>(obB->getUserPointer());

			if (o1 && o2) {
				//std::cout << *o1 << " with " << *o2 << std::endl;
			}
		}

		// I don't care about collision normals at the moment...
		/*
		for (int j = 0; j < numContacts; ++j)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f) {
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
		}
		*/
	}

	btTransform trans;
	ballRigidBody->getMotionState()->getWorldTransform(trans);

//	std::cout << "sphere: " << trans.getOrigin().getZ() << std::endl;

//	ballRigidBody->applyTorque(btVector3(0,0,0));


	// Control
	btVector3 torque(0, 0, 0);
	int maxTorque = 6.0f;
	if (upKey) {
		torque.setX(maxTorque);
	} else if (downKey) {
		torque.setX(-maxTorque);
	} else {
		torque.setX(0);
	}

	if (leftKey) {
		torque.setZ(maxTorque);
	} else if (rightKey) {
		torque.setZ(-maxTorque);
	} else {
		torque.setZ(0);
	}

	//std::cout << "torque: (" << torque.getX() << ", " << torque.getY() << ", " << torque.getZ() << ")" << std::endl;
	//std::cout << "velocity: (" << ballRigidBody->getLinearVelocity().getX() << ", " << ballRigidBody->getLinearVelocity().getY() << ", " << ballRigidBody->getLinearVelocity().getZ() << ")" << std::endl;

	if (torque != btVector3(0, 0, 0)) {
		ballRigidBody->activate();
	}
	ballRigidBody->applyTorque(torque);
	//ballRigidBody->applyTorqueImpulse(torque);

	//ballRigidBody->applyCentralForce(torque);

	mousePosition = camera.screenToWorld(ofVec3f((float)ofGetMouseX(), (float)ofGetMouseY(), 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(ofToString(ofGetFrameRate())+"fps", 10, 15);

	ofVec3f ballPosition(ballMotionState->m_graphicsWorldTrans.getOrigin().getX(),
		ballMotionState->m_graphicsWorldTrans.getOrigin().getY(),
		ballMotionState->m_graphicsWorldTrans.getOrigin().getZ());
	camera.setPosition(ballPosition.x, ballPosition.y + 10, ballPosition.z - 5.0f);
	camera.lookAt(ballPosition, ofVec3f(0, -1, 0));

	ofVec3f lightPosition = ballPosition;
	lightPosition.x += 3;
	lightPosition.y += 10;
	light.setPosition(lightPosition);

	ofEnableDepthTest();
	camera.begin();

	// Draw debug
	ofSetLineWidth(1.0f);
	ofSetColor(255, 0, 200);
	//dynamicsWorld->debugDrawWorld();

	// Lighting
	ofEnableLighting();
	light.enable();

	// Draw platform
	{
		btScalar m[16];
		platformMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
		ofPushMatrix();
		ofMultMatrix(ofMatrix4x4(m));
		ofSetColor(170, 170, 170);
		ofDrawBox(0, 0, 0, 24, 2, 24);
		ofPopMatrix();
	}

	// Draw wall
	{
		btScalar m[16];
		wallMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
		ofPushMatrix();
		ofMultMatrix(ofMatrix4x4(m));
		ofSetColor(100, 100, 100);
		ofDrawBox(0, 0, 0, 2, 2, 2);
		ofPopMatrix();
	}

	// Draw crate
	{
		btScalar m[16];
		crateMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
		ofPushMatrix();
		ofMultMatrix(ofMatrix4x4(m));
		ofSetColor(0, 0, 255);
		ofDrawBox(0, 0, 0, 2, 2, 2);
		ofPopMatrix();
	}

	// Draw ball
	{
		btScalar m[16];
		ballMotionState->m_graphicsWorldTrans.getOpenGLMatrix(m);
		ofPushMatrix();
		ofMultMatrix(ofMatrix4x4(m));
		ofSetColor(255, 0, 0);

		ofNoFill();
		ofDrawSphere(0, 0, 0, 0.5f);
		ofFill();

		//ofSetLineWidth(2.0f);
		//ofNoFill();
		ofSetColor(255, 255, 0);
		ofDisableLighting();
		ofCircle(0, 0, 0, 0.54f);
		ofEnableLighting();
		//ofFill();

		ofPopMatrix();
	}

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
