%% For Educaton Purpose
% Experiments of LTE Uplink TRX
% Tutor's Version
% Version 1.51  
% Copyright (C) HUST EIC 

clear; clc; close all;

workpath = "D:\Mobile Communication Experiment\courseworks"; %% 改为自己的工作目录
cd(workpath);
addpath(genpath(workpath));

GroupNo = 0; 
result.GroupNo = 0;

%% 0.1. General Parameters Setting ......
tbsize = 57336;   % TB（传输块）大小
module_type = 3;  % 调制方式：= 1 for QPSK; = 2 for 16QAM; = 3 for 64QAM
prb_num = 100;    % PRB数目
rbstart = 0;      
Qm = module_type*2;
UL_subframe_num = 2; % 子帧序号
ue_index = 60;   
cellid = 0;        

antnum =1; % 接收天线数目：  = 1 for 单天线接收； = 2 for 两天线接收
addnoiseflag = 0; %1:添加噪声  0：不添加噪声

% 速率匹配使用参数
Channel_type =0;  % 信道类型
Nir = 0;          
direction = 1;     
RVidx = 0;
Nl = 1;
G = 12*12*prb_num*Qm; % 本例实验可以简单应用该公式！
mimo_type = 1;
cfi = 1;           % CFI
cp_type = 0;   

C = 10;
Cp = 10;
Cm = 0;

Kp = 5760;
Km = 5696;
F = 0; 
% Cp = C+
% Cm = C-
% Kp = K+
% Km = K-

%% [C, Cp, Kp, Cm, Km, F]  = cdblk_para_cal(tbsize); % void for now
E = [8640 8640 8640 8640 8640 8640 8640 8640 8640 8640]; 
% E_cal(G,C,module_type,Nl); % 计算每个子码块的速率匹配后的输出长数 

%% 0.2. 信源产生
% info_data = Source_data_gen(1, 1, tbsize, 1, 0);
load info_data.mat;
% dlmwrite('.\data\Source.dat',info_data,'delimiter','\n','precision',1);
[result.exp00, par] = SeqSign(info_data); %  the signature is FA3754
%%%% 0.1. General Parameters Setting ######
%% ############################################################

%%%%%%%%%%%%% Now, it is your turn to do something right %%%%%%%%%%%%%%%

%% Exp.01 - CRC添加与码块分割 .....................................
% 1.1 CRC添加 
% crc_data = CRC_attach(info_data,24,0);
crc_24a = lte_CRC24A(info_data);   % 1. 需要学生写的代码模块 <<<<<<<<<<<<<<<<<<<<
                              %     crc_24a : 1-by-24
                              %     infor_data : 1-by-tbsize
                              
crc_24b = lte_CRC24B(info_data);   % 2. 需要学生写的代码模块 <<<<<<<<<<<<<<<<<<<<
                              %     crc_24b : 1-by-24
                              %     infor_data : 1-by-tbsize
crc_data =[info_data,crc_24a]; % CRC比特需要附在TB比特序列末尾，1-by-(tbsize+24)
result.exp0101 = (dec2hex([8,4,2,1]*reshape(crc_24a, 4, [])))';  
result.exp0102 = (dec2hex([8,4,2,1]*reshape(crc_24b, 4, [])))'; 
%%%% 1.1 CRC添加 ######

% 1.2 码块分割 
tbCrcBits = [info_data, crc_24a];
[Cp, Kp, Cm, Km, F, cdblkseg_data] =  lte_pusch_cb_seg(tbCrcBits);
C = Cp+Cm;
result.exp0103 = SeqSign(cdblkseg_data, result.GroupNo);
%%%% 1.2 码块分割 ######

% % 自我检查（查看result）：
    % exp0101: 'FA3754'
    % exp0102: '6382DB'
% % 验收检查：
    % exp0103: '87A4**'

%% Exp.01 - CRC添加与码块分割 ####################################



%% Exp.02 - 信道化 ..............................................

% 2.1 Turbo 编码
coded_data = zeros(3*C,Cp+4);  % 初始化（维度确定）
codedSym = lte_TurboEncoder(C, cdblkseg_data, Cm, Km, Kp, F);
result.exp0201 = SeqSign(codedSym, result.GroupNo);
%%%% 2.1 Turbo 编码 ######

% 2.2 子块交织和速率匹配
[rmSym, rmLen]=lte_RateMatching (codedSym, Channel_type, Nir, C, Cm, direction, module_type, RVidx, Nl, G,Km,Kp);
result.exp0202 = SeqSign(rmSym, result.GroupNo);
%%%% 2.2 子块交织和速率匹配 ######

% 2.3 码块级联 
ccbcSym = lte_CB_concate(C, rmSym, rmLen);
result.exp0203 = SeqSign(ccbcSym, result.GroupNo);
%%%% 2.3 码块级联 ######

% 2.4 信道交织 
intlvSym = lte_interleaver(ccbcSym, prb_num, Qm);
result.exp0204 = SeqSign(intlvSym, result.GroupNo);
%%%% 2.4 信道交织 ######

%% 2.5 加扰 
vrb_num = prb_num;
subframeno = UL_subframe_num;
scrmbedSym = lte_scramble(intlvSym,vrb_num,Qm,subframeno,ue_index,cellid);
result.exp0205 = SeqSign(scrmbedSym, result.GroupNo);
%%%% 2.5 加扰 ######

% % 自我检查（查看result）：
    % exp0201: '5EA351'
    % exp0202: 'BEB9E3'
    % exp0203: 'ED9A8B'
    % exp0204: '0C2DF6'
% % 验收检查：
    % exp0205: '971A3*'

%% Exp.02 - 信道化 #################################################


%% Exp.03 - 调制符号与导频生成实验.....................................
% 3.1 - 调制
% Mod_Sig = lte_pusch_modulation(scrmbedSym, prb_num, module_type)

module_type = 3; % 3 for 64QAM
Mod_Sig = lte_pusch_modulation(scrmbedSym, prb_num, module_type);
result.exp0301 = SeqSign(Mod_Sig, result.GroupNo);
% 3.1 - 调制 #####

% 3.2 - 导频
% [Resp_Pilot, Resp_Pilot_Base] = lte_pusch_rs_gen(prb_num,Group_hop_flag, Seq_hop_flag, Slot_idx, cellid, deltass, ndmrs1, Cyc_shift, Symbol_index)
Group_hop_flag = 0;
Seq_hop_flag = 0;
deltass = 0;
ndmrs1 = 0;
Cyc_shift = 0;
Symbol_index = 3;

Slot_idx = 2*UL_subframe_num;
[Resp_Pilot0,Resp_Pilot0_Base] = lte_pusch_rs_gen(prb_num,0,0,Slot_idx,cellid,0,0,0,Symbol_index);

Slot_idx = 2*UL_subframe_num+1;
[Resp_Pilot1,Resp_Pilot1_Base] = lte_pusch_rs_gen(prb_num,0,0,Slot_idx,cellid,0,0,0,Symbol_index);

result.exp0302 = SeqSign([Resp_Pilot0, Resp_Pilot1], result.GroupNo);

% 3.2 - 导频 #####
% % 自我检查（查看result）：
    % exp0301: '7?9C04'
    % exp0302: '6A2E?D'
% % 验收检查：
    % exp0301: '7?9C04'
    % exp0302: '6A2E?D'

%% Exp.03 - 调制符号与导频生成实验######################################

