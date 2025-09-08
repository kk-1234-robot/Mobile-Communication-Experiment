%****************************************************************
%For LTE standard 3gpp 36212-830
%Info_Data: Input Information bits                             %
% Attach_Length: CRC Attach bits length (24/16/8 can selected) %
% CRC_type: Only for CRC Attach bits length 24, 0 for type A; 1 for type B %
% Output: Information add CRC attach bits                       %
%****************************************************************

function Output = CRC_attach(Info_Data,Attach_Length,CRC_type)
% Copyright 2001 Yeh Heng
% CRC attachment added (24/16/8 attachment bits can select)
% Info_Data=[0 1 1 1 0 1 0 1 0 1 0 0 0 0 1 0 0 0 0 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 0 0 0 0 1 1 0 1 0 0 0 0 0 0 0 0 0 0 0 1 1 1 0 0 0 0 1 0 0 0 0 1 1 0 1 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 1 1 0 1 0 0 1 0 1 0 1 0 0 0 0 1 1 1 1 1 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 1 1 0 0 0 1 0 0 0 0 0 1 0 0 0 1 0 0 0 1 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];% 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
if Attach_Length == 24
    if CRC_type == 0
        Output = [Info_Data,lte_CRC24A(Info_Data)];
    elseif CRC_type == 1
        Output = [Info_Data,lte_CRC24B(Info_Data)];
    end
elseif Attach_Length == 16
    Output = [Info_Data,lte_CRC16(Info_Data)];
elseif Attach_Length == 8
    Output = [Info_Data,lte_CRC8(Info_Data)];
end
end