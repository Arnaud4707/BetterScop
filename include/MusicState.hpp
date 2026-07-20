#ifndef MUSICSTATE_HPP
#define MUSICSTATE_HPP

#include <iostream>
#include "../include/DataAudio.hpp"

struct InstrumentState
{
	float	time;
	bool 	active;
	int		pitch;
	int 	velocity;
	float 	rms;
	float 	centroid;
	float 	rolloff;
	float 	zcr;
	float 	bass;
	float 	mid;
	float 	high;
	bool 	noteOn;
	bool 	noteOff;

	InstrumentState(){
		time = 0.f;
		active = false;
		pitch = 0;
		velocity = 0;
		rms = 0.f;
		centroid = 0.f;
		rolloff = 0.f;
		zcr = 0.f;
		bass = 0.f;
		mid = 0.f;
		high = 0.f;
		noteOn = false;
		noteOff = false;
	};

	InstrumentState(const InstrumentState& obj) = default;

	InstrumentState& operator=(const InstrumentState& obj) = default;

	void dataAudio(const DataAudio& obj)
	{
		time = obj.getTime();
		rms = obj.getRms();
		centroid = obj.getCentroid();
		rolloff = obj.getrolloff();
		zcr = obj.getZcr();
		bass = obj.getBass();
		mid = obj.getMid();
		high = obj.getHight();
	};

	void noteActive(const Note& obj, float lastTime, float currentTime)
	{
		time = currentTime;
		active = true;
		pitch = obj.getPitch();
		velocity = obj.getVelocity();
		if (lastTime < obj.getStart() && currentTime >= obj.getStart())
		{
			noteOff = false;
			noteOn = true;
		}
	};

	void noteNoActive(const Note& obj, float lastTime, float currentTime)
	{
		time = currentTime;
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

	float globalRMS;
	float globalBass;
	float globalMid;
	float globalHigh;

	void fillGlobalRMS(){
		globalRMS += drums.rms;
		globalRMS += bass.rms;
		globalRMS += guitar.rms;
		globalRMS += piano.rms;
		globalRMS += other.rms;
		globalRMS += vocals.rms;
		globalRMS /= 6;
	};
	
	void fillGlobalBass(){
		globalBass += drums.bass;
		globalBass += bass.bass;
		globalBass += guitar.bass;
		globalBass += piano.bass;
		globalBass += other.bass;
		globalBass += vocals.bass;
		globalBass /= 6;
	};
	
	void fillGlobalMid(){
		globalMid += drums.mid;
		globalMid += bass.mid;
		globalMid += guitar.mid;
		globalMid += piano.mid;
		globalMid += other.mid;
		globalMid += vocals.mid;
		globalMid /= 6;
	};
	
	void fillGlobalHigh(){
		globalHigh += drums.high;
		globalHigh += bass.high;
		globalHigh += guitar.high;
		globalHigh += piano.high;
		globalHigh += other.high;
		globalHigh += vocals.high;
		globalHigh /= 6;
	};

	void global(){
		globalRMS = 0.f;
		globalBass = 0.f;
		globalMid = 0.f;
		globalHigh = 0.f;	
		fillGlobalBass();
		fillGlobalMid();
		fillGlobalHigh();
		fillGlobalRMS();
	}
	
};
#endif