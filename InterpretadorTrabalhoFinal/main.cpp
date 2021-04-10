#include <iostream>
#include <string>
#include "estruturas.h"

//tokens utilizados
#define NUMERO 100
#define OPERACAO  100
#define NAO_OPERACAO -1
#define SOMA 1
#define SUBTRACAO 2
#define MULTIPLICACAO 3
#define DIVISAO 4
#define ATRIBUICAO 5
#define INTEIRO 'int'
#define FLOAT 'float'
#define CHAR 'char'
#define SE 'if'
#define ENQUANTO 'while'


using namespace std;


int valor;
string input; 
void error(string);
void print(char);
int calc(int, int, int);
FUNCAO expr();
FUNCAO term();
FUNCAO rest();
void match(char);
char nextToken();
char lookahead;

//Lexer
int count = 0;
char nextToken(){
  if (count == input.length())
    return EOF;
  return input[count++];
}


//Parser
FUNCAO expr(){
  FUNCAO
 e, t, r;
  t = term();
  r = rest();
  e.valor = calc(t.valor, r.op, r.valor);
  return e;
}
FUNCAO rest(){
  FUNCAO
 e, t, r;
  e.op = NAO_OPERACAO;
  if (lookahead == '-'){
     match('-');
     e.op = SUBTRACAO;
     t = term();
     r = rest();

  } 
  else if (lookahead == '+'){
    match('+');
    e.op = SOMA;
    t = term();
    r = rest();
  }
  else if (lookahead == '*'){
    match('*');
    e.op = MULTIPLICACAO;
    t = term();
    r = rest();
  }
  else if (lookahead == '/'){
    match('/');
    e.op = DIVISAO;
    t = term();
    r = rest();
  }
  else if(lookahead == '=') {
    match('=');
    e.op = ATRIBUICAO;
    t = term();
    r = rest();
  }

   else if (lookahead != EOF) {
    error("Erro de sintaxe");
  }
  e.valor = calc(t.valor, r.op, r.valor);
  return e;
}

FUNCAO term(){
  FUNCAO r;
  r.op = NAO_OPERACAO;
  switch (lookahead) {
    case '0': match('0'); r.valor = 0; break;
    case '1': match('1'); r.valor = 1; break;
    case '2': match('2'); r.valor = 2; break;
    case '3': match('3'); r.valor = 3; break;
    case '4': match('4'); r.valor = 4; break;
    case '5': match('5'); r.valor = 5; break;
    case '6': match('6'); r.valor = 6; break;
    case '7': match('7'); r.valor = 7; break;
    case '8': match('8'); r.valor = 8; break;
    case '9': match('9'); r.valor = 9; break;
    case 'x': match('x'); r.valor = valor; break;
    default: error("Erro na escrita .");
  }
  return r;
}

void match(char c){
  
  if (lookahead == c) {
    lookahead = nextToken();
  } else {
    string s = "Found " + to_string(lookahead) + " but expected " + to_string(c);
    error(s);
  }
}

//regras matematicas
int calc(int v1, int op, int v2){
  switch (op){
    case NAO_OPERACAO : return v1;
    case SOMA : return v1+v2;
    case SUBTRACAO : return v1-v2;
    case MULTIPLICACAO : return v1*v2;
    case DIVISAO : return v1/v2;
    case ATRIBUICAO : valor = v2; return v2;
  }
  return 0;
}

//Tratamento de Erro
void error(string msg){
  cout << endl << "Erro de sintaxe: "<< msg << endl;
  cout << input << endl;
  abort();
}

//
void print(char c){
  cout << c;
}

// --- MAIN 
int main(){
  cout << ">> ";
  getline(cin, input);
  while (!input.empty()){
    lookahead = nextToken();
    FUNCAO e = expr();
    cout << e.valor << endl << ">> ";
    getline(cin, input);
    count = 0;
  }
}