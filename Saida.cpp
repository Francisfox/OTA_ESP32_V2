#include "Saida.h"
Saida::Saida(int pin){ 
  _pin = pin;
  pinMode(_pin, OUTPUT); 
}
void Saida::test_Saida(){
  if(millis() - _tempoAnterior >= _tempo){
    _tempoAnterior = millis();
    digitalWrite(_pin, _estado);
    _estado = !_estado;
  }
}
void Saida::ON(){
  digitalWrite(_pin,HIGH);
}
void Saida::OFF(){
  digitalWrite(_pin,LOW);
}
