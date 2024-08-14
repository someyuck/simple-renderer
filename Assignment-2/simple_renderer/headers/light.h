#pragma once

#include "common.h"

enum LightType {
	POINT_LIGHT=0,
	DIRECTIONAL_LIGHT=1,
	NUM_LIGHT_TYPES
};

struct Light {
	LightType type;
	Vector3f positionOrDirection;
	Vector3f radiance;

	Light() {};
	Light(LightType type, Vector3f positionOrDirection, Vector3f radiance) :
		type(type), positionOrDirection(positionOrDirection), radiance(radiance) {};
};

typedef std::vector<Light> Lights;

Lights loadLights(nlohmann::json sceneConfig);