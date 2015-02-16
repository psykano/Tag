#ifndef CLIENT_EVENT_SYSTEM_H
#define CLIENT_EVENT_SYSTEM_H

#include "EventSystemInterface.h"
#include <vector>
#include <map>

class ClientEventSystem : public EventSystemInterface {
	struct MovementInputEvent {
		unsigned int playerNum;
		float x;
		float z;
		float dt;
		MovementInputEvent(unsigned int _playerNum, float _x, float _z, float _dt) : playerNum(_playerNum), x(_x), z(_z), dt(_dt) {}
	};

	struct ReceivedMovementInputEvent : MovementInputEvent {
		unsigned int playerNum;
		float e;
		ReceivedMovementInputEvent(unsigned int _playerNum, float _x, float _z, float _dt, float _e) : MovementInputEvent(_playerNum, _x, _z, _dt), e(_e) {}
	};

public:
	virtual void step(float dt);
	virtual void playerConnectedEvent(unsigned int playerNum);
	virtual void playerDisconnectedEvent(unsigned int playerNum);
	virtual void playerMovementInputEvent(unsigned int playerNum, float x, float z, float dt);
	void addLocalPlayer(unsigned int playerNum);
	void receivedPlayerMovementInputEvent(unsigned int playerNum, float x, float z, float dt, float e);

private:
	std::map<unsigned int, unsigned int> myReceivedMovementInputEvents;
	std::vector<float> dtsSinceLastReceivedMovementInputEvent;
	std::vector<ReceivedMovementInputEvent> receivedMovementInputEvents;

	std::map<unsigned int, unsigned int> myMovementInputEvents;
	std::map<unsigned int, float>  dtsSinceLastMovementInputEvent;
	std::vector<MovementInputEvent> movementInputEvents;
};

#endif