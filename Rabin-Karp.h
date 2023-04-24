#pragma once
#include <string>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <fstream>




template <typename T>
class file {
private:
	ifstream file_x, file_y;

public:

	virtual T readFile() = 0;
	ifstream& const getFile_x();
	ifstream& const getFile_y();
	void setFile_x(string fileName);
	void setFile_y(string fileName);
};


template <typename T>
class brute_force :public file<T>
{
private:
	struct index
	{
		int sentence_x, sentence_y, index_x, index_y;
	};

	vector<char> filex, filey;
	vector<index>plagiarised_sentences;
	int threshold;
public:



	brute_force(string xfilename, string yfilename, int t);
	void readFile();
	bool ishamming(string a, string b);
	int brute_check(vector<char> txt2, vector<char> txt);
	vector<char> const getsentence_filex(int i);
	vector<char> const getsentence_filey(int i);
	int const number_of_phrases_filex();
	int const number_of_phrases_filey();
	void push_plagiarized_indexes(int sentencex, int sentencey, int index_x, int index_y);
	index const getIndex(int ind);
	vector<char> const getfilexvector();
	vector<char> const getfileyvector();
	

};


template <typename T>
class RabinKarp : public file<T> {
private:
	int hash;
	int words;
	int mainIndex;
	int corpus1Index;
	int corpus2Index;
	int corpus3Index;
	int mainIndexPrint;
	int corpus1IndexPrint;
	int corpus2IndexPrint;
	int corpus3IndexPrint;

	string mainFile;
	string corpusFile;
	bool isMatch;

	unordered_map<int, string> mainSplit{};
	unordered_map<int, string> mainSplitPrint{};
	unordered_map<int, string> c1Split{};
	unordered_map<int, string> c1SplitPrint{};
	unordered_map<int, string> c2Split{};
	unordered_map<int, string> c2SplitPrint{};
	unordered_map<int, string> c3Split{};
	unordered_map<int, string> c3SplitPrint{};
	unordered_map<string, string> found{};
public:
	RabinKarp();
	virtual string readFile();
	int hashFunction(string str, long long  p, long long x); 
	virtual string removeSpaces(string str, int& i, int words) = 0;
	virtual string calcBound(string str, int& i, int words) = 0;
	void setHash(int x);
	void setWords(int x);
	void setMainIndex(int x);
	void setCorpus1Index(int x);
	void setCorpus2Index(int x);
	void setCorpus3Index(int x);
	void setMainIndexPrint(int x);
	void setCorpus1IndexPrint(int x);
	void setCorpus2IndexPrint(int x);
	void setCorpus3IndexPrint(int x);
	void setMainFile(string mainFile);
	void setCorpusFile(string corpusFile);
	void setMatch(bool match);
	void setMainSplit(int hashValue, string mainFile);
	void setMainSplitPrint(int hashValue, string mainFile);
	void setC1Split(int hashValue, string corpusFile);
	void setC1SplitPrint(int hashValue, string corpusFile);
	void setC2Split(int hashValue, string corpusFile);
	void setC2SplitPrint(int hashValue, string corpusFile);
	void setC3Split(int hashValue, string corpusFile);
	void setC3SplitPrint(int hashValue, string corpusFile);
	void setFound(string corpusFile, string mainFile);

	int const getHash(string str);
	int const getWords();
	int const getMainIndex();
	int const getCorpus1Index();
	int const getCorpus2Index();
	int const getCorpus3Index();
	int const getMainIndexPrint();
	int const getCorpus1IndexPrint();
	int const getCorpus2IndexPrint();
	int const getCorpus3IndexPrint();
	string const getMainFile();
	string const getCorpusFile();
	bool const getIsMatch();

	unordered_map<int, string> const getMainSplit(int hashValue);
	unordered_map<int, string> const getMainSplitPrint(int hashValue);
	unordered_map<int, string> const getC1Split(int hashValue);
	unordered_map<int, string> const getC1SplitPrint(int hashValue);
	unordered_map<int, string> const getC2Split(int hashValue);
	unordered_map<int, string> const getC2SplitPrint(int hashValue);
	unordered_map<int, string> const getC3Split(int hashValue);
	unordered_map<int, string> const getC3SplitPrint(int hashValue);
	unordered_map<string, string> const getFound(string strC);





};

template <typename T>
class Phrases : public RabinKarp<T> {
public:
	Phrases();
	int numberOfPhrases(int length, int phrases);
	unordered_map<string, string> rabinKarpPolyPhrases(string main, string c1, string c2, string c3, int words); 
	unordered_map<string, string> rabinKarpFingerPrintPhrases(string main, string c1, string c2, string c3, int words); 


};


template <typename T>
class Sentences : public RabinKarp<T> {
public:
	Sentences();
	int numberOfSentences(string str);
	unordered_map<string, string> rabinKarpPolySentences(string main, string c1, string c2, string c3); 
	unordered_map<string, string> rabinKarpFingerPrintSentences(string main, string c1, string c2, string c3); 
};

