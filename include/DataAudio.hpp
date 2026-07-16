#ifndef DATAAUDIO_HPP
#define DATAAUDIO_HPP

#include <iostream>
#include <string>

class DataAudio
{
private:
	float time;
	float rms;
	float centroid;
	float rolloff;
	float zcr;
	float bass;
	float mid;
	float high;

public:
	DataAudio() {};
	DataAudio(float dtime, float drms, float dcentroid, float drolloff, float dzcr, float dbass, float dmid, float dhight)
	{
		time = dtime;
		rms = drms;
		centroid = dcentroid;
		rolloff = drolloff;
		zcr = dzcr;
		bass = dbass;
		mid = dmid;
		high = dhight;
	};
	~DataAudio() {};

	const float &getTime() const
	{
		return (this->time);
	};
	const float &getRms() const
	{
		return (this->rms);
	};
	const float &getCentroid() const
	{
		return (this->centroid);
	};
	const float &getrolloff() const
	{
		return (this->rolloff);
	};
	const float &getZcr() const
	{
		return (this->zcr);
	};
	const float &getBass() const
	{
		return (this->bass);
	};
	const float &getMid() const
	{
		return (this->mid);
	};
	const float &getHight() const
	{
		return (this->high);
	};
};

#endif