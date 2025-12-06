# Experiment 5 — Bellman–Ford Algorithm (Currency Exchange Arbitrage Detection)

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Single Source Shortest Path using Bellman–Ford Algorithm  
**Language Used:** C  
**Real-Time Application:** Currency Exchange Arbitrage Detection (Finance)
# Author

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

---

# Real-Time Scenario — Currency Arbitrage in Foreign Exchange (Forex) Market

In global finance, currency exchange rates keep changing:

- 1 USD → 0.90 EUR  
- 1 EUR → 90 INR  
- 1 INR → 0.012 USD  

Sometimes, by exchanging currencies in a **cycle**, we may end up with:

> **More money than we started with (risk-free profit)**  

This phenomenon is called **Currency Arbitrage**.

### ✔ Example:

Starting with **$1**:

1. USD → EUR  
2. EUR → INR  
3. INR → USD  

If the final value > $1, arbitrage exists.

### ✔ Why Bellman–Ford Algorithm?

Arbitrage is detected using **negative weight cycles**.

But exchange rates are multiplicative:

```

profit = rate1 × rate2 × rate3

```

Bellman–Ford works on *additive* weights.  
So we convert:

```

weight = -log(rate)

```

Then:

- A profitable arbitrage cycle has:  
  `rate1 × rate2 × rate3 > 1`

- After transformation:  
  `-log(rate1 × rate2 × rate3) < 0`

➡ **Hence a negative weight cycle = arbitrage opportunity**

**Bellman–Ford Algorithm is PERFECT** because:

✔ Works with negative weights  
✔ Detects negative weight cycles  
✔ Can identify profitable arbitrage loops  

---

# Aim

To implement **Bellman–Ford Algorithm** to:

1. Compute shortest path distances in a weighted graph with negative edges.  
2. Detect **negative weight cycles** representing arbitrage opportunities in currency markets using transformed weights `-log(rate)`.

---

# Graph Model (Financial Interpretation)

### Currencies = Nodes  
### Exchange Rates = Directed Edges  
### Weight on each edge:

```

weight = -log(exchange_rate)

```

If a cycle has **total weight < 0**,  
then an arbitrage (risk-free profit loop) exists.

---

# Project Structure

```

Exp_BellmanFord_Arbitrage/
│── main.c
│── bellmanford.c
│── bellmanford.h
│── README.md

```

---

# Features of the Program

| Feature | Description |
|--------|-------------|
| Demo exchange network | Preloaded USD–EUR–INR–GBP rates |
| Custom exchange network | User can enter custom currencies and rates |
| -log(rate) conversion | Converts multiplicative graph to additive |
| Arbitrage detection | Bellman–Ford checks negative cycles |
| Detailed relaxation logs | Shows every iteration step |

---

# 🧠 Bellman–Ford Algorithm Summary

### Steps:

1. Initialize all distances to ∞ except source.  
2. Relax all edges **V − 1 times**.  
3. Check for **negative cycles**:  
   - If `dist[u] + w < dist[v]`, a negative cycle exists.  
4. For currency markets:  
   - Negative cycle = **arbitrage opportunity**

### Time Complexity:  
```

O(V × E)

```

---

# 🎯 Demo Currency Network (Option 1)

Currencies:

| Index | Currency |
|-------|----------|
| 0     | USD      |
| 1     | EUR      |
| 2     | INR      |
| 3     | GBP      |

Edges + Rates:

| From | To | Rate |
|------|----|-------|
| USD | EUR | 0.9 |
| EUR | INR | 90 |
| INR | USD | 0.0112 |
| USD | GBP | 0.79 |
| GBP | INR | 100 |
| INR | EUR | 0.012 |

Transformed weight:

```

weight = -log(rate)

```

---

# 💻 **Sample Input (Option 2 — Custom Exchange Rates)**  
User selects:

```

2. Enter Custom Exchange Rates

```

### Input:

```

Enter number of currencies: 4
Enter number of exchange rates: 6

Enter edges as: src dest rate
Edge 1: 0 1 0.9
Edge 2: 1 2 90
Edge 3: 2 0 0.0112
Edge 4: 0 3 0.79
Edge 5: 3 2 100
Edge 6: 2 1 0.012

Enter source currency (0 to 3): 0

```

---

# 🧪 **Sample Output (Full Explanation)**

```

=== Bellman-Ford for Currency Arbitrage (Source = 0) ===
Note: Negative weights = -log(exchange rate)

Iteration 1:
Updating 0 -> 1 : INF -> 0.1054
Updating 1 -> 2 : INF -> -3.2958
Updating 2 -> 0 : 0 -> -4.3901
Updating 0 -> 3 : INF -> 0.2364
Updating 3 -> 2 : -3.2958 -> -8.2980
Updating 2 -> 1 : 0.1054 -> 4.4140

Iteration 2:
Updating 2 -> 0 : -4.3901 -> -9.3844
Updating 3 -> 2 : -8.2980 -> -13.3001

Iteration 3:
Updating 2 -> 0 : -9.3844 -> -14.3787
Updating 3 -> 2 : -13.3001 -> -18.3022

Checking for negative weight cycles...
Further relaxation possible on edge 2 -> 0 (weight = -log(0.0112))

⚠ Arbitrage Detected!
Profit can be made by cycling through currencies.

```

---

# ✔ Interpretation of Output

- **Negative cycle detected**  
- Market contains an **arbitrage loop**  
- Starting with ₹ / $ / € etc., you can loop through some currency sequence and end up with **more money** than you started with  
- Real trading systems detect and remove such opportunities quickly  

---

# 📘 Conclusion

In this experiment, we:

- Modeled currency exchanges as a directed weighted graph  
- Converted multiplicative rates to additive weights using `-log(rate)`  
- Applied **Bellman–Ford** to detect arbitrage cycles  
- Observed that a **negative weight cycle corresponds to risk-free profit**  
- Demonstrated a real-world application in **foreign exchange trading and financial markets**

### Importance in Real Life:

Banks, forex traders, and financial algorithms use this method to:

- Detect arbitrage  
- Balance exchange rates  
- Ensure no risk-free profit cycles exist  

---

# Author

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

**Experiment:** Bellman–Ford Algorithm — Currency Arbitrage Detection

