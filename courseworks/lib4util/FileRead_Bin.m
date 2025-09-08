function [outData]=FileRead_Bin(filename,dataformat,len);
% function [outData] = FileRead_Bin(filename,dataformat,len);
% dataformat = 'uchar' for Unsigned Integer, 8bits
%              'schar' for Signed Integer, 8bits
%              'int*' for integer; * bits ( * = 8,16,32,64)
%              'uint*' for unsigned integer; * bits (* = 8,16,32,64)
%              'float*' for floating-point; * bits (* = 32, 64)
%              'double' for double; 64bits
% len = length for read
% Type help FileIO for more functions!
f = fopen(filename,'r');
outData = fread(f,len,dataformat);
fclose(f);