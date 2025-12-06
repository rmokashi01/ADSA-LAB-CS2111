# Experiment 1 — Skip List Implementation (Student Database)
**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Operations on Skip Lists  
**Language Used:** C  
**Application Example:** Student Database Management (Insert, Search, Delete, Display)

**Subject Teacher:** Prof. K. S. Gandle  
**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*
**Government College of Engineering, Karad (GCEK)** 

---

## **Aim**
To implement **Skip List** data structure and perform the following operations:  
- Insertion of student records  
- Searching a student by roll number  
- Deleting a student record  
- Displaying all students in sorted order  

A skip list provides **O(log n)** performance for insert, search, and delete, similar to balanced trees but simpler to implement.

---

## **Overview of Skip List**

A **Skip List** is a probabilistic data structure built using multiple levels of linked lists.  
Each element may appear in more than one level depending on randomization.

### Why Skip Lists?
- Faster search compared to normal linked lists  
- Simple compared to BST, AVL, Red-Black trees  
- Uses probability-based level generation  

---

## 🧱 **Structure Used**

### **Node Structure**
Each node stores:
- `roll number` (key)
- `name`
- `marks`
- `forward[]` pointer array
- `nodeLevel`

### **Skip List Structure**
Stores:
- `header` node
- `current highest level`

---

## 📂 **Project Structure**

```

Exp1_SkipList_StudentDB/
│── main.c
│── skiplist.c
│── skiplist.h
│── README.md   ← (this file)

````

---

## **Features Implemented**

| Operation | Description |
|----------|-------------|
| Insert Student | Adds a new student or updates existing |
| Search Student | Finds student by roll number |
| Delete Student | Removes student record |
| Display All | Shows all records in sorted order |
| Preloaded Demo Data | Automatically loads 10 student records |

---

## 👨‍🎓 **Preloaded Demo Students**
Program startup me automatically load hone wale 10 Indian student records:

| Roll No | Name | Marks |
|--------|-------------------|-------|
| 101 | Rehan Mokashi | 92.5 |
| 102 | Sakshi Patil | 96.0 |
| 103 | Priya Patil | 79.4 |
| 104 | Sneha Kulkarni | 85.2 |
| 105 | Arjun Rao | 91.3 |
| 106 | Neha Singh | 76.8 |
| 107 | Manish Deshmukh | 83.0 |
| 108 | Kiran Joshi | 89.1 |
| 109 | Ritika Mehta | 95.0 |
| 110 | Sagar Pawar | 72.5 |

---

## **How to Compile**

Terminal me run karein:

```bash
gcc main.c skiplist.c -o exp1
````

Run program:

```bash
./exp1      # Windows: exp1.exe
```

---

## 📜 **Sample Output**

```
10 demo student records loaded successfully!

===== Student Database using Skip List =====
1. Insert / Update Student
2. Search Student by Roll
3. Delete Student by Roll
4. Display All Students
5. Exit
Enter your choice: 4

Roll    Name               Marks
-------------------------------------------
101     Rehan Mokashi      92.50
102     Sakshi Patil       96.00
103     Priya Patil        79.40
104     Sneha Kulkarni     85.20
105     Arjun Rao          91.30
106     Neha Singh         76.80
107     Manish Deshmukh    83.00
108     Kiran Joshi        89.10
109     Ritika Mehta       95.00
110     Sagar Pawar        72.50
-------------------------------------------
```

---

## **Algorithm Summary**

### 🔹 *Insertion Algorithm*

1. Start from highest level
2. Move forward while next key < target
3. Record update pointers
4. Generate random level
5. Insert node at all required levels

### 🔹 *Search Algorithm*

1. Start at highest level
2. Traverse until key is found or list ends

### 🔹 *Deletion Algorithm*

1. Same traversal as search
2. Update pointers at each level
3. Free node memory
4. Adjust list level if necessary

---

## **Conclusion**

This experiment demonstrates:

* Efficient implementation of Skip List
* Use of probabilistic balancing
* Real-world application: Student Database System
* Understanding multi-level linked structures

Skip List achieves **logarithmic performance** with simpler implementation compared to balanced BSTs.

---

## **Author**

**Mr. Rehan Mokashi**  
*Student, F.Y. M.Tech (Computer Science & Engineering)*  
**Government College of Engineering, Karad (GCEK)**  

**Subject:** Advanced Data Structures and Algorithms (ADSA)  
**Subject Teacher:** Prof. K. S. Gandle  

**Experiment:** ADSA Laboratory — Experiment 1


---


