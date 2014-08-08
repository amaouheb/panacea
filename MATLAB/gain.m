close all
clear all
clc

load graphes;
load ShortestPath;

%%%%%%%%%%%%% caclcul du gain en pourcentage en prenant le chemin le plus court
%%%%%%%%%%%%% %%%

m=1;
p=1;
a=1;
for j=1:size(D,2)
    nb_in=0;
    for i=1:size(D,1)
        if (length(D{i,j})>3)  % le chemin n'est pas direct 
            nb_in=nb_in+1;
            %%%boucle pour trouver le couple source destination%%%%
            if (mod(i,19) == 0)
                k=i/19;
                l=19;
            else
                k=floor(i/19)+1;
                l=mod(i,19);
            end
            %on ne prend pas en considération les pertes totales cas où on
            %ne dispose pas de valeur pour le rtts et où clairement le gain
            %sera signifiant car aucun paquet n'a été reçu.
            if (Graphe{j}(l,k)~=2000)
                Gain(m) =((Graphe{j}(l,k)-D{i,j}(1))*100)/(Graphe{j}(l,k));% pourcentage du gain en temps en prenant le plus court chemin
                m=m+1;
%                 if (max(Gain) >76)
%                     Graphe{j}(k,l)
%                     D{i,j}(1)
%                     i
%                     ligne(a)=k
%                     colonne(a)=l
%                     graphe(a)=j
%                     a=a+1;
%                     pause
%                 end
               
            end
        end
    end
      gain_moyen(p)= mean(Gain);% gain moyen en pourcentage en temps par lien dans chaque graphe
      gain_max(p)= max(Gain); % gain maximal en pourcnetage en temps par lien dans chaque graphe 
      p=p+1;
end  

%moyenne_nndirect = (mean(rate)); % moyenne des chemins non directs sur tous les graphes 

moyenne_gain_moyen = (mean(gain_moyen)); % moyenne des gains moyens en temps sur tous les graphes
moyenne_gain_max = (mean(gain_max)); % moyenne des gains max en temps sur tous les graphes 


figure 
plot (gain_moyen,'r','LineWidth',2);
hold on 
plot ( [0,3835],[moyenne_gain_moyen, moyenne_gain_moyen] , 'b','LineWidth',2);
hold off 
ylabel('\fontname{arial}\fontsize{17}gain en pourcentage par graphe');
xlabel('\fontname{arial}\fontsize{17}temps par palier de 2 min');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'Gain_moyen_Pourcentage','fig');

figure 
plot (gain_max,'r');
hold on
plot ( [0,3835], [moyenne_gain_max, moyenne_gain_max], 'k');
hold off 
ylabel('gain en pourcentage par graphe');
xlabel('temps par palier de 2 min');
title('gain max en prenant le plus court chemin en fonction du temps');
saveas(gcf,'Gain_max_Pourcentage','fig');
