// simple_main.cpp    /// The name of this file
#include <iostream>
using namespace std;

#include "Coins.h"
const int CENTS_FOR_CANDYBAR = 482;


int main()
{
    ///  The first line creates a Coins object called 'pocket.'
    Coins pocket( 100, 10, 10, 100 );
    cout << "I started with " << pocket << " in my pocket" << endl;
    
    ///  This line creates a Coins object called payForCandy and initializes it.
    Coins payForCandy =
	pocket.extract_exact_change( coins_required_for_cents(CENTS_FOR_CANDYBAR) );
    cout << "I bought a candy bar for " << CENTS_FOR_CANDYBAR
           << " cents using " << payForCandy << endl;
    cout << "I have " << pocket << " left in my pocket" << endl;
    return 0;
} 
       
