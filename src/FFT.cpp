#include "../include/fft/FFT.hpp"

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
		if (!f.empty())
			dbass = std::stof(f);
	}
	if (std::getline(ss, g, ','))
	{
		if (!g.empty())
			dmid = std::stof(g);
	}
	if (std::getline(ss, h, ','))
	{
		if (!h.empty())
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
		float cbass, cmid, chigh, crms, ccentroid;

		try
		{
			parseFaceToken(line, time, rms, centroid, rolloff, zcr, bass, mid, high);
			if (bass < 0 || mid < 0 || high < 0 || rms < 0)
    			continue;
			cbass = std::log1p(bass);
			cmid = std::log1p(mid);
			chigh = std::log1p(high);
			crms = std::log1p(rms);
			ccentroid = std::log1p(centroid);
			stats.minRms = std::min(stats.minRms, crms);
			stats.maxRms = std::max(stats.maxRms, crms);
			stats.minCentroid = std::min(stats.minCentroid, ccentroid);
			stats.maxCentroid = std::max(stats.maxCentroid, ccentroid);
			stats.minBass = std::min(stats.minBass, cbass);
			stats.maxBass = std::max(stats.maxBass, cbass);
			stats.minMid = std::min(stats.minMid, cmid);
			stats.maxMid = std::max(stats.maxMid, cmid);
			stats.minHigh = std::min(stats.minHigh, chigh);
			stats.maxHigh = std::max(stats.maxHigh, chigh);

			DataAudio dfft(time, crms, ccentroid, rolloff, zcr, cbass, cmid, chigh);
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
