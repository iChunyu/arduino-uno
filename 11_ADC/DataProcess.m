% ADC sampling
% Experiment file:
%   V0: DAC works in the open loop
%   V1: DAC works in the closed loop
% (closed-loop parameters to be optimized)

% XiaoCY 2022-03-13

%%
clear;clc
InitPlot(3,25)

load('V0.mat')
load('V1.mat')

%%
[V0a, V1a] = alignsignals(V0, V1);

figure
t0 = (0:length(V0a)-1)/10;
plot(t0,V0a,'DisplayName','OpenLoop')
hold on
grid on
t1 = (0:length(V1a)-1)/10;
plot(t1,V1a,'DisplayName','ClosedLoop')
legend
xlabel('Time [s]')
ylabel('$V_\mathrm{ADC}\ \mathrm{[V]}$','Interpreter','latex')


figure
iLPSD(V0,10,'DisplayName','OpenLoop')
hold on
iLPSD(V1,10,'DisplayName','ClosedLoop')
legend
xlabel('Frequency [Hz]')
ylabel('$V_\mathrm{ADC}\ \mathrm{[V/\sqrt{Hz}]}$','Interpreter','latex')
