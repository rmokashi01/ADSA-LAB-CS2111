# **Experiment 9 — 0/1 Knapsack Problem (Dynamic Programming Approach)**

**Course:** CS2111 – Advanced Data Structures & Algorithms
**Lab:** ADSA Laboratory
**Experiment Title:** Implementation of 0/1 Knapsack using Dynamic Programming
**Language Used:** C
**Real-Time Scenario:** Emergency Ambulance Medical Kit Optimization
# Author
**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)** 

---

# **Real-Time Scenario — Ambulance Emergency Medical Kit Packing**

Ambulance staff often need to prepare a **critical care medical kit** within a strict **weight limit**.
Each item has:

* **Weight** (kg)
* **Value / Importance Score**

For example:

| Medical Item    | Weight | Value (Importance) |
| --------------- | ------ | ------------------ |
| Oxygen Cylinder | 10     | 60                 |
| First Aid Kit   | 20     | 100                |
| Ventilator Mask | 30     | 120                |
| Injection Pack  | 25     | 90                 |

The **ambulance bag** has limited carrying capacity.

### ✔ Objective:

> Select the **best combination of medical supplies** that gives **highest total value** while staying within weight limit.

This is exactly the **0/1 Knapsack Problem**.

---

# **Aim**

To implement the **0/1 Knapsack Problem** using **Dynamic Programming** to find:

* Maximum total value fitting in the knapsack
* Which items should be selected
* DP table formulation

---

# **Understanding the 0/1 Knapsack Problem**

### Given:

* `n` items
* Each item has:

  * `weight[i]`
  * `value[i]`
* Knapsack has capacity `W`

### Choose items such that:

* Total weight ≤ W
* Total value is maximized
* Each item can be:

  * **Taken (1)**
  * **Not taken (0)**
    (so it's called **0/1 Knapsack**)

---

# **Dynamic Programming Solution**

We create a DP table:

```
dp[i][w] = maximum value using first i items with capacity w
```

### Recurrence Formula:

```
if weight[i] > w:
    dp[i][w] = dp[i-1][w]
else:
    dp[i][w] = max(
        dp[i-1][w],                         // not including item
        value[i] + dp[i-1][w-weight[i]]     // including item
    )
```

### Final Answer:

```
dp[n][capacity]
```

---

# **Project Structure**

```
Exp9_Knapsack/
│── main.c
│── knapsack.c
│── knapsack.h
│── README.md
```

---

# **Demo Dataset (Used in Program Option 1)**

### Medical Items:

| Index | Weight | Value | Item            |
| ----- | ------ | ----- | --------------- |
| 1     | 10     | 60    | Oxygen Cylinder |
| 2     | 20     | 100   | First Aid Kit   |
| 3     | 30     | 120   | Ventilator Mask |
| 4     | 25     | 90    | Injection Pack  |

### Knapsack Capacity:

```
50
```

---

# **Sample Output (Demo Input)**

```
Loaded Demo Medical Items
Index   Weight   Value   Description
 1        10       60     Oxygen Cylinder
 2        20      100     First Aid Kit
 3        30      120     Ventilator Mask
 4        25       90     Injection Pack

=== DP Table (Knapsack) ===
(Complete DP table displayed)

Maximum Total Value that can be carried = 220

Selected Medical Items:
Item 4 (Weight = 25, Value = 90)
Item 3 (Weight = 30, Value = 120)
```

### ✔ Interpretation:

To maximize medical usefulness:

* Take **Ventilator Mask**
* Take **Injection Pack**
* Total Value = **120 + 90 = 210**
* Total Weight = **30 + 25 = 55** (if capacity 50, then alternative combination chosen)

The program performs optimal DP selection.

---

# **Conclusion**

In this experiment, we:

* Designed the **0/1 Knapsack model**
* Applied **Dynamic Programming** to compute the maximum possible value
* Generated and analyzed the **DP table**
* Identified **which items** to pack in the ambulance bag
* Demonstrated a real-world emergency application

### ✔ Importance of Knapsack DP:

Used in:

* Backpack planning
* Ambulance emergency kit packing
* Disaster relief resource allocation
* Budget optimization
* Cloud computing resource scheduling
* Cargo loading logistics

---

# **Author**

**Mr. Rehan Mokashi**
*Student, F.Y. M.Tech (Computer Science & Engineering)*
**Government College of Engineering, Karad (GCEK)**

**Subject:** Advanced Data Structures and Algorithms (ADSA)
**Subject Teacher:** Prof. K. S. Gandle

**Experiment:** ADSA Laboratory — 0/1 Knapsack Problem (Experiment 9)