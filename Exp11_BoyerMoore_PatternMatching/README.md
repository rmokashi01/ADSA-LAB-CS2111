# Experiment 11 — Boyer–Moore Pattern Matching Algorithm
 
**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Pattern Matching Using Boyer–Moore Algorithm (Bad-Character Heuristic)  
**Language Used:** C  
**Application Example:** Searching Critical Medical Terms in Patient Reports  
 

## **Author**

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

---

## **Aim**

To implement the **Boyer–Moore Pattern Matching Algorithm** using the **Bad-Character Heuristic** and compare its efficiency with basic string matching methods by performing fast keyword search in long textual data.

---

## **Overview of Boyer–Moore Algorithm**

The **Boyer–Moore Algorithm** is one of the fastest string-search algorithms used in practical applications such as:

* Text editors
* Code search tools
* Searching logs or reports
* Bioinformatics (DNA sequence matching)

It works **right-to-left** while comparing the pattern and uses two powerful heuristics:

### ✔ 1. Bad Character Rule

If a mismatch occurs at pattern index `j`, shift the pattern based on **last occurrence of the mismatched character** in the pattern.

### ✔ 2. Good Suffix Rule

(Not implemented here, as ADSA syllabus mostly requires Bad Character rule.)

### Why is Boyer–Moore Fast?

* Compares from **end of pattern**, reducing comparisons
* Jumps ahead multiple positions instead of shifting by 1
* Works extremely well on large texts

---

## 🧱 **Structure Used**

### **Bad-Character Table**

A table storing the **last occurrence index** of every possible character:

```
badchar[c] = last index of character c in pattern
```

Used to compute the skip value:

```
shift = max(1, j - badchar[text[shift + j]])
```

---

## 📂 **Project Structure**

```
Exp11_BoyerMoore_PatternMatching/
│── main.c
│── boyer_moore.c
│── boyer_moore.h
│── README.md   ← (this file)
```

---

## **Application Example — Searching Medical Keywords in Reports**

Healthcare systems frequently analyze long reports to find critical terms such as:

* “fever”
* “infection”
* “cancer”
* “hypertension”
* “diabetes”

Boyer–Moore provides **fast keyword detection**, making it perfect for Electronic Health Record (EHR) systems.

Example text used in demo:

```
Patient shows signs of chronic infection and mild fever.
Further tests show no indication of cancer or thyroid disorder.
Secondary infection suspected based on lab results.
```

---

## **How to Compile**

```bash
gcc main.c boyer_moore.c -o exp11
```

Run program:

```bash
./exp11     # Windows: exp11.exe
```

---

## 📜 **Sample Output**

```
=== Boyer–Moore Pattern Matching Trace ===
Text length = 158, Pattern length = 9

Checking alignment at shift 0:
Mismatch at text[8] = 's'
Bad-character last seen at pattern[-1]
Shifting pattern by 9 positions

Checking alignment at shift 9:
Matched: pattern[8] = 'n' with text[17] = 'n'
Matched: pattern[7] = 'o' with text[16] = 'o'
Matched: pattern[6] = 'i' with text[15] = 'i'
Matched: pattern[5] = 't' with text[14] = 't'
Matched: pattern[4] = 'c' with text[13] = 'c'
Matched: pattern[3] = 'e' with text[12] = 'e'
Matched: pattern[2] = 'f' with text[11] = 'f'
Matched: pattern[1] = 'n' with text[10] = 'n'
Matched: pattern[0] = 'i' with text[9] = 'i'
✔ Match found at index 9

Checking alignment at shift 25:
...
Total matches found: 2
```

---

## **Algorithm Summary**

### 🔹 *Bad Character Preprocessing*

1. Initialize table with `-1`
2. For each character in pattern:

   * Store its last index

### 🔹 *Pattern Matching Phase*

1. Align pattern at shift `s = 0`
2. Compare from rightmost index `j = m - 1`
3. If mismatch:

   * Compute `shift = max(1, j - badchar[text[s + j]])`
4. If full match (`j < 0`):

   * Report match
   * Shift pattern intelligently

### 🔹 *Time Complexity*

| Case    | Complexity               |
| ------- | ------------------------ |
| Best    | **O(n / m)** (very fast) |
| Average | **Sublinear**            |
| Worst   | O(nm) (rare)             |

---

## **Conclusion**

This experiment demonstrates:

* Implementation of **Boyer–Moore using Bad Character Rule**
* Efficient pattern matching on long textual data
* Practical application in healthcare text analysis
* Significant improvement over brute-force matching
* Understanding of character shift tables and backward comparison

Boyer–Moore is widely used in **search engines**, **medical record scanners**, and **log analysis tools** for high-speed pattern detection.

---

## **Author**

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

**Experiment:** ADSA Laboratory — Experiment 11 (Boyer–Moore Pattern Matching)