#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

class PhysicsEngineInterface;
class EventSystemInterface;

class GameInterface {
public:
	virtual ~GameInterface() {}
	virtual void setup() = 0;
	virtual void cleanup() = 0;
	virtual void step(float dt) = 0;
	virtual const PhysicsEngineInterface* getPhysicsEngine() = 0;
	virtual EventSystemInterface* getEventSystem() = 0;
};

#endif