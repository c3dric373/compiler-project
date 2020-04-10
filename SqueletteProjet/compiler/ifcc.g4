grammar ifcc;

axiom :
    prog
;

prog :
    initbloc 'int' 'main' '(' ')' '{' bloc '}'
;

initbloc : // this is the bloc just before the main, it will contain all the function declarations and definitions
    initfun*  #blocinit
;

initfun : // function declaration or definition
     'void' NAME '(' (type NAME (',' type NAME)*)? ')' ';'           #declproc
    |type NAME '(' (type NAME (',' type NAME)*)? ')' ';'             #declfun
    |'void' NAME '(' (type NAME (',' type NAME)*)? ')' '{' bloc '}'  #defproc
    |type NAME '(' (type NAME (',' type NAME)*)? ')' '{' bloc '}'    #deffun
;

type :
     'int'   #int
    |'char'  #char
;

bloc :
	instr*  #blocinstr
;

instr : // instructions
     'int' NAME (',' NAME)* ';'                                                      #declint
    |'char' NAME (',' NAME)* ';'                                                     #declchar
    |'int' NAME '[' expr ']' ';'                                                     #declinttab
    |'char' NAME '[' expr ']' ';'                                                    #declchartab
    |'int' NAME '=' expr ';'                                                         #defint
    |'char' NAME '=' expr ';'                                                        #defchar
    |NAME '=' expr ';'                                                               #affexpr
    |NAME '[' expr ']' '=' expr ';'                                                  #afftab
    |'if' '(' expr ')' '{' bloc '}'                                                  #ifbloc
    |'if' '(' expr ')' '{' bloc '}' 'else' '{' bloc '}'                              #ifelsebloc
    |'while' '(' expr ')' '{' bloc '}'                                               #whilebloc
    |'for' '(' initfor? ';' expr? ';' (loopinstr(',' loopinstr)*)? ')' '{' bloc '}'  #forbloc
    |'{' bloc '}'                                                                    #instrbloc
    |NAME '(' (NAME (',' NAME)*)? ')' ';'                                            #callproc
    |'putchar' '(' NAME ')' ';'                                                      #putchar
    |'return' ';'                                                                    #return
    |'return' expr ';'                                                               #returnexpr
;

// the next two rules are special rules for the for loop because we cant have any expression possible
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

expr : // operations we can do in an expression, sorted by priority order
     '('expr')'                        #par
    |'-' expr                          #minus
    |expr '*' expr                     #mult
    |expr '-' expr                     #sub
    |expr '+' expr                     #add
    |'!' expr                          #not
    |expr '==' expr                    #eq
    |expr '!=' expr                    #neq
    |expr '<=' expr                    #leq
    |expr '>=' expr                    #geq
    |expr '<' expr                     #low
    |expr '>' expr                     #geat
    |expr '&' expr                     #and
    |expr '^' expr                     #xor
    |expr '|' expr                     #or
    |NAME '(' (NAME (',' NAME)*)? ')'  #callfun
    |'getchar' '(' ')'                 #getchar
    |CONST                             #const
    |CONSTCHAR                         #constchar
    |NAME                              #name
    |NAME '[' expr ']'                 #tabaccess
;

// terminal nodes
CONST : [0-9]+ ;
CONSTCHAR : '\'' [a-zA-Z_0-9] '\'' ;
NAME : [a-zA-Z_]+[a-zA-Z_0-9]* ;

// ignore comments, directives and white spaces
COMMENT1 : '/*' .*? '*/' -> skip ;
COMMENT2 : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN) ;
