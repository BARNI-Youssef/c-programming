# Project suggestions

## Problem
An abandoned rail network is being renovated.  
The routes connecting two big cities have train stations in the smaller cities in between.  
The train stations are all separated by 1h from each other, as the old routes are all connected and can have multiple routes to the same cities, you need to help the railroad engineers to know:

1. All the routes between the two big cities.
2. shortest path between the two big cities. (using Breadth First Search algorithm)
3. the routes that can make x number of trains go from a big city to another in the shortest time you will need to give the routes that maximize the flow in the network.

#### NOTE 01: The above steps should be delivered as separated programs.
#### NOTE 02: beside the two big cities a train stations can only contains 1 train at a time.

### INPUT

```bash
$ cat map00
3
5
S-c1 
S-c2 
c1-c3 
c2-E
c3-E
```

- the first number `3` represent the number of trains that will be used.
- the second number `5` represent the number of the cities in network.

- the big cities are always represented by `S` and `E`.

- the other cities are represented by `cx` where x is the city number. (city number can be very large)

- the `x-y` writing represent the link between two cities.

### Usage example
```bash
$ ./part01 map01
number of routes possible is: 4
S -> c1 -> c3 -> E
S -> c1 -> c4 -> E
S -> c2 -> c3 -> E
S -> c2 -> c3 -> c1 -> c4 -> E
```

```bash
$ ./part03 map01
number of routes possible is: 4
S -> c1 -> c3 -> E
S -> c1 -> c4 -> E
S -> c2 -> c3 -> E
S -> c2 -> c3 -> c1 -> c4 -> E

best routes: 
S -> c1 -> c4 -> E
S -> c2 -> c3 -> E

trains movements:
t1-S->c1 t2-S->c2
t1-c1->c4 t2-c2->c3 t3-S->c1 t4-S->c2
t1-c4->E t2-c3->E t3-c1->c4 t4-c2->c3 t5-S->c1 t6-S->c2
t3-c4->E t4-c3->E t5-c1->c4 t6-c2->c3 t7-S->c1 t8-S->c2
t5-c4->E t6-c3->E t7-c1->c4 t8-c2->c3 t9-S->c1 t10-S->c2
t7-c4->E t8-c3->E t9-c1->c4 t10-c2->c3
t9-c4->E t10-c3->E

hours spent for all trains to arrives:
7 hours.
```

NOTE: we can't use the other paths because we can't have 2 train depart from the start and be at `c1` or `c2` at the same time and we we can't use the long path because it will result in more hour spent.
NOTE: the number of ants sometimes affects the number of valid paths selected.

### Other examples:

```bash
$ cat map01
10
6
E-c3
E-c4
S-c1
S-c2
c1-c3
c1-c4
c2-c3
```

```bash
$ cat map02
10
6
c1-S
c1-c2
c2-S
c2-E
c2-c4
c3-S
c3-E
c3-c4
E-c4
```

```bash
$ cat map03
100
22
c0-c14
c0-c12
c1-c12
c1-c5
c1-c13
c1-c19
c2-c1
c2-c9
c2-c18
c3-c4
c3-c5
c4-c10
c4-c15
c5-c15
c5-c11
c5-c0
c5-c15
c5-c18
c5-c1
c6-c5
c6-c0
c7-c8
c8-c0
c8-c16
c8-c6
c9-c18
c9-c8
c9-c11
c10-c17
c10-c13
c10-c1
c10-c2
c10-c3
c11-c15
c11-c17
c11-c4
c11-c6
c12-c2
c12-c14
c13-c3
c14-c0
c14-c10
c14-c17
c14-c18
c14-c1
c14-c6
c14-c9
c14-c17
c15-c17
c15-c10
c16-c1
c17-c10
c18-c11
c19-c11
c19-c18
S-c8
S-c2
S-c18
E-c14
```