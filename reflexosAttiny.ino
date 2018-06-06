/*Xogo de reflexos, debes pulsar o botón cando se acenda o led do medio, se acertas subirás un nivel, se fallas perderás.*/

//definimos os pines onde van os leds, boton e buzzer
    int led1=0;
    int led2=1;
    int led3=2;
    int buzzer=4;
    int boton=3;

//definimos as variables que necesitaremos para ter conta do tempo
    long tempoActual=0;
    long tempoAceso=1200;

//definimos unha variable que almacenara o numero aleatorio que fai que
//se encenda un led determinado
    long numeroChou;

//led2Aceso nos indicara se o led numero 2, ao que temos que reaccionar
// estara ou non aceso. Por iso e "boolean" que so admite "true" o "false"
    boolean led2Aceso;

//estas duas variables nos serviran para ter conta das pulsacions do boton
    int botonAntes=0;
    int botonAgora;

//esta variable nos servira para ter conta do nivel ao que chegamos
    int nivel=0;

void setup() {
    //Esperamos un segundo para que comece
      delay(1000);
    //definimos os pines dos leds e buzzer como saidas e o boton coma entrada
      pinMode(led1,OUTPUT);
      pinMode(led2,OUTPUT);
      pinMode(led3,OUTPUT);
      pinMode(buzzer, OUTPUT);
      pinMode(boton,INPUT);
     }

void loop(){
   //chamamos a funcion de encendido    
       acendeLeds();
   //leremos o boton e comparamos
       compara();   
    }

//funcion de encendido de Leds
    void acendeLeds() {
      //comproba se xa pasou o intervalo de tempo que definimos como tempoAceso
          if ((millis()-tempoActual)>tempoAceso){
            //Apagamos todos os leds un intre para evitar que pareza que non cambian se se repite o mesmo led
            digitalWrite (led1,LOW);
            digitalWrite (led2,LOW);
            digitalWrite (led3,LOW);
            delay(20);
      //Escollemos un numero ao chou que pode ser 1,2 ou 3
          numeroChou=random(1,4);
      //segundo o numero que saia, encendemos un led ou outro e definimos se led2Aceso
      //e "true" o "false"
          switch (numeroChou) {
              case 1:
                  digitalWrite (led1,HIGH);
                  digitalWrite (led2,LOW);
                  digitalWrite (led3,LOW);
                  led2Aceso=false;
                  break;
              case 2:
                  digitalWrite (led1,LOW);
                  digitalWrite (led2,HIGH);
                  digitalWrite (led3,LOW);
                  led2Aceso=true;
                  break;
              case 3:
                  digitalWrite (led1,LOW);
                  digitalWrite (led2,LOW);
                  digitalWrite (led3,HIGH);
                  led2Aceso=false;
                  break;
             }
     //con esta liña "reseteamos" o tempoActual
         tempoActual=millis();
       }
  }

//funcion que le o boton e comproba se acertamos
    void compara() {
        //Leo o boton
            botonAgora=digitalRead(boton);
       //Comparo se o boton cambiou de estado
      //Se cambiou de estado e, ademais, vale 1
          if (botonAgora!=botonAntes && botonAgora==1){
              //Se o que estaba aceso non era o led 2 e chamo a funcion "perdiches()"
                  if (led2Aceso==false) {
                      perdiches();
                     }
              //en caso contrario sera que o fixen ben e chamo a funcion "acertas()"
                  else {
                      acertas();
                     }
                 }
     //Se non cambiou de estado, transformo o estado actual en estado anterior
         else {
             botonAntes=botonAgora;
            }
         }
 
//Funcion en caso de perder
    void perdiches(){
      digitalWrite(buzzer,HIGH);
                delay(600);
                digitalWrite(buzzer, LOW);
        //Encendo e apago os tres leds durante 0,3 seg, cinco veces
            for (int i=0;i<5;i++){
                digitalWrite (led1,HIGH);
                digitalWrite (led2,HIGH);
                digitalWrite (led3,HIGH);
                digitalWrite(buzzer,LOW);
                delay(200);
                digitalWrite (led1,LOW);
                digitalWrite (led2,LOW);
                digitalWrite (led3,LOW);
                digitalWrite(buzzer,HIGH);
                delay(200);
                }
                delay(300);
                digitalWrite(buzzer,LOW);
                //reinicio o nivel no que comezo
            nivel=0;
        //reinicio a variable de tempo de transicion do led
           tempoAceso=1200;
       }

//Funcion en caso de acertar
    void acertas() {
        //Gardo o estado en que estou coma estado anterior
            botonAntes=digitalRead(boton);     
        //subo un nivel
            nivel++;
        //Encendo os tres leds durante 0,6 seg e os apago durante 0,4
            digitalWrite (led1,HIGH);
            digitalWrite (led2,HIGH);
            digitalWrite (led3,HIGH);
            delay(600);
            digitalWrite (led1,LOW);
            digitalWrite (led2,LOW);
            digitalWrite (led3,LOW);
            digitalWrite (buzzer,HIGH);
            delay(400);
            digitalWrite (buzzer,LOW);
          //fago que o tempo de transicion sexa o 90% do anterior
            tempoAceso=tempoAceso*0.9;
       }
