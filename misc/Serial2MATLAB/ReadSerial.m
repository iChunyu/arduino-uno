% Read serial data from Arduino and plot data

% XiaoCY 2023-03-07

%%
clear;clc

% use `serialportlist` to see serial list
s = serialport('/dev/ttyACM0', 9600);
fs = 1/20e-3;

filename = 'testdata.dat';
save_time = 10;         % time length of data to be saved
fft_time = 3;           % time length of data to perform `fft`

%%
fid = fopen(filename,'w');

% for FFT
nfft = fft_time*fs;
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

while s.NumBytesAvailable > 0
    s.flush
end
for k = 1:save_time*fs
    subplot(211)
    x = eval(s.read(18,'char'));    % use `Serial.print` in arduino
    % x = eval(s.readline);         % use `Serial.println` in arduino
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
delete(s);