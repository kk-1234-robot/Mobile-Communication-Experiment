function intleaverdata = lte_interleaver(crcdatain,prb_num,Qm)

symb_length = prb_num*12*Qm;
data_length = prb_num*144*Qm;
data_row = data_length/(12*Qm);
count = 1;

for i = 1:12
    for j = 1:data_row
        index = (j - 1)*12*Qm + (i-1)*Qm+1;
        intleaverdata(1,count:count+Qm -1) = crcdatain(1,index:index+Qm-1);
        count = count + Qm;
    end
end

end