function FileIO()
% File I/O Tips:
% FileRead_Ascii(FileName, Format, Length)      - Using fscanf() Function;   
% FileWrite_Ascii(FileName, Format, Data)       - Using fprintf() Function;    
% FileRead_Bin(FileName, Format)                - Using fread() Function;    
% FileWrite_Bin(FileName, Format, Data)         - Using fwrite() Function;
% ftell(fid): return the file pointer
% fseek(fid, offset, origin): setting the file pointer
% % % offset: A value that is interpreted as follows,
% % % offset > 0 :  Move position indicator offset bytes toward the end of the file.
% % % offset = 0 :  Do not change position.
% % % offset < 0 :  Move position indicator offset bytes toward the beginning of the file.
% % % 
% % % origin: A string whose legal values are
% % % 'bof' : -1: Beginning of file
% % % 'cof' :  0: Current position in file
% % % 'eof' :  1: End of file


