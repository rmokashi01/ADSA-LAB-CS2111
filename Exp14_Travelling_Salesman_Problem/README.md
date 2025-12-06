# Experiment 14 — Travelling Salesman Problem (TSP)

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Implementation of Travelling Salesman Problem (Brute Force)  
**Language Used:** C  
**Application Example:** Ambulance Routing / Delivery Route Optimization / Tourist Visit Planning  

**Subject Teacher:** Prof. K. S. Gandle  
**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

---

## **Aim**

To implement the **Travelling Salesman Problem (TSP)** using **Brute Force Backtracking** to find the **minimum cost tour** that visits all cities exactly once and returns to the starting city.

---

## **Overview of TSP**

The **Travelling Salesman Problem** is a classic optimization problem in graph theory and operations research.

Given:

* A set of cities
* A distance matrix

The goal is:

> Find the shortest possible route that visits every city exactly once and returns to the origin city.

### ✔ Why TSP is Important?

* Used in logistics & courier routing
* Used in ambulance & emergency medical routing
* Used in chip design & circuit optimization
* Used in robotics & path planning
* NP-hard → brute-force is used for small inputs

---

## 🛠️ **Algorithm Used: Brute-Force Backtracking**

This experiment uses:

> **Backtracking to generate all permutations** of cities
> and compute the cost of each possible tour.

### **Steps:**

1. Fix the starting city (city 0).
2. Generate permutations of remaining cities.
3. For each permutation:

   * Calculate total travel cost.
   * Add return cost to starting city.
4. Track the minimum-cost tour seen so far.

### **Time Complexity:**

```
O(n!)
```

(Suitable for n ≤ 10)

---

## 🩺 **Application 1 — Ambulance / Medical Supply Routing**

Hospitals often need to plan optimized routes for:

* Ambulance pickup
* Blood sample collection
* Oxygen cylinder distribution
* Emergency medical transport

TSP helps minimize:

* Travel distance
* Fuel cost
* Emergency response time

### Scenario Cities:

```
Central Hospital
Clinic 1
Clinic 2
Diagnostic Lab
Trauma Center
```

---

## 📦 **Application 2 — Delivery Route Optimization (Courier / Food Delivery)**

Companies like Swiggy, Zomato, Amazon, DTDC use TSP logic to decide the order of:

* Customer deliveries
* Pickup points
* Return to warehouse

---

## 🏙️ **Application 3 — Tourist City Visit Planning**

A tourist wants to visit multiple cities:

```
Karad → Satara → Pune → Mumbai → Kolhapur → back to Karad
```

TSP finds the **shortest travel plan**.

---

## 📂 **Project Structure**

```
Exp14_TSP/
│── main.c
│── tsp.c
│── tsp.h
│── README.md   ← (this file)
```

---

## **How to Compile**

```bash
gcc main.c tsp.c -o exp14
```

Run:

```bash
./exp14      # Windows: exp14.exe
```

---

## 📜 **Program Menu**

```
===== Experiment 14 – Travelling Salesman Problem (TSP) =====
1. Delivery Route Optimization (Courier / Food Delivery)
2. Ambulance / Medical Supply Routing
3. Tourist City Visit Planning
4. Enter Custom Distance Matrix
5. Exit
```

---

# 🧪 **Sample Output (Scenario 2 – Ambulance Routing)**

```
Loaded Scenario 2: Ambulance / Medical Supply Routing

Exploring all possible tours using backtracking...

=== Optimal Travelling Salesman Tour ===
Path: Central Hospital -> Clinic 1 -> Clinic 2 -> Diagnostic Lab -> Trauma Center -> Central Hospital
Total Minimum Cost: 40
```

*(Cost depends on sample distance matrix.)*

---

## **Algorithm Summary**

### 🔹 *Backtracking Steps*

* Mark first city as visited
* For every unvisited city:

  * Visit it
  * Recurse
  * Backtrack

### 🔹 *Pruning*

* If partial path cost > current best → prune this branch

### 🔹 *Selection*

* Update best path whenever a full tour is found

---

## **Conclusion**

This experiment demonstrates:

* Implementation of **Brute-Force TSP using Backtracking**
* Application of optimization strategy using permutations
* Real-world use cases in **healthcare, logistics, and tourism**
* Understanding of computational difficulty (NP-hardness)

TSP is one of the most studied optimization problems and forms the basis of many routing algorithms.

---

## **Author**

**Mr. Rehan Mokashi**
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

**Experiment:** ADSA Laboratory — Experiment 14 (TSP)  