function [output,tail_bits]=rsc_encode(x,data_length)
m=3;
k=4;
g=[1 0 1 1;1 1 0 1];
register = [0, 0, 0, 0];

in = 0;
output  = zeros(1, data_length);

for i = 1 : data_length
    register(1,1) = x(i);
    in = mod(sum(register .* g(1,:)),2);
    output(1,i) = mod(sum([in,register(1,2:1:4)].*g(2,:)),2);
    register(1, 2:1:4) = [in,register(1,2:1:3)];
end

for i = 1: 3
    in = 0;
    tail_bits(1,i) = mod(sum([in,register(1,2:1:4)].*g(2,:)),2);%zk
    tail_bits(2,i) = mod(sum([0,0,register(1,3:1:4)].*g(1,:)),2);%xk
    register(1, 2:1:4) = [in,register(1,2:1:3)];
end
end


