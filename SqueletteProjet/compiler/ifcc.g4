grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' OPENPAR CLOSEPAR OPENBRACE bloc RETURN expr ';' CLOSEBRACE 
     ;

bloc :
	instr*  #blocinstr
	;

instr :
	  decl   #instrdecl
	| def    #instrdef
	| affct  #instraffct
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

expr   :
	 expr '+' expr #add
	|expr '-' expr #sub
	|'-' expr      #minus
	|expr '*' expr #mult

	|'('expr')'    #par
	|CONST         #const
	|NAME          #name
	;

//les plus specifiques avant
OPENPAR : '('; 
CLOSEPAR : ')';
OPENBRACE : '{';
CLOSEBRACE : '}';
RETURN : 'return' ;
CONST : [0-9]+ ;
NAME: [a-zA-Z_]+[a-zA-Z_0-9]* ;//chiffres lettres underscore et blanc souligne ou blanc souligne tout seul 
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

