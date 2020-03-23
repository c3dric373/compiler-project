grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' OPENPAR CLOSEPAR OPENBRACE bloc RETURN expr ';' CLOSEBRACE 
     ;

bloc : 
	  declI
	| declI bloc
	|
	//| instr bloc
	;

declI   : 
         'int' NAME '=' CONST ';' #definition 
	 |'int' NAME '=' expr ';' #definition
        ;

expr   :
	 expr '+' expr #plus
	|expr '-' expr #moins
	|'-' expr #opposite
	|expr '*' expr #mult

	//pour après |expr '/' expr #div
	//pour après |expr '%' expr #mod

	|expr '&' expr #etbit
	|expr '|' expr #oubit
	|expr '^' expr #xorbit
	|'!' expr #notbool

	// après |expr '&&' expr #etbool
	//après |expr '||' expr #oubool

	|expr '<' expr #grt
	|expr '>' expr #lowt
	|expr '==' expr #equals
	|expr '<=' expr #gret
	|expr '>=' expr #lowet
	|expr '!=' expr #diff

	|'('expr')'#par
	|CONST #const
	|NAME #name
	;

//instr : 
//	
//	;

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


