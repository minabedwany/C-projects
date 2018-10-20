#include "String.h"

void test_constructors_and_print()
{
    String s("Hello World"); // this calls the regular constructor
    cout << s << endl; // this uses copy constructor to pass the String to operator <<
    String test("Testing Print!");
    cout<< test<< endl<<"\n";
}

void test_assignment()
{
    String s("Assignment successful!");
    String test("Another Assignment Successful");
    String k("");
    k = s;
    cout<<k<<endl;
    k= test;
    cout<< k<<endl<<"\n";
}

void test_relationals()
{
    String firstString("aaaaaa");
    String secondString("aabb");
    String thirdString("Helloooo");
    String fourthString("Hello");

    cout << "LT: " << (secondString < firstString) << endl;
    cout << "GT: " << (secondString > firstString) << endl;
    cout << "LE: "<< (secondString <= firstString) << endl;
    cout << "GE: "<< (thirdString >= fourthString) << endl;
    cout << "!=: " << (thirdString != fourthString) << endl;
    cout << "==: " << (thirdString == fourthString) << endl <<"\n";

}

void test_reverse()
{
    String s("Reverse");
    cout<<"Reverse result: "<<s.reverse()<<endl;
    String test("Hello");
    cout<<"Another reverse: "<<test.reverse()<<endl<<"\n";
}

void test_concatenation()
{
    string s("First-Concatenation ");
    string k("Second-Concatenation ");
    string j("Third-Concatenation ");
    cout<< "+: "<<s+k<<endl;
    cout<< "+=: "<<(k+=j) <<endl;
    cout << "+=: "<<(s+=j) <<endl;
    cout<< "+: "<<s+k<<endl<<"\n";
}

void test_indexing()
{
    String s("abcdefgh");
    cout<< "Third index String[2]: "<< s[2]<<endl;
    cout << "Sixth index String[5]: "<< s[5]<< endl;
    cout << "String[40]: " << s[40] <<endl<<"\n";
}

void test_size()
{
    String s("123");
    String z("123456789");
    cout << "Testing size of string: "<<s.size()<<endl;
    cout << "Testing another bigger size: "<<z.size()<<endl<<"\n";
}

void test_finding_indexOf()
{
    String s("Helloooo");
    String haystack("I am writing C++ code");
    String needle("C++");
    String fail("blah");
    cout <<"Looking for -o- in -Helloooo- : " <<s.indexOf('o')<<endl;
    cout <<"Looking for -C++- in -I am writing C++ code- : "<<haystack.indexOf(needle)<<endl;
    cout <<"Looking for -z- in -Helloooo- (should fail) : "<< s.indexOf('z') <<endl;
    cout <<"Looking for -blah- in -I am writing C++ code- (Should fail) : "<<haystack.indexOf    (fail)<<endl<<"\n";
}

void test_reading_input()
{
    String str("blah");
    String test("");
    cout <<"Testing reading input. Enter a string: ";
    cin >> str;
    cout << "Input Successful: " <<str<<endl;

    cout <<"Let's do it one more time. Enter a string: ";
    cin >> test;
    cout << "Input Successful again: " <<test<<endl<<"\n";

}

int main()
{
    test_constructors_and_print();
    test_assignment();
    test_relationals();
    test_reverse();
    test_concatenation();
    test_indexing();
    test_size();
    test_finding_indexOf();
    test_reading_input();
    String :: final_report_on_allocations();
return 0;
}

