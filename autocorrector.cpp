#include <bits/stdc++.h>
using namespace std;

bool autocorrect;
vector<string> dictionary;
const string path = "qwerty/";


// Loading the dictionary in vector.
void LoadDictonary()
{
	ifstream infile("large_dictionary.txt");
    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        dictionary.push_back(line);
    }
    sort(dictionary.begin(),dictionary.end());
}


// Binary search for searching words in huge dictionary
bool BinarySearch(string word)
{
	if (binary_search(dictionary.begin(), dictionary.end(), word)) 
		return true;
	return false;
}


/*Editing the word by replacing the two levels character of qwerty keyboard, 
adding character, rearranging them and deleting the characters.*/

set <string> WordEditing(string word) 
{
	set <string> words;
	string edited_word;

	// Adding a-z before every character
	for (int i = 0; i < word.length() + 1; i++) 
	{
		for (char c = 'a'; c <= 'z'; c++) 
		{
			edited_word = word.substr(0, i) + c + word.substr(i);
			words.insert(edited_word);
		}
	}

	// Replacing every character by max 2 level of qwerty keyboard
	for (int i = 0; i < word.length(); i++) 
 	{
 		vector<char> replace;

 		string filename = path+word[i]+".txt";

 		ifstream infile(filename.c_str());
    	string line;
    	while (getline(infile, line))
    	{
        	istringstream iss(line);
        	replace.push_back(line[0]);
    	}
    	for(vector<char>::iterator it = replace.begin(); it != replace.end() ; it++)
    	{
			edited_word = word.substr(0, i) + *it + word.substr(i + 1);
			words.insert(edited_word);	
    	}

		replace.clear();
	}


	// Rearranging
	for (int i = 0; i < word.length() - 1; i++)
	{
		edited_word = word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2);
		words.insert(edited_word);
 	}



	// Deleting each character one by one
	for (int i = 0; i < word.length(); i++)
	{
		edited_word = word.substr(0, i) + word.substr(i + 1);
		words.insert(edited_word);
	}

	return words;
}


vector <string> AutoSuggestions(string word) 
{

	vector <string> candidates;
	if(BinarySearch(word))
	{
		candidates.push_back(word);
		return candidates;	
	}

	autocorrect = true;
	set <string> edit1 = WordEditing(word);

	for (set<string>::iterator it = edit1.begin() ; it != edit1.end() ; it++)
	{
		if(BinarySearch(*it))
			candidates.push_back(*it);
	}
	if (candidates.size() > 0) 
		return candidates;

	candidates.clear();

	for (set<string>::iterator it = edit1.begin() ; it != edit1.end() ; it++)
	{
		set <string> edit2 = WordEditing(*it);
		for (set<string>::iterator it2 = edit1.begin() ; it2 != edit1.end() ; it2++)
		{
			if(BinarySearch(*it2))
				candidates.push_back(*it2);
		}
	}
	if (candidates.size() > 0) 
		return candidates;
	
	autocorrect = false;
	candidates.clear();
	candidates.push_back(word);
	return candidates;
}


void PrintOutput(string word)
{
	vector<string> final_list =  AutoSuggestions(word);
	int i = 0 ;
	for(vector<string>::iterator it = final_list.begin() ; i < 5 && it != final_list.end() ; i++, it++)
		cout<<i+1<<". "<<*it<<endl;
}


int main(void) 
{
	// Buliding a dictionary from file
	LoadDictonary();
	int t;
	// t is number of test cases.
	cin>>t;
	while(t--)
	{
		// Input the string 
		string word;
		autocorrect = false;
		cin>>word;
		PrintOutput(word);
		autocorrect ? cout<<"Autocorrected: Yes\n" : cout<<"Autocorrected: No\n";
		cout<<endl;
	}
}
