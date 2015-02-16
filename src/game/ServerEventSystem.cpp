#include "ServerEventSystem.h"

void ServerEventSystem::step(float dt) {
	for (std::vector<float>::iterator it = dtsSinceLastMovementInputEvent.begin(); it != dtsSinceLastMovementInputEvent.end(); ++it) {
		*it += dt;
	}

	// Process events
	std::vector<MovementInputEvent>::iterator it = movementInputEvents.begin();
	while (it != movementInputEvents.end()) {
		if (dtsSinceLastMovementInputEvent.at(it->playerNum) >= it->dt) {
			// Ease back in sync
			dtsSinceLastMovementInputEvent.at(it->playerNum) -= it->dt;
			dtsSinceLastMovementInputEvent.at(it->playerNum) /= 2.0f;
			if (dtsSinceLastMovementInputEvent.at(it->playerNum) <= 1.0f / 60.0f) {
				dtsSinceLastMovementInputEvent.at(it->playerNum) = 0;
			}

			// Process input *** TODO

			// send input event *** TODO
			//queueMovementInputMessage(it->playerNum, it->x, it->z, dt, dtSinceLastInputEvent.at(it->playerNum));

			it = movementInputEvents.erase(it);
		} else {
			++it;
		}
	}
}

void ServerEventSystem::playerConnectedEvent(unsigned int playerNum) {
	if (playerNum >= dtsSinceLastMovementInputEvent.size()) {
		dtsSinceLastMovementInputEvent.push_back(0);
	} else {
		dtsSinceLastMovementInputEvent.at(playerNum) = 0;
	}

}

void ServerEventSystem::playerDisconnectedEvent(unsigned int playerNum) {
	
}

void ServerEventSystem::playerMovementInputEvent(unsigned int playerNum, float x, float z, float dt) {
	movementInputEvents.push_back(MovementInputEvent(playerNum, x, z, dt));
}