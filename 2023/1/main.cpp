#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using std::string;

const string digits[9] = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

bool isNum(char c)
{
    return c >= '0' && c <= '9';
}

int compare(string line)
{
    for (int i=0; i<9; i++)
    {
        if (strncmp(line.c_str(), digits[i].c_str(), digits[i].length()) == 0) return i+1;
    }
    return -1;
}

void part1(string line, int& sum)
{
    int i = 0;
    int j = line.length();
    while(i<j && (!isNum(line[i]) || !isNum(line[j])))
    {
        if (!isNum(line[i])) i++;
        if (!isNum(line[j])) j--;
    }
    int n1 = line[i]-'0';
    int n2 = line[j]-'0';
    switch (isNum(line[i])*10+isNum(line[j]))
    {
        case 11: 
            sum += n1*10 + n2;
            break;
        case 1:
            sum += n2 + n2*10;
            break;
        case 10:
            sum += n1 + n1*10;
            break;
    }
}

void part2(string line, int& sum)
{
    int i = 0;
    int j = line.length()-1;
    int n1 = -1;
    int n2 = -1;
    while (i<=j && (n1 == -1 || n2 == -1))
    {  
        if (isNum(line[i]) && n1==-1)
        {
            n1 = line[i]-'0';
        } else if(n1==-1){
            if (int n=compare(line.substr(i)); n!=-1)
            {
                n1 = n;
            } else {
                i++;
            }
        }
        if (isNum(line[j]) && n2==-1)
        {
            n2 = line[j]-'0';
        } else if(n2==-1){
            if (int n=compare(line.substr(j-1, line.length()-j+1)); n!=-1)
            {
                n2 = n;
            } else {
                j--;
            }
        }
    }
    int num = 0;
    switch((n1!=-1)*10+(n2!=-1))
    {
        case 11:
            num += n1*10 + n2;
            break;
        case 10:
            num += n1*10 + n1;
            break;  
        case 1:
            num += n2*10 + n2;
            break;  
    }
    sum += num;
}

int main(int argc, char* argv[])
{
    string line;
    std::ifstream file("data");
    int sum1 = 0;
    int sum2 = 0;
    while(std::getline(file, line))
    {
        part1(line, sum1);
        part2(line, sum2);
    }
    std::cout << "Part 1: " << sum1 << "\n";
    std::cout << "Part 2: " << sum2 << "\n";
    file.close();
}
