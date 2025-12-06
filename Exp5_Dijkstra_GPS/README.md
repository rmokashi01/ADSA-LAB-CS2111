# Experiment – Dijkstra’s Algorithm (GPS Navigation System)

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Implementation of Dijkstra’s Algorithm for Shortest Path  
**Language Used:** C  
**Real-Time Scenario:** GPS Navigation System for City Routes

## 👨‍💻 **Author & Academic Information**

**Author:** **Mr. Rehan Mokashi**  
**Program:** First Year M.Tech (Computer Science & Engineering)  
**Institution:** Government College of Engineering, Karad (GCEK)  
**University:** Shivaji University, Kolhapur  
**Academic Year:** 2025-2026

---

## Aim

To implement **Dijkstra’s Algorithm** to find the **shortest path** from a source location to all other locations in a **road network**, simulating the working of a **GPS navigation system**.

---

## Real-Time Scenario — GPS Navigation System

Consider a **city map** where each important place is:

- 🏠 Home  
- 🏙 City Center  
- 🚉 Railway Station  
- 🏬 Shopping Mall  
- 🏥 Hospital  
- 🎓 University  

Each **place** is a node in a graph.  
Each **road between two places** is an edge with weight = distance (in km) or travel time (in minutes).

The **GPS System** has to compute:

> *“From your current location, what is the shortest route and distance to every other destination?”*

Dijkstra’s algorithm is used inside GPS devices and apps (like Google Maps) to compute this.

---

## 🧱 Graph Model (Demo City Map)

We use 6 locations:

| Node | Place           |
|------|-----------------|
| 0    | Home            |
| 1    | City Center     |
| 2    | Railway Station |
| 3    | Shopping Mall   |
| 4    | Hospital        |
| 5    | University      |

### Adjacency Matrix (Demo)

Each number is the distance in km:

```text
          0   1   2   3   4   5
    0 [   0   4   0   2   0   0 ]
    1 [   4   0   5   1   7   3 ]
    2 [   0   5   0   6   2   0 ]
    3 [   2   1   6   0   0   4 ]
    4 [   0   7   2   0   0   3 ]
    5 [   0   3   0   4   3   0 ]
````

* `0` means there is **no direct road** between those two locations.
* Any `> 0` value means there *is* a road with that distance as weight.

---

## Features Implemented

| Feature             | Description                                           |
| ------------------- | ----------------------------------------------------- |
| Demo GPS Map        | Predefined small city road network                    |
| Custom Input        | User can enter own adjacency matrix                   |
| Shortest Distances  | From source to all locations                          |
| Path Reconstruction | Shows the path using intermediate nodes               |
| Step-wise Logs      | Shows which node is selected, which edges are relaxed |
| Real Scenario       | Mapping to GPS navigation concept                     |

---

## How to Compile and Run

From inside the `Exp5_Dijkstra_GPS` folder:

```bash
gcc main.c dijkstra.c -o exp5
```

Run:

```bash
./exp5      # Windows: exp5.exe
```

---

## Sample Run (Demo City Network)

### Input:

* Choose option: `1` (Use Demo City Road Network)
* Choose source location: `0` (Home)

### Output (Sample Style):

```text
Loaded demo city road network graph for GPS Navigation.
Nodes and their corresponding places:
0 - Home
1 - City Center
2 - Railway Station
3 - Shopping Mall
4 - Hospital
5 - University

Enter source location (0 to 5): 0

=== Dijkstra's Algorithm for GPS Navigation (Source = 0) ===
Note: 0 in adjacency matrix means 'no direct road'.

Selected location 0 with current shortest distance = 0
Relaxing roads from 0 to its neighbours...
  Found shorter route to 1: old dist = 99999, new dist = 4
  Found shorter route to 3: old dist = 99999, new dist = 2

Selected location 3 with current shortest distance = 2
Relaxing roads from 3 to its neighbours...
  Found shorter route to 1: old dist = 4, new dist = 3
  Found shorter route to 5: old dist = 99999, new dist = 6
  Found shorter route to 2: old dist = 99999, new dist = 8

...

=== Final Shortest Routes from Source 0 ===
Location    Distance    Path (by node index)
-------------------------------------------------
0           0           0
1           3           0 -> 3 -> 1
2           8           0 -> 3 -> 2
3           2           0 -> 3
4           9           0 -> 3 -> 5 -> 4
5           6           0 -> 3 -> 5
```

(You can map node numbers to places using the table above.)

---

## 🧠 Algorithm Summary

### Dijkstra’s Algorithm Steps

1. Initialize distances of all nodes as **INF**, except source = 0
2. Mark all nodes as **unvisited**
3. Repeat:

   * Pick the unvisited node with **minimum distance**
   * Mark it as visited
   * Relax all its adjacent edges:
     `if dist[u] + weight(u,v) < dist[v] then update dist[v]`
4. Continue until all nodes are visited or unreachable

### Time Complexity

* Using adjacency matrix and linear search for min:
  **O(V²)**

---

## 📘 Conclusion

In this experiment, we:

* Modeled a real-time **GPS navigation problem** using graphs
* Implemented **Dijkstra’s algorithm** to find shortest routes
* Showed both **distance values** and **actual paths**
* Observed how a GPS internally picks the **best route** from source to all destinations

This forms the base of modern **navigation apps, transport planning, ride-sharing services, and network routing systems**.

---

## Author

**Mr. Rehan Mokashi**
*Student, F.Y. M.Tech (Computer Science & Engineering)*
**Government College of Engineering, Karad (GCEK)**

**Subject:** Advanced Data Structures and Algorithms (ADSA)
**Subject Teacher:** Prof. K. S. Gandle

**Experiment:** ADSA Laboratory — Dijkstra’s Algorithm (GPS Navigation)

