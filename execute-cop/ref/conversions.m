% Execute-CoP Conversions

clc;
close all;
clear all;
format short eng

adc_bits = 11;
adc_max = 2^11;
adc_supply = 5; % Volts

% Battery voltage:
% ================
% vb = 10:0.1:55;
% G = 0.0738;
% vo = vb.*G;
% adc = uint16((vo./adc_supply)*adc_max);
% span_vb = max(vb) - min(vb)
% 
% resolution = span_vb/256   % V/tick
% min_adc = min(adc)
% max_adc = max(adc)
% gain = double((max_adc - min_adc))/256
% tmp = (3*(adc - min_adc))/16;
% out = uint8(tmp);
% 
% figure()
% plot(vb, out)
% xlabel('+VB')
% ylabel('Byte representation')
% title('+VB represented in 1 byte');

% Gate voltage:
% ================
vg = 2.5:0.1:15;
G = 0.43;
vo = vg.*G;
adc = uint16((vo./adc_supply)*adc_max);
span_vg = max(vg) - min(vg)

resolution = span_vg/256   % V/tick
min_adc = min(adc)
max_adc = max(adc)
gain = double((max_adc - min_adc))/256
tmp = (3*(adc - min_adc))/26;
out = uint8(tmp);

figure()
plot(vg, out)
xlabel('+VG')
ylabel('Byte representation')
title('+VG represented in 1 byte');

% Temperature:
% ================
T = -40:1:125;
Tc = 0.01;
T0 = 0.5;
vo = Tc.*T + T0;
adc = (vo./adc_supply).*adc_max;
encoded_t = (adc - 41).*8./21;
encoded_t = uint8(encoded_t);

figure()
plot(T, encoded_t)
xlabel('Temperatuce (C)')
ylabel('Byte representation')
title('Temperature represented in 1 byte');

% =====================================================
% Tests - can be used to convert debugger values
% =====================================================
disp('[Test +VB]')
real_vb = 24;
adc = uint16((0.0738*real_vb./adc_supply)*adc_max)
min_adc = 302;
encoded_vb = ((3*(adc-min_adc)) / 16)   
decoded_vb = adc_supply*((16*double(encoded_vb)/3 + min_adc )/adc_max) / 0.0738

disp('[Test +VG]')
real_vg = 10;
adc = uint16((0.43*real_vg./adc_supply)*adc_max);
min_adc = 440;
encoded_vg = ((3*(adc-min_adc)) / 26)  
encoded_vg = 153
decoded_vg = adc_supply*(( 26*double(encoded_vg)/3 + min_adc )/adc_max) / 0.43

disp('[Test +3V3]')
real_3v3 = 3.5475;
adc = (real_3v3/adc_supply)*adc_max
encoded_3V3 = uint8((adc * 8)/50)
encoded_3V3 = 218
decoded_3V3 = (double(encoded_3V3)*50/8)/adc_max*adc_supply

disp('[Test Temp]')
real_temp = 33;
vo = Tc.*real_temp + T0;
adc = (vo/adc_supply)*adc_max;
adc = uint16(adc);
encoded_temp = (adc - 41).*8./21
encoded_temp = 114
decoded_temp = (((((21/8)*double(encoded_temp) + 41 )/adc_max)*adc_supply) - T0) / Tc
