#pragma once
#include <string>


class Word {

private:
	bool is_valid;
	bool is_complete;
	std::string word;
	std::string exp;

public:
	Word();
	void clear();

	bool get_isvalid() { return is_valid; }
	bool get_iscomplete() { return is_complete; }

	bool operator < (const Word& w) const { return word < w.word; }
	bool operator == (const Word& w) const { return word == w.word; }

	std::string get_word() { return word; }
	std::string get_exp() { return exp; }

	void affix(char c);
	void update(Word w);

};


class Phrase {
	
private:
	Word w1, w2;

public:
	Phrase(Word wv1 = Word(), Word wv2 = Word()) {
		w1 = wv1;
		w2 = wv2;
	}

	bool operator < (const Phrase& ph) const { return w1 < ph.w1 || (w1 == ph.w1 && w2 < ph.w2); }
	bool operator == (const Phrase& ph) const { return w1 == ph.w1 && w2 == ph.w2; }

	Word first() { return w1; }
	Word second() { return w2; }

	void update(Phrase ph) {
		w1.update(ph.w1);
		w2.update(ph.w2);
	}

};