#include "Graph.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

using std::ifstream;
using std::priority_queue;
using std::pair;
using std::getline;


void Graph::readAirports(string & filename) {
  ifstream file(filename);
  string line;
  vector<string> data;
  getline(file, line);  // ignore the first row
  if (file.is_open()) {
    while (getline(file, line)) {
      data.clear();
      // split and store data
      std::stringstream ss(line);
      string part;
      while (getline(ss, part, ',')) {
        data.push_back(part);
      }
      // data[4] is 3-digit airport name code
      // data[7] is longitude and data[6] is latitude
      if (data.size() > 7 && airports.find(data[4]) == airports.end()) {
        airports[data[4]] = new Node(data[4], atof(data[7].c_str()), atof(data[6].c_str()));
      }
    }
  } else {
    // throw exceptions
    std::cout << "The file is not opened for read." << std::endl;
  }
}

void Graph::readRoutes(string & filename) {
  ifstream file(filename);
  string line;
  vector<string> data;
  getline(file, line);  // ignore the first row
  if (file.is_open()) {
    while (getline(file, line)) {
      // split and store data
      data.clear();
      std::stringstream ss(line);
      string part;
      while (getline(ss, part, ',')) {
        data.push_back(part);
      }
      // data[2] is source airport, data[4] is destination airport.
      if (airports.find(data[2]) != airports.end() && airports.find(data[4]) != airports.end()) {
        vector<Node*> reachable_airports = airports.at(data[2])->adj;
        if (std::find(reachable_airports.begin(), reachable_airports.end(), airports.at(data[4])) == reachable_airports.end()) {
          airports.at(data[2])->adj.push_back(airports.at(data[4]));
        }
      }
    }
  } else {
    // throw exceptions
    std::cout << "The file is not opened for read." << std::endl;
  }
}

Graph::Graph() {
  string filename1 = "data/airports.csv";
  string filename2 = "data/routes.csv";
  readAirports(filename1);
  readRoutes(filename2);
}

Graph::~Graph() {
  for (auto &pair : airports) {
    delete pair.second;
  }
}

unordered_map<string, vector<string>> Graph::getShortestPaths(string name) {
  return getShortestPaths(airports.at(name));
}

unordered_map<string, vector<string>> Graph::getShortestPaths(Node* node) {

  // Initialization.
  unmarkAll();
  start = node;
  unordered_map<string, vector<string>> paths;
  priority_queue<pair<double, Node*>, vector<pair<double, Node*>>,
      std::greater<pair<double, Node*>>> pq;
  node->d = 0;

  // Dijkstra's edge relaxation.
  pq.push({node->d, node});
  while (!pq.empty()) {
    Node* v = pq.top().second;
    pq.pop();
    mark(v);
    for (Node* u : v->adj) {
      if (marked(u) || !servicable(u)) continue;
      if (u->d > v->d + dist(v, u)) {
        u->d = v->d + dist(v, u);
        u->prev = v;
        pq.push({u->d, u});
      }
    }
  }

  // Outputs into a map.
  for (const auto &pair : airports) {
    Node* n = pair.second;
    vector<string> path;
    string name = n->name;
    if (!n->prev) {
      path.push_back("N/A");
      paths[name] = path;
      continue;
    }
    path.push_back(std::to_string(n->d) + " KM");
    path.push_back(n->name);
    int count = 0;
    while (n) {
      n = n->prev;
      if (n) {
        path.push_back(n->name);
        count++;
      }
    }
    path.push_back(std::to_string(count) + " FLIGHTS");
    std::reverse(path.begin(), path.end());
    paths[name] = path;
  }

  return paths;
}

void Graph::disable(vector<string> &list) {
  for (string &name : list) {
    disable(airports.at(name));
  }
}

void Graph::enableAll() {
  for (const auto &pair : airports) {
    Node* airport = pair.second;
    enable(airport);
  }
}

void Graph::unmarkAll() {
  for (const auto &pair : airports) {
    Node* airport = pair.second;
    airport->marked = false;
  }
}

unordered_map<Graph::Node*, vector<Graph::Node*>> Graph::transpose() {
  unordered_map<Node*, vector<Node*>> t;
  for (const auto &pair : airports) {
    Node* airport = pair.second;
    for (const auto &n : airport->adj) {
      vector<Node*> vec;
      if (t.find(n) == t.end()) {
        vec.push_back(airport);
        t[n] = vec;
      } else {
        vec = t.at(n);
        vec.push_back(airport);
        t[n] = vec;
      }
    }
  }
  return t;
}

unordered_map<int, vector<string>> Graph::findSCC() {

  // Initialization.
  unmarkAll();

  // Topologically sort the nodes using DFS.
  list<Node*> Q = topologicalSort();

  // Create a temporary map representing the graph with reversed edges.
  unordered_map<Node*, vector<Node*>> t = transpose();

  // Re-initialization.
  unmarkAll();
  unordered_map<int, vector<string>> scc;

  // Second DFS to identify different strongly connected components.
  int region = 1;
  for (Node* v : Q) {
    if (!servicable(v)) continue;
    if (!marked(v)) {
      vector<string> component;
      DFS_SCC(v, component, region, t);
      scc[region] = component;
      region++;
    }
  }

  return scc;
}

list<Graph::Node*> Graph::topologicalSort() {
  list<Graph::Node*> Q;
  for (const auto &pair : airports) {
    Node* v = pair.second;
    if (!servicable(v)) continue;
    if (!marked(v)) {
      DFS_TS(v, Q);
    }
  }
  return Q;
}

void Graph::DFS_TS(Node* v, list<Graph::Node*> &Q) {
  mark(v);
  for (Node* u : v->adj) {
    if (!servicable(u)) continue;
    if (!marked(u)) {
      DFS_TS(u, Q);
    }
  }
  Q.push_front(v);
}

void Graph::DFS_SCC(Node* v, vector<string> &component, int region, 
    unordered_map<Node*, vector<Node*>> &t) {
  mark(v);
  v->regionNumber = region;
  for (Node* u : t[v]) {
    if (!servicable(u)) continue;
    if (!marked(u)) {
      DFS_SCC(u, component, region, t);
    }
  }
  component.push_back(v->name);
}

Graph::Iterator::Iterator() {
  current = nullptr;
}

Graph::Iterator::Iterator(Node* v) {
  current = v;
  visited[v] = true;
  for (Node* node : v->adj) {
    q.push(node);
    visited[node] = true;
  }
}

Graph::Iterator & Graph::Iterator::operator++() {
  if (q.empty()) {
    current = nullptr;
    return *this;
  }
  Node* v = q.front();
  q.pop();
  current = v;
  for (Node* node : v->adj) {
    if (visited.find(node) == visited.end()) {
      visited[node] = true;
      q.push(node);
    }
  }
  return *this;
}

string Graph::Iterator::operator*() {
  return current->name;
}

bool Graph::Iterator::operator!=(const Graph::Iterator &other) {
  return current != other.current;
}

Graph::Iterator Graph::begin() const {
  return Iterator(start);
}

Graph::Iterator Graph::end() const {
  return Iterator();
}

double Graph::dist(Node* v, Node* u) {
  double distance;
  double lo1 = v->longitude, lo2 = u->longitude;
  double la1 = v->latitude, la2 = u->latitude;
  distance = sin(degToRad(la1)) * sin(degToRad(la2)) + cos(degToRad(la1)) * cos(degToRad(la2)) * cos(degToRad(lo1-lo2));
  distance = acos(distance);
  distance = distance * 6371;
  return distance;
}

double Graph::degToRad(double degree) {
  return degree/180 * M_PI;
}