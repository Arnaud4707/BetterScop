#include "../include/FFT.hpp"

void parseFaceToken(const std::string &token, float &dtime, float &drms, float &dcentroid, float &drolloff, float &dzcr, float &dbass, float &dmid, float &dhight)
{
	std::stringstream ss(token);
	std::string a, b, c, d, e, f, g, h;

	dtime = drms = dcentroid = drolloff = dzcr = dbass = dmid = dhight = -1.0f;

	if (std::getline(ss, a, ','))
	{
		if (!a.empty())
			dtime = std::stof(a);
	}
	if (std::getline(ss, b, ','))
	{
		if (!b.empty())
			drms = std::stof(b);
	}
	if (std::getline(ss, c, ','))
	{
		if (!c.empty())
			dcentroid = std::stof(c);
	}
	if (std::getline(ss, d, ','))
	{
		if (!d.empty())
			drolloff = std::stof(d);
	}
	if (std::getline(ss, e, ','))
	{
		if (!e.empty())
			dzcr = std::stof(e);
	}
	if (std::getline(ss, f, ','))
	{
		if (!e.empty())
			dbass = std::stof(f);
	}
	if (std::getline(ss, g, ','))
	{
		if (!e.empty())
			dmid = std::stof(g);
	}
	if (std::getline(ss, h, ','))
	{
		if (!e.empty())
			dhight = std::stof(h);
	}
}

FFT::FFT(std::string text)
{
	std::ifstream file(text);
	std::string line;

	minRms = minCentroid = minBass = minMid = minHigh = std::numeric_limits<float>::max();
	maxRms = maxCentroid = maxBass = maxMid = maxHigh = std::numeric_limits<float>::lowest();

	std::getline(file, line);
	while (std::getline(file, line))
	{
		float time, rms, centroid, rolloff, zcr, bass, mid, high;
		try
		{
			parseFaceToken(line, time, rms, centroid, rolloff, zcr, bass, mid, high);
			minRms = std::min(minRms, rms);
			maxRms = std::max(maxRms, rms);
			minCentroid = std::min(minCentroid, centroid);
			maxCentroid = std::max(maxCentroid, centroid);
			minBass = std::min(minBass, bass);
			maxBass = std::max(maxBass, bass);
			minMid = std::min(minMid, mid);
			maxMid = std::max(maxMid, mid);
			minHigh = std::min(minHigh, high);
			maxHigh = std::max(maxHigh, high);

			DataAudio dfft(time, rms, centroid, rolloff, zcr, bass, mid, high);
			fft.push_back(dfft);
		}
		catch (const std::exception &e)
		{
			// Évite le crash si le fichier .csv a un format de ligne corrompu
			std::cerr << "Erreur lors du parsing d'un fichier csv coté fft : " << e.what() << "\n";
		}
	}
	index = 0;
}
