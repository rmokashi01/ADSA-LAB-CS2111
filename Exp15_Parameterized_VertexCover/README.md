# **Experiment 15 — Parameterized Algorithm (k-Vertex Cover Problem)**   

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Implementation of Parameterized Algorithm using k-Vertex Cover  
**Language Used:** C  
**Application Example:** Network Security Hardening (Monitoring Critical Machines)  

**Subject Teacher:** Prof. K. S. Gandle  
**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

---

## **Aim**

To study and implement a **Parameterized Algorithm** using the **k-Vertex Cover problem**, where the parameter is `k`.
The goal is to identify whether a graph has a vertex cover of size ≤ `k` using a **bounded search tree algorithm**.

---

# 📌 **Overview of Parameterized Algorithms**

Parameterized algorithms analyze complexity based on:

```
Input size (n)  AND  parameter (k)
```

▶ Traditional complexity: `O(f(n))`
▶ Parameterized complexity: `O(f(k) * n^c)`

Where `f(k)` may be exponential but `n^c` remains polynomial.

This allows solving NP-hard problems efficiently when the parameter `k` is small—even if the graph itself is large.

---

# 🧠 **Why k-Vertex Cover?**

The **Vertex Cover** problem is:

> Find a smallest set of vertices such that every edge in the graph has at least one endpoint in that set.

Vertex Cover is **NP-Complete**, but becomes tractable when using parameter `k`.

Parameterized bound:

```
Running Time ≈ O(2^k × n²)
```

Efficient for small `k` values (e.g., k ≤ 10).

---

# 🛡️ **Real-Time Application — Network Security Hardening**

In cyber-security systems:

* Vertices = Servers / Machines / Routers
* Edges = Communication links
* Goal = Choose **k critical nodes** to install monitoring tools (IDS, firewall logging, threat sensors)

A valid set of `k` monitored machines must **cover all communication links**.

This ensures:

* Every data-flow path is monitored
* Threat detection coverage across the network
* Minimum number of machines monitored (cost-efficient)

Example monitored nodes:

```
Gateway + File Server
```

These two alone can cover all network traffic paths.

---

# 🧱 **Algorithm Used — Branching (Bounded Search Tree)**

### Key Idea:

For an uncovered edge `(u, v)`:

We must pick **either u or v** in the vertex cover.

So we recursively branch:

```
1. Include u → solve with k-1
2. Include v → solve with k-1
```

If any branch succeeds, a valid vertex cover ≤ k exists.

### Algorithm Steps:

1. If all edges are covered → SUCCESS
2. If k = 0 but uncovered edges remain → FAIL
3. Select an uncovered edge `(u, v)`
4. Branch:

   * Mark `u` as covered → solve for k-1
   * Mark `u` as uncovered; mark `v` as covered → solve for k-1
5. Combine results
6. Maintain a solution array to store chosen vertices

---

# 📂 **Project Structure**

```
Exp15_ParameterizedAlgorithm_VertexCover/
│── pvertexcover.h
│── pvertexcover.c
│── main.c
│── README.md   ← (this file)
```

---

# 🧪 **Program Menu**

```
===== Experiment 15 – Parameterized Algorithm (k-Vertex Cover) =====
1. Use Demo Network Security Scenario
2. Enter Custom Graph
3. Exit
```

---

# 🔍 **Demo Scenario: Network Security Graph**

Vertices:

| Index | Machine Name    |
| ----- | --------------- |
| 0     | Gateway         |
| 1     | Web Server      |
| 2     | Database Server |
| 3     | File Server     |
| 4     | Backup Server   |

Sample connections:

```
0 - 1  
0 - 2  
1 - 3  
2 - 3  
3 - 4  
```

---

# 🧪 **Sample Output (k = 2)**

```
=== Parameterized Vertex Cover (k = 2) ===
Running bounded search tree algorithm with branching.

A vertex cover of size ≤ 2 was found.
Vertices included in vertex cover (by index): 0 3

Selected vertices in vertex cover (detailed):
Vertex 0 (Gateway)
Vertex 3 (File Server)
```

Interpretation:

✔ Monitoring **Gateway** and **File Server** covers the entire network traffic.

---

# 📘 **Conclusion**

This experiment demonstrates:

* Understanding of **Parameterized Complexity**
* Implementation of **k-Vertex Cover using bounded search tree**
* How intelligent branching reduces exponential explosion
* Application of parameterized algorithms in **network security monitoring**
* Practical demonstration of solving NP-hard problems for small parameters

Parameterized algorithms are a powerful approach in modern algorithm design, enabling efficient solutions for computationally hard problems.

---

# **Author**  

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

**Experiment:** ADSA Laboratory — Experiment 15 (Parameterized Algorithm)  
