//Vending machine
#pragma once
#include <conio.h>   // getch
#include <string>
#include <iostream>
#include <iomanip>
#include "Item.h"

using namespace std;


void main()
{
	ItemMachine *myMachine = new ItemMachine;	
								// instance of ItemMachine

	myMachine->dispStock();
	myMachine->setcredit(400);	// set machine credit to 400
	myMachine->requestItem(1);  // request item number 0
	myMachine->dispStock();
	
	_getch();   // get character (delay)
}




















