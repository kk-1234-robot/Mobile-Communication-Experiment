%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Cdblk_concate  Code block concatenation
% C: Code block number
% Info_data: data of each code block, C rows
% data_len: length of each code block, C rows 1 column
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function output = lte_CB_concate(C,Info_data,data_len)

output = [];
for i = 1:C
    output = [output,Info_data(i, 1:1:data_len(1,i))];
end
end

