#include "pch.h"
#include "GoldbergTarjanAlgorithm.h"
#include <vector>

/*
    EmptyGraphsAndSimpleGraphs category checks if algorithm works correctly with irregular graphs
*/

TEST(EmptyAndSimpleGraphs, Test1) {
    Graph g(1);

    EXPECT_EQ(g.getMaxFlow(0, 0), 0);
}

TEST(EmptyAndSimpleGraphs, Test2) {
    Graph g(2);
    g.addEdge(0, 1, 10);

    EXPECT_EQ(g.getMaxFlow(0, 1), 10);
}

TEST(EmptyAndSimpleGraphs, Test3) {
    Graph g(3);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 15);

    EXPECT_EQ(g.getMaxFlow(0, 2), 10);
}

TEST(EmptyAndSimpleGraphs, Test4) {
    Graph g(4);
    g.addEdge(0, 1, 30);
    g.addEdge(1, 2, 15);
    g.addEdge(1, 3, 30);
    g.addEdge(3, 2, 30);

    EXPECT_EQ(g.getMaxFlow(0, 2), 30);
}

TEST(EmptyAndSimpleGraphs, Test5) {
    Graph g(3);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 0);

    EXPECT_EQ(g.getMaxFlow(0, 2), 0);
}

/*
    MultipleEdgesBeetwenNodes category checks if algorithm works correctly with graphs were one node has multiple edges
*/

TEST(MultipleEdgesBeetwenNodes, Test1) {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 1);

    EXPECT_EQ(g.getMaxFlow(0, 2), 2);
}

/*
    FullCapacityGraph category checks if algorithm works correctly with graphs were capacity sums up to the sink
*/

TEST(FullCapacityGraph, Test1) {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 10);
    g.addEdge(2, 3, 20);

    EXPECT_EQ(g.getMaxFlow(0, 3), 30);
}

/*
    HighCapacityEdgeLowCapacityEdge category checks if algorithm works correctly with graphs were edges are both very high capacity and low capacity
*/

TEST(HighCapacityEdgeLowCapacityEdge, Test1) {
    Graph g(4);
    g.addEdge(0, 1, 30);
    g.addEdge(1, 2, 10);
    g.addEdge(2, 3, 40);  // <---
    g.addEdge(1, 3, 20);

    EXPECT_EQ(g.getMaxFlow(0, 3), 30);
}

TEST(HighCapacityEdgeLowCapacityEdge, Test2) {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 100); // <---
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 15);
    g.addEdge(1, 4, 20);

    EXPECT_EQ(g.getMaxFlow(0, 4), 15);
}

TEST(HighCapacityEdgeLowCapacityEdge, Test3) {
    Graph g(5);
    g.addEdge(0, 1, 100); // <---
    g.addEdge(0, 2, 5);
    g.addEdge(2, 3, 10);
    g.addEdge(3, 4, 15);
    g.addEdge(1, 4, 20);

    EXPECT_EQ(g.getMaxFlow(0, 4), 25);
}

TEST(HighCapacityEdgeLowCapacityEdge, Test4) {
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 50);  // <---
    g.addEdge(1, 3, 10);
    g.addEdge(1, 4, 20);
    g.addEdge(2, 5, 100); // <---
    g.addEdge(3, 5, 5);
    g.addEdge(4, 5, 15);

    EXPECT_EQ(g.getMaxFlow(0, 5), 55);
}

TEST(HighCapacityEdgeLowCapacityEdge, Test5) {
    Graph g(6);
    g.addEdge(0, 1, 20);
    g.addEdge(0, 2, 50);
    g.addEdge(1, 3, 10);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 5, 100); // <---
    g.addEdge(3, 5, 20);
    g.addEdge(4, 5, 15);

    EXPECT_EQ(g.getMaxFlow(0, 5), 65);
}

/*
    BasicGraphs category checks if algorithm works correctly with generic graphs
*/

TEST(BasicGraphs, Test1) {
    Graph g(6);
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    EXPECT_EQ(g.getMaxFlow(0, 5), 23);
}

TEST(BasicGraphs, Test2) {
    Graph g(8);
    g.addEdge(0, 2, 11);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 16);
    g.addEdge(2, 3, 13);
    g.addEdge(3, 4, 10);
    g.addEdge(4, 5, 12);
    g.addEdge(5, 6, 4);
    g.addEdge(6, 7, 14);
    g.addEdge(3, 7, 9);
    g.addEdge(1, 6, 20);
    g.addEdge(6, 4, 7);

    EXPECT_EQ(g.getMaxFlow(0, 7), 13);
}

TEST(BasicGraphs, Test3) {
    Graph g(7);
    g.addEdge(0, 2, 31);
    g.addEdge(1, 2, 14);
    g.addEdge(2, 3, 57);
    g.addEdge(3, 4, 4);
    g.addEdge(3, 5, 17);
    g.addEdge(4, 5, 12);
    g.addEdge(5, 6, 4);

    EXPECT_EQ(g.getMaxFlow(0, 6), 4);
}

/*
    ALotOfEdgesGraphs categry checks if algorithm works correctly with graphs that have a lot of edges
*/

TEST(ALotOfEdgesGraphs, Test3) {
    Graph g(10);
    g.addEdge(0, 2, 99);
    g.addEdge(0, 1, 59);
    g.addEdge(0, 4, 101);
    g.addEdge(0, 7, 69);
    g.addEdge(1, 2, 107);
    g.addEdge(1, 3, 45);
    g.addEdge(1, 4, 57);
    g.addEdge(2, 3, 40);
    g.addEdge(2, 4, 17);
    g.addEdge(3, 4, 19);
    g.addEdge(3, 5, 4);
    g.addEdge(3, 6, 31);
    g.addEdge(4, 5, 81);
    g.addEdge(4, 6, 13);
    g.addEdge(4, 7, 4);
    g.addEdge(4, 8, 43);
    g.addEdge(5, 6, 12);
    g.addEdge(5, 7, 32);
    g.addEdge(5, 8, 111);
    g.addEdge(6, 7, 79);
    g.addEdge(6, 8, 7);
    g.addEdge(7, 8, 32);
    g.addEdge(1, 5, 15);
    g.addEdge(4, 5, 12);
    g.addEdge(5, 6, 4);
    g.addEdge(7, 9, 31);
    g.addEdge(2, 9, 14);
    g.addEdge(3, 9, 57);

    EXPECT_EQ(g.getMaxFlow(0, 9), 102);
}

#include<fstream>
#include<chrono>
using namespace std::chrono;
ofstream fout("inputs.txt");
ofstream out("results.txt");
vector <int> results;

TEST(MoreEdges, Test1) {
    int V, E;
    ifstream in("tests\\MoreEdges\\1.txt");
    in >> V >> E;
    Graph g(V);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        in >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    fout << V << " " << E << endl;
    auto start = high_resolution_clock::now();
    g.getMaxFlow(0, V - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    out << duration.count() << endl;
}

TEST(MoreEdges, Test2) {
    int V, E;
    ifstream in("tests\\MoreEdges\\2.txt");
    in >> V >> E;
    Graph g(V);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        in >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    fout << V << " " << E << endl;
    auto start = high_resolution_clock::now();
    g.getMaxFlow(0, V - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    out << duration.count() << endl;
}

TEST(MoreEdges, Test3) {
    int V, E;
    ifstream in("tests\\MoreEdges\\3.txt");
    in >> V >> E;
    Graph g(V);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        in >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    fout << V << " " << E << endl;
    auto start = high_resolution_clock::now();
    g.getMaxFlow(0, V - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    out << duration.count() << endl;
}

TEST(MoreEdges, Test4) {
    int V, E;
    ifstream in("tests\\MoreEdges\\4.txt");
    in >> V >> E;
    Graph g(V);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        in >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    fout << V << " " << E << endl;
    auto start = high_resolution_clock::now();
    g.getMaxFlow(0, V - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    out << duration.count() << endl;
}

TEST(MoreEdges, Test5) {
    int V, E;
    ifstream in("tests\\MoreEdges\\5.txt");
    in >> V >> E;
    Graph g(V);
    int u, v, w;
    for (int i = 0; i < E; i++) {
        in >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    fout << V << " " << E << endl;
    auto start = high_resolution_clock::now();
    g.getMaxFlow(0, V - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    out << duration.count() << endl;

    fout << endl << "end of MoreEdges tests" << endl;
    out << "end of MoreEdges tests" << endl;
}