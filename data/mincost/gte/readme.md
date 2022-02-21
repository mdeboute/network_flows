# Instances from Netflow

This directory contains a number of files of the form gte_bad.XXXXXX

These files are instances of a minimum-cost flow problem on a
particular 49 node graph. The instances differ in the choice of
capacities and demands. We ran these problems using the RELAXT-III
code of Bertsekas and Tseng. The interesting thing that happened was
the running times varied greatly. A file with the name gte_bad.XXXX
represents a graph which took XXXX milliseconds. These seems to be
bad examples for the RELAXT-III code, it would be interesting to see
how other minimum-cost flow code performed on these problems.

cf. --Cliff Stein (cliff@theory.lcs.mit.edu)

## DIMACS minimum-cost flow format

**Comment Lines**: Comment lines give human-readable information about the file and are ignored by programs. Comment lines can appear anywhere in the file. Each comment line begins with a lower-case character c.

    c This is an example of a comment line.

**Problem Line**: There is one problem line per input file. The problem line must appear before any node or arc descriptor lines. For minimum-cost flow network instances the problem line has the following format:

    p min NODES ARCS

The lower-case character p signifies that this is a problem line. The three-character problem designator min identifies the file as containing specification information for a minimum-cost flow problem. The NODES field contains an integer value specifying n, the number of nodes in the network. The ARCS field contains an integer value specifying m, the number of arcs in the network.

**Node Descriptors**: All node descriptor lines must appear before all arc descriptor lines. For minimum-cost flow instances, the node descriptor lines describe supply and demand nodes, but not transshipment nodes. That is, only nodes with nonzero node supply values appear. There is one node descriptor line for each such node, with the following format.

    n ID FLOW

The lower-case character n signifies that this is a node descriptor line. The ID field gives a node identification number, an integer between 1 and n. The FLOW field gives the amount of supply at node ID.

**Arc Descriptors**: There is one arc descriptor line for each arc in the network. For a minimum-cost flow instance, arc descriptor lines are of the following form.

    a SRC DST LOW CAP COST

The lower-case character a signifies that this is an arc descriptor line. For a directed arc (v,w) the SRC field gives the identification number for the source vertex v, and the DST field gives the destination vertex w. Identification numbers are integers between 1 and n. The LOW field specifies the minimum abount of flow that can be sent along arc (v,w), and the CAP field gives the maximum amount of flow that can be sent along arc (v,w) in a feasible flow. The COST field contains the per-unit cost of flow sent along arc (v,w).
