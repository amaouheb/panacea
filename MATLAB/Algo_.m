function [ck k cont_k path]= Algo3(n,c,c0,k0,src,dest,beta)

t_ini=cputime;

if n*(n-1) ~= size(c,2)
    disp('Not good size of vector c!');
end


%defining vertices
ind2=0;
ind1=0;
for i=1:n
    ind1=0;
    for j=1:n
        if i~=j
            v_s(ind1+1+ind2*(n-1))=i;
            v_d(ind1+1+ind2*(n-1))=j;
            mat(ind1+1+ind2*(n-1),:)=[i j]';
          %  i
          %  j
          %  c(ind1+1+ind2*(n-1),:)=input('Number:');
            ind1=ind1+1;
        end
    end
    ind2=ind2+1;
end

%Show the graph with the c costs:
%disp('Created graph:');
%DG = sparse(v_s,v_d,c);
%h = view(biograph(DG,[],'ShowWeights','on'))
%disp('Are you sure?');
%pause

%c0 = 0.1.*ones(1,size(c,2)); 
ck = c0;

cont_k=0; 
cont_loop=0;
k=k0; %k=zeros(1,n*(n-1));

u=-1;
while u~=0
  u=0;
  for i=1:size(path,2)-1
      mypath=[path(i) path(i+1)];
      var=find(ismember(mat,mypath,'rows'));
      if k(var)==0
         k(var)=1; cont_k=cont_k+1;
         ck(var)=c(var);
     %    mat(var,:)
         u=u+1;
      end
  end
  DG = sparse(v_s,v_d,ck);
  [dist, path, pred] = graphshortestpath(DG, src, dest);
  for i=1:size(k,2)
          if ck(i)==0.001
              ck_mod(i)=realmax;
          else
              ck_mod(i)=ck(i);
          end
  end
  DG = sparse(v_s,v_d,ck_mod);
  [dist2, path2, pred2] = graphshortestpath(DG, src, dest);

  %h = view(biograph(DG,[],'ShowWeights','on'))
%   for i=1:size(path,2)-1
%       mypath=[path(i) path(i+1)];
%       var=find(ismember(mat,mypath,'rows'));
%       if k(var)==0
%          k(var)=1; cont_k=cont_k+1;
%          ck(var)=c(var);
%      %    mat(var,:)
%          u=u+1;
%       end
%   end
  if u>0
      cont_loop=cont_loop+1;
      if dist2 <= beta * dist
         u=0;
      end
  end
end
end
