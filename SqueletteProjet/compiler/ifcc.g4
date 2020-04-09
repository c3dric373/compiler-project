grammar ifcc;

axiom : prog
      ;

prog : initbloc 'int' 'main' OPENPAR CLOSEPAR OPENBRACE bloc RETURN expr ';' CLOSEBRACE
;

initbloc :
    initfun*  #blocinit
;

initfun :
     'void' NAME OPENPAR (type NAME (',' type NAME)*)? CLOSEPAR ';'                        #declproc
    |type NAME OPENPAR (type NAME (',' type NAME)*)? CLOSEPAR ';'                          #declfun
    |'void' NAME OPENPAR (type NAME (',' type NAME)*)? CLOSEPAR OPENBRACE bloc CLOSEBRACE  #defproc
    |type NAME OPENPAR (type NAME (',' type NAME)*)? CLOSEPAR OPENBRACE bloc CLOSEBRACE    #deffun
;

type :
     'int' #int
    |'char' #char
;

bloc :
	instr*  #blocinstr
;

instr :
	 'int' NAME (',' NAME)* ';'                                                                            #declint
	|'char' NAME (',' NAME)* ';'                                                                           #declchar
	|'int' NAME '[' expr ']' ';'                                                                           #declinttab
	|'char' NAME '[' expr ']' ';'                                                                          #declchartab
	|'int' NAME '=' expr ';'                                                                               #defint
	|'char' NAME '=' expr ';'                                                                              #defchar
	|NAME '=' expr ';'                                                                                     #affexpr
	|NAME '[' expr ']' '=' expr ';'                                                                        #afftab
    |'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE                                                  #ifbloc
    |'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE 'else' OPENBRACE bloc CLOSEBRACE                 #ifelsebloc
    |'while' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE                                               #whilebloc
    |'for' OPENPAR initfor? ';' expr? ';' (loopinstr(',' loopinstr)*)? CLOSEPAR OPENBRACE bloc CLOSEBRACE  #forbloc
	|OPENBRACE bloc CLOSEBRACE                                                                             #instrbloc
	|NAME OPENPAR (NAME (',' NAME)*)? CLOSEPAR ';'                                                         #callproc
	|'putchar' OPENPAR NAME CLOSEPAR ';'                                                                   #putchar
	|RETURN ';'                                                                                            #return
  	|RETURN expr ';'                                                                                       #returnexpr
;

initfor :
	 'int' NAME (',' NAME)*      #fordeclint
	|'char' NAME (',' NAME)*     #fordeclchar
	|'int' NAME '[' expr ']'     #fordeclinttab
	|'char' NAME '[' expr ']'    #fordeclchartab
	|'int' NAME '=' expr         #fordefint
	|'char' NAME '=' expr        #fordefchar
	|NAME '=' expr               #foraffexpr
	|NAME '[' expr ']' '=' expr  #forafftab
;

loopinstr :
	 NAME '=' expr               #loopaff
	|NAME '[' expr ']' '=' expr  #loopafftab
;

expr :
	 '('expr')'                                 #par
	|'-' expr                                   #minus
	|expr '*' expr                              #mult
	|expr '-' expr                              #sub
	|expr '+' expr                              #add
	|'!' expr                                   #not
    |expr '==' expr                             #eq
    |expr '!=' expr                             #neq
    |expr '<=' expr                             #leq
    |expr '>=' expr                             #geq
    |expr '<' expr                              #low
    |expr '>' expr                              #geat
    |expr '&' expr                              #and
    |expr '^' expr                              #xor
    |expr '|' expr                              #or
	|NAME OPENPAR (NAME (',' NAME)*)? CLOSEPAR  #callfun
	|'getchar' OPENPAR CLOSEPAR                 #getchar
	|CONST                                      #const
	|CONSTCHAR                                  #constchar
	|NAME                                       #name
	|NAME '[' expr ']'                          #tabaccess
;

//les plus specifiques avant
OPENPAR : '(';
CLOSEPAR : ')';
OPENBRACE : '{';
CLOSEBRACE : '}';
RETURN : 'return' ;
CONST : [0-9]+ ;
CONSTCHAR : '\'' [a-zA-Z_0-9] '\'' ;
NAME: [a-zA-Z_]+[a-zA-Z_0-9]* ; //chiffres lettres underscore et blanc souligne ou blanc souligne tout seul
COMMENT1 : '/*' .*? '*/' -> skip ;
COMMENT2 : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

