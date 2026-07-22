#include "../include/MusicAnalyzer.hpp"

void MusicAnalyzer::update(InstrumentState &state, int index)
{
	history[index].threshold = stats[index]->minRms + 0.75f * (stats[index]->maxRms - stats[index]->minRms);

	state.rmsDelta = state.rms - history[index].lastRms;
	state.attackThreshold = 0.15f * (stats[index]->maxRms - stats[index]->minRms);

	if (state.noteOn)
		state.pulse = 1.f;
	else
		state.pulse *= 0.90f;

	state.movement =  abs(state.bass - history[index].lastBass) + abs(state.mid - history[index].lastMid) + abs(state.high - history[index].lastHigh);

	state.brightness = 0.7f * normalizedCentroïd(state.centroid, index) + 0.3f * normalizedHigh(state.high, index);

	history[index].lastRms = state.rms;
	history[index].lastCentroid = state.centroid;
	history[index].lastBass = state.bass;
	history[index].lastMid = state.mid;
	history[index].lastHigh = state.high;
}

void	MusicAnalyzer::updateGlobal(MusicState& state)
{
	state.brightness =
		(
		    state.drums.brightness +
		    state.bass.brightness +
		    state.guitar.brightness +
		    state.piano.brightness +
		    state.vocals.brightness +
		    state.other.brightness
		) / 6.f;

	if (state.drums.rmsDelta > state.drums.attackThreshold)
		state.beat = 1.f;
	else
		state.beat *= 0.9f;

	state.kick = state.drums.bass > 0.75f && state.drums.high < 0.30f
		&& state.drums.rmsDelta > state.drums.attackThreshold;

	state.snare = state.drums.mid > 0.60f && state.drums.rmsDelta > state.drums.attackThreshold;
	// state.snare = state.drums.centroid > 0.60f && state.drums.rmsDelta > state.drums.attackThreshold;
	state.hihat = state.drums.high > 0.7f && state.drums.zcr > 0.8f;
	// state.hihat = state.drums.high > 0.75f && state.drums.centroid > 0.80f;
};
