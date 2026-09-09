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
		std::vector<Note>	notes;
		size_t 				index;
	public:
		Midi() {};
		Midi(std::string text);
		Midi(const Midi& obj) = default;
		Midi &operator=(const Midi& obj) = default;
		~Midi() = default;
		
		const std::vector<Note>& getNotes() const {
			return (notes);
		};
		void setIterator(size_t it) {
			index = it;
		};
		size_t getIndex() const {
			return (index);
		};
};

#endif