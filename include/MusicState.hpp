#ifndef MUSICSTATE_HPP
#define MUSICSTATE_HPP

#include <iostream>
#include "../include/DataAudio.hpp"

struct InstrumentState
{
	// audio
	float rms;
	float rmsDelta;
	float bass;
	float mid;
	float high;
	float centroid;
	float zcr;

	// midi
	bool active;
	bool noteOn;
	bool noteOff;
	int pitch;
	int velocity;

	// animation
	float attackThreshold;
	float pulse;
	float energy;
	float brightness;
	float movement;

	InstrumentState()
	{
		rms = 0.f;
		rmsDelta = 0.f;
		bass = 0.f;
		mid = 0.f;
		high = 0.f;
		centroid = 0.f;

		active = false;
		noteOn = false;
		noteOff = false;
		pitch = 0;
		velocity = 0;

		pulse = 0.f;
		attackThreshold = 0.f;
		energy = 0.f;
		brightness = 0.f;
		movement = 0.f;
	};

	InstrumentState(const InstrumentState &obj) = default;

	InstrumentState &operator=(const InstrumentState &obj) = default;

	void dataAudio(const DataAudio &obj)
	{
		rms = obj.getRms();
		centroid = obj.getCentroid();
		zcr = obj.getZcr();
		bass = obj.getBass();
		mid = obj.getMid();
		high = obj.getHight();
		energy = 0.6f * rms + 0.3f * bass + 0.1f * mid;
	};

	void noteActive(const Note &obj, float lastTime, float currentTime)
	{
		active = true;
		pitch = obj.getPitch();
		velocity = obj.getVelocity();
		if (lastTime < obj.getStart() && currentTime >= obj.getStart())
		{
			noteOff = false;
			noteOn = true;
		}
	};

	void noteNoActive(const Note &obj, float lastTime, float currentTime)
	{
		active = false;
		pitch = obj.getPitch();
		velocity = obj.getVelocity();
		if (lastTime < obj.getEnd() && currentTime >= obj.getEnd())
		{
			noteOn = false;
			noteOff = true;
		}
	};
};

struct MusicState
{
	InstrumentState drums;
	InstrumentState bass;
	InstrumentState piano;
	InstrumentState guitar;
	InstrumentState vocals;
	InstrumentState other;

	float globalEnergy;
	float beat;
	float brightness;

	bool kick;
	bool snare;
	bool hihat;

	void fillGlobalEnergy()
	{
		globalEnergy += drums.energy;
		globalEnergy += bass.energy;
		globalEnergy += guitar.energy;
		globalEnergy += piano.energy;
		globalEnergy += other.energy;
		globalEnergy += vocals.energy;
		globalEnergy /= 6;
	};
};
#endif