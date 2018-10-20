// Coins.h		///  The name of this file.
#include <iostream>
#include <math.h>
using namespace std;
const int CENTS_PER_QUARTER = 25, CENTS_PER_DIME = 10, CENTS_PER_NICKEL = 5;
class Coins
{
public:
    // constructs ‘this’ Coins object so it has the number of each coin 
    // given in the respective parameters
    Coins(int q, int d, int n, int p){
	quarters=q;
	dimes=d;
	nickels=n;
	pennies=p;
    } 

    // remove the coins from c and put them into ‘this’ Coins object
    void deposit_coins( Coins & c ){
	quarters += c.quarters;
	dimes += c.dimes;
	nickels += c.nickels;
	pennies += c.pennies;
    } 
  
    // returns true only if this Coins object has enough of each type of coin to cover
    // a possible extraction of the specific coins in c
    bool has_exact_change_for_coins( Coins c ){
	return quarters >= c.quarters && dimes >= c.dimes && nickels >= c.nickels && pennies 		>= c.pennies;
    }

    // removes from this Coins object the specific number of each type of coin given in c
    Coins extract_exact_change( Coins c ){
	if (has_exact_change_for_coins(c)){
	    quarters -= c.quarters;
	    dimes -= c.dimes;
	    nickels -= c.nickels;
	    pennies -= c.pennies;
	}
	else 
	    cout << "Not enough coins to extract exact change"<< endl;
	return c;
    }

    // returns how many cents the coins in this object total, e.g., 1,1,1,1 returns 41
    int total_value_in_cents(){
	return quarters*CENTS_PER_QUARTER + dimes*CENTS_PER_DIME + nickels*CENTS_PER_NICKEL +		pennies;
    }
    // prints out the info in this coins in this format “6 quarters, 2 dimes, …”
    // this is the method called by the inserter
    void print( ostream & out ){
	cout << quarters << " quarters, " << dimes << " dimes, " << nickels << " nickels, " 
	<< pennies << " pennies";
	return;
    }

private:
    int quarters, dimes, nickels, pennies;
};
// an appropriate inserter for a Coins object
ostream & operator << ( ostream & out, Coins c )
{
  c.print( out );
  return out;
}

// coins_required_for_cents() can use math or while loops to
// decide how to satisify the need for amount_in_cents
// first take as many quarters, then as many dimes, etc. E.g.,
// coins_required_for_cents(117) will return Coins(4,1,1,2)
Coins coins_required_for_cents(int amount_in_cents){
    int q;
    int d;
    int n;
    int p;
    
    q = floor(amount_in_cents /CENTS_PER_QUARTER);
    d = floor((amount_in_cents % CENTS_PER_QUARTER)/ CENTS_PER_DIME);
    n = floor(((amount_in_cents % CENTS_PER_QUARTER)% CENTS_PER_DIME)/ CENTS_PER_NICKEL);
    p = (((amount_in_cents % CENTS_PER_QUARTER)% CENTS_PER_DIME)% CENTS_PER_NICKEL);
  
    return Coins(q,d,n,p);
}
