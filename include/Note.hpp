#ifndef NOTE_HPP
#define NOTE_HPP

#include <iostream>
#include <string>

class Note
{
private:
	int instrument;
	int pitch;
	float start;
	float end;
	float velocity;

public:
	Note(){};
	Note(int ist, int pt, float st, float nd, int velos){
		instrument = ist;
		pitch = pt;
		start = st;
		end = nd;
		velocity = velos;
	};
	~Note(){};

	const int &getInstrument() const
	{
		return (this->instrument);
	};
	const int &getPitch() const
	{
		return (this->pitch);
	};
	const float &getStart() const
	{
		return (this->start);
	};
	const float &getEnd() const
	{
		return (this->end);
	};
	const float &getVelocity() const
	{
		return (this->velocity);
	};
};

#endif