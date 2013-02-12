
#ifndef _enums_
#define _enums_

enum  TypeOfConversion{ConversionToSimple,ConversionToAddress,ConversionToBase_12_Code,ConversionToBmcType,ConversionToBmcOpCode,ConversionToBmcOpRegField};
enum StringStyle{PrintStyle,BmcStyle};
enum  Boolean {FALSE,TRUE};
enum  RuntimeErrors {OutOfMemory,StackEmpty,UnableToOpenFile,UnableToWriteFile,NCA,CompilingError,FatalError,UnableToDeleteTempFile};
enum TrimMethod {All, Start, End}; 
enum Directive { STRING, DATA, ENTRY, EXTERN, NONE };
enum ItemType{TDirective, TCommand,TLabel};
enum ParamType {Param_register,Param_word,Param_dimentional,Param_relative,Param_Number,Param_error};
enum BmcField{BmcOperationCode,BmcSrcAddType,BmcSrcReg,BmcDstAddType,BmcDstReg };
enum FileExtension{FILE_OB,FILE_EXT,FILE_ENT};
#endif

/*
NCA - No command-line arguments
*/
