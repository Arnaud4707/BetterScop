#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "shader.hpp"
#include "ObjectBlender.hpp"
#include "MusicEngine.hpp"
#include "MusicAnalyzer.hpp"
#include "AnimationEngine.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

extern Light light;

extern float vertices[216];
extern unsigned int indices[];
extern bool autoRot;
extern bool wareFrame;
extern	float factor;
extern	bool onTexture;

extern Material emerald;
extern Material jade;
extern Material obsidian;
extern Material pearl;
extern Material ruby;
extern Material turquoise;
extern Material brass;
extern Material bronze;
extern Material chrome;
extern Material copper;
extern Material gold;
extern Material silver;
extern Material black_plastic;
extern Material cyan_plastic;
extern Material green_plastic;
extern Material red_plastic;
extern Material white_plastic;
extern Material yellow_plastic;
extern Material black_rubber;
extern Material cyan_rubber;
extern Material green_rubber;
extern Material red_rubber;
extern Material white_rubber;
extern Material yellow_rubber;

#endif