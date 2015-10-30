%option yylineno
%{
#include "include/Compiler/Callbacks.hpp"
#define YY_DECL extern "C" int yylex()
extern "C" int yywrap(void){return 1;}
%}
%%
function {scanSymbol(yytext, yylineno);}
type {scanSymbol(yytext, yylineno);}
auto {scanSymbol(yytext, yylineno);}
if {scanSymbol(yytext, yylineno);}
else {scanSymbol(yytext, yylineno);}
while {scanSymbol(yytext, yylineno);}
return {scanSymbol(yytext, yylineno);}
import {scanSymbol(yytext, yylineno);}
true {scanSymbol(yytext, yylineno);}
false {scanSymbol(yytext, yylineno);}
@ {scanSymbol(yytext, yylineno);}
# {scanSymbol(yytext, yylineno);}
= {scanSymbol(yytext, yylineno);}
\. {scanSymbol(yytext, yylineno);}
\' {scanSymbol(yytext, yylineno);}
; {scanSymbol(yytext, yylineno);}
"(" {scanSymbol(yytext, yylineno);}
")" {scanSymbol(yytext, yylineno);}
"{" {scanSymbol(yytext, yylineno);}
"}" {scanSymbol(yytext, yylineno);}

\"(\\.|[^"])*\" {scanString(yytext, yylineno);}
\<(\\.|[^>])*\> {scanSpecial(yytext, yylineno);}

[a-zA-Z][a-zA-Z0-9\-+\*/&<>|_\\]* {scanIdentifier(yytext, yylineno);}
[\-\+\*/&<>|_\\] {scanIdentifier(yytext, yylineno);}
-?[0-9]+ {scanInt(yytext, yylineno);}
[0-9]+\.[0-9]+([eE][\+\-]?[0-9]+)? {scanFloat(yytext, yylineno);}

[ \n\r\t]
. {reportUnexpected(yytext, yylineno);}
%%
// int main()
// {
//     yylex();
// }