Few of the intresting problem related to 2-SAT that i came across.
Giant_piazza.cpp The question give us n choices of n people of m topping in the piazza , every person must get at least one wish true. that is (x1 v y1 )^(x2 v y2)^...so on.
the idea is to create directed implication graph and find all strongly connected component and no (x) and (not of x) should be present in same SCC. Then we have solution 
otherwise not. If solution exits based on top sort that we get from kosaraju algo would be good enough to assign the value to each toppings.
