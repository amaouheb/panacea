close all
clear all
clc

nb_lien= 342; % nombre de liens 
duree = 3836; % duree de l'experience en 2min

A= importdata('pertes.txt'); % recuperer le fichier des pourcentages de perte

%%%%%%%%%%%%%%%% Pourcentage des liens en panne en fonction du temps %%%%%%%%%%%%%%%%

B= matintrlv(A,length(A)/duree,duree); % regrouper à la suite dans un seul vecteur les pourcentages de perte enregistrés dans le mm tps  
B= reshape(B,nb_lien,length(B)/nb_lien); % chaque vecteur correspond au meme tps 

for i=1:duree
    per_panne(i) = (length(find(B(:,i)==100))/nb_lien)*100;
end

moyenne_per = mean(per_panne);

figure 
plot (per_panne,'b');
hold on 
plot ( [0,duree],[moyenne_per, moyenne_per] , 'r');
hold off 
ylabel('pourcentage des liens en panne');
xlabel('temps par palier de 2 min');
title('pourcentage des liens en panne en fonction du temps');
saveas(gcf,'p_panne','fig');

[n, xout] = hist(per_panne,0:1:max(per_panne));
figure;
bar(xout, n);
c = .05;
text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
set(gca, 'ylim', [0 max(n)*(1+2*c)])
ylabel('durée en 2min');
xlabel('nbr de liens en panne au même temps');
title('histogramme du nbre de liens en panne ');
saveas(gcf,'hist_p_panne','fig');

figure;
[h,stats] = cdfplot(per_panne);
set(h,'color','r','LineStyle','-');
ydata = get(h,'YData');
ydata = ydata.*100;
set(h,'YData',ydata);
ylabel('\fontname{arial}\fontsize{17} pourcentage de temps');
xlabel('\fontname{arial}\fontsize{17}pourcentage de panne');
title('\fontname{arial}\fontsize{17}');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'repar_per_panne','fig');

%%%%%%%%%%%%%%%% Fréquence (par minute) de pannes d'un lien  %%%%%%%%%%%%%%%%

C = reshape(A, duree,length(A)/duree);

for i=1:nb_lien
    endommage(i)=length(find(C(:,i))>100);
end

[n, xout] = hist(endommage,0:1:max(endommage));
figure
bar(xout, n);
c = .05;
text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
set(gca, 'ylim', [0 max(n)*(1+2*c)])
ylabel('nbr de liens');
xlabel('nbre de fois où une perte est detectee');
title('nbre de cas de pertes par lien');
saveas(gcf,'endommage','fig');

%%%%%%%%% nbr de pannes consécutives et durée de ces pannes pour chaque lien %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

duree_panne = zeros(nb_lien,nb_lien);
nb_panne_cons = zeros(1,nb_lien); % nbr de pannes qui dure au moins deux fois 
nb_panne_1 = zeros(1,nb_lien);
k=0;
for i=1:nb_lien 
    X=find(C(:,i)==100);% les moments où une panne est detectée
    nb_panne(i)=length(X);
    j=1;
    while j<=length(X)
        if (j<length(X) & (X(j+1)==X(j)+1)) % verifier si la panne va durer 
            nb_panne_cons(i) = nb_panne_cons(i) +1;
            k=k+1; 
            nb_panne_1(i) = nb_panne_1(i)+1;
            duree_panne(i,k)=duree_panne(i,k)+1;
            while (j< length(X) & (X(j+1) == X(j)+1) ) % compter la durée de cette panne
                duree_panne(i,k)=duree_panne(i,k)+1;
                nb_panne_1(i) = nb_panne_1(i)+1;
                j=j+1;
            end
        else %sinn la panne ne va duree qu'une seule fois
            k=k+1;
            nb_panne_1(i) = nb_panne_1(i)+1;
            duree_panne(i,k)=duree_panne(i,k)+1;
        end
        j=j+1;
    end
   k=0;
  duree_pannes(i)=sum(duree_panne(i,:));
end

max_duree = max(duree_panne,[],2); % la durée max d'une panne 


[n, xout] = hist(nb_panne,0:1:max(nb_panne));
figure;
bar(xout, n);
c = .05;
text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
set(gca, 'ylim', [0 max(n)*(1+2*c)])
ylabel('\fontname{arial}\fontsize{17}nbr de liens');
xlabel('\fontname{arial}\fontsize{17}nbr de pannes');
title('\fontname{arial}\fontsize{17}histogramme des nbr de pannes');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'hist_nb_panne','fig');

% figure 
% hist(nb_panne_cons);
% ylabel('nbr de liens');
% xlabel('nbr de pannes consécutives');
% title('histogramme des nbr de pannes consécutives');
% saveas(gcf,'hist_nb_panne_cons','fig');

[n, xout] = hist(max_duree);
figure 
bar(xout, n);
c = .05;
text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
set(gca, 'ylim', [0 max(n)*(1+2*c)])
ylabel('\fontname{arial}\fontsize{17}nbr de liens ');
xlabel('\fontname{arial}\fontsize{17}duree max de la panne');
title('\fontname{arial}\fontsize{17}histogramme des durees max de panne');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'hist_max_duree','fig');

[n, xout] = hist(duree_pannes,0:1:max(duree_pannes));
figure
bar(xout, n);
c = .05;
text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
set(gca, 'ylim', [0 max(n)*(1+2*c)]);
ylabel('\fontname{arial}\fontsize{17}nbr de liens');
xlabel('\fontname{arial}\fontsize{17}duree cummulée des pannes');
title('\fontname{arial}\fontsize{17}histogramme des durees de pannes')
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'hist_duree_pannes','fig');


figure;
[h,stats] = cdfplot(max_duree);
set(h,'color','r','LineStyle','-');
ydata = get(h,'YData');
ydata = ydata.*100;
xdata = get(h,'XData');
xdata = xdata.*2;
set(h,'xData',xdata);
set(h,'YData',ydata);
ylabel('\fontname{arial}\fontsize{17}pourcentage des liens en panne');
xlabel('\fontname{arial}\fontsize{17}durée de la panne en min');
title('\fontname{arial}\fontsize{17}');
set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,'repar_perte_lien','fig');
