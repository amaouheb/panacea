% cette fonction prend en entrée une matrice de coûts représentant un graphe direct, une source et une
% destination pour donner en sortie le plus court chemin entre la source et
% la desination et la distance de ce chemin
function ShortestPath = bf (costs, source , destination)


%Préparation des entrées de la fonction graphshortestpath 
k=1;
a=[];
b=[];
c=[];
while k < 20 
    for i=1:19
        x(i)=i;
        y(i)=k;
    end
    a=[a x];
    b=[b y];
    z=costs(k,:);
    %z=costs(:,k)';
    c=[c z];
    k=k+1;    
end

DG = sparse(a,b,c); 
[dist,path,pred] = graphshortestpath(DG,source,destination);%Find the shortest path in the graph from node source to destination

ShortestPath= [dist,path]; % on récupère le plus court chemin et la distance
end





