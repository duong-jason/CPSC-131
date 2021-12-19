#pragma once
#include <iostream>
#define MAX_STORAGE 10

using namespace std;

class Item {
public:
    string name;
    int sellIn;
    int quality;

	Item(): name(""), sellIn(0), quality(0) {}
	Item(string new_name, int new_sellIn, int new_quality) : name(new_name), sellIn(new_sellIn), quality(new_quality) { }
};

class GildedRose {
private:
	Item* inventory = new Item[MAX_STORAGE];
	size_t stock;

public:
	GildedRose() : stock(0) {} // initialize data
	~GildedRose() { delete[] inventory; } // deallocate data

	// adds another item for sale	
	void add(const Item& object) {
		if (stock == MAX_STORAGE) {
			cout << "LIMIT STORAGE = " << MAX_STORAGE << endl;
			exit(1);
		}
		else inventory[stock++] = object;
	}

	// returns the number of items currently for sale
	size_t size() const { return stock; }

	// returns the item at a given index position 
	Item get(const size_t& shelf) const { return inventory[shelf]; }

	// perform identical to the get function
	Item operator[](const size_t& shelf) {
		if (shelf > stock) return {};
		else return inventory[shelf];
	}
};
