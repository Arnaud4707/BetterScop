#ifndef MUSICANALYZER
#define MUSICANALYZER

#include "MusicEngine.hpp"

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
};

class MusicAnalyzer
{
	private:
		std::array<const AudioStats*, 6> stats;
		std::array<AnalyzerState, 6> history;

	public:
		MusicAnalyzer(){};
		MusicAnalyzer(std::array<const AudioStats*, 6> obj) : stats(obj) {};
		void update(InstrumentState &state, int index);

		void updateGlobal(MusicState& state);

		float normalizedRms(float nb, int index)
		{
			return 2.f * ((nb - stats[index]->minRms) / (stats[index]->maxRms - stats[index]->minRms)) - 1.f;
		};
		float normalizedCentroïd(float nb, int index)
		{
			return 2.f * ((nb - stats[index]->minCentroid) / (stats[index]->maxCentroid - stats[index]->minCentroid)) - 1.f;
		};
		float normalizedBass(float nb, int index)
		{
			return 2.f * ((nb - stats[index]->minBass) / (stats[index]->maxBass - stats[index]->minBass)) - 1.f;
		};
		float normalizedMid(float nb, int index)
		{
			return 2.f * ((nb - stats[index]->minMid) / (stats[index]->maxMid - stats[index]->minMid)) - 1.f;
		};
		float normalizedHigh(float nb, int index)
		{
			return 2.f * ((nb - stats[index]->minHigh) / (stats[index]->maxHigh - stats[index]->minHigh)) - 1.f;
		};
};

#endif