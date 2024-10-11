#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

enum class PartOfSpeech
{
	Unknown,
	Noun,
	Pronoun,
	Adjective,
	Adverb,
	Verb,
	Preposition,
	Conjunction,
	Interjection,
};

struct Word
{
	std::string m_word{};
	std::string m_definition{};
	PartOfSpeech m_pos = PartOfSpeech::Unknown;
};

class Dictionary
{
	Word* words;
	int amountWords;

public:
	Dictionary();
	~Dictionary();
	Dictionary(const char* filename);
	void searchWord(const char* word)const;

};

#endif