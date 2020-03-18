grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' OPENPAR CLOSEPAR OPENBRACE bloc RETURN expr ';' CLOSEBRACE 
     ;

bloc : 
	                #b6
	| declI bloc    #b1
	| decl  bloc    #b8
	| aff   bloc    #b2
	| if    bloc    #b3
	| while bloc    #b4
	| instr bloc    #b7
	;

declI   : 
	 'int' NAME '=' expr ';' #definition
        ;

decl    : 
	 'int' NAME ';' #declaration
        ;

aff   : 
	  NAME '=' expr ';' #aff
        ;

expr   :
	 expr '+' expr              #plus
	|expr '-' expr              #moins
	|'-' expr                   #opposite
	|expr '*' expr              #mult

	//pour après |expr '/' expr #div
	//pour après |expr '%' expr #mod

	|expr '&' expr #etbit
	|expr '|' expr #oubit
	|expr '^' expr #xorbit
	|'!' expr #notbool

	// après |expr '&&' expr    #etbool
	//après |expr '||' expr     #oubool

	|expr '<' expr              #grt
	|expr '>' expr              #lowt
	|expr '==' expr             #equals
	|expr '<=' expr             #gret
	|expr '>=' expr             #lowet
	|expr '!=' expr             #diff

	|'('expr')'                 #par
	|CONST                      #const
	|NAME                       #name
	;

if: 
	'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE #if1
	|'if' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE 'else' OPENBRACE bloc CLOSEBRACE #if2
	;

while: 
	'while' OPENPAR expr CLOSEPAR OPENBRACE bloc CLOSEBRACE #while
	;

//optionnel for: 
//	'for' OPENPAR expr ';' expr';' instr CLOSEPAR OPENBRACE bloc CLOSEBRACE #while
//	;

instr : 
	 aff    #instr1
	|if     #instr2
	|while  #instr3
	
;

//les plus specifiques avant
RETURN : 'return' ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);


NAME: [a-zA-Z_]+[a-zA-Z_0-9]* ;//chiffres lettres underscore et blanc souligne ou blanc souligne tout seul 
OPENPAR : '('; 
CLOSEPAR : ')';
OPENBRACE : '{';
CLOSEBRACE : '}';


