# cplex-examples

## Linear and Mixed Integer Programming Models

### model-1
A simple example, made without classes, and inside the ```main``` function. The model has 3 variables of 1 subindex (x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub>). After model is solved solution status, solution value (obj. function), values of variables, and slacks of constraints are printed.

### model-2
A simple linear model example. A ```CplexModel``` class is created from within all steps are executed, then an object to call the constructor of the class is created in the ```main``` function to run the model. The model has 2 variables of 1 subindex (x<sub>1</sub>, x<sub>2</sub>). After model is solved solution status, solution value (obj. function), values of variables, and slacks of constraints are printed.

### glasses-model
A simple linear model example of a production of glasses. A ```CplexModel``` class is created.

### min-flow-model
An example minimum flow model, A ```CplexModel``` class is created. After solve the problem to other constraints are added to call cplex to re-optimize the previous solved model. 

### feed-mix
An example of a feed-mix problem. This example is in the book: Bazaraa. Linear Programming and Network Flows. 4th Ed. Chapter 1 Exercise 1.3 page 29-30.

### model-by-columns
An simple example of a linear model populated by columns with one type of variable (x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub>). A ```Cplex``` class is created within all steps are executed.

### integer-model-pcol
An example of an integer model with two types of variables of 1 subindex (x<sub>i</sub> and y<sub>i</sub>). This model is populated by columns.

## Constraint Programming Models
### graph-coloring
An introduction example to Constraint Programming (CP). An instance about a problem of graph coloring is solved with this solution method.

### house-building
A simple example of a CP Model to organize tasks for building a house. Only precedence constraint ```IloEndBeforeStart``` is used.

### flow-shop-cp
A CP model for a classic Flow-shop Scheduling Problem. Instance data format is provided in the examples of the cplex local installation folder.
