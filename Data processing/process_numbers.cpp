#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    
    ifstream in("rand_numbers.txt");
    ofstream out_even("even.txt");
    ofstream out_odd("odd.txt");

    vector<int> V;
    copy( istream_iterator<int>(in), istream_iterator<int>(),back_inserter(V) );
    sort( V.begin(), V.end() );

    for_each(V.begin(), V.end(),
        [&](int i){ 
            if (i%2 == 0)
                out_even << i <<endl;
            else
                out_odd << i << " "; 
        } );



    return 0;
}
