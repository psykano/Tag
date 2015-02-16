#ifndef EVENT_SYSTEM_INTERFACE_H
#define EVENT_SYSTEM_INTERFACE_H

class EventSystemInterface {
public:
	virtual ~EventSystemInterface() {}
	virtual void step(float dt) = 0;
	virtual void playerConnectedEvent(unsigned int playerNum) = 0;
	virtual void playerDisconnectedEvent(unsigned int playerNum) = 0;
	virtual void playerMovementInputEvent(unsigned int playerNum, float x, float z, float dt) = 0;
};

#endif