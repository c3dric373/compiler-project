grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' OPENPAR CLOSEPAR OPENBRACE bloc RETURN expr ';' CLOSEBRACE 
     ;

bloc :
	instr*  #blocinstr
	;

instr :
	 decl        #instrdecl
	|def         #instrdef
	|affct       #instraffct
	|ifinstr     #instrif
	|whileinstr  #instrwhile
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
     'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE bloc #ifbloc
    //|'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE 'else' OPENBRACE bloc CLOSEBRACE #ifelse
    ;

whileinstr :
     'while' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE #whilebloc
     ;

expr :
	 '('expr')'      #par
	|'!' expr        #not
    |expr '==' expr  #eq
    |expr '!=' expr  #neq
    |expr '<=' expr  #leq
    |expr '>=' expr  #geq
    |expr '<' expr   #low
    |expr '>' expr   #geat
	|expr '*' expr   #mult
	|expr '-' expr   #sub
	|expr '+' expr   #add
	|'-' expr        #minus
	|CONST           #const
	|NAME            #name
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

