#ifndef TAG_GAME_H
#define TAG_GAME_H

#include "GameInterface.h"
#include <vector>

class PhysicsEngineInterface;
class EventSystemInteface;
class ModelInterface;
class ControllerInterface;

class TagGame : public GameInterface {
public:
	TagGame(bool server);
	~TagGame();
	virtual void setup();
	virtual void cleanup();
	virtual void step(float dt);
	virtual const PhysicsEngineInterface* getPhysicsEngine();
	virtual EventSystemInterface* getEventSystem();

private:
	// To avoid problems with destruction
	TagGame(const TagGame& other) {}
	TagGame& operator= (const TagGame& other) {return *this;}

	PhysicsEngineInterface* physics;
	EventSystemInterface* eventSystem;
	std::vector<ModelInterface*> models;
	std::vector<ControllerInterface*> playerControllers;
};

#endif