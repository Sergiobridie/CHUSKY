#include <NewPing.h>
NewPing ultra (5,4);


char dato;
int vd;
int vi;
int a;
int b;
int distancia;
volatile boolean opci=1;
void setup( ) {
  //configuramos E/S digitales del robot
  Serial.begin(9600);
 
  pinMode(8,OUTPUT);  //  Motor derecha
  pinMode(9,OUTPUT);  //
  
  pinMode(6,OUTPUT);  //  Motor izquierda
  pinMode(7,OUTPUT);  // 
  
  pinMode(2, INPUT);
  attachInterrupt(0,inte,RISING); 
}

void loop() {

switch (opci){
  
  case (0):{ //Modo esquivaobjetos
    Serial.print ("esta en modo esquivaobjetos");
    Serial.println (opci);
    distancia = ultra.ping_cm();

  while (distancia >= 25 && opci == 0){
    movimiento(1,1,150,150); 
    Serial.println ("para alante");
    Serial.println (opci);
    distancia = ultra.ping_cm();
 }
    Serial.println ("giro derecha");
    movimiento (1,0,150,150);
    delay (200);
    
    if (opci==1){
      analogWrite (11,0);
      analogWrite (10,0);
      
    }
    break;
    }
  case (1):{             //Modo bluetooth

    Serial.print ("esta en modo bluetooth");
    Serial.println (opci);
    if (Serial.available() > 0) {
    dato = Serial.read();
   // Serial.println(dato);
      switch (dato) {
      case ('F'): {    
          //robot movimiento adelante
          movimiento(1,1,255,255);
          break;
        }
      case ('B'): {    
          //robot movimiento atrás
          movimiento (0,0,255,255);
          break;          
       }
      case ('L'): {       
          //robot movimiento izquierda
          movimiento (0,1,0,255); 
          break;
        }
      case ('R'): {     
          //robot movimiento derecha
          movimiento(1,1,255,0);
          break;
        }
      case ('G'): {    
          //robot movimiento adelante y izquierda
          movimiento (1,1,85,255);
          break;
        }
      case ('I'): {    
          //robot movimiento adelante y derecha
          movimiento(1,1,255,85);
          break;
        }
      case ('H'): {    
          //robot movimiento atras y izquierda
          movimiento (0,0,85,255);
          break;
        }
      case ('J'): {    
          //robot movimiento atras y derecha
           movimiento(0,0,255,85); 
          break;
        }
      case ('S'): {     
          //paro motores
          analogWrite (11,0);
          analogWrite (10,0); 
          break;
        }
      case ('X'): { 
        //giro
          movimiento(1,0,255,255);
          delay(1000);
          break;
       }
      case ('x'): { 
         //giro
          movimiento(0,10,255,255);
          delay(1000);
          break;
       }
    }
  } 
  break; 
  }
} 
}
void movimiento (int a,int b,int vd,int vi){
  
          analogWrite (11,vd);
          digitalWrite (8,a);
          digitalWrite (9,!a);
          analogWrite (10,vi);
          digitalWrite (6,!b);
          digitalWrite (7,b);
  
}
void inte (){
  opci = !opci;
  Serial.println (opci);
  delay (150);
  analogWrite (11,0);
  analogWrite (10,0);
}

