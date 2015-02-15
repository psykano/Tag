#include "TagGame.h"
#include "BulletPhysicsEngine.h"
#include "BulletModel.h"

TagGame::TagGame() {
	physics = new BulletPhysicsEngine();
}

TagGame::~TagGame() {
	delete physics;
}

void TagGame::setup() {
	physics->setup();

	// This should be done through map parsing (for model type and location) and object creation (for model's [physics] properties) somehow...
	//map->generate(); ?

	BulletPhysicsEngine* bulletPhysics = dynamic_cast<BulletPhysicsEngine*>(physics);

	// Ground
	{
		BulletModel* model = new BulletModel();
		models.push_back(model);

		btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
		btCollisionShape* groundShape = bulletPhysics->getGroundShape();
		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));

		model->setup(groundShape, groundMotionState, groundRigidBodyCI);
		bulletPhysics->addRigidBodyToWorld(model->getRigidBody());
	}

	// Platform
	{
		BulletModel* model = new BulletModel();
		models.push_back(model);

		btDefaultMotionState* platformMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
		btCollisionShape* platformShape = bulletPhysics->getPlatformShape();
		btRigidBody::btRigidBodyConstructionInfo platformRigidBodyCI(0, platformMotionState, platformShape, btVector3(0, 0, 0));
		platformRigidBodyCI.m_friction = 1.0f;
		platformRigidBodyCI.m_rollingFriction = 0.6f;
		platformRigidBodyCI.m_restitution = 0.5f;

		model->setup(platformShape, platformMotionState, platformRigidBodyCI);
		bulletPhysics->addRigidBodyToWorld(model->getRigidBody());
	}

	// Wall
	{
		BulletModel* model = new BulletModel();
		models.push_back(model);

		btDefaultMotionState* wallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 12, 0)));
		btCollisionShape* wallShape = bulletPhysics->getUnitBoxShape();
		btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI(0, wallMotionState, wallShape, btVector3(0, 0, 0));
		wallRigidBodyCI.m_friction = 1.0f;
		wallRigidBodyCI.m_rollingFriction = 0.6f;
		wallRigidBodyCI.m_restitution = 0.5f;

		model->setup(wallShape, wallMotionState, wallRigidBodyCI);
		bulletPhysics->addRigidBodyToWorld(model->getRigidBody());
	}

	// Crate
	{
		BulletModel* model = new BulletModel();
		models.push_back(model);

		btDefaultMotionState* crateMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-4, 12, 0)));
		btCollisionShape* crateShape = bulletPhysics->getUnitBoxShape();

		btScalar mass = 0.5f;
		btVector3 crateInertia(0, 0, 0);
		crateShape->calculateLocalInertia(mass, crateInertia);
		btRigidBody::btRigidBodyConstructionInfo crateRigidBodyCI(mass, crateMotionState, crateShape, crateInertia);

		crateRigidBodyCI.m_friction = 0.6f;
		crateRigidBodyCI.m_rollingFriction = 0.6f;

		model->setup(crateShape, crateMotionState, crateRigidBodyCI);
		bulletPhysics->addRigidBodyToWorld(model->getRigidBody());
	}

	// Player
	{
		BulletModel* model = new BulletModel();
		models.push_back(model);

		btDefaultMotionState* playerMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 24, 0)));
		btCollisionShape* playerShape = bulletPhysics->getUnitBallShape();

		btScalar mass = 1.0f;
		btVector3 playerInertia(0, 0, 0);
		playerShape->calculateLocalInertia(mass, playerInertia);
		btRigidBody::btRigidBodyConstructionInfo playerRigidBodyCI(mass, playerMotionState, playerShape, playerInertia);

		playerRigidBodyCI.m_friction = 1.4f;
		playerRigidBodyCI.m_rollingFriction = 0.6f;
		playerRigidBodyCI.m_restitution = 0.5f;
		playerRigidBodyCI.m_angularDamping = 0.6f;
		//playerRigidBodyCI.m_linearDamping = 0.3f;
		
		model->setup(playerShape, playerMotionState, playerRigidBodyCI);
		bulletPhysics->addRigidBodyToWorld(model->getRigidBody());

		// For the collision callbacks
		model->getRigidBody()->setCollisionFlags(model->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	}
}

void TagGame::cleanup() {
	physics->cleanup();

	for (std::vector<ModelInterface*>::iterator it = models.begin(); it != models.end(); ++it) {
		delete *it;
	}
	models.clear();
}

void TagGame::step(float dt) {
	physics->step(dt);
}

const PhysicsEngineInterface* TagGame::getPhysicsEngine() {
	return physics;
}