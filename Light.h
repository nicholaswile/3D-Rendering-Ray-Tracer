#pragma once

#include <vector>

class Light {
public:
	float intensity;
	float position[3];
	float direction[3];
	enum lightType { ambient, point, directional };
	lightType type;

protected:
	Light(lightType);
};

class AmbientLight: public Light {
public:
	AmbientLight(float intensity) : Light(ambient) {
		this->intensity = intensity;
	}
};

class PointLight: public Light {
public:
	PointLight(float intensity, float position[3]) : Light(point) {
		this->intensity = intensity;
		memcpy(this->position, position, sizeof(this->position));
	}
};

class DirectionalLight: public Light {
public:
	DirectionalLight(float intensity, float direction[3]) : Light(directional) {
		this->intensity = intensity;
		memcpy(this->direction, direction, sizeof(this->direction));
	}
};