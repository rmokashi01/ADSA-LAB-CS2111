# **Experiment 8 — Edmonds–Karp Implementation (Hospital Oxygen Supply Network)**

**Course:** CS2111 – Advanced Data Structures & Algorithms
**Lab:** ADSA Laboratory
**Experiment Title:** Edmonds–Karp Algorithm (BFS-based Ford–Fulkerson)
**Language Used:** C
**Real-Time Scenario:** Hospital Oxygen Supply Network Optimization

# Author
**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**

---

# **Real-Time Scenario — Hospital Oxygen Supply Network**

During emergencies (e.g., COVID-19 waves), hospitals must supply oxygen efficiently from:

* A **central oxygen tank** (source)
* Through pipelines (edges)
* To critical units such as **ICU**, **Operation Theatre**, **Emergency Ward**, and **Ventilator Support Unit** (sink)

Each pipeline has a **maximum flow capacity** (liters per minute).

### ✔ Problem:

Find the **maximum amount of oxygen** that can be supplied from the central tank to the ventilator support unit **without exceeding pipe limits**.

This is perfectly modeled as a **Max Flow problem**, solved using the **Edmonds–Karp algorithm**, which uses **Breadth-First Search (BFS)** to find shortest augmenting paths.

Edmonds–Karp is more stable and predictable than Ford–Fulkerson (DFS).

---

# **Aim**

To implement the **Edmonds–Karp Algorithm** to compute the **maximum oxygen flow** in a hospital supply network and explain how BFS ensures optimal augmenting paths.

---

# **Graph Model**

### **Vertices (Nodes): Hospital Units**

| Vertex | Unit Name                      |
| ------ | ------------------------------ |
| 0      | Central Oxygen Tank (Source)   |
| 1      | ICU Block                      |
| 2      | Operation Theatre (OT)         |
| 3      | Emergency Ward                 |
| 4      | General Ward                   |
| 5      | Ventilator Support Unit (Sink) |

### **Edges represent oxygen pipelines**

Each edge `(u → v)` has a capacity:

```
capacity[u][v] = maximum oxygen flow allowed (lit/min)
```

---

# **Project Structure**

```
Exp8_EdmondsKarp_OxygenNetwork/
│── main.c
│── edmonds_karp.c
│── edmonds_karp.h
│── README.md
```

---

# 🧠 **Edmonds–Karp Algorithm — Summary**

Edmonds–Karp is a specific implementation of the **Ford–Fulkerson method** using **BFS**.

### ✔ Steps:

1. Build residual graph
2. Use **BFS** to find shortest augmenting path
3. Compute bottleneck capacity
4. Update residual graph
5. Add bottleneck to flow
6. Repeat until no BFS path exists

### ✔ Advantages over DFS approach:

* Predictable runtime
* Avoids long augmenting paths
* Time complexity:

```
O(V × E²)
```

---

# 🏥 **Demo Hospital Oxygen Network (Option 1)**

### ASCII Diagram

```
                 (12)
      0 ----> 1 -------> 3 ----->(20)----> 5
      |        ^        ^                     ^
    (13)     (10)     (9)                  (4)
      |        |        |                     |
      v     (4)|        |                     |
      2 --------         -----> 4 -------------
            (14)            (7)
```

* Known maximum oxygen flow: **23 units**

---

# **Sample Input (Option 2 – Custom Entry)**

When user selects:

```
2. Enter Custom Capacity Network (Adjacency Matrix)
```

Example input:

```
Enter number of vertices: 4

Enter adjacency matrix:
0 10 5 0
0 0 15 10
0 0 0 10
0 0 0 0

Enter source vertex: 0
Enter sink vertex: 3
```

This represents:

* 0 → 1 (10 L/min)
* 0 → 2 (5 L/min)
* 1 → 3 (10 L/min)
* 2 → 1 (15 L/min)
* 2 → 3 (10 L/min)

---

# **Sample Output (Demo Hospital Network)**

```
=== Edmonds–Karp (BFS) for Max Oxygen Flow ===
Source = 0, Sink = 5

Augmenting Path 1 (oxygen flow added = 12):
0 -> 1 -> 3 -> 5
Current Maximum Oxygen Flow = 12

Augmenting Path 2 (oxygen flow added = 11):
0 -> 2 -> 4 -> 5
Current Maximum Oxygen Flow = 23

=== Final Maximum Oxygen Flow from 0 to 5 = 23 units ===
```

### ✔ Interpretation

The hospital can supply **23 units of oxygen per minute** from the central tank to the ventilator unit using optimal routing.

---

# **Conclusion**

In this experiment, we:

* Modeled a **hospital oxygen pipeline system** as a flow network
* Used **Edmonds–Karp (BFS version of Ford–Fulkerson)**
* Found the **maximum oxygen delivery capacity**
* Ensured routing uses shortest augmenting paths
* Observed that Edmonds–Karp is more efficient than DFS-based approaches

### Real-World Relevance

This approach is used in:

* Hospital infrastructure optimization
* Emergency resource planning
* Network bandwidth routing
* Electrical grid optimization
* Supply chain logistics

---

# **Author**

**Mr. Rehan Mokashi**
*Student, F.Y. M.Tech (Computer Science & Engineering)*
**Government College of Engineering, Karad (GCEK)**

**Subject:** Advanced Data Structures and Algorithms (ADSA)
**Subject Teacher:** Prof. K. S. Gandle

**Experiment:** ADSA Laboratory — Edmonds–Karp Algorithm (Experiment 8)
