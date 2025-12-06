# Experiment 10 — Brute Force Pattern Matching (Naive String Matching)

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Single Source Shortest Path using Bellman–Ford Algorithm  
**Language Used:** C  
**Real-Time Application:** Implementation of Brute Force Pattern Matching
# Author

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

---

# **Real-Time Scenario — Medical Keyword Search in Patient Report**

Hospitals maintain detailed **patient medical reports** including symptoms, diagnosis, and treatment notes.

Suppose a doctor wants to quickly find if the report mentions a specific keyword such as:

* “fever”
* “diabetes”
* “cough”
* “hypertension”
* “infection”

To locate the keyword, we need a **string searching algorithm**.

The simplest method = **Brute-Force Pattern Matching**.

---

# **Aim**

To implement the **Brute-Force (Naive) String Matching Algorithm** and locate all occurrences of a pattern inside a given text.

---

# 🧠 **Algorithm Explanation**

Let:

* `text` = the full medical report
* `pattern` = keyword to search

### ✔ Steps:

1. Start from index `i = 0` in text
2. Compare pattern with substring `text[i .. i+m-1]`
3. If mismatch occurs → shift the pattern by 1 → try next position
4. If all characters match → record a successful match
5. Continue until entire text is scanned

### ✔ Time Complexity:

```
Worst-case: O(n × m)
```

Where:

* `n` = length of text
* `m` = length of pattern

### ✔ Why is brute-force important?

* Easiest pattern matching algorithm
* Basis for advanced algorithms like KMP, Rabin-Karp, Boyer-Moore
* Works well on small or simple strings

---

# **Project Structure**

```
Exp_BruteForcePatternMatching/
│── main.c
│── pattern_matching.c
│── pattern_matching.h
│── README.md
```

---

# **Demo Input (Option 1: Preloaded Medical Report)**

Text:

```
Patient reports mild fever and headache since two days.
No history of diabetes or hypertension.
Fever pattern is intermittent with slight cough.
```

Pattern searched:

```
fever
```

---

# **Sample Output (Demo Input)**

```
=== Brute-Force Pattern Matching Trace ===

Checking at text index 0: Pati
Mismatch at j = 0 (text[0] = 'P', pattern[0] = 'f')

Checking at index 1: atie
Mismatch ...

...

Checking at index 15: fever
✔ Match found at index 15

Checking at index 90: Fever
Mismatch at j = 0 (text[90] = 'F', pattern[0] = 'f')

Total 1 occurrence(s) of pattern "fever" found in text.
```

---

# **Conclusion**

In this experiment, we:

* Implemented the **Brute-Force Pattern Matching Algorithm**
* Compared characters of text and pattern sequentially
* Printed step-by-step matching process
* Successfully located all occurrences of keywords in medical report text

### ✔ Applications:

* Searching disease names in patient records
* Keyword search in documents, logs, and files
* Basic text editor implementations
* Spell-check and data filtering

---

# Author

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle 

**Experiment:** Brute-Force Pattern Matching (String Search)