#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <deque>

struct History
{
	std::deque<float> rms;
	std::deque<float> energy;
	std::deque<float> bass;
	std::deque<float> mid;
	std::deque<float> high;

	size_t maxSize = 512;

	//r = rms; e = energy; b = bass; m = mid; h = hight;
	void push(float r, float e, float b, float m, float h)
	{
		rms.push_back(r);
		energy.push_back(e);
		bass.push_back(b);
		mid.push_back(m);
		high.push_back(h);

		if (rms.size() > maxSize)
		{
			rms.pop_front();
			energy.pop_front();
			bass.pop_front();
			mid.pop_front();
			high.pop_front();
		}
	}
};

#endif