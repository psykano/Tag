#ifndef TAG_GAME_H
#define TAG_GAME_H

#include "GameInterface.h"
#include "ModelInterface.h"
#include <vector>

#include "BulletModel.h"

class PhysicsEngineInterface;

class TagGame : public GameInterface {
public:
	TagGame();
	~TagGame();
	virtual void setup();
	virtual void cleanup();
	virtual void step(float dt);
	virtual const PhysicsEngineInterface* getPhysicsEngine();

private:
	// To avoid problems with destruction
	TagGame(const TagGame& other) {}
	TagGame& operator= (const TagGame& other) {return *this;}

	PhysicsEngineInterface* physics;
	std::vector<ModelInterface*> models;
};

#endif