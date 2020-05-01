
#include <LiquidCrystal.h>

typedef struct
{
  int Trigger;   // Trigger Pin
  int Echo;      // Echo Pin
  int Led;       // Led Pin
  int Distancia; // Distancia em cm
} ItemSonar;

#define BLOQUEADO 1
#define LIBERADO  0

const int distanciaLimite = 30; // 30cm
const int qtSonares = 4;
ItemSonar Sonares[qtSonares] = {
                                {13, 12,  11,  0}, 
                                {10,  9,   8,  0},
                                { 7,  6,   5,  0},
                                { 4,  3,   2,  0} 
                               };  
/* {Trigger_Pin, Echo_Pin, Led_Pin, Distancia} */

// Utilizando os pinos analógicos como GPIO (General Purpose Input Output)
LiquidCrystal Display( A0, A1, A2, A3, A4, A5);

/*
** rotina aproveitada de tinkercad.com
*/
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


void setup()
{
 
  // leds
  for(int i=0; i < qtSonares; i++)
  {
    pinMode(Sonares[i].Led, OUTPUT);
  }

  // Utilizando as portas analógicas como saídas digitais.
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  
  //botão de seleção de modo de depuração
  pinMode( 0, INPUT);
  
  Display.begin(16, 2);
  Display.print("Iniciando...");
  
  randomSeed(analogRead(2));
  
  Serial.begin(9600);
  
}

void loop()
{
  Display.clear();
  
  for(int i=0; i < qtSonares; i++)
  {
    Sonares[i].Distancia = 0.01723 * readUltrasonicDistance(Sonares[i].Trigger, Sonares[i].Echo);
    
    // vaga está ocupada?
    if(Sonares[i].Distancia <= distanciaLimite )
    {
      digitalWrite(Sonares[i].Led, HIGH); // aciona led vermelho
    }
    else
    {
      digitalWrite(Sonares[i].Led, LOW); // aciona led verde
    }
    delay(100);
  }

  int se = BLOQUEADO; // sensor 0
  int sc = BLOQUEADO; // sensor 1
  int sd = BLOQUEADO; // sensor 2
  int si = BLOQUEADO; // sensor 3
  
  if( Sonares[0].Distancia > distanciaLimite ) se = LIBERADO; 
  if( Sonares[1].Distancia > distanciaLimite ) sc = LIBERADO;
  if( Sonares[2].Distancia > distanciaLimite ) sd = LIBERADO;
  if( Sonares[3].Distancia > distanciaLimite ) si = LIBERADO;
  
  // transição para E
  if( se == LIBERADO &&
      sc == LIBERADO &&
      sd ==LIBERADO  &&
      si ==LIBERADO )
  {
    //TODAS VAGAS LIVRES
    Display.setCursor(0,0);
    Display.print("Vagas livres: 2");
    Serial.println("Vagas livres: 2");
    Display.setCursor(0,1);
    Display.print("Vaga especial: 2");
    Serial.println("Vaga especial: 2");
    
  }
  
  // 1 VAGA LIVRE NORMAL E 1 ESPECIAL
  if( se == LIBERADO  &&
      sc == BLOQUEADO &&
      sd == LIBERADO &&
      si == BLOQUEADO ||
      se == BLOQUEADO &&
      sc == LIBERADO &&
      sd == BLOQUEADO &&
      si == LIBERADO  )
  {
    // 1 VAGA PARA PESSOAS COMUNS E 1 VAGA PARA PESSOAS COM DEFICIENCIA OU IDOSO
    int escolha = random(2);
    if( escolha == 0 )
    {
      Display.setCursor(0,0);
      Display.print("Vaga livre: 1");
      Serial.println("Vaga livre: 1");
      Display.setCursor(0,1);
      Display.print("Vaga especial: 1");
      Serial.println("Vaga especial: 1 ");
    } 
    
  }

  // 1 VAGA ESPECIAL
  if( se == BLOQUEADO &&
      sc == BLOQUEADO &&
      sd == LIBERADO &&
      si == BLOQUEADO ||
      se == BLOQUEADO &&
      sc == BLOQUEADO &&
      sd == BLOQUEADO &&
      si == LIBERADO )
  {
    // 1 VAGA PARA PESSOAS ESPECIAIS
    Display.print("Vaga especial: 1");
    Serial.println("Vaga especial: 1");
  }

  // 1 VAGA LIVRE NORMAL
  if( se == LIBERADO  &&
      sc == BLOQUEADO &&
      sd == BLOQUEADO &&
      si == BLOQUEADO ||
      se == BLOQUEADO &&
      sc == LIBERADO &&
      sd == BLOQUEADO &&
      si == BLOQUEADO )
  {
    //1 VAGA PARA PESSOAS COMUM
    Display.print("Vagas livre: 1");
    Serial.println("Vagas livre: 1");
  }
  
    // 1 VAGA LIVRE NORMAL E 1 ESPECIAL
  if( se == BLOQUEADO  &&
      sc == LIBERADO &&
      sd == LIBERADO &&
      si == BLOQUEADO ||
      se == LIBERADO &&
      sc == BLOQUEADO &&
      sd == BLOQUEADO &&
      si == LIBERADO  )
  {
    // 1 VAGA PARA PESSOAS COMUNS E 1 VAGA PARA PESSOAS COM DEFICIENCIA OU IDOSO
      Display.setCursor(0,0);
      Display.print("Vaga livre: 1");
      Serial.println("Vaga livre: 1");
      Display.setCursor(0,1);
      Display.print("Vaga especial: 1");
      Serial.println("Vaga especial: 1 ");
    } 
  
    // 1 VAGA LIVRE NORMAL E 2 ESPECIAL
  if( se == BLOQUEADO  &&
      sc == LIBERADO &&
      sd == LIBERADO &&
      si == LIBERADO ||
      se == LIBERADO &&
      sc == BLOQUEADO &&
      sd == LIBERADO &&
      si == LIBERADO  )
  {
    // 1 VAGA PARA PESSOAS COMUNS E 2 VAGA PARA PESSOAS COM DEFICIENCIA OU IDOSO
      Display.setCursor(0,0);
      Display.print("Vaga livre: 1");
      Serial.println("Vaga livre: 1");
      Display.setCursor(0,1);
      Display.print("Vaga especial: 2");
      Serial.println("Vaga especial: 2 ");
    }
  
   // 2 VAGA LIVRE NORMAL E 1 ESPECIAL
  if( se == LIBERADO  &&
      sc == LIBERADO &&
      sd == BLOQUEADO &&
      si == LIBERADO ||
      se == LIBERADO &&
      sc == LIBERADO &&
      sd == LIBERADO &&
      si == BLOQUEADO  )
  {
    // 2 VAGA PARA PESSOAS COMUNS E 1 VAGA PARA PESSOAS COM DEFICIENCIA OU IDOSO
      Display.setCursor(0,0);
      Display.print("Vaga livre: 2");
      Serial.println("Vaga livre: 2");
      Display.setCursor(0,1);
      Display.print("Vaga especial: 1");
      Serial.println("Vaga especial: 1 ");
    }
  
  // 2 VAGA LIVRE NORMAL
  if( se == LIBERADO &&
      sc == LIBERADO &&
      sd == BLOQUEADO &&
      si == BLOQUEADO )
  {
    // 2 VAGA PARA PESSOAS COMUM
    Display.print("Vagas livre: 2");
    Serial.println("Vagas livre: 2");
  }
  
  // 2 VAGA LIVRE ESPECIAL
  if( se == BLOQUEADO &&
      sc == BLOQUEADO &&
      sd == LIBERADO &&
      si == LIBERADO )
  {
    // 2 VAGA PARA PESSOAS ESPECIAIS
    Display.print("Vaga especial: 2");
    Serial.println("Vaga especial: 2");
  }

  // SEM VAGAS!
  if( se == BLOQUEADO &&
      sc == BLOQUEADO &&
      sd == BLOQUEADO &&
      si == BLOQUEADO)
  {
    // bloqueo total
    Display.print("SEM VAGAS !!!");
    Serial.println("SEM VAGAS !!!");
  }


  delay(1000); // Delay a little bit to improve simulation performance
 
}
