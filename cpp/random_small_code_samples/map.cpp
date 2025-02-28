#include <map>
#include <string>
#include <utility>

using namespace std;

int main()
{

    typedef pair<int, int> range_t;

    map<range_t, string> filenames_by_range;

    range_t range = make_pair(10, 100);

    filenames_by_range.insert( pair<range_t, string>(range, "output_filename") );
}
