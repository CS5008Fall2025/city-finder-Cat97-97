# Report
Fill out these report questions. 


1. What is the difference between a directed and undirected graph?

In a directed graph, each edge has an orientation (u → v) and only allows traversal in that direction; (u → v) is different from (v → u). In an undirected graph, an edge connects two vertices symmetrically, so traversal is allowed both ways. Practically, an undirected edge {u, v} can be represented as two directed edges (u → v) and (v → u). Algorithmically, this changes reachability and path computations because direction matters in directed graphs but not in undirected graphs.

2. What is the Big O of Dijkstra's algorithm.... 
   * Assuming you used an array (or list) to store the vertices.
   * Assuming you used a heap / priority queue to store the vertices.

Assuming a standard adjacency-list representation:
- Array/list (select-min via linear scan): O(V^2 + E) time, typically simplified to O(V^2) for sparse-to-dense mixes (the V select-min steps dominate).
- Binary heap (priority queue): O((V + E) log V) time; for sparse graphs (E ≈ V), this is O(V log V). With a Fibonacci heap one can achieve O(E + V log V), though that is mainly of theoretical interest in C projects.

3. Explain in your own words what that means for larger graphs when trying to find the shortest distance. 

For small graphs, an O(V^2) implementation is often fast enough and simpler to code. As graphs grow, O(V^2) becomes a bottleneck because the linear-scan “select-min” repeats V times. Using a priority queue reduces the dominant factor to log V per relaxation and scales much better: for millions of vertices/edges, O((V + E) log V) is orders of magnitude faster and is the practical choice for real-world routing.

## Deeper Thinking
4. For this assignment, you didn't need the most "efficient" set of data structures (for example, a heap wasn't required). However, think on the scale of google/apple maps - they have to deal with millions of vertices and edges. What data structures would you use to store the graph? Why? Somethings to consider - would you be able to store the entire graph at a time? Could you break it up into smaller pieces? How would you do that? Would there be advantages to caching/memoization of paths? You are free to explore your thoughts on this subject/reflect on various ideas. Other than a realization of some scalability of problems, there isn't a wrong answer. 

Practical, large-scale routing uses:
- Adjacency lists with compact integer IDs and structure-of-arrays layouts for cache locality.
- Name → ID lookup via hash tables or minimal perfect hashing.
- Geographic partitioning (tiles/cells) so only a relevant subgraph is loaded/kept hot in memory; long routes are stitched across region boundaries.
- Preprocessing to accelerate queries: contraction hierarchies (CH), multi-level Dijkstra, ALT (A* with landmarks/triangles), and transit-node routing. These give big speedups by reducing the search space.
- Heuristics like A* with an admissible heuristic (e.g., great-circle distance) to guide the search toward the target.
- Caching/memoization: frequently queried OD pairs, or partial results like boundary-to-boundary shortcuts within regions. CDN-like edge caching for popular city pairs can further reduce latency.
- Storage: a mix of memory-mapped read-only graph segments for static roads and small dynamic overlays (closures/traffic) updated incrementally.
This combination balances RAM limits, I/O cost, and query time requirements at scale.




## Future Understanding
5. Related to shortest distance, is a problem called the "messenger" or "traveling sales person" problem commonly abbreviated to TSP. This problem is to find the shortest path that visits **every** vertex in a graph. Another way to look at it, is you are an delivery driver, and you have a series of packages to deliver. Can you find an optimal path for your deliveries that minimizes the total distance traveled? Imagine if you had 5 stops. How many different paths are there?  There are 120 possible paths to look at! (assuming fully connected routes). 
   * How many possible paths are there if you have 6 stops?
   * How many possible paths are there if you have 10 stops?
6. What type of growth is this problem? 
7. Take some time to research TSP problems. It falls under a certain classification of problems? What is it? 
8. Provide some examples of fields / problems that use TSP.

Using the same assumption as the prompt (n! possibilities for n stops):
- 6 stops: 6! = 720 possible paths.
- 10 stops: 10! = 3,628,800 possible paths.
Type of growth: factorial growth, which is super-polynomial and intractable for exact brute force.
Classification: TSP is NP-hard (optimization version). The decision version (“is there a tour of length ≤ K?”) is NP-complete.
Applications: vehicle routing/logistics, printed circuit board drilling, VLSI design, robotics path planning, DNA sequencing/fragment assembly, astronomical telescope scheduling, and workforce/field service routing.



> [!TIP]
> We are having you explore TSP, so you can see the terms used for problem classification that are often the foundation of computer science theory. You will not be asked to know about TSP outside of this assignment or even problem classification. Computer Science is often about dealing with problems considered "too hard" or "impossible", and finding ways to make them possible! As such, knowing topics such as N, NP, NP-Complete, etc. is important to understand the limits (to break).


## Technical Interview Practice Questions
For both these questions, are you are free to use what you did as the last section on the team activities/answered as a group, or you can use a different question.

1. Select one technical interview question (this module or previous) from the [technical interview list](https://github.com/CS5008-khoury/Resources/blob/main/TechInterviewQuestions.md) below and answer it in a few sentences. You can use any resource you like to answer the question.

Sample technical question: What is a hash table, and what are the average/worst-case complexities?
Answer: A hash table stores key→value pairs in an array indexed by a hash of the key. With a good hash function and load factor, average time for lookup/insert/delete is O(1). In the worst case (e.g., many collisions or adversarial inputs), operations can degrade to O(n). Implementations mitigate this with resizing, separate chaining, or open addressing strategies and, sometimes, randomized hashing.

2. Select one coding question (this module or previous) from the [coding practice repository](https://github.com/CS5008-khoury/Resources/blob/main/LeetCodePractice.md) and include a c file with that code with your submission. Make sure to add comments on what you learned, and if you compared your solution with others. 

Included: coding_practice.c (Two Sum). It demonstrates an open-addressing hash map to reach O(n) average time, with brief comments on lessons learned.