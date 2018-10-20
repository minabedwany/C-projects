#include <iostream>
using namespace std;
#include "Coins.h"
const int CENTS_FOR_CHIPS = 68;


int main()
{
Coins pocket(5,3,6,8);
Coins piggyBank(50,50,50,50);

cout <<"I started with "<<pocket<<" in my pocket"<<endl;

Coins payForChips = pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CHIPS));
cout <<"I bought chips for "<< CENTS_FOR_CHIPS<<" cents using "<< payForChips<<" from my pocket"<<endl;
cout<<"I have "<<pocket<< " left in my pocket"<<endl;

cout <<"\nI started with "<<piggyBank<<" in my piggyBank"<<endl;
Coins transfer = piggyBank.extract_exact_change(coins_required_for_cents(205));
cout<<"I transferred $2.05 from piggyBank to pocket using "<<transfer<<" from my piggyBank"<<endl;

pocket.deposit_coins(transfer);
cout<<"I now have "<<piggyBank<<" left in my piggyBank and "<<pocket<<" in my pocket"<<endl;

Coins sofa(10,10,10,10);
cout<<"\nI deposited "<<sofa<<" I found in my sofa into my piggyBank"<<endl;
piggyBank.deposit_coins(sofa);
cout<<"I now have $"<<piggyBank.total_value_in_cents()/100<<"."<<piggyBank.total_value_in_cents()%100<<" in my piggyBank"<<endl;

return 0;
}

