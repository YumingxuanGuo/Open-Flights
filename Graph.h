#pragma once
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <math.h>
#include <sstream>
#include <queue>
#include <stdlib.h>

using std::string;
using std::vector;
using std::list;
using std::unordered_map;
using std::queue;

class Graph {
  private:
    struct Node {
      /* data */
      string name;            // airport's 3-digit name code (UPPERCASE)
      vector<Node*> adj;      // vector of destination airports
      bool marked;            // whether it has been visited
      bool inService;
      Node* prev;
      double d;
      int regionNumber;
      double longitude;
      double latitude;
      Node(string airport_name, double airport_longitude, double airport_latitude) : 
          name(airport_name), marked(false), inService(true), prev(NULL), d(INT64_MAX), regionNumber(-1), longitude(airport_longitude), latitude(airport_latitude) {};
    };

  public:
    class Iterator : std::iterator<std::forward_iterator_tag, Graph::Node> {
      public:
        Iterator();
        Iterator(Node* start);
        Iterator & operator++();
        string operator*();
        bool operator!=(const Iterator &other);
      
      public:
        Node* current;
        queue<Node*> q;
        unordered_map<Node*, bool> visited;
    };

  private: 
    void readAirports(string & filename);
    void readRoutes(string & filename);

    Node* start;
    unordered_map<string, Node*> airports;
    // unordered_map<Node*, float> betweennessCentrality;
    
  public:
    Iterator begin() const;
    Iterator end() const;

    Graph();
    ~Graph();
    unordered_map<string, vector<string>> getShortestPaths(string name);  // Assume in service.
    unordered_map<string, vector<string>> getShortestPaths(Node* node);
    unordered_map<int, vector<string>> findSCC();

    double dist(Node* v, Node* u);
    double degToRad(double degree);

    int getLable(string name) {return airports.at(name)->regionNumber;}

    void mark(Node* v) {v->marked = true;}
    bool marked(Node* v) {return v->marked;}
    void unmarkAll();

    void printShortestPath();
    void printSCC();

    void disable(vector<string> &list);
    void disable(Node* v) {v->inService = false;}
    void enable(Node* v) {v->inService = true;}
    bool servicable(Node* v) {return v->inService;}
    void enableAll();

    list<Graph::Node*> topologicalSort();
    unordered_map<Node*, vector<Node*>> transpose();
    void DFS_TS(Node* v, list<Graph::Node*> &Q);
    void DFS_SCC(Node* v, vector<string> &component, int region, unordered_map<Node*, vector<Node*>> &t);
};