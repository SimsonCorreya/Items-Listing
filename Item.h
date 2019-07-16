#pragma once
#include <iostream>

using namespace std;
class Item;
class Beverage;
class Ingredient;
class ItemMachine;

class Item
{
	int price;				// price per item
	int stocklevel;			// stock
public:
	
	Item();
	Item(int cost, int stock);
	~Item();
	
	virtual bool getavailability(Ingredient *supply[]);
	virtual void dispense(Ingredient *supply[]);

	int getPrice() { return price; }
	void setPrice(int temp) { price = temp; }

	int getStock() { return stocklevel; }
	void setStock(int temp) { stocklevel = temp; }
	
};

class Beverage : public Item 
{
	int Bev_ingredients[5];    // ingredient codes

public:
	Beverage(int ingredientCodes[5]);
	~Beverage();

	// overridden methods
	bool getavailability(Ingredient *supply[]);
	void dispense(Ingredient *supply[]);
};

class Ingredient
{
	int ingredientCode;     // ingredient code
	int measure;			// required for 1 cup (g)
	int level;				// total level (g)

public:		
	Ingredient(int code, int unit, int stocklevel);
	~Ingredient();
	
	void setcode(int temp) { ingredientCode = temp; }
	int getcode() { return ingredientCode; }

	void setlevel(int temp) { level = temp; }
	int getlevel() { return level; }

	void setmeasure(int temp) { measure = temp; }
	int getmeasure() { return measure; }

	void fetchMeasure();
};

class ItemMachine
{
	friend class Item;
	friend class Beverage;
	int credit, dispensed;
public:

	Ingredient *ingredients[5];
	Beverage *beverage[1];
	Item *items[5];
	
	ItemMachine();
	
	void requestItem(int num);
	void setcredit(int sum);
	bool checkCredit(int num);
	void dispStock();
};
