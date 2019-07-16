#include "Item.h"
#include <iomanip>

// ITEM -------------------------------------------------------
Item::Item() {}
Item::Item(int cost, int stock) 
{
	setPrice(cost);
	setStock(stock);
}
Item::~Item() 
{
}
bool Item::getavailability(Ingredient *supply[])
{
	cout << "\nGetting item availablity" << endl;
	if (stocklevel)return(true); else return(false);
}
void Item::dispense(Ingredient *supply[])
{
	cout << "\nDispensing Item" << endl;
	stocklevel--;
}

// BEVERAGE ---------------------------------------------------
Beverage::Beverage(int ingredientCodes[5])
{
	int price = 0;
	for (int i = 0; i < 5; i++)
	{
		Bev_ingredients[i] = ingredientCodes[i];// copy ingredient codes
		if (Bev_ingredients[i] != 0) price++;// adds 1 to price for each ingredient

	}
	setPrice(price);
	setStock(100);
}
Beverage::~Beverage() {
	cout << "Default Constructor" << endl;
}
bool Beverage::getavailability(Ingredient *supply[])
{
	cout << "Checking Beverage Availability..." << endl;
	int outOfStockCodes[5], outOfStockCount=0;

	for (int i = 0; i < 5; i++)						// loop all itemmachine ingredients indices
	{
		if (Bev_ingredients[i] != 0)								// 0 if ingredient not used
		{		
			for (int j = 0; j < 5; j++) 
			{
				if (supply[i]->getcode() == Bev_ingredients[j])		// if code matches ingredient used
				{
					if (supply[i]->getlevel() < supply[i]->getmeasure())
					{
						outOfStockCodes[outOfStockCount] = supply[i]->getcode();
						outOfStockCount++;
					}
				}
			}
			
		}			
	}

	for (int i = 0; i < outOfStockCount; i++)	// print out out of stock ingredients
	{
		cout << "Ingredient with code "
			<< outOfStockCodes[i]
			<< " has insufficient stock" << endl;
	}

	if (outOfStockCount == 0)					// if ingredients in stock
	{
		cout << "All ingredients are sufficiently in stock" << endl;
		return true;
	} else return false;						// else ingredients are in stock
}
void Beverage::dispense(Ingredient *supply[])
{
	cout << "\nDispensing Item..." << endl;

	for (int i = 0; i < 5; i++)						// loop all itemmachine ingredients indices
	{
		if (Bev_ingredients[i] != 0)								// 0 if ingredient not used
		{
			for (int j = 0; j < 5; j++)
			{
				if (supply[j]->getcode() == Bev_ingredients[i])		// if code matches ingredient used
				{
					supply[j]->fetchMeasure();
				}
			}

		}
	}

	
}

// INGREDIENT -------------------------------------------------
Ingredient::Ingredient(int code, int unit, int stocklevel)
{
	setcode(code);
	setlevel(stocklevel);
	setmeasure(unit);
}
Ingredient::~Ingredient()
{
	cout << "Ingredient Destroyed";
}
void Ingredient::fetchMeasure()
{ 
	level = level - measure; 
}

// ITEMMACHINE ------------------------------------------------
ItemMachine::ItemMachine()
{
	int ingredientsArray[5] = { 1,0,0,0,0 };

	items[0]       = new Item(1, 2);				// item(cost,stock)
	items[1]       = new Beverage(ingredientsArray);
	ingredients[0] = new Ingredient(2, 20, 100);	// ingredient(code,unit,stocklevel)
	ingredients[1] = new Ingredient(3, 20, 100);
	ingredients[2] = new Ingredient(4, 20, 100);
	ingredients[3] = new Ingredient(5, 20, 100);
	ingredients[4] = new Ingredient(1, 20, 100);
	credit = 0;
	dispensed = 0;   
}
void ItemMachine::requestItem(int num)
{
	cout << "\nRequesting item number: " << num << endl;
	if (!checkCredit(num)) cout << "Insufficient credit" << endl;
	if (items[num]->getavailability(ingredients))
	{
	items[num]->dispense(ingredients);
	dispensed++;
	}
	else cout << "Ingredients out of stock, item cannot be dispensed" << endl;
}
void ItemMachine::setcredit(int sum)
{
	credit = credit + sum;
}
bool ItemMachine::checkCredit(int num)
{
	if (credit >= items[num]->getPrice()) return true;
	else return false;
}
void ItemMachine::dispStock() 
{
	cout << " " << endl;
	cout << setw(5) << "Code"
		<< setw(8) << "Measure" 
		<< setw(8) << "Stock" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << setw(5) << ingredients[i]->getcode()
			<< setw(8) << ingredients[i]->getmeasure()
			<< setw(8) << ingredients[i]->getlevel() << endl;  
	}
}


