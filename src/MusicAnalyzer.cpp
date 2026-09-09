#include "../include/musicEngine/MusicAnalyzer.hpp"

void MusicAnalyzer::update(InstrumentState &state, int index)
{
	history[index].threshold = stats[index]->minRms + 0.75f * (stats[index]->maxRms - stats[index]->minRms);

	// std::cout
	// << " index: " << "raw bass = " << state.bass
	// << " index: " << "raw mid = " << state.mid
	// << " index: " << "raw high = " << state.high
	// << " index: " << "raw rms = " << state.rms
	// << " index: " << "raw centroid = " << state.centroid
	// << std::endl;
	state.bass = normalizedBass01(state.bass, index);
	state.mid = normalizedMid01(state.mid, index);
	state.high = normalizedHigh01(state.high, index);
	state.rms = normalizedRms01(state.rms, index);
	state.centroid = normalizedCentroïd01(state.centroid, index);
	state.energy = 0.6f * state.rms + 0.3f * state.bass + 0.1f * state.mid;
	// std::cout
	// << " index: " << index << " bass = " << state.bass
	// << " index: " << index << " mid = " << state.mid
	// << " index: " << index << " high = " << state.high
	// << " index: " << index << " rms = " << state.rms
	// << " index: " << index << " centroid = " << state.centroid
	// << std::endl;
	state.rmsDelta = state.rms - history[index].lastRms;
	state.attackThreshold = 0.15f;

	history[index].avgAttack = 0.98f * history[index].avgAttack + 0.02f * fabs(state.rmsDelta);

	if (state.noteOn)
		state.pulse = 1.f;
	else
		state.pulse *= 0.90f;

	state.movement =  fabs(state.bass - history[index].lastBass) + fabs(state.mid - history[index].lastMid) + fabs(state.high - history[index].lastHigh);

	state.brightness = 0.7f * state.centroid + 0.3f * state.high;
}

void	MusicAnalyzer::updateHistory(InstrumentState &state, int index)
{
	history[index].lastRms = state.rms;
	history[index].lastCentroid = state.centroid;
	history[index].lastBass = state.bass;
	history[index].lastMid = state.mid;
	history[index].lastHigh = state.high;
}

static inline void color(MusicState& state)
{
	float low = state.drums.bass + state.bass.bass;
	float mid = state.guitar.mid + state.piano.mid + state.vocals.mid;
	float high = state.other.high + state.drums.high + state.vocals.high;
	float total = low + mid + high + 1e-6f;

	state.global.low = low / total;
	state.global.mid = mid / total;
	state.global.high = high / total;
}
void fillGlobal(MusicState& state)
{
	state.global.energy =
	(
		state.drums.energy
		+ state.bass.energy
		+ state.guitar.energy
		+ state.piano.energy
		+ state.other.energy
		+ state.vocals.energy
	) / 6.f;

	state.global.brightness =
		(
		    state.drums.brightness +
		    state.bass.brightness +
		    state.guitar.brightness +
		    state.piano.brightness +
		    state.vocals.brightness +
		    state.other.brightness
		) / 6.f;

	state.global.movement =
		(
		    state.drums.movement +
		    state.bass.movement +
		    state.guitar.movement +
		    state.piano.movement +
		    state.other.movement +
		    state.vocals.movement
		) / 6.f;
};

void	MusicAnalyzer::updateGlobal(MusicState& state)
{
	fillGlobal(state);

	AnalyzerState &drums = history[DRUMS];

	float kickEnergy = 0.6f * state.drums.bass + 0.4f * state.drums.rms;

	drums.avgKickEnergy = 0.95f * drums.avgKickEnergy + 0.05f * kickEnergy;

	float delta = kickEnergy - drums.avgKickEnergy;
	drums.avgDelta = 0.98f * drums.avgDelta + 0.02f * fabs(delta);

	if (delta > drums.avgDelta * 2.f)
    	beat = 1.f;
	else
		beat *= 0.9f;

	state.global.beat = beat;


	state.kick =
		state.drums.bass > 0.75f &&
		state.drums.high < 0.30f &&
		state.drums.rmsDelta > history[DRUMS].avgAttack * 2.f &&
		state.drums.centroid < 0.35f;

	state.snare =
		state.drums.mid > 0.55 &&
		state.drums.high > 0.35 &&
		state.drums.bass < 0.60 &&
		state.drums.rmsDelta > history[DRUMS].avgAttack * 2.f;
	
	// state.snare = state.drums.centroid > 0.60f && state.drums.rmsDelta > state.drums.attackThreshold;
	state.hihat = state.drums.high > 0.7f && state.drums.zcr > 0.8f;
	// state.hihat = state.drums.high > 0.75f && state.drums.centroid > 0.80f;

	if (state.kick)
		state.kickPulse = 1.f;
	else
		state.kickPulse *= 0.9f;
	if (state.snare)
		state.snarePulse = 1.f;
	else
		state.snarePulse *= 0.9f;
	if (state.hihat)
		state.hihatPulse = 1.f;
	else
		state.hihatPulse *= 0.9;

	// std::cout
	// << " state.kickPulse: " << state.kickPulse
	// << " state.snarePulse: " << state.snarePulse
	// << " state.hihatPulse: " << state.hihatPulse
	// << " state.global.intensity: " << state.global.intensity
	// << "minBass = " << stats[DRUMS]->minBass
// << " maxBass = " << stats[DRUMS]->maxBass
	// << std::endl;
	

	color(state);
	state.global.intensity = 0.45f * state.global.energy + 0.35f * state.global.movement + 0.20f * state.global.beat;
};
