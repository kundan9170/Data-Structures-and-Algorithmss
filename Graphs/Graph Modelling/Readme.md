## This section contains my solution of few of the problem related to graph modelling that i stumbled upon.
# So, what is Graph Modeling?
Changing Given Graph into state graph is called Graph Modelling. In State graph, every vertex will store additional information, representing some state of the problem, 
and the edges represent transitions between states. We can see it like a finite state machine and we are going to compute the shortest path from
the initial state to some final state which helps in solving a lot of problem. The construction of the state graph is usually the challenge in this kind of problem, and after the graph 
is built we will have a good time using Dijkstra's algorithm.
### Codes
1. G_Bicycles.cpp (CF Round 918 Div.4).
#### Problem
The Problem gives us a graph of city and each city you can by new bicyle. Each road have some time and each cycle have some slowness factor. So, total time taken to traverse a road will be time[i]*slow[i]. Then the problem ask us the Shortest Time to reach city n from 1.
##### Solution
We model graph as n*n nodes, n is number of city and number of bicyle. Then we apply Dijkstra.
