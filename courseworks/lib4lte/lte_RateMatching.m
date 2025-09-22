function [rmdata,rmlen]=lte_RateMatching(codedata,Channel_type, Nir, C, Cm,direction, module_type, RVidx, Nl, G,Km,Kp)

[m,n] = size(codedata);
rmlen = 0;
rmdata = [];

for i = 1:3:m - 2
    if (i + 2)/3 <= Cm
        coded_len = Km + 4;
    else
        coded_len = Kp + 4;
    end
    [Output,out_len] = RateMatching(codedata(i:i+2,1:coded_len), Channel_type, Nir, C, direction, module_type, RVidx, Nl, G, (i-1)/3);
    rmdata = [rmdata;Output];
    rmlen((i+2)/3) = out_len;
end

end