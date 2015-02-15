#include "BulletPhysicsEngine.h"
#include "../BulletDebugDrawer.h"
#include "ModelInterface.h"

// Global variables for collision callback
extern ContactAddedCallback gContactAddedCallback;
extern ContactProcessedCallback gContactProcessedCallback;
extern ContactDestroyedCallback gContactDestroyedCallback;

// From here, you can modify some properties (e.g. friction) of the contact point before it gets processed.
// WARNING: does not appear to work when using multithreaded solvers.
static bool ContactAddedCollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) {
	ModelInterface* model0 = static_cast<ModelInterface*>(colObj0Wrap->getCollisionObject()->getUserPointer());
	ModelInterface* model1 = static_cast<ModelInterface*>(colObj1Wrap->getCollisionObject()->getUserPointer());
	model0->collidedWith(model1);
	model1->collidedWith(model0);

	// This return value is currently ignored, but to be on the safe side: return false if you don't calculate friction.
	return false;
}

// NOTE: this gets called for every collision, regardless if collision object has CF_CUSTOM_MATERIAL_CALLBACK
// So if this is used in the future, think about modifying how gContactProcessedCallback is called in btPersistentManifold.cpp
static bool ContactProcessedCollisionCallback(btManifoldPoint& cp, void* body0, void* body1) {

	// This return value is currently ignored
	return false;
}

// userPersistentData is the value of the m_userPersistentData member of the btManifoldPoint which has been destroyed (this can be set in gContactAddedCallback or gContactProcessedCallback)
// NOTE: This will not be called for any contact point unless cp.m_userPersistentData is set!
static bool ContactDestroyedCollisionCallback(void* userPersistentData) {

	// This return value is currently ignored
	return false;
}

void BulletPhysicsEngine::setup() {
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

	// Oh Bullet...
	gContactAddedCallback = &ContactAddedCollisionCallback;
	//gContactProcessedCallback = &ContactProcessedCollisionCallback; // See the NOTE
	gContactDestroyedCallback = &ContactDestroyedCollisionCallback;

#ifdef DEBUG_DRAW
	// Debug drawing
	debugDrawer = new BulletDebugDrawer();
	debugDrawer->setDebugMode(btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
	dynamicsWorld->setDebugDrawer(debugDrawer);
#endif

	// Shapes
	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	platformShape = new btBoxShape(btVector3(12, 1, 12));
	unitBallShape = new btSphereShape(0.5);
	unitBoxShape = new btBoxShape(btVector3(1, 1, 1));
}

void BulletPhysicsEngine::cleanup() {
	// Order matters
#ifdef DEBUG_DRAW
	delete debugDrawer;
#endif
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;

	delete groundShape;
	delete platformShape;
	delete unitBallShape;
	delete unitBoxShape;
}

void BulletPhysicsEngine::step(float dt) {
	dynamicsWorld->stepSimulation(dt, 10);
}

void BulletPhysicsEngine::debugDraw() const {
#ifdef DEBUG_DRAW
	dynamicsWorld->debugDrawWorld();
#endif
}

void BulletPhysicsEngine::addRigidBodyToWorld(btRigidBody* body) {
	dynamicsWorld->addRigidBody(body);
}

btCollisionShape* BulletPhysicsEngine::getGroundShape() {
	return groundShape;
}

btCollisionShape* BulletPhysicsEngine::getPlatformShape() {
	return platformShape;
}

btCollisionShape* BulletPhysicsEngine::getUnitBallShape() {
	return unitBallShape;
}

btCollisionShape* BulletPhysicsEngine::getUnitBoxShape() {
	return unitBoxShape;
}