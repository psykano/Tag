#ifndef MODEL_INTERFACE_H
#define MODEL_INTERFACE_H

class ModelInterface {
public:
	virtual ~ModelInterface() {}
	// Unfortunately, setup's arguments are going to be physics engine specific
	virtual void cleanup() = 0;
	virtual void collidedWith(ModelInterface* model) = 0;
	virtual void applyTorque(float x, float y, float z) = 0;
};

#endif