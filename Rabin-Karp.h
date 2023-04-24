#pragma once
#include <string>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <fstream>


using namespace std;
//no need for inheritance if objects can differ
//the name of the parent class

template <typename T>
class file {
private:
	ifstream x, y; 

public:
	virtual T readFile();
	ifstream& getX();
	ifstream& getY();
	void setX(string fileName);
	void setY(string fileName);
};

template <typename T>
class RabinKarp : public file<T>{
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
	int hashFunction(string str, long long  p, long long x); //will be coded inside each function but it will be the same code
	virtual string removeSpaces(string str, int& i, int words) = 0;//phrases will use words and sentences will not 
	virtual string calcBound(string str, int& i, int words) = 0;// both this and remove space will be coded in their class
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

	int const getHash  ();
	int const getWords  ();
	int const getMainIndex ();
	int const getCorpus1Index ();
	int const getCorpus2Index ();
	int const getCorpus3Index ();
	int const getMainIndexPrint ();
	int const getCorpus1IndexPrint ();
	int const getCorpus2IndexPrint ();
	int const getCorpus3IndexPrint ();
	string const getMainFile ();
	string const getCorpusFile ();
	bool const getIsMatch ();

	unordered_map<int, string> const getMainSplit ();
	unordered_map<int, string> const getMainSplitPrint ();
	unordered_map<int, string> const getC1Split ();
	unordered_map<int, string> const getC1SplitPrint ();
	unordered_map<int, string> const getC2Split ();
	unordered_map<int, string> const getC2SplitPrint ();
	unordered_map<int, string> const getC3Split ();
	unordered_map<int, string> const getC3SplitPrint ();
	unordered_map<string, string> const getFound ();





};

template <typename T>
class Phrases : public RabinKarp<T> {
public:
	Phrases();
	int numberOfPhrases(int length, int phrases);
	unordered_map<string, string> rabinKarpPolyPhrases(string main, string c1, string c2, string c3, int words); //Polynomial
	unordered_map<string, string> rabinKarpFingerPrintPhrases(string main, string c1, string c2, string c3, int words); //FingerPrint

	
};


template <typename T>
class Sentences : public RabinKarp<T> {
public:
	Sentences();
	int numberOfSentences(string str);
	unordered_map<string, string> rabinKarpPolySentences(string main, string c1, string c2, string c3); //Polynomial
	unordered_map<string, string> rabinKarpFingerPrintSentences(string main, string c1, string c2, string c3); //FingerPrint
};

