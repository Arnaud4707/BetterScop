#ifndef FFT_HPP
#define FFT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "DataAudio.hpp"

class FFT
{
private:
	std::vector<DataAudio> fft;

public:
	FFT(std::string text);
	~FFT();

	const std::vector<DataAudio> getFFT() const {
		return (fft);
	};
};

#endif