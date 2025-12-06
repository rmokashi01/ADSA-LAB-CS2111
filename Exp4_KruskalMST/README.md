# 📘 Experiment 4 — Kruskal’s Algorithm (Minimum Spanning Tree)

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Implementation of Kruskal's Algorithm for Minimum Spanning Tree  
**Language Used:** C  
**Real-Time Scenario:** Smart Campus Road/Network Design (GCEK Campus Example)

## 👨‍💻 **Author & Academic Information**

**Author:** **Mr. Rehan Mokashi**  
**Program:** First Year M.Tech (Computer Science & Engineering)  
**Institution:** Government College of Engineering, Karad (GCEK)  
**University:** Shivaji University, Kolhapur  
**Academic Year:** 2025-2026

---

## 📌 Aim

To implement **Kruskal’s Algorithm** to find the **Minimum Spanning Tree (MST)** of a connected, undirected, weighted graph using:

- Edge sorting  
- Union–Find (Disjoint Set)  
- Cycle detection  
- Greedy strategy  

The program uses both a **demo real-life scenario** and **custom user input**.

---

# 🌍 Real-Time Scenario — Smart Campus Road/Network Design (GCEK)

Imagine the **Government College of Engineering, Karad (GCEK)** campus where different buildings must be connected with:

- **Optical fiber LAN cables**, or  
- **Smart road network**, or  
- **CCTV backbone wiring**, etc.

Each building is represented as a **node**, and each possible cable/road connection is an **edge** with a cost (distance or rupees).

### 🎯 Objective
> Connect all buildings with the **minimum total cost**, ensuring **no loops**, **no redundant cables**, and **full connectivity** across the campus.

This is a **Minimum Spanning Tree problem**, and **Kruskal’s Algorithm** solves it optimally.

---

## 🏫 Sample GCEK Campus Mapping (Used in Demo)

| Node | Building |
|------|----------|
| 0 | Admin Block |
| 1 | CSE Department |
| 2 | Library |
| 3 | Hostel |
| 4 | Workshop |

### Demo Edges (Possible Roads/Cables)

| Connection | Cost |
|-----------|------|
| 0 ↔ 1 | 10 |
| 0 ↔ 2 | 6 |
| 0 ↔ 3 | 5 |
| 1 ↔ 3 | 15 |
| 2 ↔ 3 | 4 |
| 1 ↔ 4 | 7 |
| 3 ↔ 4 | 8 |

These represent **potential connections**, and Kruskal’s algorithm finds the **cheapest** network connecting all buildings.

---

# 🧠 Understanding Kruskal’s Algorithm

Kruskal’s Algorithm is a **Greedy MST algorithm**.

### ✔ Steps:
1. Sort all edges in **increasing order of weight**  
2. Pick the **cheapest edge**  
3. Add it to MST **only if it does NOT form a cycle**  
4. Use **Union-Find** to detect cycles  
5. Stop when MST contains **V – 1 edges**

### ✔ Time Complexity:
- Sorting edges: **O(E log E)**
- Union-Find operations: **O(E α(V)) ≈ O(E)**  
- Overall: **O(E log E)**

---

# 🧱 Data Structures Used

### **Edge Structure**
```c
typedef struct
{
    int src;
    int dest;
    int weight;
} Edge;
````

### **Union–Find Structure**

* `makeSet()`
* `findSet()` (with path compression)
* `unionSet()`

---

# 🚀 Features Implemented

| Feature             | Description                          |
| ------------------- | ------------------------------------ |
| Demo Campus Graph   | Preloaded real-time GCEK scenario    |
| Custom Graph Input  | User can enter their own V, E, edges |
| Sorting of Edges    | Bubble sort for educational clarity  |
| Union–Find          | Tracks connected components          |
| Cycle Detection     | Avoids redundant/loop edges          |
| Step-by-step Output | Shows accepted/rejected edges        |
| MST Summary         | Total minimum cost displayed         |

---

# 💻 Sample Program Interaction

### **User chooses Demo Graph**

```
Loaded demo campus road network graph (GCEK-style).
Vertices (0-4): 0-Admin, 1-CSE, 2-Library, 3-Hostel, 4-Workshop
```

### **Edges Sorted by Weight**

```
2 -- 3 (cost = 4)
0 -- 3 (cost = 5)
0 -- 2 (cost = 6)
1 -- 4 (cost = 7)
3 -- 4 (cost = 8)
0 -- 1 (cost = 10)
1 -- 3 (cost = 15)
```

### **Edge Selection Process**

```
Considering edge 2 -- 3 (cost = 4) → Accepted
Considering edge 0 -- 3 (cost = 5) → Accepted
Considering edge 0 -- 2 (cost = 6) → Rejected (cycle)
Considering edge 1 -- 4 (cost = 7) → Accepted
Considering edge 3 -- 4 (cost = 8) → Accepted
```

### **Final MST Output**

```
=== Final Minimum Spanning Tree ===
2 -- 3   4
0 -- 3   5
1 -- 4   7
3 -- 4   8
-----------------
Total Minimum Cost = 24
```

---

# 🛠️ Compilation Instructions

Compile:

```bash
gcc main.c kruskal.c -o exp4
```

Run:

```bash
./exp4      # Windows: exp4.exe
```

---

# 📜 Algorithm Summary

### **Sorting Edges**

Edges sorted by weight using simple bubble sort for clarity.

### **Union-Find**

Keeps track of which nodes belong to which connected component.

### **Cycle Detection**

If `findSet(src) == findSet(dest)`, edge forms a cycle → reject.

### **MST Construction**

Stop when MST contains **V − 1** edges.

---

# 📘 Conclusion

In this experiment, we successfully:

* Modeled a **real-world network design** using graph theory
* Implemented **Kruskal’s MST Algorithm** using Union–Find
* Understood how greedy selection avoids cycles
* Observed step-by-step decisions of edge acceptance/rejection
* Found the **minimum total cost** required to connect all buildings

This forms the foundation for **network design**, **transport planning**, **electrical grid layout**, and **infrastructure optimization**.

---

# 👤 Author

**Mr. Rehan Mokashi**
*Student, F.Y. M.Tech (Computer Science & Engineering)*
**Government College of Engineering, Karad (GCEK)**

**Subject:** Advanced Data Structures and Algorithms (ADSA)
**Subject Teacher:** Prof. K. S. Gandle

**Experiment:** ADSA Laboratory — Experiment 4

---

