clear;clc

s = serialport('/dev/ttyUSB0', 9600);

fs = 1/20e-3;
filename = 'testdata.dat';
Time = 10;
Tfft = 3;

%%
fid = fopen(filename,'w');

% for FFT
nfft = Tfft*fs;
data = nan(nfft,1);
N1 = floor(nfft/2);
f = fs/nfft*(1:N1-1)';

figure
subplot(211)
box on
grid on
an = animatedline('Color',[0.1765 0.5216 0.9412]);
an.MaximumNumPoints = nfft;

subplot(212)
box on
grid on

flush(s);
for k = 1:Time*fs
    subplot(211)
    x = eval(s.readline);
    fprintf(fid, '%s    %+16.13f\n',datestr(now,'yyyy-mm-dd HH:MM:ss.FFF'),x);
    addpoints(an,(k-1)/fs,x)
    drawnow
    xlabel('Time [s]')
    ylabel('Signal')

    if k <= nfft
        data(k) = x;
    else
        data = [data(2:end); x];
        Y = abs(fft(data))*sqrt(2/fs/nfft);
        subplot(212)
        loglog(f,Y(2:N1))
        y0 = floor(log10(min(Y)))-1;
        y1 = ceil(log10(max(Y)));
        ylim([10^y0 10^y1])
        xlabel('Frequency [Hz]')
        ylabel('PSD')
    end
end

fclose(fid);