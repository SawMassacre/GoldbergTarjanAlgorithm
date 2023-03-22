#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

int MIN_PER_RANK = 3; //how fat dag should be
int MAX_PER_RANK = 3;
int MIN_RANKS = 3;    //how tall graph should be
int MAX_RANKS = 3;
int PERCENT = 50;     //chance of vertex having an edge

std::string changeFileName(std::string fileName, int num) {
    std::stringstream ss(fileName);
    std::string name;
    ss >> name >> num; // extract the name and number from the file name

    // increment the number and form the new file name
    std::string newFileName = name + std::to_string(num + 1) + ".txt";
    return newFileName;
}

std::ofstream out;

void Generator(std::string path) {
    long long t1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    out.open(path);
    std::vector <int> u, v, w;
    int vertices = 0, eCount = 0;
    srand((unsigned int)t1);
    int ranks = MIN_RANKS + (rand() % (MAX_RANKS - MIN_RANKS + 1));
    for (int i = 0; i < ranks; i++)
    {
        //new vertices with higher rank than previous ones
        int new_vertices = MIN_PER_RANK + (rand() % (MAX_PER_RANK - MIN_PER_RANK + 1));
        //edges from old vertices to new vertices
        for (int j = 0; j < vertices; j++)
            for (int k = 0; k < new_vertices; k++)
                if ((rand() % 100) < PERCENT) {
                    //printf ("%d %d\n", j, k + vertices); /* An Edge.  */
                    u.push_back(j);
                    v.push_back(k + vertices);
                    w.push_back(rand() % 100); //make odd rand less than 100
                    eCount++;
                }
        vertices += new_vertices; //accumulate into old vertices set
    }
    //path as string
    out << vertices << " " << eCount << std::endl;
    for (int i = 0; i < v.size(); i++) {
        out << u[i] << " " << v[i] << " " << w[i] << std::endl;
    }

    out.close();
}

int main() {
    int Amount;
    std::cin >> Amount;
    std::string path;
    for (int i = 0; i < Amount; i++) {
        path = changeFileName(path, i);
        Generator(path);
        path.clear();
    }
}

/*int MIN_PER_RANK = 1;
int MAX_PER_RANK = 14;
int MIN_RANKS = 3;
int MAX_RANKS = 15;
int PERCENT = 50; */