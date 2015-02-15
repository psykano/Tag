#include "BulletModel.h"
#include <assert.h>

void BulletModel::setup(btCollisionShape* _collisionShape, btMotionState* _motionState, btRigidBody::btRigidBodyConstructionInfo& rigidBodyCI) {
	if (!_collisionShape) {
		assert("Error: collision shape cannot be NULL!");
	}
	
	if (!_motionState) {
		assert("Error: motion state cannot be NULL!");
	}

	collisionShape = _collisionShape;
	motionState = _motionState;
	rigidBody = new btRigidBody(rigidBodyCI);
	rigidBody->setUserPointer(this);
}

void BulletModel::cleanup() {
	// We don't handle the deletion of the collision shape since it can be used for multiple models
	delete motionState;
	delete rigidBody;
}

void BulletModel::collidedWith(ModelInterface* model) {
	// need to deal with state here.... how *** TODO ***
}

btRigidBody* BulletModel::getRigidBody() {
	return rigidBody;
}