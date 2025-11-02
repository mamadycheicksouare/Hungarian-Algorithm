# Hungarian Algorithm Implementation

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

A high-performance C implementation of the Hungarian algorithm (Kuhn-Munkres algorithm) for solving the assignment problem with double precision floating-point costs.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Real-World Applications](#real-world-applications)
- [Installation](#installation)
- [Usage](#usage)
- [Example](#example)
- [Algorithm Complexity](#algorithm-complexity)
- [Technical Details](#technical-details)
- [License](#license)
- [Author](#author)

## 🎯 Overview

The Hungarian algorithm solves the **assignment problem**: given an *n×m* cost matrix, find the optimal assignment of workers to jobs that minimizes the total cost. This implementation handles both square and rectangular matrices with double precision accuracy.

### What is the Assignment Problem?

Given:
- *n* workers
- *m* jobs  
- Cost matrix *C[i][j]* = cost of assigning worker *i* to job *j*

Find: Assignment that minimizes total cost while ensuring each worker is assigned to at most one job.

## ✨ Features

- ✅ **Optimal Solution**: Guaranteed to find the minimum-cost perfect matching
- ✅ **Rectangular Matrix Support**: Handles *n×m* matrices where *n ≠ m*
- ✅ **Double Precision**: Accurate floating-point cost calculations
- ✅ **Efficient**: O(n³) time complexity
- ✅ **Memory Safe**: Proper dynamic memory management
- ✅ **Production Ready**: Battle-tested in real-world applications

## 🚀 Real-World Applications

This implementation has been successfully deployed in:

### 1. **Autonomous Vehicle Fleet Management**
- **Use Case**: Matching available autonomous golf vehicles with incoming client requests
- **Objective**: Minimize total distance/travel time across the fleet
- **Impact**: Optimized vehicle utilization and reduced client wait times

### 2. **Computer Vision Pipeline** 
- **Use Case**: Assignment module in Vision Transformer (ViT) training for PPE vest detection
- **Context**: Part of a safety monitoring system for construction sites
- **Note**: Later replaced with YOLO for superior real-time performance requirements

### Other Potential Applications
- Task scheduling in distributed systems
- Resource allocation in cloud computing
- Ride-sharing driver-passenger matching
- Image feature matching in computer vision
- Network flow optimization

## 📦 Installation

### Prerequisites
- GCC compiler (or any C compiler)
- Standard C library

### Compilation

```bash
gcc hungarian.c -o hungarian
```

For optimized build:
```bash
gcc -O3 hungarian.c -o hungarian
```

With debugging symbols:
```bash
gcc -g hungarian.c -o hungarian
```

## 💻 Usage

### Basic Example

```c
#include <stdio.h>
#include <stdlib.h>


int main() {
    int n = 3;  // number of workers
    int m = 4;  // number of jobs
    
    // Allocate cost matrix
    double **cost = alloc_matrix(n, m);
    
    // Fill cost matrix
    cost[0][0] = 9.0; cost[0][1] = 2.5; cost[0][2] = 7.1; cost[0][3] = 8.3;
    cost[1][0] = 6.2; cost[1][1] = 4.8; cost[1][2] = 3.0; cost[1][3] = 7.9;
    cost[2][0] = 5.0; cost[2][1] = 8.1; cost[2][2] = 1.5; cost[2][3] = 8.7;
    
    // Solve assignment problem
    int *match = (int *)malloc(m * sizeof(int));
    double total_cost = hungarian(n, m, cost, match);
    
    // Print results
    printf("Minimum total cost = %.3f\n", total_cost);
    for (int j = 0; j < m; j++) {
        if (match[j] != -1) {
            printf("Job %d -> Worker %d (Cost = %.2f)\n",
                   j, match[j], cost[match[j]][j]);
        } else {
            printf("Job %d -> unassigned\n", j);
        }
    }
    
    // Cleanup
    free(match);
    free_matrix(cost, n);
    return 0;
}
```

### Running the Example

```bash
./hungarian
```

**Output:**
```
Minimum total cost = 10.200
Job 0 -> Worker 1 (Cost = 6.20)
Job 1 -> Worker 0 (Cost = 2.50)
Job 2 -> Worker 2 (Cost = 1.50)
Job 3 -> unassigned
```

## 📊 Example

### Problem Setup

You have 3 workers and 4 jobs with the following costs:

|         | Job 0 | Job 1 | Job 2 | Job 3 |
|---------|-------|-------|-------|-------|
| Worker 0| 9.0   | 2.5   | 7.1   | 8.3   |
| Worker 1| 6.2   | 4.8   | 3.0   | 7.9   |
| Worker 2| 5.0   | 8.1   | 1.5   | 8.7   |

### Optimal Solution

Minimum total cost = 10.200

Job 0 -> Worker 1 (Cost = 6.20)

Job 1 -> Worker 0 (Cost = 2.50)

Job 2 -> Worker 2 (Cost = 1.50)

Job 3 -> unassigned


## ⚡ Algorithm Complexity

- **Time Complexity:** O(n³) where n = max(number of workers, number of jobs)
- **Space Complexity:** O(n²) for the padded cost matrix and auxiliary arrays

The algorithm uses:
- Dual variables (u, v) for reduced cost computation
- Augmenting path technique for iterative improvement
- Dijkstra-like shortest path search in each iteration

## 🔧 Technical Details

### Matrix Padding

When the cost matrix is not square (n ≠ m), the algorithm automatically pads it to size N×N where N = max(n, m) by adding:
- Dummy workers with high costs (1e9) if n < m
- Dummy jobs with high costs (1e9) if m < n

This ensures the algorithm can find a valid matching.

### Numerical Stability

- Uses `double` precision for all calculations
- `INF = 1e18` for theoretical infinity
- Padding cost of `1e9` prevents overflow while maintaining distinction from actual costs

### Memory Management

The implementation follows strict memory management:
1. All allocations are explicitly freed
2. Helper functions provided for matrix allocation/deallocation
3. No memory leaks in normal execution paths

### Edge Cases

- **More jobs than workers** (n < m): Some jobs remain unassigned
- **More workers than jobs** (n > m): Some workers remain unassigned
- **Equal workers and jobs** (n = m): Perfect matching with all assigned
- **Zero costs**: Handled correctly
- **Negative costs**: Not supported (algorithm minimizes positive costs)

### Some Possible Improvments

- Add maximization variant (maximum weight matching)
- Support for negative costs
- Sparse matrix optimization
- Performance benchmarks

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Mamady Cheick Souare**

- GitHub: [mamadycheicksouare](https://github.com/mamadycheicksouare)
- Email: mamadycheicksouare@gmail.com

## 🙏 Acknowledgments

- Original algorithm by Harold Kuhn (1955)
- Implementation inspired by competitive programming community
- Tested in production environments during internship projects

## 📖 References

- Kuhn, H. W. (1955). "The Hungarian Method for the assignment problem". *Naval Research Logistics Quarterly*.
- Munkres, J. (1957). "Algorithms for the Assignment and Transportation Problems". *Journal of the Society for Industrial and Applied Mathematics*.
