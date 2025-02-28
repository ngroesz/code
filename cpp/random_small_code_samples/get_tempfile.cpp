#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

string file_extension(const string & filename)
{
    size_t last_dot = filename.find_last_of(".");
    return filename.substr(last_dot + 1); 
}

string get_tempfile(string input_filename)
{
    string input_file_basename = basename((char *)input_filename.c_str());

    //stringstream temp_filename;
    //temp_filename << input_file_basename << ".temp." << file_extension(input_filename);

    return temp_filename.str();
}

int main()
{
    cout << "filename: " << get_tempfile("new_file.txt") << endl;
}

