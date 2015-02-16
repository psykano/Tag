#include "ClientEventSystem.h"

void ClientEventSystem::step(float dt) {
	for (std::vector<float>::iterator it = dtsSinceLastReceivedMovementInputEvent.begin(); it != dtsSinceLastReceivedMovementInputEvent.end(); ++it) {
		*it += dt;
	}

	for (std::map<unsigned int, float>::iterator it = dtsSinceLastMovementInputEvent.begin(); it != dtsSinceLastMovementInputEvent.end(); ++it) {
		++it->second;
	}

	// lots TODO here! ***
}

void ClientEventSystem::playerConnectedEvent(unsigned int playerNum) {
	if (playerNum >= dtsSinceLastReceivedMovementInputEvent.size()) {
		dtsSinceLastReceivedMovementInputEvent.push_back(0);
	} else {
		dtsSinceLastReceivedMovementInputEvent.at(playerNum) = 0;
	}

}

void ClientEventSystem::playerDisconnectedEvent(unsigned int playerNum) {
	
}

void ClientEventSystem::playerMovementInputEvent(unsigned int playerNum, float x, float z, float dt) {
	++myMovementInputEvents.at(playerNum);
	movementInputEvents.push_back(MovementInputEvent(playerNum, x, z, dt));
	// send input event *** TODO
	//queueMovementInputMessage(playerNum, x, z, dt);
}

void ClientEventSystem::addLocalPlayer(unsigned int playerNum) {
	myReceivedMovementInputEvents[playerNum] = 0;
	myMovementInputEvents[playerNum] = 0;
	dtsSinceLastMovementInputEvent[playerNum] = 0;
}

void ClientEventSystem::receivedPlayerMovementInputEvent(unsigned int playerNum, float x, float z, float dt, float e) {
	if (myReceivedMovementInputEvents.count(playerNum) > 0) {
		++myReceivedMovementInputEvents.at(playerNum);
	}
	receivedMovementInputEvents.push_back(ReceivedMovementInputEvent(playerNum, x, z, dt, e));
}