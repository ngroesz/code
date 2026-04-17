#include <boost/bind.hpp>
#include <vector>
#include <iostream>
#include <map>

using namespace std;
using namespace boost;

bool comparator(int a, int b, map<int, double> & match_scores_by_title)
{
    map<int, double>::const_iterator itr;
    double a_score = 0, b_score = 0;

    itr = match_scores_by_title.find(a);
    if (itr != match_scores_by_title.end()) {
        a_score = itr->second;
    }

    itr = match_scores_by_title.find(b);
    if (itr != match_scores_by_title.end()) {
        b_score = itr->second;
    }

    if (a_score != 0 && b_score != 0) {
        return b_score < a_score;
    }
    return a < b;
}

int main()
{
    vector<int> match_titles;

    map<int, double> match_scores_by_title;

    match_scores_by_title.insert(pair<int, double>(101, 3.4));
    match_scores_by_title.insert(pair<int, double>(102, 2.7));
    match_scores_by_title.insert(pair<int, double>(103, 9.4));

    for (map<int, double>::iterator itr = match_scores_by_title.begin(); itr != match_scores_by_title.end(); ++itr) {
        match_titles.push_back(itr->first);
    }

    sort(
        match_titles.begin(),
        match_titles.end(),
        bind(comparator, _1, _2, match_scores_by_title)
    );

    for (vector<int>::iterator itr = match_titles.begin(); itr != match_titles.end(); ++itr) {
        cout << "title: " << *itr << endl;
    }
}
