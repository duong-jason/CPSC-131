#pragma once
#include <iostream>
#include "sanitize.hpp"
#include <map>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class TextGen {
private:
    fstream read;
    map<string, vector<string>> graph;

public:
    TextGen(unsigned int seed) { srand(seed); }
    ~TextGen() { graph.clear(); };

    void readIn(const string& filename) {
        read.open(filename);
        if (read.is_open()) {
            string state = "^", token;

            while (read >> token) {
                sanitize(token);

                // new sentence -> append end-of-marker '$'
                if (isEndPunctuation(state[0])) {
                    graph[state].push_back("$"); // '.' : '$'
                    graph["^"].push_back(token); // '^' : "token"
                } else {
                    if (isEndPunctuation(token.back())) {
                        state = token.substr(0, token.size() - 1);
                        token = (1, token[token.size() - 1]);
                    }

                    graph[state].push_back(token);
                }

                state = token;
            }

            read.close();
        } else {
            cout << "Could not open \'" << filename << "\'\n";
            exit(1);
        }
    }

    // returns true if the given char is one of the following
    bool isEndPunctuation(const char& c) { return c == '.' || c == '?' || c == '!'; }

    // returns value at given key
    map<string, vector<string>> get_markovChain() { return graph; }

    vector<string> getValues(const string& key) { return graph[key]; }

    // returns a randomly generated sentence
    string generateSentence() {
        string state = "^", token;
        
        while (state != "$" && graph.count(state) > 0) {
            int pos = rand() % graph[state].size();
            token += graph[state][pos] + " ";
            state = graph[state][pos];
        }
        // removes end-of-marker symbol -> '$'
        while (!isEndPunctuation(token.back())) token.pop_back();

        return token;
    }

};
