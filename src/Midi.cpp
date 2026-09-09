#include "../include/midi/Midi.hpp"

void parseFaceToken(const std::string &token, int &dinstrument, int &dnote, float &dstart, float &dend, int &dvelocity)
{
	std::stringstream ss(token);
	std::string a, b, c, d, e;

	dinstrument = dnote = dvelocity = -1; // Valeurs par défaut si absent
	dstart = dend = -1.0f;

	if (std::getline(ss, a, ','))
	{
		if (!a.empty())
			dinstrument = std::stoi(a);
	}
	if (std::getline(ss, b, ','))
	{
		if (!b.empty())
			dnote = std::stoi(b);
	}
	if (std::getline(ss, c, ','))
	{
		if (!c.empty())
			dstart = std::stof(c);
	}
	if (std::getline(ss, d, ','))
	{
		if (!d.empty())
			dend = std::stof(d);
	}
	if (std::getline(ss, e, ','))
	{
		if (!e.empty())
			dvelocity = std::stoi(e);
	}
}

Midi::Midi(std::string text)
{
	std::ifstream file(text);
	std::string line;

	std::getline(file, line);
	while (std::getline(file, line))
	{
		int instru;
		int nt;
		float st;
		float nd;
		int velos;
		try
		{
			parseFaceToken(line, instru, nt, st, nd, velos);

			Note dnote(instru, nt, st, nd, velos);
			notes.push_back(dnote);
		}
		catch (const std::exception &e)
		{
			// Évite le crash si le fichier .csv a un format de ligne corrompu
			std::cerr << "Erreur lors du parsing d'un fichier csv coté midi : " << e.what() << "\n";
		}
	}
	index = 0;
}