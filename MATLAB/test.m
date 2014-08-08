close all
clear all
clc

x = rand(1,15)*10;
[n, xout] = hist(x, 1:2:10);

% figure
% bar(xout, n);
% c = .05;
% text(xout, n+c*max(n), num2str(n(:)), 'horizontalalignment', 'center')
% set(gca, 'ylim', [0 max(n)*(1+2*c)])