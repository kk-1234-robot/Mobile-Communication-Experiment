function [okk]=FileWrite_Ascii(fname,format,dat)
% function [okk]=FileWrite_Ascii(fname,format,dat)
% only write real sequence; 
% Type help FileIO for more functions!
% fprintf(fid,'%6.2f  %12.8f\n',y);

fid=fopen(fname,'wt');
okk=fprintf(fid,format,dat);
fclose(fid);
