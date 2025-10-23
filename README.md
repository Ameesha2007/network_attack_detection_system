# Combinatorics & Graph Theory — Network attack detection system Project

project description: 
- This project implements graph algorithms to analyze networks: Bellman‑Ford for negative-cycle detection (used here as a routing‑anomaly heuristic), DFS for connectivity checks, and Kruskal (with DSU) for computing a minimum spanning tree (MST).

Key features: 
- Bellman‑Ford: detect negative-weight cycles (flagged as suspicious “attack loops”).
- DFS: check whether the undirected network is fully connected.
- Kruskal + DSU: produce an MST and total cost to suggest a minimal secure topology.

Run / Input format:
- Input (interactive or via stdin):
  1) V — number of nodes (0..V-1)
  2) E — number of edges
  3) E lines: src dest weight
- Example:
``` 
4
4
0 1 1
1 2 2
2 3 3
0 3 10
```

Output
- Bellman‑Ford: alerts if a negative cycle is present.
- DFS: reports whether all devices are connected.
- Kruskal: prints MST edges and the total cost.

Algorithm complexities
- Bellman‑Ford: O(V * E)
- DFS: O(V + E)
- Kruskal: O(E log E) (dominant cost is sorting edges; DSU operations are near-constant amortized)

Sample inputs & expected outputs
1) Fully connected example
Input:
```
4
4
0 1 1
1 2 2
2 3 3
0 3 10
```
Expected:
- No negative-cycle alert
- "All devices are connected (No isolation detected)."
- MST printed and total cost shown

2) Negative-cycle example
Input:
```
3
3
0 1 1
1 2 -2
2 0 -1
```
Expected:
- "Alert: Suspicious negative cycle detected (Possible Attack Loop)!"
- Connectivity and MST outputs follow


  
