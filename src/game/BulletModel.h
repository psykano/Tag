#ifndef BULLET_MODEL_H
#define BULLET_MODEL_H

#include "ModelInterface.h"
#include "btBulletDynamicsCommon.h"

class BulletModel : public ModelInterface {
public:
	void setup(btCollisionShape* _collisionShape, btMotionState* _motionState, btRigidBody::btRigidBodyConstructionInfo &rigidBodyCI);
	virtual void cleanup();
	virtual void collidedWith(ModelInterface* model);
	virtual void applyTorque(float x, float y, float z);
	btRigidBody* getRigidBody();

private:
	btCollisionShape* collisionShape;
	btMotionState* motionState;
	btRigidBody* rigidBody;
};

#endif