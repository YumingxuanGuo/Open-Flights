# Goals

## Leading Question

Ever since the pendemics began, air travel has been largely influenced due to the shut down of certain airline routes. However, it is unclear how the shut down of certain airlines impact travel in certain regions. 

Target Goal: Using data from OpenFlights, to make a search tool for the airline routes all over the world, where users can input the unavailable air routes or airlines. It will be able to output the shortest path from one airport to another and the set of airports that can be pairwisedly reached.

## Dataset Acquisition and Processing

We have obtained the data of the airports and the routes from the [website](https://openflights.org/data.html). The data are in the format of ".csv" files, containing fields including the 3-letter label of a airport, the latitude and longitude of the loaction of a airport, the starting airport and the destination of a flight, etc. We separate the data by line and then separate the fields by commas. We have chosen to process these data when constructing the graph class that represent the whole group of airports. Each airport is being wrapped up in a node class along with its relavent information, including its adjacent nodes (edges) which are reachable from the original airport. To avoid the dirty or unused data, we check the data when reading it: e.g., if the name of the starting airport or the destination of a route is not recognized, we simply ignor this piece of data.

## Graph Algorithms

We have implemented at least three functions using graph algorithms in our projects:

1. To find the shortest path from one airport to all other airports.

   **Algorithm:** Dijkstra's (single source shortest path) algorithm.

   **Input:** The departure airport.

   **Output:** A dictionary that maps each airport (as the destination) to an ordered list of airports (as the shortest path) with the cumulative distance being the last element of the list.

   **Time complexity:** O(|V|+|E|lg|V|).

2. To find out the regions (strongly connected components) that can be fully traversed if certain routes are closed.

   **Algorithm:** Kosaraju (strongly connected component) algorithm.

   **Input:** None.

   **Output:** A dictionary that maps each strongly connected component's number lable to an unordered list of airports that share the same component. It also updates each node's (which represent each airport) component lable.

   **Time complexity:** O(|V|+|E|).

Besides, we have also written multiple DFS helper functions (to help with the two algorithms) and a BFS iterator (which enables a for-ranged loop).

## Final Deliverable

We will prove that our projects work by experimenting multiple times on different subsets of the data and check the result with the world map.

## Timeline

| Time   | Tasks                                                        |
| ------ | ------------------------------------------------------------ |
| Week 1 | Obtain and process the data; Consider the general architecture of the project. |
| Week 2 | Construct the graph structure; Implement the breadth first traversal and one of the algorithms. |
| Week 3 | Implement the other two algorithms.                          |
| Week 4 | Debugging and data trials.                                   |



**Name:**	Yumingxuan Guo |  Yujie Miao |  Bangyan Shi  |  Pai Zheng

**NetID:**	yg17           |  yujiem4    |  bangyan3  |  Pai Zheng
