close all;
clear all;
clc;


load emg_healthy.txt;
load emg_myopathy.txt


load segm1_healthy.txt;
load segm2_healthy.txt;
load segm3_healthy.txt;
load segm4_healthy.txt;
load segm5_healthy.txt;
load segm6_healthy.txt;
load segm7_healthy.txt;
load segm8_healthy.txt;
load segm9_healthy.txt;
load segm10_healthy.txt;

load segm1_myopathy.txt;
load segm2_myopathy.txt;
load segm3_myopathy.txt;
load segm4_myopathy.txt;
load segm5_myopathy.txt;
load segm6_myopathy.txt;
load segm7_myopathy.txt;
load segm8_myopathy.txt;
load segm9_myopathy.txt;
load segm10_myopathy.txt;

load segm1_neuropathy.txt;
load segm2_neuropathy.txt;
load segm3_neuropathy.txt;
load segm4_neuropathy.txt;
load segm5_neuropathy.txt;
load segm6_neuropathy.txt;
load segm7_neuropathy.txt;
load segm8_neuropathy.txt;
load segm9_neuropathy.txt;
load segm10_neuropathy.txt;



x1=segm1_healthy(:,2);
x2=segm2_healthy(:,2);
x3=segm3_healthy(:,2);
x4=segm4_healthy(:,2);
x5=segm5_healthy(:,2);
x6=segm6_healthy(:,2);
x7=segm7_healthy(:,2);
x8=segm8_healthy(:,2);
x9=segm9_healthy(:,2);
x10=segm10_healthy(:,2);

a1=segm1_myopathy(:,2);
a2=segm2_myopathy(:,2);
a3=segm3_myopathy(:,2);
a4=segm4_myopathy(:,2);
a5=segm5_myopathy(:,2);
a6=segm6_myopathy(:,2);
a7=segm7_myopathy(:,2);
a8=segm8_myopathy(:,2);
a9=segm9_myopathy(:,2);
a10=segm10_myopathy(:,2);

b1=segm1_neuropathy(:,2);
b2=segm2_neuropathy(:,2);
b3=segm3_neuropathy(:,2);
b4=segm4_neuropathy(:,2);
b5=segm5_neuropathy(:,2);
b6=segm6_neuropathy(:,2);
b7=segm7_neuropathy(:,2);
b8=segm8_neuropathy(:,2);
b9=segm9_neuropathy(:,2);
b10=segm10_neuropathy(:,2);


y1=abs(fft(x1));
y2=abs(fft(x2));
y3=abs(fft(x3));
y4=abs(fft(x4));
y5=abs(fft(x5));
y6=abs(fft(x6));
y7=abs(fft(x7));
y8=abs(fft(x8));
y9=abs(fft(x9));
y10=abs(fft(x10));

z1=abs(fft(a1));
z2=abs(fft(a2));
z3=abs(fft(a3));
z4=abs(fft(a4));
z5=abs(fft(a5));
z6=abs(fft(a6));
z7=abs(fft(a7));
z8=abs(fft(a8));
z9=abs(fft(a9));
z10=abs(fft(a10));

w1=abs(fft(b1));
w2=abs(fft(b2));
w3=abs(fft(b3));
w4=abs(fft(b4));
w5=abs(fft(b5));
w6=abs(fft(b6));
w7=abs(fft(b7));
w8=abs(fft(b8));
w9=abs(fft(b9));
w10=abs(fft(b10));





figure;
plot(w1),grid,title('Fft in valoare absoluta pt un segment de semnal(30ms)')


%plot(emg_healthy(:,1),emg_healthy(:,2)-mean(emg_healthy(:,2)))

%figure(2);
%plot(emg_myopathy(:,1),emg_myopathy(:,2)-mean(emg_myopathy(:,2)))