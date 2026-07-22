#ifndef ANIMATIONENGINE_HPP
#define ANIMATIONENGINE_HPP

#include "AnimationState.hpp"
#include "MusicState.hpp"

class AnimationEngine
{
	private:
		AnimationState state;

	public:
		AnimationState update(const MusicState &music, float dt){
			(void)dt;
			state.objectScale = 1.f + music.globalEnergy / 8;
			// state.objectScale = 1.f + (0.30f * music.drums.pulse) / 2  + (0.15f * music.bass.pulse) / 2;
			// state.objectScale = 1.f + 0.25f * music.bass.pulse + 0.15f * music.drums.pulse;
			// state.rotationSpeed = 0.3f + music.piano.movement * 2.f;
			state.rotationSpeed = 0.3f + music.piano.movement + 0.5f * music.guitar.energy;
			// state.rotation += dt * state.rotationSpeed;

			// state.color.x = music.brightness;
			// state.color.y = 0.2f;
			// state.color.z = 1.f - music.brightness;

			// state.color.x = music.brightness;
			// state.color.y = 1;
			// state.color.z = music.globalEnergy;

			// state.color = vec3(music.bass.energy,music.piano.energy,music.vocals.brightness);
			
			state.color.x = music.drums.bass;
			state.color.y = music.guitar.mid;
			state.color.z = music.vocals.high;
			
			state.glow = 0.6f * music.vocals.energy + 0.4f * music.other.energy;
			
			if(music.kick)
			    state.bloom += 0.5f;
			if(music.snare)
			    state.bloom += 0.3f;
			state.bloom *= 0.95f;

			state.distortion = music.guitar.movement * 0.4f;
			
			if(music.kick)
    			state.cameraShake = 1.f;
			state.cameraShake *= 0.92f;
			
			state.cameraZoom = 1.f - 0.1f * music.beat;

			if(music.hihat)
				state.particleRate += 30;

			state.particleRate *= 0.98f;
			return (state);
		};

};

#endif