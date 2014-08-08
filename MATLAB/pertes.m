close all
clear all
clc

nb_lien= 342; % nombre de liens 
duree = 3836; % duree de l'experience en 2min

A= importdata('pertes.txt'); % recuperer le fichier des pourcentages de perte

%%%%%%%%%%%%%%%% Pourcentage moyen des pertes par lien en fonction du temps %%%%%%%%%%%%%%%%

B= matintrlv(A,length(A)/duree,duree); % regrouper à la suite dans un seul vecteur les pourcentages de perte enregistrés dans le mm tps  
B= reshape(B,nb_lien,length(B)/nb_lien); % chaque vecteur correspond au meme tps

for i=1:duree
   perte_tps(i) = mean(B(:,i));
   max_perte_tps(i) = max(B(:,i));
end

moyenne_tps = mean(perte_tps);
max_tps = mean(max_perte_tps);

figure 
plot (perte_tps,'b');
hold on 
plot ( [0,duree],[moyenne_tps, moyenne_tps] , 'r');
hold off 
ylabel('pourcentage moyen des pertes par lien');
xlabel('temps par pas de 2min');
title('pourcentage moyen des pertes par lien fct du tps');
saveas(gcf,'pertes_tps','fig');

figure 
plot (max_perte_tps,'b');
hold on 
plot ( [0,duree],[max_tps, max_tps] , 'r');
hold off 
ylabel('max de pertes par lien');
xlabel('temps par pas de 2min');
title('max de pertes par lien fct du tps');
saveas(gcf,'max_tps','fig');

%%%%%%%%%%%%%%%% Pourcentage moyen des pertes sur toute l'expérience en fonction du lien%%%%%%%%%%%%%%%%

C = reshape(A, duree,length(A)/duree);

for i=1:nb_lien
    perte_lien(i) = mean(C(:,i));
end

moyenne_lien = mean(perte_lien);

figure
plot (perte_lien,'b');
hold on 
plot ( [0,nb_lien],[moyenne_lien, moyenne_lien] , 'r');
hold off 
ylabel('pourcentage moyen des pertes');
xlabel('lien');
title('pourcentage moyen des pertes fct du lien');
saveas(gcf,'pertes_lien','fig');


[n, xout] = hist(perte_lien,0:0.1:max(perte_lien));
figure;
bar(xout, n);
c = .05;
text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
set(gca, 'ylim', [0 max(n)*(1+2*c)]);
ylabel('\fontname{arial}\fontsize{17}nbr de liens');
xlabel('\fontname{arial}\fontsize{17}pourcentage de perte');
title('\fontname{arial}\fontsize{17}histogramme des pourcentages de perte ');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'hist_perte_lien','fig');



figure;
[h,stats] = cdfplot(perte_lien);
set(h,'color','r','LineStyle','-');
ydata = get(h,'YData');
ydata = ydata.*100;
set(h,'YData',ydata);

ylabel('\fontname{arial}\fontsize{17}pourcentage des liens');
xlabel('\fontname{arial}\fontsize{17}pourcentage de pertes');
title('\fontname{arial}\fontsize{17}');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'repar_perte_lien','fig');