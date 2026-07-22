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

	stats.minRms = stats.minCentroid = stats.minBass = stats.minMid = stats.minHigh = std::numeric_limits<float>::max();
	stats.maxRms = stats.maxCentroid = stats.maxBass = stats.maxMid = stats.maxHigh = std::numeric_limits<float>::lowest();

	std::getline(file, line);
	while (std::getline(file, line))
	{
		float time, rms, centroid, rolloff, zcr, bass, mid, high;
		try
		{
			parseFaceToken(line, time, rms, centroid, rolloff, zcr, bass, mid, high);
			stats.minRms = std::min(stats.minRms, rms);
			stats.maxRms = std::max(stats.maxRms, rms);
			stats.minCentroid = std::min(stats.minCentroid, centroid);
			stats.maxCentroid = std::max(stats.maxCentroid, centroid);
			stats.minBass = std::min(stats.minBass, bass);
			stats.maxBass = std::max(stats.maxBass, bass);
			stats.minMid = std::min(stats.minMid, mid);
			stats.maxMid = std::max(stats.maxMid, mid);
			stats.minHigh = std::min(stats.minHigh, high);
			stats.maxHigh = std::max(stats.maxHigh, high);

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
