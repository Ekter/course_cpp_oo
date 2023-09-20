#include <string>
#include <iostream>
#include <fstream>
#include <map>

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
    cout << hash_ << " " << val << endl;
    return input_st{hash_, val};
}

map<double, string> parseFile(string filename)
{
    map<double, string> map_;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        input_st tmp = parseLine(line);
        map_[tmp.number] = tmp.hash;
    }
    return map_;
}

int parseInput(string input, map<double, string> map_, double precision = 0.01)
{
    if (input == "END")
    {
        cout << "Goodbye!" << endl;
        return -1;
    }
    int found_number = 0;
    if (input.substr(0, 1) == "+")
    {
        cout << "Searching for range(" << precision * 100 << "\% precision)" << endl;
        input = input.substr(1);
        double input_ = stod(input);
        map<double, string>::iterator it = map_.lower_bound(input_ * (1 - precision));
        while (it->first <= input_ * (1 + precision))
        {
            cout << " * Pair found :" << endl;
            cout << "  -> " << it->second << " " << it->first << endl;
            it++;
            found_number++;
        }
    }
    else
    {
        cout << "Searching for exact hash" << endl;
        for (auto &[key, value] : map_)
        {
            if (value == input)
            {
                cout << " * Pair found : " << endl;
                cout << "  -> " << value << " " << key << endl;
                found_number++;
            }
        }
    }
    if (found_number == 0)
    {
        cout << "No pair found" << endl;
    }
    return found_number;
}

int main()
{
    map<double, string> myMap = parseFile("mean_and_median/data/full_10000.txt");
    cout << "Map size main : " << myMap.size() << endl;
    cout << "Enter hash/value to search for : " << endl;
    string input = "";
    while (input != "END")
    {
        cin >> input;
        if (parseInput(input, myMap, 0.01) < 0)
        {
            return 0;
        }
    }
}
