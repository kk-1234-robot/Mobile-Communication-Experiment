clear; clc; close all;
load info_data.mat;
FileID = fopen("data.dat","w");
fprintf(FileID, "0x0000000%d,\n",info_data);
fclose(FileID);