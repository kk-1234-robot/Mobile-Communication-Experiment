function[out] =pseudo_random_seq_gen(init_value,length)
%generatot pseudo_random_sequence according to Cinit
x_2 = int2bit(init_value,31,false)';
x_1 = [1,zeros(1,30)];
Nc = 1600;
x_2 = [x_2,zeros(1,length + Nc - 31)];
x_1 = [x_1,zeros(1,length + Nc - 31)];
for i = 1:length + Nc - 31
    x_1(i + 31) = mod(x_1(i + 3) + x_1(i),2);
    x_2(i + 31) = mod(x_2(i+3)+x_2(i+2)+x_2(i+1)+x_2(i),2);
end
for i = 1:length
    out(i) = mod(x_1(i+Nc) + x_2(i + Nc),2);
end

end
