close all
clear all
clc 

%Ce script permet de tracer toutes les figures des fichiers (liens)
%contenus dans le répertoire courant et de les sotkcer dans ce même repertoire sous la forme 'Rttssource_destiantion.fig'  

rep = '/home/amaouheb/panacea/traces/RTTS'; %repertoire
ext = '*.log'; % extension des fichiers à récupérer 

chemin = fullfile(rep,ext); % concatener pour avoir le chemin  ./*.log

list = dir(chemin); % retounrner une variable de type liste ac les infos sur les fichiers, le nom en partucilier

for i = 1:numel(list)
   
   A = importdata(list(i).name);
%    figure
%    plot(A(:,1),'r');
%    hold on
%    plot(A(:,2),'g'); 
%    hold on 
%    plot(A(:,3),'b');
%    legend('rtt min','rtt avg','rtt max');
%    ylabel('rtt en ms');
%    xlabel('tps par palier de 2min');
%    title (strrep(list(i).name,'.log',''));
%    saveas(gcf,strrep(list(i).name,'.log',''),'fig'); 
   
   figure 
   hist(A(:,1));
   ylabel('nbr d occurence');
   xlabel('rtt en ms');
   title (strrep(list(i).name,'.log','_min'));
   saveas(gcf,strrep(list(i).name,'.log','min'),'fig'); 
   figure 
   hist(A(:,2));
   ylabel('nbr d occurence');
   xlabel('rtts en ms');
   title (strrep(list(i).name,'.log','_avg'));
   saveas(gcf,strrep(list(i).name,'.log','avg'),'fig'); 
   figure 
   hist(A(:,3));
   ylabel('nbr d occurence');
   xlabel('rtt en ms');
   title (strrep(list(i).name,'.log','_max'));
   saveas(gcf,strrep(list(i).name,'.log','max'),'fig'); 

end