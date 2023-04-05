# cplex-examples

## Linear and Mixed Integer Programming Models

### [model-1](https://github.com/oscaralejandro1907/cplex-examples/tree/main/model-1/Model)
A simple example, made without classes, and inside the ```main``` function. The model has 3 variables of 1 subindex (x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub>). After model is solved solution status, solution value (obj. function), values of variables, and slacks of constraints are printed.

### [model-2](https://github.com/oscaralejandro1907/cplex-examples/tree/main/model-2/Model)
A simple linear model example. A ```CplexModel``` class is created from within all steps are executed, then an object to call the constructor of the class is created in the ```main``` function to run the model. The model has 2 variables of 1 subindex (x<sub>1</sub>, x<sub>2</sub>). After model is solved solution status, solution value (obj. function), values of variables, and slacks of constraints are printed.

### [glasses-model](https://github.com/oscaralejandro1907/cplex-examples/tree/main/glasses-model/Model)
A simple linear model example of a production of glasses. A ```CplexModel``` class is created.

### [min-flow-model](https://github.com/oscaralejandro1907/cplex-examples/tree/main/min-flow-model/Model)
An example minimum flow model, A ```CplexModel``` class is created. After solve the problem to other constraints are added to call cplex to re-optimize the previous solved model. 

### [feed-mix](https://github.com/oscaralejandro1907/cplex-examples/tree/main/feed-mix/feed-mix)
An example of a feed-mix problem. This example is in the book: Bazaraa. Linear Programming and Network Flows. 4th Ed. Chapter 1 Exercise 1.3 page 29-30.

### [model-by-columns](https://github.com/oscaralejandro1907/cplex-examples/tree/main/model-by-columns/Model)
An simple example of a linear model populated by columns with one type of variable (x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub>). A ```Cplex``` class is created within all steps are executed.

### [integer-model-pcol](https://github.com/oscaralejandro1907/cplex-examples/tree/main/integer-model-pcol/Model)
An example of an integer model with two types of variables of 1 subindex (x<sub>i</sub> and y<sub>i</sub>). This model is populated by columns.

### [cut-stock](https://github.com/oscaralejandro1907/cplex-examples/tree/main/cut-stock/Model)
An example of a cutting stock problem. Solved by a column generation procedure

### [tsp](https://github.com/oscaralejandro1907/cplex-examples/tree/main/tsp/TSP)
A complete tsp model

## Multi-Objective Problems

### [multi-obj-sample](https://github.com/oscaralejandro1907/cplex-examples/tree/main/multi-obj-sample/multiObj-sample)
Two examples of simple multiobjective problems

### [eps-constraint-example](https://github.com/oscaralejandro1907/cplex-examples/tree/main/eps-constraint-example/eps-constraint-example)
A simple bi-objective model solved by the eps-Constraint method.

## Constraint Programming Models

### [graph-coloring](https://github.com/oscaralejandro1907/cplex-examples/tree/main/graph-coloring)
An introduction example to Constraint Programming (CP). An instance about a problem of graph coloring is solved with this solution method.

### [house-building](https://github.com/oscaralejandro1907/cplex-examples/tree/main/house-building)
A simple example of a CP Model to organize tasks for building a house. Only precedence constraint ```IloEndBeforeStart``` is used.

### [flow-shop-cp](https://github.com/oscaralejandro1907/cplex-examples/tree/main/flow-shop-cp)
A CP model for a classic Flow-shop Scheduling Problem. Instance data format is provided in the examples of the cplex local installation folder.

### [job-shop](https://github.com/oscaralejandro1907/cplex-examples/tree/main/job-shop)
A CP model for a classic Job Shop Scheduling problem. Instance data an steps based on the example provided in the cplex local installation folder.

### [flex-job-shop](https://github.com/oscaralejandro1907/cplex-examples/tree/main/flex-job-shop)
A CP model for a classic Flexible Job Shop Scheduling problem. Instance data an steps based on the example provided in the cplex local installation folder.

