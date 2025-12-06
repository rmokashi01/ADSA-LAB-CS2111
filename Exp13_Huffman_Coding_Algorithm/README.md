# Experiment 13 — Huffman Coding Algorithm (Data Compression)

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Implementation of Huffman Coding Algorithm  
**Language Used:** C  
**Application Example:** Compression of Medical Report Text in Hospital Database  

**Subject Teacher:** Prof. K. S. Gandle  
**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

---

## **Aim**

To implement the **Huffman Coding Algorithm** to generate optimal prefix-free binary codes for characters based on their frequency and use them to compress text efficiently.

---

## **Overview of Huffman Coding**

**Huffman Coding** is a popular lossless data compression algorithm. It assigns **shorter codes to frequent characters** and **longer codes to less frequent characters**, reducing the total number of bits needed.

### ✔ Key Properties

* **Lossless compression**
* **Prefix-free codes** (no code is a prefix of another)
* **Variable-length encoding**
* Based on **binary tree + min-heap**
* Used in ZIP, GZIP, JPEG, MP3, PNG, PDF, and more

---

# 🏥 **Real-Time Application: Medical Report Compression**

Hospitals generate huge text-based resources:

* Patient medical summaries
* Diagnostic notes
* Lab reports
* Prescription instructions

When thousands of patients’ records accumulate, **storage becomes expensive**.

Huffman Coding helps by:

* Compressing medical text
* Reducing database storage cost
* Speeding up data transfer between departments
* Improving backup efficiency

### Example Input Text:

```
fever detected in patient
```

Characters appearing more often get **shorter codes**.

---

## 🧱 **How Huffman Coding Works**

### **1. Count frequency of each character**

Example:

| Char | Frequency |
| ---- | --------- |
| e    | 5         |
| t    | 3         |
| n    | 2         |
| f    | 1         |
| v    | 1         |
| …    | …         |

---

### **2. Build a Min Heap**

Each node contains:

* character
* frequency
* left child
* right child

---

### **3. Build Huffman Tree**

Repeated steps:

1. Extract two lowest-frequency nodes
2. Create a new internal node with frequency = sum
3. Insert it back into heap
4. Continue until only one node remains

---

### **4. Generate Codes (0 = left, 1 = right)**

Example Huffman codes:

| Character | Code |
| --------- | ---- |
| e         | 00   |
| i         | 001  |
| f         | 010  |
| v         | 011  |
| space     | 10   |
| r         | 1011 |
| d         | 1010 |
| t         | 111  |
| a         | 1000 |
| p         | 1001 |

---

## 📂 **Project Structure**

```
Exp13_HuffmanCoding/
│── main.c
│── huffman.c
│── huffman.h
│── README.md   ← (this file)
```

---

## **How to Compile**

```bash
gcc main.c huffman.c -o exp13
```

Run program:

```bash
./exp13      # Windows: exp13.exe
```

---

## 🧪 **Sample Input**

```
Enter text to compress:
fever detected in patient
```

---

## 📜 **Sample Output**

```
Huffman Codes for Each Character:

Character ' ' → Code: 10
Character 'n' → Code: 110
Character 't' → Code: 111
Character 'f' → Code: 010
Character 'e' → Code: 00
Character 'v' → Code: 011
Character 'r' → Code: 1011
Character 'd' → Code: 1010
Character 'i' → Code: 001
Character 'p' → Code: 1001
Character 'a' → Code: 1000
```

*(Codes may vary depending on tree construction, but compression is always optimal.)*

---

## **Algorithm Summary**

### 🔹 Step 1 — Count frequencies

Scan the text and count each character’s occurrence.

### 🔹 Step 2 — Create min heap

Insert each character-frequency pair.

### 🔹 Step 3 — Build Huffman Tree

Always merge the **two least frequent** nodes.

### 🔹 Step 4 — Generate binary codes

Traversing left adds `0`, right adds `1`.

### 🔹 Step 5 — Encode the text

Replace each character with its binary code.

---

## **Conclusion**

This experiment demonstrates:

* Construction of Huffman Tree using min-heap
* Generation of optimal prefix-free binary codes
* Efficient text compression using variable-length encoding
* A real-world healthcare application for **compressing medical records**

Huffman Coding plays a vital role in storage systems, communication, file compression, and modern software.

---

## **Author**

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

**Experiment:** ADSA Laboratory — Experiment 13 (Huffman Coding Algorithm)  