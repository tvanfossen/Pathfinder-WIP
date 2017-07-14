# Pathfinder-WIP

Latest:

Runs a path finding search by Djikstra's algorithm. Dijkstra's is run several times to prevent missed paths in the weighted graph. Weighted graph is then fed back into a DFS from target to start outputting the memory addresses of the shortest path from start to target as well as returning the minimum length.

Still an edge case that causes a seg fault - main.cpp file generates random grids to run against the pathfinder in attempt to find the case causing the seg fault with no luck.

