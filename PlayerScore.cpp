#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class PlayerScore
{
private:
    int score_;
    string last_;
    string first_;

public:
    PlayerScore(string line) {}
    ~PlayerScore() = default;
    int getScore() { return score_; }
    string getLast() { return last_; }
    string getFirst() { return first_; }
    string prettyprint() { cout << "|" << setw(20) << last_ << "|" << setw(20) << first_ << "|" << setw(20) << score_ << "|" << endl; }
    bool operator<(const PlayerScore &rhs) const
    {
        return score_ < rhs.score_;
    }
};

PlayerScore::PlayerScore(string line)
{
    string delimiter = ",";
    string token;
    int pos = 0;
    int i = 0;
    while ((pos = line.find(delimiter)) != string::npos)
    {
        token = line.substr(0, pos);
        if (i == 0)
        {
            last_ = token;
        }
        else if (i == 1)
        {
            first_ = token;
        }
        else if (i == 2)
        {
            score_ = stoi(token);
        }
        line.erase(0, pos + delimiter.length());
        i++;
    }
}

int main()
{
    string filename = "players.csv";
    ifstream file(filename);
    string line;
    vector<PlayerScore> players;
    while (getline(file, line))
    {
        PlayerScore player(line);
        players.push_back(player);
    }
    cout << "Unsorted Players: " << endl;
    for (auto &&player : players)
    {
        player.prettyprint();
    }
    sort(players.begin(), players.end());
    cout << "Sorted Players: " << endl;
    for (auto &&player : players)
    {
        player.prettyprint();
    }
}
