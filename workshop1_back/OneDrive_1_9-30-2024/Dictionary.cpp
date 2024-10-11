#include "Dictionary.h"

PartOfSpeech stringToPOS(const std::string& posStr) {
	if (posStr == "n." || posStr == "n. pl.") return PartOfSpeech::Noun;
	else if (posStr == "adv.") return PartOfSpeech::Adverb;
	else if (posStr == "a.") return PartOfSpeech::Adjective;
	else if (posStr == "v." || posStr == "v. i." || posStr == "v. t." || posStr == "v. t. & i.") return PartOfSpeech::Verb;
	else if (posStr == "prep.") return PartOfSpeech::Preposition;
	else if (posStr == "pron.") return PartOfSpeech::Pronoun;
	else if (posStr == "conj.") return PartOfSpeech::Conjunction;
	else if (posStr == "interj.") return PartOfSpeech::Interjection;
	else return PartOfSpeech::Unknown;
}

Dictionary::Dictionary():words(nullptr), amountWords(0)
{
}

Dictionary::~Dictionary() 
{
	delete[] words;
}

Dictionary::Dictionary(const char* filename)
{
	std::ifstream dic_file(filename);

	if (!dic_file) 
	{
		words = nullptr;
		amountWords = 0;
		return;
	}

	std::string buffer;
	int count = 0; 

	while (std::getline(dic_file, buffer)) count++;
	amountWords = count;
	words = new Word[amountWords];
	dic_file.clear();
	dic_file.seekg(0);

	int index = 0; 
	while (std::getline(dic_file, buffer) && index < amountWords) 
	{
		std::istringstream string_buff(buffer);
		std::string word, pos, definition;

		if (!(string_buff >> word >> pos)) continue;

		std::getline(string_buff, definition);

		words[index].m_word = word; 
		words[index].m_definition = definition;
		words[index].m_pos = stringToPOS(pos);

		index++;
	}

}




void Dictionary::searchWord(const char* word) const {
	std::string searchWord(word);
	bool found = false;

	for (int i = 0; i < amountWords; ++i) {
		if (words[i].m_word == searchWord) {
			if (!found) {
				std::cout << words[i].m_word << " - ";
				if (words[i].m_pos != PartOfSpeech::Unknown) {
					std::cout << "(" << static_cast<int>(words[i].m_pos) << ") "; 
				}
				std::cout << words[i].m_definition << std::endl;
				found = true;
			}
			else {
				std::cout << "     - ";
				if (words[i].m_pos != PartOfSpeech::Unknown) {
					std::cout << "(" << static_cast<int>(words[i].m_pos) << ") ";
				}
				std::cout << words[i].m_definition << std::endl;
			}
		}
	}

	if (!found) {
		std::cout << "Word '" << searchWord << "' was not found in the dictionary." << std::endl;
	}
}

