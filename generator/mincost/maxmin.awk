#!/usr/bin/awk -f

#-------------------------------------------------------------
# THIS IS A FIXED VERSION
# Awk program to change DIMACS max-flow format to min-cost format
# by the following rules:
# --Add an uncapacitated edge from sink to source, with cost -1
# --All nodes are transshipment nodes
# --All arc costs are 0
#-------------------------------------------------------------

#Change header line or flag bad header

($1 == "p") && ($2 == "max") {nodes = $3; arcs = $4;
	print "p", "min", nodes, arcs
 	print "c Transformed from a max-flow problem.";
			}
($1 == "p") && ($2 != "max") {print " ERROR--NOT A MAX-FLOW INPUT"; }

#Copy comment lines
$1 == "c"	{print $0}

#Save source and sink to make new arc
($1 == "n") && ($3 == "s") {source = $2; }
($1 == "n") && ($3 == "t") {sink = $2;}

#Copy arcs with 0 cost and 0 lower bounds
$1 == "a"	{print $1, " ", $2 " " $3 " " 0  " " $4 " " 0}

#Make new arc from sink to source.
#Uncapacitated value is represented as a negative number

END	{print "n"," " source " " 1
print "n"," " sink, " " -1}