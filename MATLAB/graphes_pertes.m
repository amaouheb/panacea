close all
clear all
clc


% 
% %%%%%%%%%%%%%%%% Créer les matrices de coûts (pertes) %%%%%%%%%%%%%%%%
% A=importdata('pertes.txt'); % récupérer le fichier des pertes
% 
% E=matintrlv(A,length(A)/3836,3836); % regrouper à la suite dans un seul vecteur les taux de pertes enregistrés dans le mm tps  
% 
% %%%%%%%%%%%%%%%%%%Créer les graphes de coûts (pertes) %%%%%%%%%%%%%%%%%
% l=1;
% k=1;
% while k < length(E) 
%     for i=1:19
%         for j=1:19
%             if i==j
%                 M(i,j)=0;
%             else 
%                 if (E(k)==0)
%                     M(i,j)=0.001;
%                 else    
%                     M(i,j)=E(k);
%                 end
%                 k=k+1;
%             end
%         end
%     end 
%     Graphe_pertes{l}=M; % Cellule contenant tous les graphes
%     l=l+1;
%     
% end
% 
% 
% %%%%%%%%%%%% Etude du plus court chemin %%%%%%%%%%%%%%% 
% l=1;
% 
% for k=1:size(Graphe_pertes,2)
%     
%     for i=1:19
%         for j=1:19
%             A=bf(Graphe_pertes{k},i,j);
%             D_pertes{l,k}=A; % les plus courts chemins du mm graphe sont contenus dans la mm colonne de la Cellule D
%             l=l+1;
%             if (l==361)
%                 l=361;
%             else   
%                 l=mod(l,361);
%             end
%         end 
%     end
% end


%%%%%%%%%%%%% caclcul du pourcentage des chemins plus courts non directs
%%%%%%%%%%%%% %%%

load graphes_pertes;
load ShortestPath_pertes;

m=1;
for j=1:size(D_pertes,2)
    nb_in=0;
    for i=1:size(D_pertes,1)
        if (length(D_pertes{i,j})>3)
            nb_in=nb_in+1;
            if (mod(i,19) == 0)
                k=i/19;
                l=19;
            else
                k=floor(i/19)+1;
                l=mod(i,19);
            end
            Gain(m) =((Graphe_pertes{j}(l,k)-D_pertes{i,j}(1))*100)/(Graphe_pertes{j}(l,k));% % pourcentage des gains en pertes  en prenant le plus court chemin
            m=m+1;
        end
    end
      rate(j)=(nb_in/size(D_pertes,1))*100; % pourcentage des chemins plus fiables non directs 
      gain_moyen(j)= mean(Gain);% pourcentage des gains moyens en pertes par lien dans chaque graphe
      gain_max(j)= max(Gain); % pourcentage des gains max en pertes par lien dans chaque graphe 
      
end

moyenne_nndirect = (mean(rate)); % moyenne des chemins non directs sur tous les graphes 

moyenne_gain_moyen = (mean(gain_moyen)); % moyenne des gains en pertes sur tous les graphes
moyenne_gain_max = (mean(gain_max)); % moyenne des gains max en temps sur tous les graphes 

figure 
plot(rate,'b');
hold on 
plot ( [0,3835],[moyenne_nndirect, moyenne_nndirect] , 'r')
hold off 
ylabel('pourcentage des chemins plus fiables non directs');
xlabel('temps par palier de 2 min');
title('pourcentage des chemins plus fiables non directs en fonction du temps');
saveas(gcf,'nondirects_pertes','fig');

figure 
plot (gain_moyen,'b');
hold on 
plot ( [0,3835],[moyenne_gain_moyen, moyenne_gain_moyen] , 'r');
hold off 
ylabel('\fontname{arial}\fontsize{17}gain en pourcentage par graphe');
xlabel('\fontname{arial}\fontsize{17}temps par palier de 2 min');
title('\fontname{arial}\fontsize{17}gain moyen en prenant le chemin plus fiable en fonction du temps');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'Gain_moyen_pertes','fig');


figure 
plot (gain_max,'b');
hold on
plot ( [0,3835], [moyenne_gain_max, moyenne_gain_max], 'r');
hold off 
ylabel('gain en pourcentage par graphe');
xlabel('temps par palier de 2 min');
title('gain max en prenant le plus court chemin en fonction du temps');
saveas(gcf,'Gain_max_pertes','fig');


% save ShortestPath_pertes D_pertes 
% save graphes_pertes Graphe_pertes