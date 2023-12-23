#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

int partOne(std::string line);

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

bool isSymbol(char c)
{
    return (!std::isdigit(c) && c != '.');
}

int parseDigit(std::string &line, int x)
{
    int i = x;
    std::string str;
    while (std::isdigit(line[i])) --i;
    i++;
    while (std::isdigit(line[i]))
    {
        str.push_back(line[i]);
        line[i++] = '.';
    }
    return getDigit(str);
}

std::vector<int> seekDigit(std::vector<std::string> &data, int y, int x)
{
    std::vector<int> digits = {};
    int i = y-1;
    int j = x-1;
    int I = y+1;
    int J = x+1;
    if (i < 0) i = y;
    if (x < 0) j = x;
    for (int ib = i;ib<=I;ib++)
    {
        for (int jb=j;jb<=J;jb++)
        {
            if (std::isdigit(data[ib][jb]))
            {
                int dig = parseDigit(data[ib], jb);
                digits.push_back(dig); 
            }
        }
    }
    return digits;
}

int main(int argc, char* argv[])
{
    std::ifstream file("data");
    std::string lineBuf;
    std::vector<std::string> data;
    int sum = 0;
    int sum2 = 0;
    while (std::getline(file, lineBuf))
    {
        data.push_back(lineBuf);
        if (data.size() >= 3)
        {
            for (size_t i=0; i<data.size()-1; ++i)
            {
                std::string line = data[i];
                for (size_t j=0; j<line.size(); ++j)
                {
                    if (isSymbol(line[j]))
                    {
                        int buff = 1; 
                        std::vector<int> vec = seekDigit(data, i, j);
                        for (int a : vec)
                        {
                            sum += a;
                            if (vec.size() >= 2) {
                                buff *= a;
                            }
                        }
                        if (buff > 1) sum2 += buff;
                    }
                }
            }
            data.erase(data.begin());
        }
    }
    std::cout << "Part One: " << sum << "\n";
    std::cout << "Part Two: " << sum2 << "\n";
    return 0;
}
