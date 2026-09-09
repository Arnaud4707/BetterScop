#ifndef NORMALIZEPEAK_HPP
#define NORMALIZEPEAK_HPP

class NormalizePeak
{
public:
	float peakGlobalEnergie = 1.f;
	float decay = 0.995f;

	NormalizePeak(){};
	float normalizeGlobalEnergie(float value) {
        value = std::abs(value);
		if (value > peakGlobalEnergie)
            peakGlobalEnergie = value;
        else
            peakGlobalEnergie *= decay; 

        if (peakGlobalEnergie < 0.001f)
            peakGlobalEnergie = 0.001f;

        return clamp(value / peakGlobalEnergie, 0.0f, 1.0f);
	};
	~NormalizePeak(){};
};

#endif