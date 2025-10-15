function out = lte_pusch_modulation(inputdata,prbnum,modutype)

temp = 1/sqrt(2);
QPSK_table = temp*[(1+1i),(1-1i),(-1+1i),(-1-1i)];

temp = 1/sqrt(10);
QAM16_table = temp*[(1+1i), (1+3j), (3+1i), (3+3j), (1-1i), (1-3j), (3-1i), (3-3j), ...
                    (-1+1i),(-1+3j),(-3+1i),(-3+3j),(-1-1i),(-1-3j),(-3-1i),(-3-3j)];

temp = 1/sqrt(42);
QAM64_table = temp*[ (3+3j),  (3+1i),  (1+3j),  (1+1i), (3+5j), (3+7j), (1+5j), (1+7j),  ...
                     (5+3j),  (5+1i),  (7+3j),  (7+1i), (5+5j), (5+7j), (7+5j), (7+7j),  ...
                     (3-3j),  (3-1i),  (1-3j),  (1-1i), (3-5j), (3-7j), (1-5j), (1-7j),  ...
                     (5-3j),  (5-1i),  (7-3j),  (7-1i), (5-5j), (5-7j), (7-5j), (7-7j),  ...
                    (-3+3j), (-3+1i), (-1+3j), (-1+1i),(-3+5j),(-3+7j),(-1+5j),(-1+7j),  ...
                    (-5+3j), (-5+1i), (-7+3j), (-7+1i),(-5+5j),(-5+7j),(-7+5j),(-7+7j),  ...
                    (-3-3j), (-3-1i), (-1-3j), (-1-1i),(-3-5j),(-3-7j),(-1-5j),(-1-7j),  ...
                    (-5-3j), (-5-1i), (-7-3j), (-7-1i),(-5-5j),(-5-7j),(-7-5j),(-7-7j)];

%%
%上面给temp赋值的几行代码是自行添加的
Qm = modutype * 2;

Grouping_inputdata = reshape(inputdata,[Qm,length(inputdata)/Qm])';%注意inputdata是行向量还是列向量
temp_seq = 2.^(Qm-1:-1:0)';
Grouping_inputdata = Grouping_inputdata*temp_seq + 1;%注意这里是矩阵乘积不是按元素相乘

if Qm == 2
    out = QPSK_table(Grouping_inputdata);
elseif Qm == 4
    out = QAM16_table(Grouping_inputdata);
elseif Qm == 6
    out = QAM64_table(Grouping_inputdata);
else
    disp("Qm Error");
    out = QAM64_table(Grouping_inputdata);
end

end
