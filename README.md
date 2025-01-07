### Advent of Code 2024 - Solutions in C

Welcome! This repository contains my participation in the **Advent of Code 2024** (AoC), a scalable algorithmic challenge inspired by an advent calendar. For this project, I chose the **C programming language**, which I am most comfortable with.

While the code is not entirely clean or polished to the level of professional standards, it reflects a sincere personal effort. Some solutions are incomplete due to time constraints and limited experience, but I believe this work is still worth sharing.

---

## Repository Structure

Each daily challenge is organized into submodules by day, along with additional utilities when necessary. Below is a detailed summary of the problems tackled and the solutions implemented:

### Day 1: Differences and Repetitions in Lists
- **Part One:** Sort two lists in ascending order and calculate the difference between corresponding pairs of numbers. This is done by iterating both lists in parallel and accumulating the differences.
- **Part Two:** Count how many times each number from the left list appears in the right list. If a number repeats in the left list, its repetitions in the right list are added again.

### Day 2: Report Security
- **Part One:** Check if the levels in a report (a list of numbers) exhibit a strictly increasing or decreasing trend. Additionally, adjacent levels must differ by a value between 1 and 3. If the trend is mixed or the difference is outside the range, the report is deemed insecure.
- **Part Two:** Determine how many reports become secure after removing a single level. This includes an advanced attempt using a `problem_dampener` flag to temporarily ignore problematic levels, though the final implementation was unsuccessful.

### Day 3: Conditional Multiplications
- **Part One:** Parse the input to find fragments in the format `mul(x, y)`, calculate the product of `x` and `y`, and sum all results. The logic involves scanning the input, extracting values within parentheses, and performing the operations.
- **Part Two:** Implement a hierarchy where operations are invalidated after encountering `don't()` until a `do()` appears. Various implementations were explored, but none fully solved the more complex aspects of the problem.

### Day 4: Searching for "XMAS" in Matrices
- **Part One:** Search for the word "XMAS" in a matrix in all 8 directions (horizontal, vertical, and diagonals). For each instance of 'X', the algorithm scans in every direction to verify if the contiguous characters form the complete word. A child process and the `get_next_line` function are used to handle input and matrix rows.
- **Part Two:** For each 'M', a possible diagonal instance of "MAS" is sought. If found, the algorithm checks whether another instance forms a cross with it.

### Day 5: Rule Validation and Updates
- **Part One:** Parse the input to separate "rules" and "updates." Each rule specifies that certain levels in the updates must appear in a specific order. The goal is to validate the updates and sum the central level of those that follow the rules.
- **Part Two:** Process incorrect updates, sort them, and calculate the sum of their central levels.

### Day 6: Tracking Guards' Paths
- **Part One:** Track the route of a guard on a map represented as a matrix. The guard (`^`, `<`, `>`, `v`) follows a path until encountering an obstacle (`#`) or the map's edge. Upon hitting an obstacle, the guard turns 90° and continues. The goal is to mark each visited cell (`X`) and count the total.
- **Part Two:** Calculate all possible configurations of obstacles to trap the guard in an infinite loop. I found this too complex to approach given the available time.

### Day 7: Formulas with Limited Operations
- **Part One:** Determine if a target result can be achieved using a combination of operands and operations (addition and multiplication) in a strictly left-to-right order. The solution generates all possible combinations, simulates the operations, and compares them to the target result.
- **Part Two:** Extend the logic to include concatenation. A bitmask is used to generate combinations of operations, and for each combination, a `switch` determines whether to perform addition, multiplication, or concatenation. The final result is compared to the expected value.

---

## Results and Reflections

This repository contains solutions for the first **7 days**, achieving a total of **10 stars** (each day has 2 parts). While the complete 25-day calendar (50 stars) was not finished, I am satisfied with what I accomplished, considering the time constraints, my experience at the time of the challenges, and the language used.

The **Advent of Code 2024** was a fun and challenging experience that helped me improve my algorithmic skills and problem-solving abilities.

