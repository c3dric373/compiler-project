grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' OPENPAR CLOSEPAR OPENBRACE bloc RETURN expr ';' CLOSEBRACE 
     ;

bloc :
	instr*  #blocinstr
	;

instr :
	  decl     #instrdecl
	| def      #instrdef
	| affct    #instraffct
	| ifinstr  #instrif
;

decl :
	'int' NAME (',' NAME)* ';' #declint
	;

def : 
	'int' NAME '=' expr ';' #defexpr
    ;

affct :
	NAME '=' expr ';' #affexpr
    ;

ifinstr :
    'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE #ifbloc
    ;

expr   :
	 CONST          #const
	|NAME           #name

	|'('expr')'     #par

	|expr '*' expr  #mult

	|expr '-' expr  #sub
	|expr '+' expr  #add
	|'-' expr       #minus
;

//les plus specifiques avant
OPENPAR : '('; 
CLOSEPAR : ')';
OPENBRACE : '{';
CLOSEBRACE : '}';
RETURN : 'return' ;
CONST : [0-9]+ ;
NAME: [a-zA-Z_]+[a-zA-Z_0-9]* ;//chiffres lettres underscore et blanc souligne ou blanc souligne tout seul
COMMENT1 : '/*' .*? '*/' -> skip ;
COMMENT2 : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

