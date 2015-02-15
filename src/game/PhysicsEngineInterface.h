#ifndef PHYSICS_ENGINE_INTERFACE_H
#define PHYSICS_ENGINE_INTERFACE_H

#define DEBUG_DRAW

class PhysicsEngineInterface {
public:
	virtual ~PhysicsEngineInterface() {}
	virtual void setup() = 0;
	virtual void cleanup() = 0;
	virtual void step(float dt) = 0;
	virtual void debugDraw() const = 0;
};

#endif