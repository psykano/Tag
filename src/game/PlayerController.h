#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "ControllerInterface.h"

class PlayerController : public ControllerInterface {
public:
	virtual void attachToModel(ModelInterface* _model);
	virtual void rollTowardVector(float x, float y, float z);

private:
	ModelInterface* model;
};

#endif