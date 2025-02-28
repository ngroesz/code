#include <iostream>
#include <string>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

int main()
{

    string filename = "national_window_map_output_123_provider_range_100_200.bin.gz";

    smatch sm;
    int range_1;
    int range_2;

    if (regex_match(filename, sm, regex(".*provider_range_(\\d+)_(\\d+).*"))) {
        cout << "matched" << endl;
        string match_1(sm[1]);
        range_1 = atoi(match_1.c_str());
        string match_2(sm[2]);
        range_2 = atoi(match_2.c_str());
        //cout << match1 << endl;
        //string match2(sm[2].first, sm[2].second);
        //cout << match2 << endl;
        //range_1 = atoi(sm[1].c_str());
        //range_2 = atoi(sm[2].c_str());

        cout << "range 1: " << range_1 << " range 2: " << range_2 << endl;
    } else {
        cout << "no match" << endl;
    }
}
