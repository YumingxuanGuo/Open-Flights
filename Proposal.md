# Final Project Proposal

## Leading Question

Ever since the pendemics began, air travel has been largely influenced due to the shut down of certain airline routes. However, it is unclear how the shut down of certain airlines impact travel in certain regions. 

Target Goal: Using data from OpenFlights, to make a search tool for the airline routes in the United States, where users can input the unavailable air routes or airlines. It will be able to output the shortest path, airports that can be reached, and the importance of certain airports under the current airline route availability.

## Dataset Acquisition and Processing

Data of the airline routes can be obtained from the [website](https://openflights.org/data.html) in the format of ".csv" files. These data include the code of the airports, the available airlines among them, the distance between each two airports, etc. Each active airport serves as a node while each available airline serves as an edge in our graph construction. The weight of each edge will be the distance between two airports in each airline. We will filter the data and discard the problematic ones.

## Graph Algorithms

We plan to implement at least three functions using graph algorithms in our projects:

1. To find the shortest path from one airport to all other airports.

   **Algorithm:** Dijkstra's (single source shortest path) algorithm.

   **Input:** the departure airport.

   **Output:** a file contains all shortest paths from the given airports to others, in the order of BFS.

   **Time complexity:** O((|V|+|E|) lg|V|).

2. To find out the regions (strongly connected components) that can be fully traversed if certain routes are closed.

   **Algorithm:** Kosaraju (strongly connected component) algorithm.

   **Input:** the departure airport, a list of airline routes that are currently unavailable.

   **Output:** All the airports in the same strongly connected component of the departure airport.

   **Time complexity:** O(|V|+|E|).

3. To find the most important airports in a given region based on betweenness centrality.

   **Algorithm:** Use Dijkstra’s algorithm to keep track of the number of times each airport appears in a shortest path, and then use the result to finish the betweenness centrality algorithm to get the influence of airports over others.
   
   **Input:** a list of airports that represents a region. 
   
   **Output:** the airport that has the greatest influence in the region.
   
   **Time complexity:** O(|V|(|V|+|E|) lg|V|).

Besides, we will also implement the breadth first search (BFS) to output a file which contains all the airports that can be reached for a given airport.

## Timeline

| Time   | Tasks                                                        |
| ------ | ------------------------------------------------------------ |
| Week 1 | Obtain and process the data; Consider the general architecture of the project. |
| Week 2 | Construct the graph structure; Implement the breadth first traversal and one of the algorithms. |
| Week 3 | Implement the other two algorithms.                          |
| Week 4 | Debugging and data trials.                                   |



**Name:**	Yumingxuan Guo |  Yujie Miao |  Bangyan Shi  |  Pai Zheng

**NetID:**	yg17           |  yujiem4    |  bangyan3  |  Pai Zheng
