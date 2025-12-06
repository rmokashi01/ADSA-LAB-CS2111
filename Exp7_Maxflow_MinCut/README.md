# Experiment 7 — Maxflow–Mincut Theorem  
**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Implementation of Ford–Fulkerson Method to Demonstrate Maxflow–Mincut Theorem  
**Language Used:** C  
**Real-Time Scenario:** Water Distribution Network (Pipeline Flow Optimization)

# Author

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)** 

---

# Real-Time Application — Water Distribution Network

Consider a **city water supply system**:

- A **source reservoir** pumps water.
- Water flows through **junctions and pipes**.
- A **treatment plant** receives water.
- Each pipe has a **maximum flow capacity** (liters/sec).

The goal:

> 🧭 **Find the maximum amount of water that can be transported from the reservoir (source) to the treatment plant (sink).**

Such problems are solved using **Max Flow algorithms**.  
The **Ford–Fulkerson method** incrementally increases the flow using **augmenting paths**.

According to the **Maxflow–Mincut Theorem**:

> Maximum amount of flow from source to sink =  
> **Minimum total capacity of edges that disconnect S from T.**

---

# Problem Model

### ✔ Nodes (Vertices)
Represent water junctions/tanks/pumps.

### ✔ Directed Edges
Represent pipes with **capacity**.

### ✔ Capacity
Maximum water the pipe can carry.

### ✔ Flow Network
A directed graph where each edge has:
```

capacity[u][v] ≥ 0

```

---

# Aim

To implement **Ford–Fulkerson Algorithm** to:

- Compute **maximum flow** from a source `s` to a sink `t`
- Identify **minimum cut edges**
- Demonstrate **Maxflow–Mincut Theorem**

---

# Project Structure

```

Exp7_Maxflow_MinCut/
│── main.c
│── maxflow.c
│── maxflow.h
│── README.md

```

---

# 🧠 Maxflow–Mincut Theorem Overview

### ✔ Max Flow
Maximum possible flow from source to sink **without exceeding pipe capacities**.

### ✔ Min Cut
Smallest set of edges which, if removed, completely disconnects source from sink.

### ✔ Theorem:
```

Maximum Flow = Minimum Cut Capacity

```

Ford–Fulkerson algorithm demonstrates this relationship.

---

# Algorithm Used — Ford–Fulkerson (DFS + Residual Graph)

### Steps:

1. Initialize flow = 0  
2. Find a path from source to sink s → … → t  
   where residual capacity > 0  
3. Augment flow along that path by minimum capacity on the path  
4. Update residual capacities  
5. Repeat until no more augmenting paths exist  
6. Remaining reachable nodes from source = **S-side of Min Cut**  
7. Edges from S → T form the **Minimum Cut**

### Time Complexity:
```

O(E × MaxFlow)

```

---

# Demo Water Network (Option 1)

Vertices:

| Vertex | Meaning |
|--------|----------|
| 0 | Source Reservoir |
| 1 | Junction A |
| 2 | Junction B |
| 3 | Junction C |
| 4 | Junction D |
| 5 | Treatment Plant (Sink) |

ASCII diagram:

```

```
  (16)
```

0 --------> 1 --------> 3 ----(20)----> 5
|           |           ^              ^
(13)       (12)       (9)             (4)
|           |           |              |
v        (10)           |              |
2 -------->--------------              |
\               \                 |
(14)             -(7)-> 4 -------

```

Expected Max Flow = **23**

---

# 🧪 Sample Input (Option 2 — Custom Adjacency Matrix)

User enters:

```

Enter number of vertices: 4

Enter adjacency matrix:
0 10 5 0
0 0 15 10
0 0 0 10
0 0 0 0

Enter source: 0
Enter sink: 3

```

Graph:

- 0 → 1 (10)
- 0 → 2 (5)
- 1 → 3 (10)
- 2 → 1 (15)
- 2 → 3 (10)

---

# 🧪 Sample Output (Option 1 Demo)

```

=== Ford–Fulkerson for Max Flow (Source = 0, Sink = 5) ===

Augmenting Path 1 (flow = 12):
0 -> 1 -> 3 -> 5
Current Max Flow = 12

Augmenting Path 2 (flow = 11):
0 -> 2 -> 4 -> 5
Current Max Flow = 23

=== Final Maximum Flow from 0 to 5 = 23 ===

```

---

# 🧪 Sample Output — Minimum Cut

```

=== Min-Cut Edges (S-side → T-side) ===
Edge    Capacity
----------------

1 -> 3  12
2 -> 4  14
----------

Sum of Min-Cut capacities = 23

Max Flow (23) = Min Cut (23)

```

**Verified Theorem ✔**

---

# 📘 Conclusion

In this experiment, we:

- Built a **water distribution network graph**  
- Implemented **Ford–Fulkerson Method**  
- Calculated **maximum flow** from source to sink  
- Identified **min-cut edges**  
- Proved the **Maxflow–Mincut Theorem**  
- Observed practical application for **pipeline design**, **network flow**, and **resource optimization**

Maxflow algorithms are widely used in:

- Water & oil pipeline design  
- Traffic routing  
- Bipartite graph matching  
- Airline scheduling  
- Computer networks  
- Supply chain optimization

---

# Author

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

**Experiment:** ADSA Laboratory — Maxflow–Mincut Theorem (Ford–Fulkerson)
