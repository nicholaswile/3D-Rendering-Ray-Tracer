#include "Light.h"

Light::Light(lightType type) {
	intensity = 0.0f;
	memcpy(position, new float [3] {0, 0, 0}, sizeof(position));
	memcpy(direction, new float[3] {0, 0, 0}, sizeof(direction));
	this->type = type;
}
