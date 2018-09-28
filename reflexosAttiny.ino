/*Xogo de reflexos, debes pulsar o botón cando se acenda o led do medio, se acertas subirás un nivel, se fallas perderás.*/

//definimos os pines onde van os leds, boton e buzzer
//version 0.2    
    int led1=2;
    int led2=1;
    int led3=0;
    int boton=3;

//// version 0.1    
//    int led1=1;
//    int led2=2;
//    int led3=3;
//    int boton=0;

//// arduino UNO   
//    int led1=8;
//    int led2=9;
//    int led3=10;
//    int boton=7;

//definimos as variables que necesitaremos para ter conta do tempo
    long tempoActual = 0;
//este seria o tempo de espera co que arranca o xogo
    long tempoAceso = 1200;
//este sera o factor de aceleracion polo que se multiplica o tempo de espera. 
//Canto mais baixo, mais acelera en cada nivel.
    float aceleracion = 0.9;

//definimos unha variable que almacenara o numero aleatorio que fai que
//se acenda un led determinado
    long numeroChou;

//led2Aceso nos indicara se o led numero 2, ao que temos que reaccionar
// estara ou non aceso. Por iso e "boolean" que so admite "true" o "false"
    boolean led2Aceso;

//estas duas variables nos serviran para ter conta das pulsacions do boton
    int botonAntes = 0;
    int botonAgora;

//esta variable nos servira para ter conta do nivel ao que chegamos
    int nivel = 0;
//esta variable sirve para amosar o nivel ao que chegamos, sendo o resto de %7
    int resto; //aqui para facela accesible a funcion amosaresto()

void setup() {
    //definimos os pines dos leds como saidas e o boton coma entrada
      pinMode(led1,OUTPUT);
      pinMode(led2,OUTPUT);
      pinMode(led3,OUTPUT);
      pinMode(boton,INPUT);
      //conta atras antes de comezar
      secuenciaInicio();
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
        apagaTodos();
        delay(20);
        
        //Escollemos un numero ao chou que pode ser 1,2 ou 3
        numeroChou=random(1,4);
        
        //segundo o numero que saia, encendemos un led ou outro e definimos se led2Aceso
        //e "true" o "false"
        digitalWrite (led1,numeroChou == 1);
        digitalWrite (led2,numeroChou == 2);
        digitalWrite (led3,numeroChou == 3);
        led2Aceso = (numeroChou == 2);
        //con esta liña "reseteamos" o tempoActual
         tempoActual=millis();
       }
    }

//funcion que le o boton e comproba se acertamos
void compara() {
  //Leo o boton
  botonAgora = digitalRead(boton);
  
  //Comparo se o boton cambiou de estado
  //Se cambiou de estado e, ademais, vale 1
  if (botonAgora != botonAntes && botonAgora){
    //Se o que estaba aceso non era o led 2 perdes e amosamos os puntos
    if (!led2Aceso) {
      amosaPuntos();
      }
    //en caso contrario sera que o fixen ben e chamo a funcion "acertas()"
      else {
        acertas();
        }
    }
  //Se non cambiou de estado, transformo o estado actual en estado anterior
    else {
      botonAntes = botonAgora;
      }
    }
 
//Funcion en caso de acertar
    void acertas() {
        //Gardo o estado en que estou coma estado anterior
            botonAntes = digitalRead(boton);     
        //subo un nivel
            nivel++;
        //Encendo os tres leds durante 0,6 seg e os apago durante 0,4
            acendeTodos();
            delay(600);
            apagaTodos();
            delay(400);
          //multiplico o tempo de transicion polo factor de aceleracion
            tempoAceso = tempoAceso*aceleracion;
       }

//Funcion para amosar a puntuacion con flashes dos leds
/* A puntuacion amosarase con flashes en binario, dando un flash 
 *  dos tres leds (111) por cada 7 niveis 
 *  acadados mais o resto. Repetirase ate premer de novo o boton
 */
  void amosaPuntos() {
    //despois dun retardo pequeno, reseteamos valores
    delay(300);
    tempoAceso=1200;
    botonAntes=0;
    //esta variable almacena o numero de setes flasheados
    int setesPasados=0;
    //almacena o tempo que duran as pulsacions dos puntos
    int tempoPuntos;
    //o numero de pulsos de 111 sera igual ao nivel acadado entre 7
    int setes= nivel/7;
    //o resto, unha vez pulsados os setes, sera o modulo de nivel entre 7
    resto=nivel%7;
    
    //comezamos o contador de tempo
    int tempo=millis();
    //variable para o bucle
    boolean parar = false;
    /*===========desde aqui==========
     * ===========================
     * ===================
     * =================
     */
    while (!parar){
      //lemos boton
      botonAgora=digitalRead(boton);
      if (botonAgora != botonAntes && botonAgora==1){
        secuenciaInicio();
        parar = true;
       }
        else {
          int tempoFlash=millis()-tempo;
         // isto e para diferenciar o primeiro sete, creo que quedaria mellor cunha pausa no canto de mais tempo aceso, pero non dou
          if (setesPasados==0){
            tempoPuntos=1800;
          }
          else {
            tempoPuntos=800;
          }
          
          if (tempoFlash<=tempoPuntos && setesPasados<setes){
              acendeTodos();
              }
          if (tempoFlash<=tempoPuntos && setesPasados==setes){
                acendeResto(); 
              }
  
              
          if (tempoFlash>tempoPuntos && tempoFlash<=tempoPuntos+600){
            apagaTodos();
            }
            
          if (tempoFlash>tempoPuntos+600) {
            tempo=millis();
            setesPasados++;
            if (setesPasados>setes){
              setesPasados = 0;
              }
            }
        }
      }
      nivel=0;
    }

// funcion para acender todos os leds
void acendeTodos(){
  digitalWrite (led1,HIGH);
  digitalWrite (led2,HIGH);
  digitalWrite (led3,HIGH);
  
}

//funcion para apagar todos os leds
void apagaTodos() {
  digitalWrite (led1,LOW);
  digitalWrite (led2,LOW);
  digitalWrite (led3,LOW);
}

//funcion que acende os leds correspondentes do resto
void acendeResto() {
   digitalWrite(led3, bitRead(resto, 0)); 
   digitalWrite(led2, bitRead(resto, 1));
   digitalWrite(led1, bitRead(resto, 2));          
}
    
void secuenciaInicio(){
        digitalWrite (led1,LOW);
        digitalWrite (led2,LOW);
        digitalWrite (led3,LOW);
        delay(400);
        digitalWrite (led1,HIGH);
        digitalWrite (led2,HIGH);
        digitalWrite (led3,HIGH);
        delay(400);
        digitalWrite (led1,LOW);
        digitalWrite (led2,HIGH);
        digitalWrite (led3,HIGH);
        delay(300);
        digitalWrite (led1,LOW);
        digitalWrite (led2,LOW);
        digitalWrite (led3,HIGH);
        delay(300);
        digitalWrite (led1,LOW);
        digitalWrite (led2,LOW);
        digitalWrite (led3,LOW);
        delay(500);
       }


    
////Funcion en caso de perder
//    void perdiches(){
//      digitalWrite(buzzer,HIGH);
//                delay(600);
//                digitalWrite(buzzer, LOW);
//        //Encendo e apago os tres leds durante 0,3 seg, cinco veces
//            for (int i=0;i<5;i++){
//                acendeTodos();
//                digitalWrite(buzzer,LOW);
//                delay(200);
//                apagaTodos();
//                digitalWrite(buzzer,HIGH);
//                delay(200);
//                }
//                delay(300);
//                digitalWrite(buzzer,LOW);
//                //reinicio o nivel no que comezo
//            nivel=0;
//        //reinicio a variable de tempo de transicion do led
//           tempoAceso=1200;
//       }
