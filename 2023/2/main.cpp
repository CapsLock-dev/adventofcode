#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

int partOne(std::string line);
int partTwo(std::string line);
int getDigit(std::string digit);

int main(int argc, char* argv[])
{
    std::ifstream file("data");
    std::string line;
    int sum = 0;
    int sum2 = 0;
    while (std::getline(file, line))
    {
        sum += partOne(line);
        sum2 += partTwo(line);
    }
    std::cout << "Part One: " << sum << "\n";
    std::cout << "Part Two: " << sum2 << "\n";
    return 0;
}

int getDigit(std::string digit)
{
    int n = 0;
    int i = digit.length()-1;
    for (char c: digit) 
    {
        c -= '0';
        n += c * std::pow(10, i--); 
    }
    return n;
}

int partOne(std::string line)
{
    std::unordered_map<std::string, int> map = {
        {"green", 13},
        {"blue", 14},
        {"red", 12}
    };
    std::string color;
    std::string digit;
    int game = 0;
    int n = 0;
    while (line[n] != ':')
    {
        if (std::isdigit(line[n])) digit.push_back(line[n]);
        n++;
    }
    game = getDigit(digit);
    digit.clear();
    for (int i=n; i<(int)line.length(); i++)
    {
        if (std::isdigit(line[i]))
        {
            digit.push_back(line[i++]);
            while (std::isdigit(line[i]))
            {
                digit.push_back(line[i++]);
            }
            i--;
        } 
        else if (std::isalpha(line[i]))
        {
            color.push_back(line[i++]);
            while (std::isalpha(line[i]))
            {
                color.push_back(line[i++]);
            }
            i--;
            if (map.contains(color)) {
                map.at(color) = map.at(color) - getDigit(digit);
                if (map.at(color) < 0) 
                {
                    return 0;
                }
            }
            color.clear();
            digit.clear();
        } 
        else if (line[i] == ';')
        {
            map = {
                {"green", 13},
                {"blue", 14},
                {"red", 12}
            };
        }
    }
    return game;
}

int partTwo(std::string line)
{
    int power = 1;
    std::unordered_map<std::string, int> minCubes = {
        {"green", 1},
        {"blue", 1},
        {"red", 1}
    };
    std::unordered_map<std::string, int> currentCubes = {
        {"green", 1},
        {"blue", 1},
        {"red", 1}
    };
    std::string color;
    std::string digit;
    int n = 0;
    while (line[n] != ':') n++;
    for (int i=n; i<(int)line.length(); i++)
    {
        if (std::isdigit(line[i]))
        {
            digit.push_back(line[i++]);
            while (std::isdigit(line[i]))
            {
                digit.push_back(line[i++]);
            }
            i--;
        } 
        else if (std::isalpha(line[i]))
        {
            color.push_back(line[i++]);
            while (std::isalpha(line[i]))
            {
                color.push_back(line[i++]);
            }
            i--;
            if (currentCubes.contains(color))
            {
                if (currentCubes.at(color) < getDigit(digit))
                {
                    currentCubes.at(color) = getDigit(digit);
                }
            }
            color.clear();
            digit.clear();
        } 
        else if (line[i] == ';')
        {
            for (auto &pair : minCubes)
            {
                std::cout << "biggest " << minCubes.at(pair.first) << ": " << currentCubes.at(pair.first) << "\n" ;
                if (minCubes.at(pair.first) < currentCubes.at(pair.first))
                {
                    minCubes.at(pair.first) = currentCubes.at(pair.first);
                }
            }
            currentCubes = {
                {"green", 1},
                {"blue", 1},
                {"red", 1}
            };
            color.clear();
            digit.clear();
        }
    }
    std::cout << "\n";
    for (auto &pair : minCubes)
    {
        if (minCubes.at(pair.first) < currentCubes.at(pair.first))
        {
            minCubes.at(pair.first) = currentCubes.at(pair.first);
        }
        power *= pair.second;
        std::cout << pair.first << " : " << std::to_string(pair.second) << "\n";
    }
    std::cout << "power: " << power << "\n";
    return power;
}
