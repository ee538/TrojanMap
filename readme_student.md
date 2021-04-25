
=========================EE599 C++ Project README==============================
                         
                        Name: Dongyu Ge, Youwei Xu

===============================================================================
## Our README file includes the following sections:

```shell
I. High-level overview of our design 
II. Detailed description of each function and its time complexity.
III. Time spent for each function.
IV. Discussion, conclusion, and lessons learned.
```


## I. High-level overview of our design 

This project builds a USC surroundings map application with using data structures in C++ and implementing various graph algorithms. The application has the following seven functionalities:

```shell
**************************************************************
* Select the function you want to execute.
* 1. Autocomplete
* 2. Find the position
* 3. CalculateShortestPath
* 4. Travelling salesman problem
* 5. Cycle Detection
* 6. Topological Sort
* 7. Exit
**************************************************************
```

When the user chooses the number from 1 to 7, the application codes will excuate the corresponding the function and help users to make further desicions.

Each point on the map is represented by the class **Node** shown below and defined in [trojanmap.h](src/lib/trojanmap.h). These nodes are stored in the parameter 'data' in the style of 'map'.

```cpp
class Node {
  public:
    std::string id;    // A unique id assign to each point
    double lat;        // Latitude
    double lon;        // Longitude
    std::string name;  // Name of the location. E.g. "Bank of America".
    std::vector<std::string>
        neighbors;  // List of the ids of all neighbor points.
};

```


## II. Detailed description of each function and its time complexity
1.STEP1:Autocomplete

```shell
* input: a patial location name; output: a vector of full name
* turn each character of input name into the lower case
* turn each character of Node name into the lower case
* compare the input name with the Node name
* if find a Node name is the same as the input name, return the Node name's lat and lon
* if the Node name does not exist in the 'data',return an empty vector
```
 

2.STEP2:Find the position

```shell
* input: a location name; output: pair<double lat, double lon>
* use for loop to traverse all nodes in 'data' data strcture
* if find a name is the same as the input name, return the location name's lat and lon
* if the location name does not exist in the 'data',return (-1,-1)
```

3.STEP3:CalculateShortestPath

We employ two methods, Dijkstra and Bellman Frod Algorithm to implement shortest path. 
```shell
dijkstra:
* input: ; output:
*
*
```

4.STEP4:Travelling salesman problem

5.STEP5:Cycle Detection
This functionality incluedes two functions:
bool TrojanMap::IsCyclicUttil
bool TrojanMap::CycleDetection

6.STEP6:Topological Sort
We employ two methods. 
```shell
method 1:
* input: a vector of location names ; output: nodes after topological sorting
*
*

method 2:
* input: a vector of location names ; output: nodes after topological sorting
* traverse the dependencies vector and find the 
*
```


## III. Time spent for each function

   



## IV. Discussion, conclusion, and lessons learned

We worked together to finish this C++ project finally. Not only has our programming ability improved further, but our understanding of algorithms, such as DFS, Bellman Ford and DAG, has also deepened. Since the thoughts about how to implememt these functions varies from person to person, thus the cooperation between us inspires some new thoughts and methods to deal with the same function, which is a motivative and excited process. This is a meaningful course for students who are prepared to become a programmar.
