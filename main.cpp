#include <string>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>

const int mutate_pro = 10;
const int pop_size = 100;
const int max_gen = 5000;
const std::string goal = "BENCUSMAKESMAGIC";

inline int rand_num(int n)
{
    return std::rand() % n;
}

std::string rand_str(int n)
{
    std::string tmp = "";
    for(int i = 0; i<n; i++)
    {
        tmp += 'A' + rand_num('Z' - 'A' + 1 );
    }

    return tmp;
}

class Entity
{
    private:
        int fitness;
        std::string DNA;
    public:
        Entity()
        {
            DNA = rand_str(goal.length());
            fitness = calc_fitness(DNA);
        }
        Entity(const std::string& str) : DNA(str)
        {
            fitness = calc_fitness(str);
        }
        int calc_fitness (std::string str)
        {
            int cnt = 0;
            for(int i = 0; i<str.length(); i++)
            {
                if(goal[i] == str[i]) cnt++;
            }

            return cnt;
        }

        void mutate ()
        {
            if(rand_num(100) < mutate_pro)
            {
                int id = rand_num(DNA.length());
                DNA[id] = 'A' + rand_num('Z' - 'A');
            }
        }

        std::string get_str() const {return DNA;}
        int get_fit() const {return fitness;}
};


Entity crossover (const Entity& a, const Entity& b)
{
    std::string new_str = "";
    std::string str_a = a.get_str();
    std::string str_b = b.get_str();

    for(int i = 0; i< str_a.length(); i++)
    {
        if(std::rand() % 2  == 0)
        {
            new_str += str_a[i];
        }
        else {
            new_str += str_b[i];
        }
    }

    //std::cout << str_a << " "<< str_b << ":" << new_str << std::endl;
    //getchar();
    return Entity(new_str);
}

bool cmp (const Entity& a, const Entity& b)
{
    if(a.get_fit() > b.get_fit())
        return true;

    return false;
}

int main()
{
    srand(time(NULL));
    std::vector<Entity> vec;

    for(int i = 0; i<pop_size; i++)
        vec.push_back(Entity());

    int gen = 0;
    int best = 0;
    while(best != goal.length() && gen < max_gen)
    {
        gen++;
        std::vector<Entity> new_entities;
        for(std::vector<Entity>::iterator i = vec.begin(); i != vec.end(); i++)
        {

            (*i).mutate();

            Entity a = vec.at(rand_num(vec.size()));
            Entity b = vec.at(rand_num(vec.size()));
            Entity new_ent = crossover(a, b);

            new_entities.push_back(new_ent);
        }

        vec.insert(vec.end(), new_entities.begin(), new_entities.end());

        std::sort(vec.begin(), vec.end(), cmp);

        int cnt = vec.size() - pop_size;
        for(int i = 0; i<cnt; i++)
        {
            vec.erase(vec.end());
        }

        best = (*vec.begin()).get_fit();
        std::cout << gen << ". generation " << best << " " << (*vec.begin()).get_str() << std::endl;
    }

    return 0;
}
