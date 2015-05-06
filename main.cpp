#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>
#include <stdio.h>

const int mutate_pro = 15;
const int crossover_pro = 40;
const int pop_size = 100;
const std::string goal = "BENCE";

int rand_num(int n)
{
    return std::rand() % n;
}

std::string rand_str(int n)
{
    srand(time(NULL));

    std::string tmp = "";
    for(int i = 0; i<n; i++)
    {
        tmp += 'A' + rand_num('Z' - 'A');
    }

    return tmp;
}

int fitness (std::string str)
{
    int cnt = 0;
    for(int i = 0; i<str.length(); i++)
    {
        if(goal[i] == str[i]) cnt++;
    }

    return cnt;
}

void mutate (std::string& str)
{
    if(rand_num(100) < mutate_pro)
    {
        int id = rand_num(str.length());
        str[id] = rand_num('Z' - 'A');
    }
}

void crossover (std::string& a, std::string& b)
{
    if(fitness(a) > fitness(b))
    {
        for(int i = 0; i<a.length(); i++)
        {
            if(rand_num(100) < crossover_pro)
            {
                b[i] = a[i];
            }
        }
    }
    else
    {
        for(int i = 0; i<a.length(); i++)
        {
            if(rand_num(100) < crossover_pro)
            {
                a[i] = b[i];
            }
        }

    }
}

int main()
{
    std::vector<std::string> list;

    for(int i = 0; i<pop_size; i++)
    {
        std::string str = rand_str(goal.length());
        list.push_back(str);
    }

    int best = 0;
    while(best != goal.length())
    {
        for(std::vector<std::string>::iterator i = list.begin(); i != list.end(); i++)
        {
            mutate(*i);
            crossover(*i, list.at(rand_num(list.size())));
        }

        int min = goal.length();
        int id = 0;
        for(int i = 0; i<list.size(); i++)
        {
            if(fitness(list.at(i)) < min)
            {
                min = fitness(list.at(i));
                id = i;
            }
        }

        list.erase(list.begin() + id);
        std::string str = rand_str(goal.length());
        list.push_back(str);

        int max = 0;
        id = 0;
        for(int i = 0; i<list.size(); i++)
        {
            if(fitness(list.at(i)) > max)
            {
                max = fitness(list.at(i));
                id = i;
            }
        }

        std::cout << fitness(list.at(id)) << " " << list.at(id) << std::endl;
    }

    return 0;
}
