#include "Graph.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::getline;
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char **argv) {
	// Input Check
  // e.g. ./main "data/Out of Service.csv" "data/From to.csv"
  if (argc != 3) {
    cout << "Invalid number of inputs!" << endl;
  }
  string outOfServiceFile = argv[1];
  string fromToFile = argv[2];

  // Initialize
  Graph graph;
	ifstream file1(outOfServiceFile);
  string line1;
  vector<string> outOfService;
  getline(file1, line1);  // ignore the first row
  if (file1.is_open()) {
		vector<string> temp;
    while (getline(file1, line1)) {
      // split and store data
			temp.clear();
      std::stringstream ss(line1);
      string part;
      while (getline(ss, part, ',')) {
        temp.push_back(part);
      }
      // temp[4] is 3-digit airport name code
      if (temp.size() > 7 && temp[4] != "\\N") {
        outOfService.push_back(temp[4]);
      }
    }
  } else {
    // throw exceptions
    std::cout << "'Out of Service.csv' is not opened for read." << std::endl;
  }
	graph.disable(outOfService);

	ifstream file2(fromToFile);
  string line2;
  vector<string> destinations;
  getline(file2, line2);
	string start = line2;
  if (file2.is_open()) {
    while (getline(file2, line2)) {
      // split and store data
      destinations.push_back(line2);
    }
  } else {
    // throw exceptions
    std::cout << "'From to.csv' is not opened for read." << std::endl;
  }

	unordered_map<string, vector<string>> paths = graph.getShortestPaths(start);
  std::cout << "Shortest paths from " << start << ":" << endl << endl;
	for (auto &destination : destinations) {
		std::cout << destination << ": ";
		for (auto &path : paths.at(destination)) {
			std::cout << path << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	unordered_map<int, vector<string>> SCC = graph.findSCC();
	int count = 0;
	std::cout << "Strongly Connected Component of " << start << ":" << std::endl;
	vector<string> &component = SCC.at(graph.getLable(start));
	for (auto airport : component) {
		std::cout << airport << " ";
		count++;
	}
	std::cout << std::endl << std::to_string(count) << " Airports" << std::endl;
	
  char save;
  cout << "Do you want to save the result? (y/n)" << endl;
  cin >> save;
  while (save != 'y' && save != 'n') {
    cout << "Invalid choice" << endl;
    cin >> save;
  }
  if (save == 'y') {
    ofstream fileSave;
    fileSave.open("Saved.txt");
    fileSave << "Shortest paths from " << start << ":" << endl << endl;
    for (auto &destination : destinations) {
      fileSave << destination << ": ";
      for (auto &path : paths.at(destination)) {
        fileSave << path << "  ";
      }
      fileSave << endl;
    }
    fileSave << endl << endl << endl;
    count = 1;
    fileSave << "Strongly Connected Component of " << start << ":" << endl << endl;
    vector<string> &component = SCC.at(graph.getLable(start));
    for (auto airport : component) {
      fileSave << airport << " ";
      if (count % 20 == 0) {
        fileSave << endl;
      }
      count++;
    }
    fileSave << endl << endl << std::to_string(count - 1) << " Airports in total." << endl;
  }
	return 0;
}