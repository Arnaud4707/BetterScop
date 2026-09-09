#include "../include/WindowManager.hpp"

void    initMaterials(void)
{
	emerald.ambient = vec3 (0.0215f, 0.1745f, 0.0215f);
	emerald.diffuse = vec3 (0.07568f, 0.61424f, 0.07568f);
	emerald.specular = vec3 (0.633f, 0.727811f, 0.633f);
	emerald.shininess = 0.6 * 128;

	jade.ambient = vec3 (0.135f, 0.2225f, 0.1575f);
	jade.diffuse = vec3 (0.54f, 0.89f, 0.63f);
	jade.specular = vec3 (0.316228f, 0.316228f, 0.316228f);
	jade.shininess = 0.1 * 128;

	gold.ambient = vec3 (0.24725f, 0.1995f, 0.0745f);
	gold.diffuse = vec3 (0.75164f, 0.60648f, 0.22648f);
	gold.specular = vec3 (0.628281f, 0.555802f, 0.366065f);
	gold.shininess = 0.4 * 128;

	obsidian.ambient = vec3 (0.05375f, 0.05f, 0.06625f);
	obsidian.diffuse = vec3 (0.18275f, 0.17f, 0.22525f);
	obsidian.specular = vec3 (0.332741f, 0.328634f, 0.346435f);
	obsidian.shininess = 0.3 * 128;

	pearl.ambient = vec3 (0.25f, 0.20725f, 0.20725f);
	pearl.diffuse = vec3 (1.0f, 0.829f, 0.829f);
	pearl.specular = vec3 (0.296648f, 0.296648f, 0.296648f);
	pearl.shininess = 0.088 * 128;

	ruby.ambient = vec3 (0.1745f, 0.01175f, 0.01175f);
	ruby.diffuse = vec3 (0.61424f, 0.04136f, 0.04136f);
	ruby.specular = vec3 (0.727811f, 0.626959f, 0.626959f);
	ruby.shininess = 0.6 * 128;

	turquoise.ambient = vec3 (0.1f, 0.18725f, 0.1745f);
	turquoise.diffuse = vec3 (0.396f, 0.74151f, 0.69102f);
	turquoise.specular = vec3 (0.297254f, 0.30829f, 0.306678f);
	turquoise.shininess = 0.1 * 128;
	
	brass.ambient = vec3 (0.329412f, 0.223529f, 0.027451f);
	brass.diffuse = vec3 (0.780392f, 0.568627f, 0.113725f);
	brass.specular = vec3 (0.992157f, 0.941176f, 0.807843f);
	brass.shininess = 0.21794872 * 128;

	bronze.ambient = vec3 (0.2125f, 0.1275f, 0.054f);
	bronze.diffuse = vec3 (0.714f, 0.4284f, 0.18144f);
	bronze.specular = vec3 (0.393548f, 0.271906f, 0.166721f);
	bronze.shininess = 0.2 * 128;

	chrome.ambient = vec3 (0.25f, 0.25f, 0.25f);
	chrome.diffuse = vec3 (0.4f, 0.4f, 0.4f);
	chrome.specular = vec3 (0.774597f, 0.774597f, 0.774597f);
	chrome.shininess = 0.6 * 128;

	copper.ambient = vec3 (0.19125f, 0.0735f, 0.0225f);
	copper.diffuse = vec3 (0.7038f, 0.27048f, 0.0828f);
	copper.specular = vec3 (0.256777f, 0.137622f, 0.086014f);
	copper.shininess = 0.1 * 128;

	silver.ambient = vec3 (0.19225f, 0.19225f, 0.19225f);
	silver.diffuse = vec3 (0.50754f, 0.50754f, 0.50754f);
	silver.specular = vec3 (0.508273f, 0.508273f, 0.508273f);
	silver.shininess = 0.4 * 128;

	black_plastic.ambient = vec3 (0.0f, 0.0f, 0.0f);
	black_plastic.diffuse = vec3 (0.01f, 0.01f, 0.01f);
	black_plastic.specular = vec3 (0.50f, 0.50f, 0.50f);
	black_plastic.shininess = 0.25 * 128;

	cyan_plastic.ambient = vec3 (0.0f, 0.1f, 0.06f);
	cyan_plastic.diffuse = vec3 (0.0f, 0.50980392f, 0.50980392f);
	cyan_plastic.specular = vec3 (0.50196078f, 0.50196078f, 0.50196078f);
	cyan_plastic.shininess = 0.25 * 128;

	green_plastic.ambient = vec3 (0.0f, 0.0f, 0.0f);
	green_plastic.diffuse = vec3 (0.1f, 0.35f, 0.1f);
	green_plastic.specular = vec3 (0.45f, 0.55f, 0.45f);
	green_plastic.shininess = 0.25 * 128;
	
	red_plastic.ambient = vec3 (0.0f, 0.0f, 0.0f);
	red_plastic.diffuse = vec3 (0.5f, 0.0f, 0.0f);
	red_plastic.specular = vec3 (0.7f, 0.6f, 0.6f);
	red_plastic.shininess = 0.25 * 128;

	white_plastic.ambient = vec3 (0.0f, 0.0f, 0.0f);
	white_plastic.diffuse = vec3 (0.55f, 0.55f, 0.55f);
	white_plastic.specular = vec3 (0.70f, 0.70f, 0.70f);
	white_plastic.shininess = 0.25 * 128;

	yellow_plastic.ambient = vec3 (0.0f, 0.1f, 0.06f);
	yellow_plastic.diffuse = vec3 (0.5f, 0.5f, 0.0f);
	yellow_plastic.specular = vec3 (0.60f, 0.60f, 0.50f);
	yellow_plastic.shininess = 0.25 * 128;

	black_rubber.ambient = vec3 (0.02f, 0.02f, 0.02f);
	black_rubber.diffuse = vec3 (0.01f, 0.01f, 0.01f);
	black_rubber.specular = vec3 (0.4f, 0.4f, 0.4f);
	black_rubber.shininess = 0.078125f * 128;

	cyan_rubber.ambient = vec3 (0.0f, 0.05f, 0.05f);
	cyan_rubber.diffuse = vec3 (0.4f, 0.5f, 0.5f);
	cyan_rubber.specular = vec3 (0.04f, 0.7f, 0.7f);
	cyan_rubber.shininess = 0.078125 * 128;

	green_rubber.ambient = vec3 (0.0f, 0.05f, 0.0f);
	green_rubber.diffuse = vec3 (0.4f, 0.5f, 0.4f);
	green_rubber.specular = vec3 (0.04f, 0.7f, 0.04f);
	green_rubber.shininess = 0.078125f * 128;

	red_rubber.ambient = vec3 (0.05f, 0.0f, 0.0f);
	red_rubber.diffuse = vec3 (0.5f, 0.4f, 0.4f);
	red_rubber.specular = vec3 (0.7f, 0.04f, 0.04f);
	red_rubber.shininess = 0.078125 * 128;

	white_rubber.ambient = vec3 (0.05f, 0.05f, 0.05f);
	white_rubber.diffuse = vec3 (0.5f, 0.5f, 0.5f);
	white_rubber.specular = vec3 (0.078125, 0.50196078f, 0.50196078f);
	white_rubber.shininess = 0.25 * 128;

	yellow_rubber.ambient = vec3 (0.05f, 0.05f, 0.0f);
	yellow_rubber.diffuse = vec3 (0.5f, 0.5f, 0.4f);
	yellow_rubber.specular = vec3 (0.7f, 0.7f, 0.04f);
	yellow_rubber.shininess = 0.078125 * 128;
}