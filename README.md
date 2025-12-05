[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/J8I-C1HJ)
# Finding The Shortest Distance

Name: Sitong Zhang

Github Account name: Cat97-97

Link to Assignment on Github: (copy and paste the link to your assignment repo here)
https://github.com/CS5008Fall2025/city-finder-Cat97-97.git
How many hours did it take you to complete this assignment (estimate)? 
15 hours
Did you collaborate with any other students/TAs/Professors? If so, tell us who and in what capacity.  
- None


Did you use any external resources (you do not have to cite in class material)? (Cite them below)  
- None (beyond standard C library and course materials)


## How to Build and Run

Prerequisites:
- macOS/Linux with `gcc` and `make` installed.
- Run all commands from the project root directory (`city-finder-Cat97-97`).

1. Build the program:

```bash
make
```

This produces an executable named `map.out`.

2. Run with the provided small dataset:

```bash
./map.out vertices.txt distances.txt
```

3. Run with the larger dataset:

```bash
./map.out city_list.dat city_distances.dat
```

4. Clean build artifacts (optional):

```bash
make clean
```

5. Optional: build and run the interview-practice program:

```bash
gcc -Wall -o two_sum.out coding_practice.c
./two_sum.out
```

6. Commands inside the interactive program:
	- `list` — list all cities
	- `<city1> <city2>` — compute shortest path and total distance
	- `help` — print help
	- `exit` — exit the program

## Testing

- Quick smoke tests:
	- `make test` (runs `tests/smoke_test.sh` against small and large datasets)

## Coding Practice File

- `coding_practice.c` implements the Two Sum problem with a hash map approach and includes notes on what was learned and how it compares with canonical solutions.

