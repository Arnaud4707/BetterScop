#ifndef MUSICANALYZER
#define MUSICANALYZER

#include "MusicEngine.hpp"
#include "../fonction_math.hpp"

enum {
	BASS = 0,
	DRUMS = 1,
	GUITAR = 2,
	PIANO = 3,
	OTHER = 4,
	VOCALS = 5
};

struct AnalyzerState
{
	float threshold = 0.f;
    float lastRms = 0.f;
    float lastCentroid = 0.f;
    float lastBass = 0.f;
    float lastMid = 0.f;
    float lastHigh = 0.f;
	float avgKickEnergy = 0.f;
	float avgDelta = 0.f;
	float avgAttack = 0.f;
};

class MusicAnalyzer
{
	private:
		std::array<const AudioStats*, 6> stats;
		std::array<AnalyzerState, 6> history;
		float beat = 0;

	public:
		MusicAnalyzer(){};
		MusicAnalyzer(std::array<const AudioStats*, 6> obj) : stats(obj) {};
		void update(InstrumentState &state, int index);

		void updateGlobal(MusicState& state);
		void updateHistory(InstrumentState &state, int index);

		float normalizedRms(float nb, int index)
		{
			float range = stats[index]->maxRms - stats[index]->minRms;
		    if (range <= 0.f)
		        return 0.f;

		    return 2.f * ((nb - stats[index]->minRms) / range) - 1.f;
		};
		float normalizedRms01(float nb, int index)
		{
			float range = stats[index]->maxRms - stats[index]->minRms;
		    if (range <= 0.f)
		        return 0.f;
    		float value = (nb - stats[index]->minRms) / range;
			return clamp(value, 0.f, 1.f);
		};
		float normalizedCentroïd(float nb, int index)
		{
			float range = stats[index]->maxCentroid - stats[index]->minCentroid;
		    if (range <= 0.f)
		        return 0.f;

		    return 2.f * ((nb - stats[index]->minCentroid) / range) - 1.f;
		};
		float normalizedCentroïd01(float nb, int index)
		{
			float range = stats[index]->maxCentroid - stats[index]->minCentroid;
		    if (range <= 0.f)
		        return 0.f;
    		float value = (nb - stats[index]->minCentroid) / range;
			return clamp(value, 0.f, 1.f);
		};
		float normalizedBass(float nb, int index)
		{
			float range = stats[index]->maxBass - stats[index]->minBass;
		    if (range <= 0.f)
		        return 0.f;

		    return 2.f * ((nb - stats[index]->minBass) / range) - 1.f;
		};
		float normalizedBass01(float nb, int index)
		{
			float range = stats[index]->maxBass - stats[index]->minBass;
		    if (range <= 0.f)
		        return 0.f;
    		float value = (nb - stats[index]->minBass) / range;
			return clamp(value, 0.f, 1.f);
		};
		float normalizedMid(float nb, int index)
		{
			float range = stats[index]->maxMid - stats[index]->minMid;
    		if (range <= 0.f)
    		    return 0.f;

    		return 2.f * ((nb - stats[index]->minMid) / range) - 1.f;
		};
		float normalizedMid01(float nb, int index)
		{
			float range = stats[index]->maxMid - stats[index]->minMid;
		    if (range <= 0.f)
		        return 0.f;
    		float value = (nb - stats[index]->minMid) / range;
			return clamp(value, 0.f, 1.f);
		};
		float normalizedHigh(float nb, int index)
		{
			float range = stats[index]->maxHigh - stats[index]->minHigh;
    		if (range <= 0.f)
    		    return 0.f;

    		return 2.f * ((nb - stats[index]->minHigh) / range) - 1.f;
		};
		float normalizedHigh01(float nb, int index)
		{
			float range = stats[index]->maxHigh - stats[index]->minHigh;
		    if (range <= 0.f)
		        return 0.f;
    		float value = (nb - stats[index]->minHigh) / range;
			return clamp(value, 0.f, 1.f);
		};
};

#endif