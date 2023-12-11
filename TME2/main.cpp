#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include <forward_list>
#include <algorithm>
#include "hashmap.hh"
using namespace std;

int main () {
	using namespace std;
	using namespace std::chrono;
	
	// vector< std::pair<string,int> > Vector_word;
	pr::HashMap<string,int> Mymap(10); //declaration table

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now(); //debut calclul temps
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		// int v = 1;
		// for (size_t i=0; i<Vector_word.size();i++){
		// 	if (Vector_word[i].first == word) {
		// 		Vector_word[i].second++;
		// 		v = 0;
		// 		break;
		// 	}
		// } 

		// if (v == 1) Vector_word.emplace_back(word, 1);
		Mymap.put(word,1);
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;

		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now(); //fin du calcul du temps
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    // cout << "mot_diff " << ": "<< Vector_word.size() << endl;
    // for (size_t i=0; i<Vector_word.size();i++){
    // 	if (Vector_word[i].first == "war")
    // 		cout << "Occurence War " << ": "<< Vector_word[i].second<< endl;
    // 	if (Vector_word[i].first == "peace")
    // 		cout << "Occurence peace " << ": "<< Vector_word[i].second<< endl;
    // 	if (Vector_word[i].first == "toto")
    // 		cout << "Occurence toto " << ": "<< Vector_word[i].second<< endl;   	
    // } 

	// Afficher le contenu de la Hashmap
	for (size_t i = 0; i < 10; i++) {
    	for (const auto &ent : Mymap.getBucket(i)) {
        	cout << "Key: " << ent.Key << ", Value: " << ent.value << endl;
    	}
	}

    return 0;
}

