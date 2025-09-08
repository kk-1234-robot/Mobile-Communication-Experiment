function [outData]=FileRead_Ascii(filename,dataformat);
% function [outData] = FileRead_Ascii(filename,dataformat);
% dataformat = '%c' for Sequence of Char
%              '%d' integer
%              '%e', '%f', '%g' floating-point numbers
% if file is in binary mode, using readfile_binary()
% Type help FileIO for more functions!
f = fopen(filename,'r');
outData = fscanf(f,dataformat);
fclose(f);
