[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/J8I-C1HJ)
# Finding The Shortest Distance

Name: Sitong Zhang

Github Account name: Cat97-97

Link to Assignment on Github: (copy and paste the link to your assignment repo here)
https://github.com/CS5008Fall2025/city-finder-Cat97-97.git
How many hours did it take you to complete this assignment (estimate)? 
13 hours
Did you collaborate with any other students/TAs/Professors? If so, tell us who and in what capacity.  
- one per row, add more if needed


Did you use any external resources (you do not have to cite in class material)? (Cite them below)  
- one row per resource


## How to Build and Run

1. Build (from project root):
	- `make`
2. Run with provided small dataset:
	- `./map.out vertices.txt distances.txt`
3. Run with larger dataset:
	- `./map.out city_list.dat city_distances.dat`
4. Commands inside the program:
	- `list` — list all cities
	- `<city1> <city2>` — compute shortest path and total distance
	- `help` — print help
	- `exit` — exit the program

## Testing

- Quick smoke tests:
	- `make test` (runs `tests/smoke_test.sh` against small and large datasets)

## Coding Practice File

- `coding_practice.c` implements the Two Sum problem with a hash map approach and includes notes on what was learned and how it compares with canonical solutions.

