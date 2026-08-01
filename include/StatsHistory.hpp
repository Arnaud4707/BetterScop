#ifndef STATSHISTORY_HPP
#define STATSHISTORY_HPP

#include "History.hpp"
#include "MusicState.hpp"

struct StatsHistory
{
	History drums;
	History bass;
	History guitar;
	History piano;
	History vocals;
	History other;
	std::deque<float> globalEnergy;

	StatsHistory push(MusicState &stats)
	{
		drums.push(stats.drums.rms, stats.drums.energy, stats.drums.bass, stats.drums.mid, stats.drums.high);
		bass.push(stats.bass.rms, stats.bass.energy, stats.bass.bass, stats.bass.mid, stats.bass.high);
		guitar.push(stats.guitar.rms, stats.guitar.energy, stats.guitar.bass, stats.guitar.mid, stats.guitar.high);
		piano.push(stats.piano.rms, stats.piano.energy, stats.piano.bass, stats.piano.mid, stats.piano.high);
		other.push(stats.other.rms, stats.other.energy, stats.other.bass, stats.other.mid, stats.other.high);
		vocals.push(stats.vocals.rms, stats.vocals.energy, stats.vocals.bass, stats.vocals.mid, stats.vocals.high);
		globalEnergy.push_back(stats.globalEnergy);
		return (*this);
	};
};

#endif