#define pinV1 5
#define pinV2 6
#define pinV3 7

#define pinC1 9
#define pinC2 10

#define MOTOR_REPOSO 0
#define MOTOR_HORARIO 1
#define MOTOR_ANTI 2

#define pinL1 13
#define pinL2 12
#define pinL3 11

#define t1000 1000
#define t2000 2000
#define t2500 2500
#define t3500 3500

int v1_estado;
int v2_estado;
int v3_estado;

int L1, L2, L3;

int motor_estado;

int etapa=0;

unsigned long tInicio, tiempo;

void setup(){
  pinMode(pinV1,OUTPUT);
  pinMode(pinV2,OUTPUT);
  pinMode(pinV3,OUTPUT);
  
  pinMode(pinC1,OUTPUT);
  pinMode(pinC2,OUTPUT);
  
  pinMode(pinL1,INPUT);
  pinMode(pinL2,INPUT);
  pinMode(pinL3,INPUT);
  
  
  
}

void loop(){
  //IPO= INPUT PROCESS OUTPUT
  
  //ENTRADAS
  L1 = digitalRead(pinL1);
  L2 = digitalRead(pinL2);
  L3 = digitalRead(pinL3);
  
  //PROCESO
  switch(etapa){
    case 0:
    //ACCIONES DE LA ETAPA
    v1_estado=HIGH;
    //TRANSICIONES DE LA ETAPA
    if(L2==HIGH){
      //ACCIONES DE LA TRANSICION
      //CAMBIO DE ETAPA
      etapa=10;
    }
    
    break;
    case 10:
    //ACCIONES DE LA ETAPA
    v1_estado=LOW;
	v2_estado=HIGH;
    //TRANSICIONES DE LA ETAPA
    if(L3==HIGH){
      //ACCIONES DE LA TRANSICION
      //CAMBIO DE ETAPA
      etapa=20;
    }
    
    break;
    case 20:
    //ACCIONES DE LA ETAPA
    v1_estado=LOW;
	v2_estado=LOW;
	tInicio=millis();
    //TRANSICIONES DE LA ETAPA
    
      //ACCIONES DE LA TRANSICION
      //CAMBIO DE ETAPA
      etapa=30;        
    break;
    case 30:
    //ACCIONES DE LA ETAPA
    tiempo=millis()-tInicio;
    //TRANSICIONES DE LA ETAPA
    if(tiempo>=t2000){
      //ACCIONES DE LA TRANSICION
      tInicio=millis();
      //CAMBIO DE ETAPA
      etapa=40;
    }    
    break;
    case 40:
    //ACCIONES DE LA ETAPA
    motor_estado=MOTOR_HORARIO;
	tiempo = millis()-tInicio;
    //TRANSICIONES DE LA ETAPA
    if(tiempo>=t3500){
      //ACCIONES DE LA TRANSICION
      tInicio=millis();
      //CAMBIO DE ETAPA
      etapa=50;
    }    
    break;
    case 50:
    //ACCIONES DE LA ETAPA
    motor_estado=MOTOR_REPOSO;
	tiempo = millis()-tInicio;
    //TRANSICIONES DE LA ETAPA
    if(tiempo>=t1000){
      //ACCIONES DE LA TRANSICION
      tInicio=millis();
      //CAMBIO DE ETAPA
      etapa=60;
    }    
    break;
    case 60:
    //ACCIONES DE LA ETAPA
    motor_estado=MOTOR_ANTI;
	tiempo = millis()-tInicio;
    //TRANSICIONES DE LA ETAPA
    if(tiempo>=t3500){
      //ACCIONES DE LA TRANSICION      
      //CAMBIO DE ETAPA
      etapa=70;
    }    
    break;
    case 70:
    //ACCIONES DE LA ETAPA
    motor_estado=MOTOR_REPOSO;
	v3_estado=HIGH;
    //TRANSICIONES DE LA ETAPA
    if(L1==LOW){
      //ACCIONES DE LA TRANSICION      
      tInicio=millis();
      //CAMBIO DE ETAPA
      etapa=80;
    }    
    break;
    case 80:
    //ACCIONES DE LA ETAPA
    v3_estado=LOW;
	tiempo=millis()-tInicio;
    //TRANSICIONES DE LA ETAPA
    if(tiempo>=t2500){
      //ACCIONES DE LA TRANSICION      
      //CAMBIO DE ETAPA
      etapa=0;
    }    
  }

  
  //SALIDA
  digitalWrite(pinV1,v1_estado);
  digitalWrite(pinV2,v2_estado);
  digitalWrite(pinV3,v3_estado);
  
  if(motor_estado==MOTOR_REPOSO){
    digitalWrite(pinC1,LOW);
    digitalWrite(pinC2,LOW);
  }else if(motor_estado==MOTOR_HORARIO){
    digitalWrite(pinC1,HIGH);
    digitalWrite(pinC2,LOW);
  }else{
    digitalWrite(pinC1,LOW);
    digitalWrite(pinC2,HIGH);
  }
     
}
