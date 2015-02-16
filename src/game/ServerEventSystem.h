#ifndef SERVER_EVENT_SYSTEM_H
#define SERVER_EVENT_SYSTEM_H

#include "EventSystemInterface.h"
#include <vector>

class ServerEventSystem : public EventSystemInterface {
	struct MovementInputEvent {
		unsigned int playerNum;
		float x;
		float z;
		float dt;
		MovementInputEvent(unsigned int _playerNum, float _x, float _z, float _dt) : playerNum(_playerNum), x(_x), z(_z), dt(_dt) {}
	};

public:
	virtual void step(float dt);
	virtual void playerConnectedEvent(unsigned int playerNum);
	virtual void playerDisconnectedEvent(unsigned int playerNum);
	virtual void playerMovementInputEvent(unsigned int playerNum, float x, float z, float dt);

private:
	std::vector<float> dtsSinceLastMovementInputEvent;
	std::vector<MovementInputEvent> movementInputEvents;
};

#endif