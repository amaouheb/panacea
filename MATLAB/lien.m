close all
clear all
clc

load graphes;
load ShortestPath;

%S={'JaponJapon','JaponCalifornie','JaponAustralie','JaponNorvège','JaponPologne','JaponFloride','JaponIrlande','JaponHonkkong','JaponCotedivoire','JaponIsrael','JaponRussie','JaponChili','JaponBresil','JaponGibraltar','JaponTexas','JaponCanada','JaponBoston','JaponFrance','JaponSingapour';'CalifornieJapon','CalifornieCalifornie','CalifornieAustralie','CalifornieNorvège','CaliforniePologne','CalifornieFloride','CalifornieIrlande','CalifornieHonkkong','CalifornieCotedivoire','CalifornieIsrael','CalifornieRussie','CalifornieChili','CalifornieBresil','CalifornieGibraltar','CalifornieTexas','CalifornieCanada','CalifornieBoston','CalifornieFrance','CalifornieSingapour';'AustralieJapon','AustralieCalifornie','AustralieAustralie','AustralieNorvège','AustraliePologne','AustralieFloride','AustralieIrlande','AustralieHonkkong','AustralieCotedivoire','AustralieIsrael','AustralieRussie','AustralieChili','AustralieBresil','AustralieyGibraltar','AustralieTexas','AustralieCanada','AustralieBoston','AustralieFrance','AustralieSingapour';'NorvègeJapon','NorvègeCalifornie','NorvègeAustralie','NorvègeNorvège','NorvègePologne','NorvègeFloride','NorvègeIrlande','NorvègeHonkkong','NorvègeCotedivoire','NorvègeIsrael','NorvègeRussie','AustralieChili','NorvègeBresil','NorvègeGibraltar','NorvègeTexas','NorvègeCanada','NorvègeBoston','NorvègeFrance','NorvègeSingapour';'PologneJapon','PologneCalifornie','PologneAustralie','PologneNorvège','PolognePologne','PologneFloride','PologneIrlande','PologneHonkkong','PologneCotedivoire','PologneIsrael','PologneRussie','PologneChili','PologneBresil','PologneGibraltar','PologneTexas','PologneCanada','PologneBoston','PologneFrance','PologneSingapour';'FlorideJapon','FlorideCalifornie','FlorideAustralie','FlorideNorvège','FloridePologne','FlorideFloride','FlorideIrlande','FlorideHonkkong','FlorideCotedivoire','FlorideIsrael','FlorideRussie','FlorideChili','FlorideBresil','FlorideGibraltar','FlorideTexas','FlorideCanada','FlorideBoston','FlorideFrance','FlorideSingapour';'IrlandeJapon','IrlandeCalifornie','IrlandeAustralie','IrlandeNorvège','IrlandePologne','IrlandeFloride','IrlandeIrlande','IrlandeHonkkong','IrlandeCotedivoire','IrlandeIsrael','IrloandeRussie','IrlandeChili','IrlandeBresil','IrlandeGibraltar','IrlandeTexas','IrlandeCanada','IrlandeBoston','IrlandeFrance','IrlandeSingapour';'HongkongJapon','HongkongCalifornie','HongkongAustralie','HongkongNorvège','HongkongPologne','HongkongFloride','HongkongIrlande','HongkongHonkkong','HongkongCotedivoire','HongkongIsrael','HongkongRussie','HongkongChili','HongkongBresil','HongkongGibraltar','HongkongTexas','HongkongCanada','HongkongBoston','HongkongFrance','HongkongSingapour';'CotedivoireJapon','CotedivoireCalifornie','CotedivoireAustralie','CotedivoireNorvège','CotedivoirePologne','CotedivoireFloride','CotedivoireIrlande','CotedivoireHonkkong','CotedivoireCotedivoire','CotedivoireIsrael','CotedivoireRussie','CotedivoireChili','CotedivoireBresil','CotedivoireGibraltar','CotedivoireTexas','CotedivoireCanada','CotedivoireBoston','CotedivoireFrance','CotedivoireSingapour';'IsraelJapon','IsraelCalifornie','IsraelAustralie','IsraelNorvège','IsraelPologne','IsraelFloride','IsraelIrlande','IsraelHonkkong','IsraelCotedivoire','IsraelIsrael','IsraelRussie','IsraelChili','IsraelBresil','IsraelGibraltar','IsraelTexas','IsraelCanada','IsraelBoston','IsraelFrance','IsraelSingapour';'RussieJapon','RussieCalifornie','RussieAustralie','RussieNorvège','RussiePologne','RussieFloride','RussieIrlande','RussieHonkkong','RussieCotedivoire','RussieIsrael','RussieRussie','RussieChili','RussieBresil','RussieGibraltar','RussieTexas','RussieCanada','RussieBoston','RussieFrance','RussieSingapour'}

S={'Japon','Californie','Australie','Norvege','Pologne','Floride','Irlande','Honkkong','Cotedivoire','Israel','Russie','Chili','Bresil','Gibraltar','Texas','Canada','Boston','France','Singapour'};

%%%%% le changement du meilleur chemin pour une source destination donnee
%%%%% fct du temps
disp('voici la liste des sources et destination possible: Japon,Californie,Australie,Norvege,Pologne,Floride,Irlande,Honkkong,Cotedivoire,Israel,Russie,Chili,Bresil,Gibraltar,Texas,Canada,Boston,France,Singapour')
source = input('Donner la source souhaitée: ','s')
destination = input('Donner la destination souhaitée: ','s')


for n=1:length(S)
    if (length(destination) == length(S{1,n}) & destination == S{1,n})
        dst=n;
    end
end
for n=1:length(S)
    if (length(source) == length(S{1,n}) & source == S{1,n})
        src=n;
    end
end
 

%%% retrouver la ligne correspondante sur la cellule des meilleurs chemins %%%
 if (dst == 19)
     i=src*19;
 else
     i=(src-1)*19 + dst;
 end
 
 changement = zeros(1,size(D,2)-1);
 Gain_Changement = zeros(1,size(D,2)-1);
 Gain_nndirect = zeros(1,size(D,2)-1);
 for j=1:(size(D,2)-1)
     
        if (length(D{i,j})>3 & Graphe{j}(dst,src)~=2000)  % le chemin n'est pas direct et le direct n'est pas en panne
            Gain_nndirect(j) =((Graphe{j}(dst,src)-D{i,j}(1))*100)/(Graphe{j}(dst,src));
        end
        if (length(D{i,j}) ~= length(D{i,j+1}))
            changement(j+1)=changement(j)+1;
            if (Graphe{j}(dst,src)~=2000)
                %%%% Attention!! il faut bien inverser les couples dans le graphe
                %%%% pour avoir le meme ordre quand pour les plus courts chemin
                %%%% En efft les expériences non synchronisées ont fait que le
                %%%% graphe(matrice des coûts) n'est pas symétrique comme le veut
                %%%% la logique
        
                Gain_Changement(j) =((Graphe{j}(dst,src)-D{i,j}(1))*100)/(Graphe{j}(dst,src));% pourcentage du gain en temps en prenant le plus court chemin
                
            end
        elseif( D{i,j}(2:end) ~= D{i,j+1}(2:end) )
            changement(j+1)=changement(j)+1;
            if (Graphe{j}(dst,src)~=2000) % le lien direct n'est pas en panne
                Gain_Changement(j) =((Graphe{j}(dst,src)-D{i,j}(1))*100)/(Graphe{j}(dst,src));% pourcentage du gain en temps en prenant le plus court chemin
                
            end
            
        else
            changement(j+1)=changement(j);
        end
end

 
 moyenne_chagement = mean(Gain_Changement);
 moyenne_nndirect = mean(Gain_nndirect);
 
figure 
plot (Gain_Changement,'b');
hold on 
plot ( [0,3835],[moyenne_chagement, moyenne_chagement] , 'r');
hold off 
ylabel('gain en pourcentage pour chaque changement de chemin');
xlabel('temps par palier de 2 min');
title([source,destination]);
saveas(gcf,'Gain_lien_changement','fig');

figure 
plot (Gain_nndirect,'b');
hold on 
plot ( [0,3835],[moyenne_nndirect, moyenne_nndirect] , 'r');
hold off 
ylabel('gain en pourcentage pour chaque chemin nn direct');
xlabel('temps par palier de 2 min');
title([source,destination]);
saveas(gcf,'Gain_lien_nndirect','fig');

figure 
plot (changement);
ylabel('nbr de changement du meilleur chemin');
xlabel('temps par palier de 2 min');
title([source,destination]);
saveas(gcf,'chemin_lien','fig');
             