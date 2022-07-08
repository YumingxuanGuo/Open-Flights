#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Graph.h"

TEST_CASE("Path form ORD to NKG")
{
	Graph graph;
    vector<string> destinations{"NKG"};
    unordered_map<string, vector<string>> paths = graph.getShortestPaths("ORD");
	REQUIRE(5 == paths.at("NKG").size());
    vector<string> ans{"2 FLIGHTS", "ORD", "ICN", "NKG", "11460.750090 KM"};
    REQUIRE(paths.at("NKG") == ans);
}

TEST_CASE("Path form POI to SYM")
{
	Graph graph;
    vector<string> destinations{"SYM"};
    unordered_map<string, vector<string>> paths = graph.getShortestPaths("POI");
	REQUIRE(10 == paths.at("SYM").size());
    vector<string> ans{"7 FLIGHTS", "POI", "LPB", "VVI", "MAD", "IST", "KTM", "KMG", "SYM", "20000.461738 KM"};
    REQUIRE(paths.at("SYM") == ans);
}

TEST_CASE("Path from POI to SYM after Disabling")
{
	Graph graph;
    vector<string> destinations{"SYM"};
    vector<string> outOfService{"VVI", "IST"};
    graph.disable(outOfService);
    unordered_map<string, vector<string>> paths = graph.getShortestPaths("POI");
	REQUIRE(10 == paths.at("SYM").size());
    vector<string> ans{"7 FLIGHTS", "POI", "LPB", "BOG", "FLL", "DTW", "PEK", "KMG", "SYM", "20220.266908 KM"};
    REQUIRE(paths.at("SYM") == ans);
}

TEST_CASE("SCC")
{
	Graph graph;
    unordered_map<int, vector<string>> SCC = graph.findSCC();
    REQUIRE(SCC.at(graph.getLable("JFK")).size() == 3172);
}

TEST_CASE("SCC after Disabling")
{
	Graph graph;
    vector<string> outOfService{"ORD"};
    graph.disable(outOfService);
    unordered_map<int, vector<string>> SCC = graph.findSCC();
    REQUIRE(SCC.at(graph.getLable("JFK")).size() == 3163);
}