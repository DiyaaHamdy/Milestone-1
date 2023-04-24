#include <string>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include "brute_.h"
#include "Rabin-Karp.h"

using namespace std;



//Reads from file and converts into string 
string get(ifstream* infile) {

    string line, temp;

    while (getline(*infile, temp)) { line = line + temp; }

    return line;

}


//Hash Function using fingerprint method 
int fingerprint(string str, int p, int x) {
    int result = 0;
    for (int i = 0; i < str.length(); i++) {
        result = (result * x + str[i]) % p;
    }
    return result;
}

//Hash Function using polynomial method
int polynomialRollingHash(string str, long long  p, long long x) {
    int result = 0;
    for (int i = 0; i < str.length(); i++) {
        //do not count punctuation aswell
        if (str[i] != ' ' && str[i] != '.' && str[i] != '?' && str[i] != '!' && str[i] != '(' && str[i] != ')' && str[i] != '[' && str[i] != ']' && str[i] != '\0')
            result = (result * x + str[i]) % p;
    }
    return result;
}

//Generate custom substrings using sentences
string calcBound(string str, int& i) {

    int x = 0;
    string sub{};
    char c;

    //when meeting punctuation counting the word after as a word if no space? "i am amazing.ahmed vs i am amazing. Ahmed

    //now i am trying to detect by sentences 

    //check using the words var multiple word size and sentences to increase chance of finding smth
    //we need to comine both algorithms to have the best chance of detecitng plagarism 
    //combine sentences with phrases 
    while (x < 1) {
        if (str[i] == '.' || str[i] == '?' || str[i] == ',' || str[i] == ';' || str[i] == '!')
        {
            x++;
            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }

        else
        {

            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }
    }



    return sub;
}

//Generate custom substrings using phrases
string calcBound(string str, int& i, int words) {

    int x = 0;
    string sub{};
    char c;

    //when meeting punctuation counting the word after as a word if no space? "i am amazing.ahmed vs i am amazing. Ahmed
    //do more than one iteration : 3 words, 2, 4
    while (x < words && i <= str.length()) {
        if (str[i] == ' ' && str[i + 1] != ' ')
        {
            x++;
            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }

        else
        {

            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }
    }



    return sub;
}


string removeSpaces(string str, int& i, int words) {
    int x = 0;
    string sub{};
    char c;

    while (x < words && i <= str.length()) {
        if (str[i] == ' ' && str[i + 1] != ' ') {
            x++;
            i++;
        }
        else {
            c = tolower(str[i]);
            sub = sub + c;
            i++;

        }

    }

    return sub;


}

string rmemoveSpaces(string str, int& i) {

    int x = 0;
    string sub{};
    char c;

    //when meeting punctuation counting the word after as a word if no space? "i am amazing.ahmed vs i am amazing. Ahmed

    //now i am trying to detect by sentences 

    //check using the words var multiple word size and sentences to increase chance of finding smth
    //we need to comine both algorithms to have the best chance of detecitng plagarism 
    //combine sentences with phrases 
    while (x < 1) {

        if (str[i] == ' ' && str[i + 1] != ' ') {
            i++;
        }
        if (str[i] == '.' || str[i] == '?' || str[i] == ',' || str[i] == ';' || str[i] == '!')
        {
            x++;
            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }

        else
        {

            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }
    }

    return sub;
}

int numberOfPhrases(int length, int phrases) {
    //# of words/phrases

    int number = 0;
    number = (length / phrases) + 1;

    return number;

}

int numberOfSentences(string str) {//do this 
    int x = 0;
    //COUNT PUNCTUATION MARKS
    string sub{};
    char c;

    //when meeting punctuation counting the word after as a word if no space? "i am amazing.ahmed vs i am amazing. Ahmed

    //now i am trying to detect by sentences 

    //check using the words var multiple word size and sentences to increase chance of finding smth
    //we need to comine both algorithms to have the best chance of detecitng plagarism 
    //combine sentences with phrases 
    while (x < 1) {
        if (str[i] == '.' || str[i] == '?' || str[i] == ',' || str[i] == ';' || str[i] == '!')
        {
            x++;
            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }

        else
        {

            c = tolower(str[i]);
            sub = sub + c;
            i++;
        }
    }



    return sub;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////Rabin-Karp Algorithm///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//RK using Poly Hash and phrases substrings
unordered_map<string, string> rabinKarpPolyPhrases(string main, string c1, string c2, string c3, int words) {
    unordered_map<int, string> mainSplit{};
    unordered_map<int, string> mainSplitPrint{};


    unordered_map<int, string> c1Split{};
    unordered_map<int, string> c1SplitPrint{};

    unordered_map<int, string> c2Split{};
    unordered_map<int, string> c3Split{};
    int hash;
    unordered_map<string, string> found{};

    vector<string> ngMain;
    vector<string> ngCorpus_1;
    //need to pass this from main input from user
    int mainIndex = 0;
    int corpus1Index = 0;
    int mainIndexPrint = 0;
    int corpus1IndexPrint = 0;
    //int corpus2Index = 0;
    //int corpus3Index = 0;
    int n = main.length();
    int m = c1.length();
    int l = 0;

    if (m > n)
        l = m;
    else
        l = n;

    //need to find proper loop parameter maybe a while
    //numberofphrases 2,3,4

    for (int i = 0; i <= numberOfPhrases(l, words); i++)
    {

        //by spliting into 3 words we have something ok but still needs impvrments against random spacing and deletion of words
        // space  still fucks and tarteeb
        //also if docs are not the same number of words I will need to use seperate funcitons
        string mSub = removeSpaces(main, mainIndex, words);
        string c1Sub = removeSpaces(c1, corpus1Index, words);
        string mSubPrint = calcBound(main, mainIndexPrint, words);
        string c1SubPrint = calcBound(c1, corpus1IndexPrint, words);
        /* string c2Sub = calcBound(c1, corpus2Index, words);
         string c3Sub = calcBound(c1, corpus3Index, words);*/
        hash = polynomialRollingHash(mSub, 1000000007, 263);
        mainSplit.insert({ hash, mSub });
        mainSplitPrint.insert({ hash, mSubPrint });

        c1Split.insert({ polynomialRollingHash(c1Sub, 1000000007, 263), c1Sub });
        c1SplitPrint.insert({ polynomialRollingHash(c1Sub, 1000000007, 263), c1SubPrint });

        /*      c1Split.insert({ polynomialRollingHash(c2Sub, 101, 257), c2Sub });
              c1Split.insert({ polynomialRollingHash(c3Sub, 101, 257), c3Sub });*/



    }



    string temp1{};
    string temp2{};
    bool match1 = true;
    //bool match2 = true;
    //bool match3 = true;
    for (auto it = mainSplit.begin(); it != mainSplit.end(); it++) {
        if (c1Split.count(it->first)) {
            match1 = true;
            temp1 = (it->second).substr(0, (it->second).size() - 1);
            temp2 = (c1Split[it->first]).substr(0, (c1Split[it->first]).size() - 1);;
            if (temp1 != temp2) {
                match1 = false;
            }

            else
            {
                if (match1 == true) {
                    //consider using emplace to insert instead of insert() b/c there maybe duplicates
                    found.insert({ c1SplitPrint[it->first] , mainSplitPrint[it->first] + "\t From Document 1 \t" });


                }

            }
        }





        //
        //if (c2Split.count(it->first)) {
        //    if (it->second != c2Split[it->first]) {
        //        match2 = false;
        //    }

        //    else
        //    {
        //        if (match2 == true) {
        //            found.insert({ c2Split[it->first] , mainSplit[it->first] + "\t From Document 2 \t" });


        //        }

        //    }
        //}
        ////
        //if (c3Split.count(it->first)) {
        //    if (it->second != c3Split[it->first]) {
        //        match3 = false;
        //    }

        //    else
        //    {
        //        if (match3 == true) {
        //            found.insert({ c3Split[it->first] , mainSplit[it->first] + "\t From Document 3 \t" });


        //        }

        //    }
        //}

    }


    //match1 = true;
    //if (it->second != c1Split[it->first]) {
    //    match1 = false;
    //}
    //else
    //{
    //    if (match1 == true) {
    //        found.insert({ c1Split[it->first] , mainSplit[it->first] + "\t From Document 1 \t" });


    //    }

    //}

    return found;
}


//RK using Poly Hash and sentence substrings
unordered_map<string, string> rabinKarpPolySentences(string main, string c1, string c2, string c3) {
    unordered_map<int, string> mainSplit{};
    unordered_map<int, string> mainSplitPrint{};

    unordered_map<int, string> c1Split{};
    unordered_map<int, string> c1SplitPrint{};

    unordered_map<int, string> c2Split{};
    unordered_map<int, string> c3Split{};
    int hash;
    unordered_map<string, string> found{};


    //need to pass this from main input from user
    int words = 3;
    int mainIndex = 0;
    int corpus1Index = 0;
    int mainIndexPrint = 0;
    int corpus1IndexPrint = 0;
    //int corpus2Index = 0;
    //int corpus3Index = 0;
    int n = main.length();
    int m = c1.length();
    int l = 0;

    if (m > n)
        l = m;
    else
        l = n;
    // numberofsemtemces 
    //need to find proper loop parameter maybe a while
    for (int i = 0; i <= 1; i++)
    {

        //by spliting into 3 words we have something ok but still needs impvrments against random spacing and deletion of words
        // space  still fucks and tarteeb
        //also if docs are not the same number of words I will need to use seperate funcitons
        string mSub = rmemoveSpaces(main, mainIndex);
        string c1Sub = rmemoveSpaces(c1, corpus1Index);
        string mSubPrint = calcBound(main, mainIndexPrint);
        string c1SubPrint = calcBound(c1, corpus1IndexPrint);
        /* string c2Sub = calcBound(c1, corpus2Index, words);
         string c3Sub = calcBound(c1, corpus3Index, words);*/
        hash = polynomialRollingHash(mSub, 1000000007, 263);
        mainSplit.insert({ hash, mSub });
        mainSplitPrint.insert({ hash, mSubPrint });

        c1Split.insert({ polynomialRollingHash(c1Sub, 1000000007, 263), c1Sub });
        c1SplitPrint.insert({ polynomialRollingHash(c1Sub, 1000000007, 263), c1SubPrint });

        /*      c1Split.insert({ polynomialRollingHash(c2Sub, 101, 257), c2Sub });
              c1Split.insert({ polynomialRollingHash(c3Sub, 101, 257), c3Sub });*/



    }

    //i think it works
    string temp1{};
    string temp2{};
    bool match1 = true;
    //bool match2 = true;
    //bool match3 = true;
    for (auto it = mainSplit.begin(); it != mainSplit.end(); it++) {
        if (c1Split.count(it->first)) {
            match1 = true;
            //temp1 = (it->second).substr(0, (it->second).size() - 1);
            //temp2 = (c1Split[it->first]).substr(0, (c1Split[it->first]).size() - 1);;
            if (it->second != c1Split[it->first]) {
                match1 = false;
            }

            else
            {
                if (match1 == true) {
                    found.insert({ c1SplitPrint[it->first] , mainSplitPrint[it->first] + "\t From Document 1 \t" });


                }

            }
        }





        //
        //if (c2Split.count(it->first)) {
        //    if (it->second != c2Split[it->first]) {
        //        match2 = false;
        //    }

        //    else
        //    {
        //        if (match2 == true) {
        //            found.insert({ c2Split[it->first] , mainSplit[it->first] + "\t From Document 2 \t" });


        //        }

        //    }
        //}
        ////
        //if (c3Split.count(it->first)) {
        //    if (it->second != c3Split[it->first]) {
        //        match3 = false;
        //    }

        //    else
        //    {
        //        if (match3 == true) {
        //            found.insert({ c3Split[it->first] , mainSplit[it->first] + "\t From Document 3 \t" });


        //        }

        //    }
        //}

    }


    //match1 = true;
    //if (it->second != c1Split[it->first]) {
    //    match1 = false;
    //}
    //else
    //{
    //    if (match1 == true) {
    //        found.insert({ c1Split[it->first] , mainSplit[it->first] + "\t From Document 1 \t" });


    //    }

    //}

    return found;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////JACCARD FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Jaccard equation
float jaccardSimilarity(const unordered_set<string>& set1, const unordered_set<string>& set2) {
    unordered_set<string> intersection;
    unordered_set<string> unionSet;

    // Calculate intersection
    for (const auto& ngram : set1) {
        if (set2.count(ngram) > 0) {
            intersection.insert(ngram);
        }
    }

    // Calculate union
    unionSet = set1;
    for (const auto& ngram : set2) {
        unionSet.insert(ngram);
    }

    float jaccard = static_cast<float>(intersection.size()) / unionSet.size();

    return jaccard;
}

//Get N-Grams for Jaccard
vector<string> generateNGrams(const string& str, int n) {
    vector<string> ngrams;
    for (int i = 0; i <= str.length() - n; i++) {
        ngrams.push_back(str.substr(i, n));
    }
    return ngrams;
}

//Calculates the percentage of similarity in the corpus vs the main using Jaccard Similarity 
void similarityPercent(string main, string c1, string c2, string c3) {

    vector<string> suspiciousNGrams = generateNGrams(main, 5);
    std::unordered_set<std::string> suspiciousSet(suspiciousNGrams.begin(), suspiciousNGrams.end());

    vector<string> referenceNGrams = generateNGrams(c1, 5);
    std::unordered_set<std::string> referenceSet(referenceNGrams.begin(), referenceNGrams.end());
    //a lot of plagarism trace it 
    float similarity = jaccardSimilarity(suspiciousSet, referenceSet);
    if (similarity >= 0.5) {
        cout << "Similarity of: " << similarity * 100 << "% suggests plagarism";
    }
    else if (similarity <= 0.5 && similarity >= 25) {
        cout << "Similarity of: " << similarity * 100 << "% is slightly high";
    }
    else
        cout << "No Plagarism";

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////MAIN FUNCTION//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {

    //map
    unordered_map<string, string> found = {};
    unordered_map<string, string> foundPoly4Phrases = {};
    unordered_map<string, string> foundPoly3Phrases = {};
    unordered_map<string, string> foundPoly2Phrases = {};


    unordered_map<string, string> foundPolySentences = {};



    //files
    ifstream c1F("Corp1.txt");
    string c1 = get(&c1F);

    ifstream c2F("c2.txt");
    string c2 = get(&c2F);

    ifstream c3F("c3.txt");
    string c3 = get(&c3F);

    ifstream infile("Sus.txt");
    string main = get(&infile);


    //found = rabinKarp(main, c1, c2, c3);
    foundPoly4Phrases = rabinKarpPolyPhrases(main, c1, c2, c3, 4);
    foundPoly3Phrases = rabinKarpPolyPhrases(main, c1, c2, c3, 3);
    foundPoly2Phrases = rabinKarpPolyPhrases(main, c1, c2, c3, 2);
    //still need to fix in sentences
    foundPolySentences = rabinKarpPolySentences(main, c1, c2, c3);


    //fingerprint
    //figure out how to writw this normally 
  /* for (auto it = found.begin(); it != found.end(); it++) {
       cout << it->first << '\t' << it->second << endl;

   }*/


   //need to create a print function
  //foundPolyPhrases print 
    for (auto it = foundPoly4Phrases.begin(); it != foundPoly4Phrases.end(); it++) {
        cout << it->first << '\t' << it->second << endl;

    }

    for (auto it = foundPoly3Phrases.begin(); it != foundPoly3Phrases.end(); it++) {
        cout << it->first << '\t' << it->second << endl;

    }

    for (auto it = foundPoly2Phrases.begin(); it != foundPoly2Phrases.end(); it++) {
        cout << it->first << '\t' << it->second << endl;

    }

    //foundPolySentences print 
    for (auto it = foundPolySentences.begin(); it != foundPolySentences.end(); it++) {
        cout << it->first << '\t' << it->second << endl;

    }

    similarityPercent(main, c1, c2, c3);

    //Now I have:
    //Jaccard sim working but i need to understand it
    //RK is working with the things need to find a nice way to priont 
    // loop i think is solved
    //multiple docs either need to be the same size or I would need to use seperate fucntion or smth else idk yet


}

void stringmatching(brute_force& a, vector<char> pattern, int index)
{

    int count = 0;
    for (int i = 1; i <= a.number_of_phrases_filey(); i++)
    {

        vector<char> temp = a.getsentence_filey(i);


        int tempI = a.brute_check(temp, pattern);

        if (tempI != -999)
        {
            if (temp.size() > pattern.size())
            {
                cout << "(";
                for (int k = 0; k < pattern.size(); k++)
                {
                    cout << pattern[k];
                }
                cout << ")";
                cout << " was plagiarised from the sentence " << i << " of the second file " << " . this sentence starts from the index : " << tempI << " of the second file " << "sentence and starts at index 0 of first file sentence" << endl;

                a.push_plagiarized_indexes(index, i, 0, tempI);
            }
            else if (temp.size() < pattern.size())
            {
                cout << "(";
                for (int l = 0; l < temp.size(); l++)
                {
                    cout << temp[l];
                }
                cout << ")";
                cout << "  was plagiarised from the sentence " << i << " of the second file " << ". this sentence starts from the index : " << tempI << " of the first file " << "sentence and starts at index 0 of second file sentence" << endl;

                a.push_plagiarized_indexes(index, i, tempI, 0);
            }
            else
            {
                cout << "(";
                for (int c = 0; c < pattern.size(); c++)
                {
                    cout << pattern[c];
                }
                cout << ")";
                cout << " was completely plagiarised from the sentence " << i << " of the second file " << endl;
                a.push_plagiarized_indexes(index, i, 0, 0);
            }
            count++;
        }

    }

    if (count == 0)
        cout << "no plagiarism" << endl;
}
void plagiarism_check(brute_force& a)
{

    cout << "checking every sentence in file 1 " << endl;
    cout << endl;
    for (int j = 1; j <= a.number_of_phrases_filex(); j++)          // every phrase in filex vector
    {
        cout << "checking sentence: " << j << endl;
        stringmatching(a, a.getsentence_filex(j), j);
    }

}
int main()
{
    brute_force a("dscc.txt", "kpvsd.txt", 2);
    plagiarism_check(a);
}