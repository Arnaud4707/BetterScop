#ifndef FFT_HPP
#define FFT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <cmath>
#include "DataAudio.hpp"
#include "AudioStats.hpp"
#include <limits>

class FFT
{
	private:
		std::vector<DataAudio> fft;
		size_t index;

	public:
		AudioStats stats;
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

};

#endif