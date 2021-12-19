#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <iterator>

using namespace std;

string cmd;

struct Website {
	string url;
	size_t size;

	Website() : url(""), size(0) {};
	Website(const string& u, const size_t& s) : url(u), size(s) {};

	friend fstream& operator>>(fstream& read, Website& page) {
		read >> cmd;
		if (cmd == "visit") read >> page.url >> page.size;
		return read;
	}

} link;

class BrowserHistory {
private:
	list<Website> history;
	list<Website>::iterator curr;
	fstream read;

public:
	BrowserHistory() = default;
	~BrowserHistory() { history.clear(); };

	void readFile(const string& filename) {
		read.open(filename);	
		if (read.is_open()) {
			while (read >> link) {
				if (cmd == "visit") visitSite(link.url, link.size);
				else if (cmd == "back") backButton();
				else if (cmd == "forward") forwardButton();
			}
		} else {
			cout << "Could not open \'" << filename << "\'\n";
			exit(1);
		}
	}

	// current webpage changes to the previous one in the visit sequence (stays the same if no such page)
	void backButton() {
		if (curr != history.begin()) --curr;
	}
	
	// current webpage changes to the next one in the visit sequence (states the same if no such page)
	void forwardButton() {
		if (curr != prev(history.end())) ++curr;
	}

	// user visits a website with a given URL and web page size in bytes
	void visitSite(const string& url, const size_t& filesize) {
		if (getHistoryLength() > 1) {
			while (curr != prev(history.end())) history.pop_back();
		}

		Website link(url, filesize);

		history.push_back(link);
		curr = prev(history.end());
	}

	// returns the current url (returns empty string if no such site)
	string currentUrl() const { return (getHistoryLength() != 0 ? curr->url : ""); }

	// returns the current webpage's page size (returns 0 if no such site)
	size_t currentPageSize() const { return (getHistoryLength() != 0 ? curr->size : 0); }

	// returns the length of the webpage history
	size_t getHistoryLength() const { return history.size(); }
};
