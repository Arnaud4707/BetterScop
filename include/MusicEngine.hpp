#ifndef MUSICENGINE_HPP
#define MUSICENGINE_HPP

#include "FFT.hpp"
#include "Midi.hpp"
#include "MusicState.hpp"

class MusicEngine
{
	private:
		float	lastTime = 0.f;

	public:
		FFT		bass_fft;
		FFT		drums_fft;
		FFT		guitar_fft;
		FFT		piano_fft;
		FFT		other_fft;
		FFT		vocals_fft;

		Midi	bass_midi;
		Midi	drums_midi;
		Midi	guitar_midi;
		Midi	piano_midi;
		Midi	other_midi;
		Midi	vocals_midi;

		MusicEngine(std::string fbass, std::string fdrums, std::string fguitar, std::string fpiano, std::string fother, std::string fvocals,
					std::string mbass, std::string mdrums, std::string mguitar, std::string mpiano, std::string mother, std::string mvocals);
		MusicEngine(const MusicEngine& obj) = default;
		MusicEngine& operator=(const MusicEngine& obj) = default;
		~MusicEngine() = default;

		MusicState	update(float time);
		InstrumentState		fillInstrument(FFT* fft, Midi* midi, float lastTime, float currentTime);
	
};

#endif