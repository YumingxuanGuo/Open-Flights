# Logs

1. Saturday Nov 13, 2021

  We decided to hold a one-hour meeting every Saturday to plan what we should do the next week. In the first meeting, we mainly discussed the structure of node and structure of graph.
  To be specific, a node in our project represents an airport. Our data fields include the airport’s name (string), other airports it maps to (vector<string>), its latitude (double), its longitude (double), whether it has been visited (bool). For Graph Structure, a graph represents the whole group of airlines. Our data fields include the complete list of nodes (vector<Node*>), the dictionary that maps the name of the airport to the actual node representation (unordered_map).

2. Wednesday Nov 17, 2021
  
We decided to shortly meet on every Wednesday afternoon to discuss a specific problem. This time, we discussed the shortest path function. Our first rough idea was to use the function to calculate the shortest path from one airport to all other reachable airports. We planned to write this function before Saturday. 

3. Saturday Nov 20, 2021
  
We checked our shortest path function discussed on Wednesday. And in this meeting, we mainly talked about the strongly connected component. Particularly, our first rough draft was to calculate the strongly connected component of the airlines, namely, the different sets of airports in which every airport can be reached from every other airport in the same set.

4. Wednesday Nov 24, 2021
  
In this meeting, we first checked our strongly connected component discussed in the last meeting. Then we planned the next step in our project. After exchanging ideas, we planned to add data. We added the constructor that read the input files in the meeting.

5. Saturday Nov 27, 2021
  
In this meeting, we mainly updated our structure of node and graph. Specifically, we added a few new fields in the node class, including whether the airport is in service (bool), its predecessor in the shortest path (Node*), its current distance from the starting point (double), the label of the strongly connected component it belongs to (int). Besides, after discussion, we removed the list of nodes in the graph class, since the same can be achieved by traversing the dictionary.

6. Wednesday Dec 1, 2021
  
In this meeting we added our main function. A rough first draft is to output the return value from the two functions. In addition, we updated function calls - revised the output type of the two functions. We have also run it on a small set of data to check if it works well.

7. Saturday Dec 4, 2021
  
In the meeting, we talked about our main function and test cases. We updated our main function - added more function calls with different goals in the main function. And we planned to add test cases by Dec 8.

8. Wednesday Dec 8, 2021
  
  We checked our test cases by checking whether the outputs are correct based on smaller amount of input. Then we discussed the video presentation. We planned to finish our project by Dec 12, 2021.

9. Sunday Dec 12, 2021
  
  We have wrapped up most of the loose ends, including the main function parameters, the data saving, the Makefile, etc. We planned to upload the presentation tomorrow.
