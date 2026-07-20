#ifndef FFT_HPP
#define FFT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "DataAudio.hpp"
#include <limits>

class FFT
{
private:
	std::vector<DataAudio> fft;

	float minRms, maxRms;
	float minCentroid, maxCentroid;
	float minBass, maxBass;
	float minMid, maxMid;
	float minHigh, maxHigh;

	size_t index;

public:
	FFT() {};
	FFT(std::string text);
	FFT(const FFT& obj) = default;
	FFT& operator=(const FFT& obj) = default;
	~FFT() = default;

	const std::vector<DataAudio>& getFFT() const {
		return (fft);
	};

	void setIterator(size_t it) {
		index = it;
	};

	size_t getIndex() const {
		return (index);
	};

	float	normalizedCentroïd(float nb){
		return 2.f * ((nb - minCentroid) / (maxCentroid - minCentroid)) - 1.f;
	};
};

#endif