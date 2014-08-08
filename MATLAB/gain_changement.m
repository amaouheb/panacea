close all
clear all
clc


load ShortestPath; 
load graphes;


%%%%%%%%%%%% Calculer le gain en pourcentage sur toute la periode de l'experience pour chaque changement de chemin %%%%%%%%%%%%%%


m=1;
for j=1:size(D,2)-1
    for i=1:size(D,1)
        if (mod(i,19) == 0)
                k=i/19;
                l=19;
        else
            k=floor(i/19)+1;
            l=mod(i,19);
         end
        if (length(D{i,j}) ~= length(D{i,j+1})) % s'ils n'ont pas la mme longueur donc le chemin a change      
            %on ne prend pas en considération les pertes totales cas où on
            %ne dispose pas de valeur pour le rtts et où clairement le gain
            %sera signifiant car aucun paquet n'a été reçu.
            if (Graphe{j}(l,k)~=2000)
                gain_changement(m) =((Graphe{j}(l,k)-D{i,j}(1))*100)/(Graphe{j}(l,k));% pourcentage du gain en temps en prenant le plus court chemin
                m=m+1;
            end
        elseif(D{i,j}(2:end) ~= D{i,j+1}(2:end)) % sinn il faut verifier si les chemins sont égaux 
            %on ne prend pas en considération les pertes totales cas où on
            %ne dispose pas de valeur pour le rtts et où clairement le gain
            %sera signifiant car aucun paquet n'a été reçu.
            if (Graphe{j}(l,k)~=2000)
                gain_changement(m) =((Graphe{j}(l,k)-D{i,j}(1))*100)/(Graphe{j}(l,k));% pourcentage du gain en temps en prenant le plus court chemin
                m=m+1;
            end
        end
    end
    Gain_changement(j)= mean(gain_changement);% gain moyen en pourcentage par changement de chemin
end

moyenne_changement= mean(Gain_changement);

figure 
plot (Gain_changement,'b');
hold on 
plot ( [0,3835],[moyenne_changement, moyenne_changement] , 'r');
hold off 
ylabel('gain en pourcentage');
xlabel('temps par palier de 2 min');
title('gain en pourcentage pour chaque changement de chemin');
saveas(gcf,'Gain_graphe_changement','fig');

