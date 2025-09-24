function codedata = lte_TurboEncoder(C,cdblksegdata,Cm,Km,Kp,F)
%codedata为三行的矩阵
%先将cdblksegdata转换为向量，并将nan变为0
info_data = cdblksegdata;
info_data(isnan(info_data)) = 0;
for i = 1:C
    if i <= Cm
        data_len(1, i) = Km;
    else
        data_len(1,i) = Kp;
    end
end

%得到交织后的矩阵
for i = 1:C
    info_data_prime(i,:) = interleave(data_len(1,i), cdblksegdata(i,:));
end

index = [4,2,10,8,1,6,7,12,5,3,11,9];

for i = 1:C

c = info_data(i,:);
c_prime = info_data_prime(i,:);

[output,tail_bits]=rsc_encode(c,length(c));
[output_prime,tail_bits_prime] = rsc_encode(c_prime,length(c_prime));
tail = reshape( [tail_bits;tail_bits_prime]',1,[]);
tail_prime(1:1:length(tail)) = tail(index);
tail_prime = reshape(tail_prime,4,3)';
codedata((i - 1) * 3 + 1,:) = [c,tail_prime(1,:)];
codedata((i - 1) * 3 + 2,:) = [output,tail_prime(2,:)];
codedata((i - 1) * 3 + 3,:) = [output_prime,tail_prime(3,:)];
if i == 1 && F > 0
    codedata(1:2,1:F) = nan*ones(2,F);
end


end



end
