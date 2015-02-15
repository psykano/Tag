#ifndef BULLET_PHYSICS_ENGINE_H
#define BULLET_PHYSICS_ENGINE_H

#include "PhysicsEngineInterface.h"
#include "btBulletDynamicsCommon.h"

class BulletPhysicsEngine : public PhysicsEngineInterface {
public:
	virtual void setup();
	virtual void cleanup();
	virtual void step(float dt);
	virtual void debugDraw() const;
	void addRigidBodyToWorld(btRigidBody* body);

	btCollisionShape* getGroundShape();
	btCollisionShape* getPlatformShape();
	btCollisionShape* getUnitBallShape();
	btCollisionShape* getUnitBoxShape();

private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
#ifdef DEBUG_DRAW
	btIDebugDraw* debugDrawer;
#endif

	btCollisionShape* groundShape;
	btCollisionShape* platformShape;
	btCollisionShape* unitBallShape;
	btCollisionShape* unitBoxShape;
};

#endif