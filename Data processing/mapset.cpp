#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>
#include <cctype>
using namespace std;

bool isOkay( set<string> x, string word )
{
    return find(x.begin(), x.end(), word) ==  x.end();
}

int main()
{
    ifstream input("sample_doc.txt");
    ifstream exclude_input("stopwords.txt");
    ofstream out("frequency.txt");

    set<string> exclusionSet;
    copy( istream_iterator<string>(exclude_input), istream_iterator<string>(), 
    inserter( exclusionSet, exclusionSet.begin() ));

    map<string, int> M;
    for_each( istream_iterator<string>(input), istream_iterator<string>(), 
        [&](string s){
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            if ( isOkay(exclusionSet, s)) 
                ++M[s]; 
        } );
    
    for_each(M.begin(), M.end(), 
        [&out](std::pair <const string, int> & E){ 
            out << E.first << " " << E.second <<endl; 
        } );    

    return 0;
}
