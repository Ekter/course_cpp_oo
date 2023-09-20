#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

struct input_st
{
    string hash;
    double number;
};

input_st parseLine(string line)
{
    string hash_ = line.substr(0, 12);
    string second_ = line.substr(12);
    double val = stod(second_);
    cout << hash_ <<" "<< val << endl;
    return input_st{hash_, val};
}

unordered_map<string, double> parseFile(string filename)
{
    unordered_map<string, double> map_;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        input_st tmp = parseLine(line);
        map_[tmp.hash] = tmp.number;
    }
    return map_;
}

int parseInput(string input, unordered_map<string, double> map_)
{
    if (input == "END")
    {
        cout << "Goodbye!" << endl;
        return -1;
    }
    if (map_.count(input)==0)
    {
        cout << "Invalid ID, not in map" << endl;
        return 0;
    }
    cout << "Value found : " << map_[input] << endl;
    return 0;
}

int main()
{
    unordered_map<string, double> myMap = parseFile("mean_and_median/data/full_10.txt");
    cout << "Map size main : " << myMap.size() << endl;
    cout << "Enter ID to search for : " << endl;
    string input = "";
    cin >> input;
    while (input != "END")
    {
        if (parseInput(input, myMap) < 0)
        {
            return 0;
        }
        cin >> input;
    }
}
