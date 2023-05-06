# graph_alg_test_env

This is a graph algorithm test environment. It is a software project for the Information Technology Labs course ar University of Turku (DTEK2074-3001) as well as a part of my (Botond Ortutay, @gitond) BSc Thesis.

#### Software description:

This software is a part of my thesis work and I intend to use it to test pathfinding algorithms for my thesis. The software comprises of modules and it is written in C++ using Object-oriented programming.

The finished project will contain at least the following modules:
- a main module for running the software
- a class implementation to represent graph data, which has functions needed by the algorithms (a function that returns neighbor relations between edges for example)
- a graph visualisation module (or function)
- a random graph generator module (or function)
- separate modules for at least the following algorithms:
	1. BFS
	2. DFS
	3. Dijkstra's algorithm
	4. A*
	- each of these modules contain implementations for these algoritms, a way to run them and a way to measure running time and memory usage
- a module for hierarchical pathfinding
- modules for heuristic algorithms used with A*, as well as high-level graph generator algorithms for hierarchical pathfinding.
- a module for handling external file operations. At least graphs, measurements and pictures (visualisation) need to be saved and possibly read from external files.

#### Information Technology Labs (DTEK2074-3001) related metadata:

Tool utilization:
- Version control (using git and GitHub)
	- GitHub Issues for tracking milestones and ToDos
	- GitHub Actions for running automatized tests on each commit

#### BSc Thesis metadata:

The following algorithm combinations will be tested:

| Number  | Abbreviation  | Pathfinding  | Heuristic  | High-level graph  |
| :------------: | :------------: | :------------: | :------------: | :------------: |
| 1  | BFS  | BFS  |   |   |
| 2  | DFS  | DFS  |   |   |
| 3  | Dij  | Dijkstra  |   |   |
| 4  | A*Man  | A*  | Manhattan  |   |
| 5  | A*Euk | A*  | Euclidean  |   |
| 6  | A*Kulm  | A*  | Angle  |   |
| 7  | HNelA*  | A*  | Euclidean  | Rectangles16  |
| 8  | BigND  | Dijkstra  |   | Rectangles64  |
| 9  | SmlND  | Dijkstra  |   | Rectangles16  |
| 10  | CHDij  | Dijkstra  |   | CH  |

#### Assets

This project uses the open-source font "Liberation Mono" by Red Hat Inc. The 
font's license allows it's usage and redistributionas long as the font itself 
or parts of it aren't sold. The original license of the font is included in 
the assets/fonts/ library

#### Academic sources

**applSciLavande**: S. R. Lawande, G. Jasmine, J. Anbarasi, and L. I. Izhar, “A Systematic Review and Analysis of Intelligence-Based Pathfinding Algorithms in the Field of Video Games,” Applied Sciences, vol. 12, no. 11, p. 5499, May 2022, doi: 10.3390/app12115499.

**ortutayBSc**: Botond Ortutay. “Polunetsintäalgoritmit (väliaikainen otsikko)”. Finnish. BA thesis. Turku: University of Turku, 2023. url: https://github.com/gitond/bsc_thesis_data_structure/blob/main/latex/thesis.pdf (visited on 04/29/2023). In preparation.
