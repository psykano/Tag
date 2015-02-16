#ifndef CONTROLLER_INTERFACE_H
#define CONTROLLER_INTERFACE_H

class ModelInterface;

class ControllerInterface {
public:
	virtual ~ControllerInterface() {}
	virtual void attachToModel(ModelInterface* _model) = 0;
	virtual void rollTowardVector(float x, float y, float z) = 0;
};

#endif