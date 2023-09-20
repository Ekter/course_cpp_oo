#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int hist_maker(string filename)
{
    ifstream file(filename);
    vector<int> hist(81, 0);
    string line;
    getline(file, line);
    while (line != "")
    {
        // read line from file
        cout << line << endl;
        // convert line to int and find the bucket
        int num = stoi(line) / 100;
        // increment the bucket
        hist[num]++;
        getline(file, line);
    }
    // find the max value in the buckets
    int max = 0;
    for (int i = 0; i < hist.size(); i++)
    {
        if (hist[i] > max)
        {
            max = hist[i];
        }
    }
    // normalize the bucket to 60
    float norm = 60.0 / max;
    vector<int> hist_norm(81, 0);
    for (int i = 0; i < hist.size(); i++)
    {
        hist_norm[i] = hist[i] * norm;
    }
    // print the histogram
    for (int i = 0; i < hist.size(); i++)
    {
        cout << setw(5) << i * 100 << " " << setw(5) << hist[i] << " : "; // not padded the right way
        cout << string(hist_norm[i], '*');
        cout << endl;
    }
    // store the histogram in a 2d vector to rotate it
    vector<vector<char>> hist_2d(60, vector<char>(81, ' '));
    for (int i = 0; i < hist_norm.size(); i++)
    {
        for (int j = 0; j < hist_norm[i]; j++)
        {
            hist_2d[j][i] = '*'; // there should be a better way to do this
        }
    }
    cout << "Rotated Histogram: " << endl;
    // print the rotated histogram
    for (int i = hist_2d.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < hist_2d[i].size(); j++)
        {
            cout << hist_2d[i][j];
        }
        cout << endl;
    }
    cout << " 0" << setw(79) << "8000" << endl;
    return 0;
}

int main()
{
    hist_maker("mean_and_median/data/data_1000.txt");
    return 0;
}
