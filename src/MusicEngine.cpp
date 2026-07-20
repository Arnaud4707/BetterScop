#include "../include/MusicEngine.hpp"

MusicEngine::MusicEngine(std::string fbass, std::string fdrums, std::string fguitar, std::string fpiano, std::string fother, std::string fvocals,
						 std::string mbass, std::string mdrums, std::string mguitar, std::string mpiano, std::string mother, std::string mvocals)
{

	bass_fft = FFT (fbass);
	drums_fft = FFT (fdrums);
	guitar_fft = FFT (fguitar);
	piano_fft = FFT (fpiano);
	other_fft = FFT (fother);
	vocals_fft = FFT (fvocals);

	bass_midi = Midi (mbass);
	drums_midi = Midi (mdrums);
	guitar_midi = Midi (mguitar);
	piano_midi = Midi (mpiano);
	other_midi = Midi (mother);
	vocals_midi = Midi (mvocals);

}

MusicState MusicEngine::update(float time)
{
	MusicState	result;

	result.bass = fillInstrument(&bass_fft, &bass_midi, lastTime, time);
	result.drums = fillInstrument(&drums_fft, &drums_midi, lastTime, time);
	result.guitar = fillInstrument(&guitar_fft, &guitar_midi, lastTime, time);
	result.piano = fillInstrument(&piano_fft, &piano_midi, lastTime, time);
	result.other = fillInstrument(&other_fft, &other_midi, lastTime, time);
	result.vocals = fillInstrument(&vocals_fft, &vocals_midi, lastTime, time);
	
	result.global();
	lastTime = time;
	return(result);
}

InstrumentState	MusicEngine::fillInstrument(FFT* fft, Midi* midi, float lastTime, float currentTime)
{
	InstrumentState result;

	for (size_t it = fft->getIndex(); it < fft->getFFT().size(); it++){
		DataAudio dit = fft->getFFT()[it];
		if (dit.getTime() >= lastTime && dit.getTime() <= currentTime)
		{
			result.dataAudio(dit);
			fft->setIterator(it + 1);
			break;
		}
	}

	for (size_t it = midi->getIndex(); it < midi->getNotes().size(); it++){
		Note dit = midi->getNotes()[it];
		if (dit.getStart() <= currentTime && dit.getEnd() >= currentTime)
		{
			result.noteActive(dit, lastTime, currentTime);
			midi->setIterator(it + 1);
			break;
		}
		else if (dit.getEnd() >= lastTime)
		{
			result.noteNoActive(dit, lastTime, currentTime);
			break;
		}
	}
	return (result);
}