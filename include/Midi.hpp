#ifndef MIDI_HPP
#define MIDI_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Note.hpp"

class Midi
{
private:
	std::vector<Note> notes;

public:
	Midi(std::string text);
	~Midi();

	const std::vector<Note>& getNotes() const {
		return (notes);
	}
};

#endif