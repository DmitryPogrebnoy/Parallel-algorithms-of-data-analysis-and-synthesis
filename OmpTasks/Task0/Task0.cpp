#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    string const delims{ " \t\n" };
    string inputString = argv[1];
    size_t begin, pos = 0;
    int counter = 0;
    while ((begin = inputString.find_first_not_of(delims, pos)) != std::string::npos)
    {
        pos = inputString.find_first_of(delims, begin + 1);
        counter++;
    }
    cout << "Input string contains " << counter << " words" << endl;
}