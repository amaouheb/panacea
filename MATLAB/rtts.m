

% %%Ce script permet à un lien donné de tracer la figure des
% %%rtts correspondante.
% 
% close all
% clear all
% clc
% 
% nb_lien= 342; % nombre de liens 
% duree = 3836; % duree de l'experience en 2min
% 
% A= importdata('concat1.txt'); % recuperer le fichier des pourcentages de perte
% 
% 
% 
% S={'Japon','Californie','Australie','Norvege','Pologne','Floride','Irlande','Honkkong','Cotedivoire','Israel','Russie','Chili','Bresil','Gibraltar','Texas','Canada','Boston','France','Singapour'};
% 
% disp('voici la liste des sources et destination possible: Japon,Californie,Australie,Norvege,Pologne,Floride,Irlande,Honkkong,Cotedivoire,Israel,Russie,Chili,Bresil,Gibraltar,Texas,Canada,Boston,France,Singapour')
% source = input('Donner la source souhaitée: ','s')
% destination = input('Donner la destination souhaitée: ','s')
% 
% for n=1:length(S)
%     if (length(destination) == length(S{1,n}) & destination == S{1,n})
%         dst=n
%     end
% end
% for n=1:length(S)
%     if (length(source) == length(S{1,n}) & source == S{1,n})
%         src=n
%     end
% end
% 
% min = reshape(A(:,1), duree,length(A)/duree);
% avg = reshape(A(:,2), duree,length(A)/duree);
% max = reshape(A(:,3), duree,length(A)/duree);
% 
% 
 close all
 clear all
 clc

%%Ce script permet à un fichier donné (un lien) de tracer la figure des
%%rtts correspondante.

% récupérer le nom du fichier du lien dont on souhaite tracer les rtts:
nomfichier = input('Donner le nom du fichier du lien souhaité : ','s');

%récupérer les données du fichier dans un tableau
A=importdata(nomfichier);

% tracer les figures
% figure
% plot(A(:,1),'r');
% ylabel('rtt min en ms');
% xlabel('tps par palier de 2min');
% title ('lien Chilie-Canada');
% saveas(gcf,strrep(nomfichier,'.log','Min'),'fig');
% 
% figure
% plot(A(:,2),'g');
% ylabel('rtt avg en ms');
% xlabel('tps par palier de 2min');
% title ('lien Gibraltar-HongKong');
% saveas(gcf,strrep(nomfichier,'.log','Avg'),'fig');

figure 
plot(A(:,2),'b','LineWidth',2);
ylabel('\fontname{arial}\fontsize{17}rtt moyen en ms');
xlabel('\fontname{arial}\fontsize{17}tps par palier de 2min');
title ('\fontname{arial}\fontsize{17}lien Chili-Canada');

set(gca, 'FontSize', 20, 'fontName','arial');
saveas(gcf,strrep(nomfichier,'.log','Max'),'fig');


