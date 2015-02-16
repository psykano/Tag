#include "PlayerController.h"
#include "ModelInterface.h"
#include <math.h>

void PlayerController::attachToModel(ModelInterface* _model) {
	model = _model;
}
	
void PlayerController::rollTowardVector(float x, float y, float z) {
	// Need to deal with state here... *** TODO
	float speed = 6.0f;
	
	// Convert to unit vector so it can't be abused
	float magnitude = sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	x = (x/magnitude) * speed;
	y = (y/magnitude) * speed;
	z = (z/magnitude) * speed;

	model->applyTorque(x, y, z);
}