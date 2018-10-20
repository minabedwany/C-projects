#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;
#include "Coins.h"

void presentMenu()
{
cout << "\n   * * * * * * * * * * * * * * * * * * * * * *  *\n"
    << "   *		 MyCoins  MENU			*\n"
    << "   *					  	*\n"
    << "   *   OPTION				ENTER	*\n"
    << "   *						*\n"
    << "   *   Show Balance (in $)		B or b	*\n"
    << "   *   Show Coins in the Bank		C or c	*\n"
    << "   *   Deposit Coins			D or d	*\n"
    << "   *   Get Coins for Purchase		P or p	*\n"
    << "   *						*\n"
    << "   *   Quit				Q or q	*\n"
    << "   *						*\n"
    << "   * * * * * * * * * * * * * * * * * * * * * *  *\n" << endl;
}

char getChoice( const char * prompt )
{
  char ch;
  cout << prompt << " (followed by enter): ";
  cin >> ch;
  return ch;
}


int get_choice( const char * prompt )
{
  int ch;
  cout << prompt << " (followed by enter): ";
  cin >> ch;
  return ch;
}


void evaluateCommand( Coins & myCoins, char choice )
{ 
  int num_value;
  string value;
  switch ( choice )
  {
    case 'B': case 'b':
      cout<<"You have $"<<myCoins.total_value_in_cents()/100<<"."<<
      	myCoins.total_value_in_cents()%100<<" in your account\n"<<endl;
      break;

    case 'C': case 'c':
      cout << "You have "<<myCoins <<"\n"<< endl;
      break;

    case 'D': case 'd':
      {
      num_value = get_choice("How many quarters?");
      if (num_value<0){
	cout<<"Cannot deposit negative quarters!"<<endl;
	break;
      }
      else{
     	Coins temp1(num_value,0,0,0);
      	myCoins.deposit_coins(temp1);
      }

      num_value = get_choice("How many dimes?");
      if (num_value<0){
        cout<<"Cannot deposit negative dimes!"<<endl;
        break;
      }
      else{
      	Coins temp2(0,num_value,0,0);
      	myCoins.deposit_coins(temp2);
      }

      num_value = get_choice("How many nickels?");
      if (num_value<0){
        cout<<"Cannot deposit negative nickels!"<<endl;
        break;
      }
      else{
      	Coins temp3(0,0,num_value,0);
     	myCoins.deposit_coins(temp3);
      }

      num_value = get_choice("How many pennies?");
      if (num_value<0){
        cout<<"Cannot deposit negative pennies!"<<endl;
        break;
      }
      else{
      Coins temp4(0,0,0,num_value);
      myCoins.deposit_coins(temp4);
      }

      break;
      }

    case 'P': case 'p':
      {
      int value = get_choice("How many cents?");
      if (value<0){
        cout<<"Withdraw amount must be a positive value!"<<endl;
        break;
      }
      else{
      	Coins temp = coins_required_for_cents(value);
      	if (myCoins.has_exact_change_for_coins(temp)){
          myCoins.extract_exact_change(temp);
          cout<<"You have extracted "<<value<<" cents from your account"<<endl;
          }
      	else
          cout << "Not enough coins to extract exact change!"<< endl;
      	break;
      }
      }
 
    case 'Q': case 'q':
      cout << "Goodbye!\n\n";
      exit(0); 	
    default:
      cout << "Invalid command " << choice << endl;
      break;
  }
}

int main()
{
  Coins myCoins(0,0,0,0);
  while ( true )
  {
    presentMenu();
    char command = getChoice("Enter a command character");
    evaluateCommand( myCoins, command );
   }
return 0;
}

