function [okk]=FileWrite_Bin(fname,format,dat)
% function [okk]=FileWrite_Bin(fname,format,dat)
% format = 'uchar', 'schar', 'char', 'intx'(x=8,16,32,...) ...
% Type help FileIO for more functions!

fid=fopen(fname,'w');
okk=fwrite(fid,dat,format);
fclose(fid);