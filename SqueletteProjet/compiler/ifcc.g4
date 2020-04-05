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
	 'int' NAME (',' NAME)* ';'                                                             #declint
	|'char' NAME (',' NAME)* ';'                                                            #declchar
	|'int' NAME '=' expr ';'                                                                #defint
	|'char' NAME '=' expr ';'                                                               #defchar
	|NAME '=' expr ';'                                                                      #affexpr
    |'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE                                   #ifbloc
    |'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE 'else' OPENBRACE bloc CLOSEBRACE  #ifelsebloc
    |'while' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE                                #whilebloc
	|OPENBRACE bloc CLOSEBRACE                                                              #instrbloc
	|NAME OPENPAR (NAME (',' NAME)*)? CLOSEPAR ';'                                          #callproc
	|RETURN ';'                                                                             #return
  	|RETURN expr ';'                                                                        #returnexpr
;

expr :
	 '('expr')'      #par
	|'-' expr        #minus
	|expr '*' expr   #mult
	|expr '-' expr   #sub
	|expr '+' expr   #add
	|'!' expr        #not
    |expr '==' expr  #eq
    |expr '!=' expr  #neq
    |expr '<=' expr  #leq
    |expr '>=' expr  #geq
    |expr '<' expr   #low
    |expr '>' expr   #geat
    |expr '&' expr   #and
    |expr '^' expr   #xor
    |expr '|' expr   #or
	|CONST           #const
	|CONSTCHAR       #constchar
	|NAME            #name
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

