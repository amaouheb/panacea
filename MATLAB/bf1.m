
% Author: Chad Hart
% Advisor: Dr. Tim Redl
% Title: Bellman-Ford Algorithm
% Description: This program implements the Bellman-Ford Shortest PathAlgorithm.
% The program will input a square matrix of any size n, which
% will denote the cost from one node to another. The rows of
% this matrix will define the cost "from" one node, while the
% columns willdefine the "to" cost.
%
% For example:
%
%         [0 2 5]
% costs = [2 0 3]
%         [5 3 0]
%
% The cost from node 2 to 3 is 3
%
%This program can be used for a directed or undirected graph.
% Please note that if the graph is undirected, the matrix
% should be symetric reflected accross the diagonal.
%
% The program will also input the source and destination node
function bellmanford(costs, source, dest)
n = size(costs, 1); % determine the size of S

S(1:n) = 0;  % initialize S to all 0's
distance(1:n) = inf; % initialize distance vector to all inf
previous(1:n) = inf; % initialize previous node vector to all inf

distance(source) = 0; % set source distance to 0
for (i = 1:n-1)
    for (j = 1:n)  % Update distance vector if feasible
        for (k = 1:n)
            if((distance(j) + costs(j,k) < distance(k)) && (costs(j,k) ~=0))
                distance(k) = distance(j) + costs(j,k);
                previous(k) = j;
            end
        end
    end
end
% distance % Output Distance vector
% previous % Output Previous Node vector
ShortestPath = [dest];
traverse = dest;
while (previous(traverse) ~= source) % Traverse backwards to find path

    ShortestPath = [previous(traverse) ShortestPath];
    traverse = previous(traverse);
end
ShortestPath = [ previous(traverse) ShortestPath]