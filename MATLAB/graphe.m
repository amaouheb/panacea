close all
clear all
clc

load graphes
load ShortestPath

% %%%%%%%%%%%%%%%% Créer les matrices de coûts %%%%%%%%%%%%%%%%
% A=importdata('concat2.txt'); % récupérer le fichier des rtts
% B= A(:,2); % récupérer la colonne des RTTS moyen
% 
% E=matintrlv(B,length(B)/3836,3836); % regrouper à la suite dans un seul vecteur les rtts enregistrés dans le mm tps  
% 
% %%%%%%%%%%%%%%%%%%Créer les graphes de coûts%%%%%%%%%%%%%%%%%
% l=1;
% k=1;
% while k < length(E) 
%     for i=1:19
%         for j=1:19
%             if i==j
%                 M(i,j)=0;
%             else 
%                 M(i,j)=E(k);
%                 k=k+1;
%             end
%         end
%     end 
%     Graphe{l}=M; % Cellule contenant tous les graphes
%     l=l+1;
%     
% end

% %%%%%%%%%%%% Etude du plus court chemin %%%%%%%%%%%%%%% 
% l=1;
% 
% for k=1:size(Graphe,2)
%     
%     for i=1:19
%         for j=1:19
%             A=bf(Graphe{k},i,j);
%             D{l,k}=A; % les plus courts chemins du mm graphe sont contenus dans la mm colonne de la Cellule D
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

m=1;
for j=1:size(D,2)
    nb_in=0;
    for i=1:size(D,1)
        if (length(D{i,j})>3)
            nb_in=nb_in+1;
            if (mod(i,19) == 0)
                k=i/19;
                l=19;
            else
                k=floor(i/19)+1;
                l=mod(i,19);
            end
            gain(m) =Graphe{j}(k,l)-D{i,j}(1);% gain en temps en prenant le plus court chemin
            m=m+1;
        end
    end
      rate(j)=(nb_in/size(D,1))*100; % pourcentage des chemins plus courts non directs 
      gain_moyen(j)= mean(gain);% gain moyen en temps par lien dans chaque graphe
      
end

moyenne_nndirect = (mean(rate)); % moyenne des chemins non directs sur tous les graphes 

moyenne_gain = (mean(gain_moyen)); % moyenne des gains en temps sur tous les graphes

figure
plot(rate,'r');
hold on 
plot ( [0,3835],[moyenne_nndirect, moyenne_nndirect] , 'b')
hold off 
ylabel('\fontname{arial}\fontsize{17}pourcentage des chemins non directs');
xlabel('\fontname{arial}\fontsize{17}temps par palier de 2 min');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'nondirects_moyen','fig');

figure 
plot (gain_moyen,'r');
hold on 
plot ( [0,3835],[moyenne_gain, moyenne_gain] , 'b')
hold off 
ylabel('gain moyen par graphe en ms');
xlabel('temps par palier de 2 min');
title('gain en prenant le plus court chemin fonction du temps');
saveas(gcf,'Gain_moyen','fig');

% save ShortestPath D 
% save graphes Graphe