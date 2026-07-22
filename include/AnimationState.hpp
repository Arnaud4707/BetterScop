#ifndef ANIMATIONSTATE_HPP
#define ANIMATIONSTATE_HPP
#include "Vec3.hpp"

struct AnimationState
{
	float objectScale = 0.f;
	float rotationSpeed = 0.f;
	float glow = 0.f;
	float bloom = 0.f;
	float particleRate = 0.f;
	vec3 color = {0.f, 0.f, 0.f};
	float cameraShake = 0.f;
	float cameraZoom = 0.f;
	float distortion = 0.f;
};

#endif