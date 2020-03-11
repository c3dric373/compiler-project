grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' bloc RETURN expr'}' 
     ;

bloc : 
	  declI
	| declI bloc
	|
	//| instr bloc
	;

declI   : 
         'int' NAME '=' CONST ';' #definition 
	 //|'int' NAME '=' EXPR ';' #definition
        ;

expr   :
	 expr '+' expr #plus
	|expr '-' expr #moins
	|expr '*' expr #mult
	//pour après |expr '/' expr #div
	|'('expr')'
	|CONST
	|NAME
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


NAME: [a-zA-Z]+;//chiffres lettres underscore et blanc souligne ou blanc souligne tout seul
