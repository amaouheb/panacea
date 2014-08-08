close all
clear all
clc


load ShortestPath; 
load graphes;
D; % Cellule ne contenant que le plus court chemin et la distance

% %%%%%%%%%%%% Calculer le nombre de fois où le plus court chemin change %%%%%%%%%%%%%%
% 
% Changement_SourceDestination = zeros(1,size(D,1)); %les changements du plus court chemin pour la meme (source,destination) 
% Changement_graphe= zeros(1,(size(D,2)-1)); %changements du plus court chemin dans le meme graphe (par pas de temps)
% 
% 
% for i=1:size(D,1);
%     for j=1:(size(D,2)-1);
%         if (length(D{i,j}) ~= length(D{i,j+1})) % s'ils n'ont pas la mme longueur donc le chemin a change
%             Changement_SourceDestination(i) = Changement_SourceDestination(i)+1;
%             Changement_graphe(j) = Changement_graphe(j)+1;  
%         elseif(D{i,j}(2:end) ~= D{i,j+1}(2:end)) % sinn il faut verifier si les chemins sont égaux 
%             Changement_graphe(j) = Changement_graphe(j)+1;
%             Changement_SourceDestination(i) = Changement_SourceDestination(i)+1;
%         end
%     end
% end
% 
% Changement_graphe = (Changement_graphe./size(D,1))*100;
% moyenne_graphe = mean (Changement_graphe);
% 
% Changement_SourceDestination = (Changement_SourceDestination./(size(D,2)-1))*100;
% moyenne_SourceDestination = mean (Changement_SourceDestination);
% 
% figure
% plot (Changement_graphe,'b');
% hold on 
% plot ([0,3835],[moyenne_graphe,moyenne_graphe],'r');
% hold off 
% xlabel('temps par pas de 2 min');
% ylabel('changement du plus court chemin en %');
% title('changement du plus court chemin en fonction du temps');
% saveas(gcf,'Changement_graphe','fig');
% 
% figure 
% plot(Changement_SourceDestination, 'r');
% hold on 
% plot([0,361],[moyenne_SourceDestination,moyenne_SourceDestination], 'b');
% xlabel('couple (source,dstination)');
% ylabel('changement du plus court chemin en %');
% title('changement du plus court chemin en fct du couple (source,destination)');
% saveas(gcf,'Changement_SourceDestination','fig');

%%%%%%%%%%%% Calculer le nombre de fois où le plus court chemin change si un gain seuil est atteint  %%%%%%%%%%%%%%



 changement_graphe_seuil = zeros(1,size(D,2)-1);
 for i=1:size(D,1);
      if (mod(i,19) == 0)
                k=i/19;
                l=19;
            else
                k=floor(i/19)+1;
                l=mod(i,19);
      end
      for j=1:(size(D,2)-1)
     
        if (length(D{i,j}) ~= length(D{i,j+1}))% s'ils n'ont pas la mme longueur donc le chemin a change
            
            %%%Verifier si le seuil de gain est atteint ou si le chemin est
            %%%en panne cas où on considère que le gain est significatif
            if ((Graphe{j}(l,k)==2000) | ((Graphe{j}(l,k)-D{i,j}(1))*100)/(Graphe{j}(l,k)) >5 )
                %%%% Attention!! il faut bien inverser les couples dans le graphe
                %%%% pour avoir le meme ordre quand pour les plus courts chemin
                %%%% En efft les expériences non synchronisées ont fait que le
                %%%% graphe(matrice des coûts) n'est pas symétrique comme le veut
                %%%% la logique
                changement_graphe_seuil(j+1)=changement_graphe_seuil(j)+1;
                
            end
        elseif( D{i,j}(2:end) ~= D{i,j+1}(2:end) ) % sinn il faut verifier si les chemins sont égaux
            %%%Verifier si le seuil de gain est atteint ou si le chemin est
            %%%en panne cas où on considère que le gain est significatif
            if ((Graphe{j}(l,k)==2000) | (Graphe{j}(l,k)-D{i,j}(1))*100)/(Graphe{j}(l,k) >5 )
                changement_graphe_seuil(j+1)=changement_graphe_seuil(j)+1;
            end
        end
    end
 end
 
 moyenne_graphe_seuil = mean (changement_graphe_seuil);
 
figure
plot (changement_graphe_seuil,'b');
hold on 
plot ([0,3835],[moyenne_graphe_seuil,moyenne_graphe_seuil],'r','LineWidth',2);
hold off 
xlabel('\fontname{arial}\fontsize{17}temps par pas de 2 min');
ylabel('\fontname{arial}\fontsize{17}pourcentage des plus courts chemins changés');
saveas(gcf,'Changement_graphe_seuil','fig');

[n, xout] = hist(changement_graphe_seuil,0:1:max(changement_graphe_seuil));
figure;
bar(xout, n);
c = .05;
text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
set(gca, 'ylim', [0 max(n)*(1+2*c)])
ylabel('\fontname{arial}\fontsize{17}nbr d occurence');
xlabel('\fontname{arial}\fontsize{17}pourcentage des plus courts chemins changés ');
title('\fontname{arial}\fontsize{17}changement du plus court chemin si 5% du gain est atteint');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'hist_changement_graphe_seuil','fig');

figure;
[h,stats] = cdfplot(changement_graphe_seuil);
set(h,'color','r','LineStyle','-');
ydata = get(h,'YData');
ydata = ydata.*100;
set(h,'YData',ydata);
ylabel('\fontname{arial}\fontsize{17} pourcentage de temps');
xlabel('\fontname{arial}\fontsize{17}pourcentage des plus courts chemins changés');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'repar_per_panne','fig');

