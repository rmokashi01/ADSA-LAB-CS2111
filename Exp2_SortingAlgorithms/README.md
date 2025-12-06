# **Experiment 2 — Advanced Sorting Algorithms Visualization & Analysis**

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Lab:** ADSA Laboratory  
**Experiment Title:** Implementation, Visualization & Comparative Analysis of Sorting Algorithms  
**Language Used:** C  
**Application Example:** Interactive Sorting Algorithm Visualizer with Step-by-Step Process Display  

## 👨‍💻 **Author & Academic Information**

**Author:** **Mr. Rehan Mokashi**  
**Program:** First Year M.Tech (Computer Science & Engineering)  
**Institution:** Government College of Engineering, Karad (GCEK)  
**University:** Shivaji University, Kolhapur  
**Academic Year:** 2025-2026

  

---

## 🎯 **Aim & Objectives**

### **Primary Aim:**
To implement three fundamental comparison-based sorting algorithms with comprehensive visualization capabilities that demonstrate their internal working mechanisms.

### **Specific Objectives:**
1. **Implement** Merge Sort, Quick Sort, and Heap Sort algorithms
2. **Visualize** each sorting step with clear, formatted output
3. **Compare** algorithmic approaches and their operational characteristics
4. **Create** an interactive user interface for algorithm selection
5. **Document** time/space complexities and practical applications

---

## 🧠 **Algorithmic Overview & Theoretical Foundation**

### **1️⃣ MERGE SORT — Divide & Conquer Paradigm**
```c
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;        // Divide
        mergeSort(arr, l, m);       // Conquer Left
        mergeSort(arr, m + 1, r);   // Conquer Right
        merge(arr, l, m, r);        // Combine
    }
}
```
**Key Characteristics:**
- **Paradigm:** Divide and Conquer
- **Stability:** ✅ Stable (preserves relative order)
- **Type:** Comparison-based, Non-inplace (requires O(n) extra space)
- **Recurrence Relation:** T(n) = 2T(n/2) + O(n)
- **Best for:** Linked Lists, External Sorting (when data doesn't fit in RAM)
- **Real-world Application:** External merge sort for database systems

### **2️⃣ QUICK SORT — Partition-Based Approach**
```c
int partitionQS(int arr[], int low, int high) {
    int pivot = arr[high];          // Pivot selection strategy
    int i = low - 1;                // Index of smaller element
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {      // Compare with pivot
            i++;
            swap(arr[i], arr[j]);   // Partitioning logic
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;                   // Final pivot position
}
```
**Key Characteristics:**
- **Paradigm:** Partition and Conquer
- **Stability:** ❌ Unstable (may change relative order)
- **Type:** Comparison-based, Inplace (O(log n) recursive stack)
- **Pivot Strategies:** Last element, First element, Median-of-three, Random
- **Best for:** General-purpose in-memory sorting
- **Real-world Application:** C standard library `qsort()`, Java `Arrays.sort()` for primitives

### **3️⃣ HEAP SORT — Binary Heap Utilization**
```c
void heapify(int arr[], int n, int i) {
    int largest = i;                // Root index
    int left = 2 * i + 1;           // Left child index
    int right = 2 * i + 2;          // Right child index
    
    // Find largest among root, left, right
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]); // Heap property violation
        heapify(arr, n, largest);   // Recursively heapify
    }
}
```
**Key Characteristics:**
- **Paradigm:** Selection Sort with Heap Data Structure
- **Stability:** ❌ Unstable
- **Type:** Comparison-based, Inplace (O(1) extra space)
- **Heap Properties:** Complete binary tree, Heap-order property
- **Best for:** When worst-case O(n log n) is required, Priority queue operations
- **Real-world Application:** Linux kernel scheduler (priority queues), Dijkstra's algorithm

---

## 🏗️ **System Architecture & Implementation**

### **File Structure**
```
Exp2_SortingAlgorithms/
├── sorting.h              # Interface declarations
├── sorting.c              # Algorithm implementations + visualization
├── main.c                 # Driver program + menu system
└── README.md              # This documentation
```

### **Modular Design**

| Module | Responsibility | Functions |
|--------|---------------|-----------|
| **Interface (sorting.h)** | Public API declaration | Sorting functions, visualization helpers |
| **Implementation (sorting.c)** | Algorithm logic | `merge()`, `partitionQS()`, `heapify()`, print utilities |
| **Driver (main.c)** | User interaction | Menu system, array management, algorithm execution |

### **Visualization Engine Design**
```c
// Hierarchical visualization structure
void printHeader()   // Algorithm title and table header
void printDivider()  // Table separators  
void printArrayStep()// Each sorting step with description
void printFooter()   // Table closure
void printArray()    // Final sorted array display
```

---

## 🚀 **Features & Innovations**

### **✅ Core Features**
1. **Interactive Menu System** – User-friendly CLI interface
2. **Step-by-Step Visualization** – Each algorithmic operation displayed
3. **Algorithm Isolation** – Independent copies for fair comparison
4. **Educational Output** – Annotated steps showing logic flow
5. **Error Handling** – Memory allocation validation

### **🎯 Advanced Features**
1. **Process Transparency** – Shows splits, merges, partitions, heap operations
2. **Subarray Tracking** – Displays current working segment of array
3. **Pivot Highlighting** – Quick Sort pivot selection and placement
4. **Heap State Display** – Shows heap structure evolution
5. **Comparison Ready** – All algorithms process identical input

---

## 📊 **Complexity Analysis & Comparison**

### **Asymptotic Analysis Table**

| Algorithm | Time Complexity | Space Complexity | Stability | In-Place | Adaptive |
|-----------|----------------|------------------|-----------|----------|----------|
| **Merge Sort** | O(n log n) | O(n) | ✅ Yes | ❌ No | ❌ No |
| **Quick Sort** | O(n²) worst, O(n log n) average | O(log n) | ❌ No | ✅ Yes | ❌ No |
| **Heap Sort** | O(n log n) | O(1) | ❌ No | ✅ Yes | ❌ No |

### **Detailed Complexity Breakdown**

#### **Merge Sort**
```
Recurrence: T(n) = 2T(n/2) + Θ(n)
Solution: Θ(n log n) [Master Theorem Case 2]
Space: Θ(n) for temporary arrays
Best Case: Already sorted → Θ(n log n)
Worst Case: Reverse sorted → Θ(n log n)
```

#### **Quick Sort**
```
Best Case: Balanced partitions → Θ(n log n)
Average Case: Random input → Θ(n log n) [Expected]
Worst Case: Already sorted + pivot at ends → Θ(n²)
Space: Θ(log n) recursion stack [Best], Θ(n) [Worst]
```

#### **Heap Sort**
```
Heap Building: O(n) [Bottom-up heapify]
Each Extraction: O(log n)
Total: O(n) + n × O(log n) = O(n log n)
Space: O(1) in-place
```

### **Empirical Performance Characteristics**

| Scenario | Merge Sort | Quick Sort | Heap Sort |
|----------|------------|------------|-----------|
| Small Arrays (<100) | Moderate | Fast | Slow |
| Large Arrays (10⁶) | Good | Excellent | Good |
| Already Sorted | O(n log n) | O(n²) [worst pivot] | O(n log n) |
| Reverse Sorted | O(n log n) | O(n²) | O(n log n) |
| Random Data | O(n log n) | O(n log n) [expected] | O(n log n) |
| Memory Usage | High | Low | Very Low |

---

## 🛠️ **Implementation Details**

### **Memory Management Strategy**
```c
// Dynamic allocation in main()
int *arr = (int*)malloc(n * sizeof(int));
if (arr == NULL) {
    printf("Memory allocation failed!\n");
    return 1;  // Graceful error handling
}
// ... algorithm execution ...
free(arr);  // Memory deallocation
```

### **Algorithm Copy Mechanism**
```c
// Create independent copies for fair comparison
int arrMerge[n], arrQuick[n], arrHeap[n];
for (int i = 0; i < n; i++) {
    arrMerge[i] = arr[i];  // Merge Sort copy
    arrQuick[i] = arr[i];  // Quick Sort copy  
    arrHeap[i] = arr[i];   // Heap Sort copy
}
```

### **Visualization Format**
```
+--------------------------------------------------------------+
| MERGE SORT - DIVIDE & CONQUER                                |
+---------------------------+----------------------------------+
| STEP                      | ARRAY ELEMENTS                  |
+---------------------------+----------------------------------+
| Split [0-9] at 4          |   5   6   4   1   2   3   7   8   9   4 |
| Merge [0-0] & [1-1]       |   5   6   4   1   2   3   7   8   9   4 |
| After Merge               |   5   6   4   1   2   3   7   8   9   4 |
+---------------------------+----------------------------------+
```

---

## 📋 **Input/Output Specifications**

### **Input Format**
```
Enter number of elements: 8
Enter 8 elements:
Element 1: 64
Element 2: 34
Element 3: 25
Element 4: 12
Element 5: 22
Element 6: 11
Element 7: 90
Element 8: 45
```

### **Output Structure**
```
1. Algorithm Selection Menu
2. Header with Algorithm Name
3. Step-by-Step Process Table
4. Final Sorted Array Display
5. Footer with Completion Message
```

### **Sample Visualization Output**
```
+--------------------------------------------------------------+
| QUICK SORT - PARTITION BASED                                 |
+---------------------------+----------------------------------+
| STEP                      | ARRAY ELEMENTS                  |
+---------------------------+----------------------------------+
| Original Array            |  64  34  25  12  22  11  90  45 |
| Partition [0-7], pivot=45 |  64  34  25  12  22  11  90  45 |
| Swap 12 <-> 64            |  12  34  25  64  22  11  90  45 |
| Swap 22 <-> 34            |  12  22  25  64  34  11  90  45 |
| Swap 11 <-> 64            |  12  22  25  11  34  64  90  45 |
| Place pivot at 4          |  12  22  25  11  34  45  90  64 |
| Pivot position: 4         |  12  22  25  11  34  45  90  64 |
+---------------------------+----------------------------------+
```

---

## 🔧 **Compilation & Execution**

### **Development Environment**
- **Compiler:** GCC (MinGW on Windows, GCC on Linux/Mac)
- **Standard:** C99
- **Dependencies:** Standard C Library only
- **Platform:** Cross-platform (Windows/Linux/macOS)

### **Build Commands**
```bash
# Compile all source files
gcc -std=c99 -Wall -Wextra -o sorting_visualizer main.c sorting.c

# Alternative with optimization
gcc -std=c99 -O2 -o sorting_visualizer main.c sorting.c

# Debug build with symbols
gcc -std=c99 -g -o sorting_visualizer_debug main.c sorting.c
```

### **Execution**
```bash
# Run the program
./sorting_visualizer        # Linux/Mac
sorting_visualizer.exe      # Windows

# Sample execution flow
$ ./sorting_visualizer
+--------------------------------------------------------------+
|                   WELCOME TO SORTING VISUALIZER              |
+--------------------------------------------------------------+

Enter number of elements: 6
Enter 6 elements:
Element 1: 38
Element 2: 27
Element 3: 43
Element 4: 3
Element 5: 9
Element 6: 82

Original Array: 38 27 43 3 9 82

+--------------------------------------------------------------+
|                    SORTING ALGORITHMS VISUALIZER             |
+--------------------------------------------------------------+
| 1. Merge Sort                                                |
| 2. Quick Sort                                                |
| 3. Heap Sort                                                 |
| 4. All Algorithms                                            |
| 5. Exit                                                      |
+--------------------------------------------------------------+
Enter your choice (1-5): 1
```

---

## 📈 **Educational Value & Learning Outcomes**

### **Conceptual Understanding**
1. **Divide & Conquer** – Merge Sort implementation
2. **Partitioning Schemes** – Quick Sort pivot strategies
3. **Heap Data Structure** – Binary heap properties and operations
4. **Recursive Thinking** – Recursive algorithm design
5. **In-place vs Out-of-place** – Memory trade-offs

### **Practical Skills Developed**
1. **Algorithm Implementation** – Translating pseudocode to C
2. **Debugging & Testing** – Verifying algorithm correctness
3. **Performance Analysis** – Understanding time/space trade-offs
4. **Code Organization** – Modular programming with headers
5. **User Interface Design** – Creating interactive CLI applications

### **Computer Science Concepts Reinforced**
- **Recurrence Relations** – Analyzing recursive algorithms
- **Asymptotic Notation** – Big-O, Big-Ω, Big-Θ analysis
- **Stable vs Unstable** – Sorting algorithm properties
- **Adaptive vs Non-adaptive** – Algorithm behavior with input
- **Cache Performance** – Memory access patterns

---

## 🧪 **Testing & Validation**

### **Test Cases Implemented**

| Test Case | Purpose | Expected Behavior |
|-----------|---------|-------------------|
| Empty Array | Edge case handling | No sorting, empty output |
| Single Element | Base case | Return same element |
| Already Sorted | Best-case scenario | Minimal operations (Heap Sort) |
| Reverse Sorted | Worst-case scenario | Maximum operations |
| Random Data | General case | Normal sorting behavior |
| Duplicate Values | Stability test | Check relative ordering |
| Large Input (n>1000) | Performance test | Verify O(n log n) scaling |

### **Validation Strategy**
1. **Unit Testing** – Individual algorithm verification
2. **Cross-validation** – All algorithms produce identical sorted output
3. **Step Verification** – Each visualized step corresponds to algorithm logic
4. **Memory Testing** – No memory leaks (valgrind/AddressSanitizer)
5. **Boundary Testing** – Array bounds and edge cases

---

## 🔍 **Advanced Topics & Extensions**

### **Potential Optimizations**
1. **Merge Sort** – Hybrid with Insertion Sort for small subarrays
2. **Quick Sort** – Median-of-three pivot, Tail recursion elimination
3. **Heap Sort** – Bottom-up heap construction, Iterative implementation
4. **Visualization** – Color coding, Animation, Graphical output

### **Extension Ideas**
1. **Add More Algorithms** – Insertion Sort, Selection Sort, Bubble Sort
2. **Performance Metrics** – Comparison count, Swap count, Execution time
3. **Graphical Interface** – GTK/Qt based visualization
4. **Algorithm Comparison** – Side-by-side execution visualization
5. **Educational Mode** – Step-by-step explanation with pseudocode

### **Research Connections**
1. **Parallel Sorting** – Merge Sort parallelization (OpenMP)
2. **External Sorting** – Merge Sort for large datasets
3. **Adaptive Sorting** – Algorithms that adapt to input patterns
4. **Cache-aware Sorting** – Blocking for better cache performance

---

## 📚 **References & Further Reading**

### **Academic References**
1. **Introduction to Algorithms** – Cormen, Leiserson, Rivest, Stein (MIT Press)
2. **The Art of Computer Programming, Vol 3** – Donald Knuth (Sorting & Searching)
3. **Algorithms** – Sedgewick & Wayne (Princeton University)

### **Online Resources**
1. **VisuAlgo** – Sorting algorithm visualizations (https://visualgo.net)
2. **GeeksforGeeks** – Algorithm implementations and explanations
3. **MIT OpenCourseWare** – 6.006 Introduction to Algorithms

### **Research Papers**
1. "Engineering a Sort Function" – Bentley & McIlroy (1993)
2. "The Analysis of Heapsort" – Schaffer & Sedgewick (1993)
3. "QuickSort with Equal Keys" – Bentley & Sedgewick (1997)

---

## 🏆 **Conclusion & Insights**

### **Key Takeaways**
1. **Algorithm Selection Depends on Context** – No single "best" sorting algorithm
2. **Trade-offs Are Fundamental** – Time vs Space, Stability vs In-place
3. **Visualization Enhances Understanding** – Abstract concepts become concrete
4. **Implementation Details Matter** – Pivot selection, base cases, edge conditions

### **Algorithm Selection Guidelines**
- **Merge Sort** – When stability needed, external sorting, linked lists
- **Quick Sort** – General-purpose in-memory sorting, average-case speed critical
- **Heap Sort** – Guaranteed O(n log n), limited memory, priority queues

### **Educational Impact**
This experiment transforms abstract algorithmic concepts into tangible, observable processes. By visualizing each step, students develop deeper intuition about algorithmic behavior, complexity analysis, and implementation techniques.

---

## 👨‍💻 **Author & Academic Information**

**Author:** **Mr. Rehan Mokashi**  
**Program:** First Year M.Tech (Computer Science & Engineering)  
**Institution:** Government College of Engineering, Karad (GCEK)  
**University:** Shivaji University, Kolhapur  
**Academic Year:** 2025-2026

**Course:** CS2111 – Advanced Data Structures & Algorithms  
**Laboratory:** ADSA Laboratory – Experiment 2  
**Faculty:** **Prof. K. S. Gandle**  
**Department:** Computer Science & Engineering  
 

---

## 📞 **Contact & Repository**

**GitHub Repository:** [https://github.com/rmokashi01](https://github.com/rmokashi01)  
**Email:** rehanmokashi786@gmail.com 

---

## ⭐ **Acknowledgments**

I express my sincere gratitude to **Prof. K. S. Gandle** for guidance and to **Government College of Engineering, Karad** for providing excellent computational facilities. Special thanks to the open-source community for educational resources that made this implementation possible.

---

*"The best sorting algorithm is the one you understand best."*  
*"First make it work, then make it fast, then make it beautiful."*

--- 

**© 2025 ADSA Laboratory, GCEK Karad. This documentation is for academic purposes only.**