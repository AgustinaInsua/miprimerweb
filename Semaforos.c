#include  <stdio.h >       // libreria estandar
#include  <stdlib.h >      // para usar exit y funciones de la libreria standard
#include  <string.h >
#include  <pthread.h >     // para usar hilos
#include  <semaphore.h >   // para usar semaforos
#include  <unistd.h >


# define  LIMITE  50
pthread_mutex_t mutex;
// creo estructura de semaforos
struct semaforos {
    sem_t sem_mezclar;
    sem_t sem_salar;
    sem_t sem_agregarCarne;
    sem_t sem_empanarMilanesas;
    sem_t sem_cocinarEnSarten;
    sem_t sem_hornear;
    sem_t sem_armarSanguche;    
    sem_t sem_cortarExtras;
	// poner demas semaforos aqui
};


// creo los pasos con los ingredientes
struct paso {
   char accion [LIMITE];
   char ingredientes [ 4 ] [LIMITE];
   
};

// creo los parametros de los hilos
struct parametro {
 int equipo_param;
 struct semaforos semaforos_param;
 struct paso pasos_param [ 9 ];
};

// funcion para imprimir las acciones y los ingredientes de la accion
void * imprimirAccion ( void * data, char * accionIn) {
	struct parametro * mydata = data;
	// calculo la longitud del array de pasos
	int sizeArray = ( int ) ( sizeof (mydata-> pasos_param ) / sizeof (mydata-> pasos_param [ 0 ]));
	// indice para recorrer array de pasos
	int i;
	for (i = 0 ; i <sizeArray; i ++) {
		// pregunto si la accion del array es igual a la pasada por parametro (si es igual la funcion strcmp devuelve cero)
		if ( strcmp (mydata-> pasos_param [i]. accion , accionIn) == 0 ) {
		printf ( "\t Equipo %d - accion %s  \n  " , mydata-> equipo_param , mydata-> pasos_param [i]. accion );
		// calculo la longitud del array de ingredientes
		int sizeArrayIngredientes = ( int ) ( sizeof (mydata-> pasos_param [i]. ingredientes ) / sizeof (mydata-> pasos_param [i]. ingredientes [ 0 ]));
		// indice para recorrer array de ingredientes
		int h;
        // si existen ingredientes para esa accion imprimir
		if(sizeArrayIngredientes!=0){
	//	printf ( "\t Equipo %d ----------- ingredientes: ---------- \n " , mydata-> equipo_param );
			for(h = 0 ; h <sizeArrayIngredientes; h ++) {
				// consulto si la posicion tiene valor porque no hay cuantos ingredientes tengo por accion
				if ( strlen (mydata-> pasos_param [i]. ingredientes [h]) != 0 ) {
							printf ( "\t Equipo %d ingrediente   %d : %s  \n " , mydata-> equipo_param , h, mydata-> pasos_param [i]. ingredientes [h]);
				}
			}
		}
		}
	}
}

// funcion para tomar de ejemplo
void * cortar ( void * data) {
    sem_wait(mutex);
	// creo el nombre de la accion de la funcion
	char * accion = " cortar " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data;
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)

    sem_post (& mydata-> semaforos_param . sem_mezclar );

	
    pthread_exit ( NULL );
    	sem_post(mutex);
}
void * cortarExtras ( void * data) {
 
	// creo el nombre de la accion de la funcion
	char * accion = " cortarExtras " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data;
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post (& mydata-> semaforos_param . sem_armarSanguche );

	
    pthread_exit ( NULL );
}
void * mezclar ( void * data) {
//	int WINPTHREAD_SEMA_API sem_wait(sem_mezclar *data);
//	sem_wait(mutex);

	// creo el nombre de la accion de la funcion
	char * accion = " mezclar " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data; 
  //  sem_wait (& mydata-> semaforos_param . sem_mezclar ); 
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post (& mydata-> semaforos_param . sem_salar );

    pthread_exit ( NULL );
 //   	sem_post(mutex);
		
}
void * salar ( void * data) {
    sem_wait(mutex);  
	// creo el nombre de la accion de la funcion
	char * accion = " salar " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data; 
 //   sem_wait (& mydata-> semaforos_param . sem_mezclar ); 
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
	sem_post(mutex);
    sem_post (& mydata-> semaforos_param . sem_agregarCarne );
	
    pthread_exit ( NULL );
		
}
void * agregarCarne ( void * data) {

	// creo el nombre de la accion de la funcion
	char * accion = " agregarCarne " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data; 
 //   sem_wait (& mydata-> semaforos_param . sem_mezclar ); 
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post (& mydata-> semaforos_param . sem_empanarMilanesas );
	
    pthread_exit ( NULL );
		
}
void * empanarMilanesas ( void * data) {

	// creo el nombre de la accion de la funcion
	char * accion = " empanarMilanesas " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data; 
 //   sem_wait (& mydata-> semaforos_param . sem_mezclar ); 
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post (& mydata-> semaforos_param . sem_cocinarEnSarten );
	
    pthread_exit ( NULL );
		
}
void * cocinarEnSarten ( void * data) {

	// creo el nombre de la accion de la funcion
	char * accion = " cocinarEnSarten " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data; 
 //   sem_wait (& mydata-> semaforos_param . sem_mezclar ); 
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
    sem_post (& mydata-> semaforos_param . sem_armarSanguche );
	
    pthread_exit ( NULL );
		
}
void * hornear ( void * data) {

	// creo el nombre de la accion de la funcion
	char * accion = " hornear " ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data; 
 //   sem_wait (& mydata-> semaforos_param . sem_mezclar ); 
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
  //  sem_post (& mydata-> semaforos_param . sem_armarSanguche );
	
    pthread_exit ( NULL );
		
}
void * armarSanguche( void * data) {

	// creo el nombre de la accion de la funcion
	char * accion = " armarSanguche" ;
	// creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
	struct parametro * mydata = data; 
 //   sem_wait (& mydata-> semaforos_param . sem_mezclar ); 
	// llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion (mydata, accion);
	// uso sleep para simular que que pasa tiempo
	sleep( 20000 );
	// doy la señal a la siguiente accion (cortar me habilita mezclar)
  //  sem_post (& mydata-> semaforos_param . sem_armarSanguche );
	
    pthread_exit ( NULL );
		
}
void * ejecutarReceta ( void * i) {
	
	// variables semaforos
	sem_t sem_mezclar;
    sem_t sem_salar;
    sem_t sem_agregarCarne;
    sem_t sem_empanarMilanesas;
    sem_t sem_cocinarEnSarten;
    sem_t sem_hornear;
    sem_t sem_armarSanguche;  
    
	// crear variables semaforos aqui
	
	// variables hilos
	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;
	pthread_t p6;
	pthread_t p7;
	pthread_t p8;
	pthread_t p9;	
	// crear variables hilos aqui
	
	// numero del equipo (casteo el puntero a un int)
	int p = * (( int *) i);
	
	printf ( "Ejecutando equipo %d  \n " , p);

	// reservo memoria para el struct
	struct parametro * pthread_data = malloc ( sizeof ( struct parametro));

	// seteo los valores al estructura
	
	// seteo numero de grupo
	pthread_data-> equipo_param = p;

	// seteo semaforos

	pthread_data-> semaforos_param . sem_mezclar = sem_mezclar;
	pthread_data-> semaforos_param . sem_salar = sem_salar;
	pthread_data-> semaforos_param . sem_agregarCarne = sem_agregarCarne;
	pthread_data-> semaforos_param . sem_empanarMilanesas = sem_empanarMilanesas;
	pthread_data-> semaforos_param . sem_cocinarEnSarten = sem_cocinarEnSarten;
	pthread_data-> semaforos_param . sem_hornear = sem_hornear;
	pthread_data-> semaforos_param . sem_armarSanguche = sem_armarSanguche;	
	// setear demas semaforos al struct aqui
	

	// seteo las acciones y los ingredientes (Faltan acciones e ingredientes) ¿Se ve hardcodeado no? ¿Les parece bien?
        sem_wait(mutex);
	 	strcpy (pthread_data-> pasos_param [ 0 ]. accion , " cortar " );
	    strcpy (pthread_data-> pasos_param [ 0 ]. ingredientes [ 0 ], " ajo " );
      strcpy (pthread_data-> pasos_param [ 0 ]. ingredientes [ 1 ], " perejil " );

	    strcpy (pthread_data-> pasos_param [ 1 ]. accion , " mezclar " );
	    strcpy (pthread_data-> pasos_param [ 1 ]. ingredientes [ 0 ], " ajo " );
      strcpy (pthread_data-> pasos_param [ 1 ]. ingredientes [ 1 ], " perejil " );
 	    strcpy (pthread_data-> pasos_param [ 1 ]. ingredientes [ 2 ], " huevo " );
 	    sem_post(mutex);
	    strcpy (pthread_data-> pasos_param [ 2 ]. accion , " salar " );	
	    strcpy (pthread_data-> pasos_param [ 3 ]. accion , " agregarCarne " );	
	    strcpy (pthread_data-> pasos_param [ 4 ]. accion , " empanarMilanesas " );	
	    strcpy (pthread_data-> pasos_param [ 5 ]. accion , " cocinarEnSarten " );	
	    strcpy (pthread_data-> pasos_param [ 6 ]. accion , " hornear " );	

	   strcpy (pthread_data-> pasos_param [ 7 ]. accion , " cortarExtras" );	    
        strcpy (pthread_data-> pasos_param [ 7 ]. ingredientes[0], " lechuga " );		
	    strcpy (pthread_data-> pasos_param [ 7 ]. ingredientes[1], " tomate " );						    
	    strcpy (pthread_data-> pasos_param [ 7 ] . ingredientes[2], " pepino " );
	    strcpy (pthread_data-> pasos_param [ 7 ]. ingredientes[3], " cebolla morada " );		
		   
	    strcpy (pthread_data-> pasos_param [ 8 ]. accion , " ArmarSanguche " );		    
	    
	// inicializo los semaforos

	sem_init (& (pthread_data-> semaforos_param . sem_mezclar ), 0 , 0 );
	sem_init (& (pthread_data-> semaforos_param . sem_salar ), 0 , 0 );
	sem_init (& (pthread_data-> semaforos_param . sem_agregarCarne ), 0 , 0 );
	sem_init (& (pthread_data-> semaforos_param . sem_empanarMilanesas ), 0 , 0 );
	sem_init (& (pthread_data-> semaforos_param . sem_cocinarEnSarten ), 0 , 0);
	sem_init (& (pthread_data-> semaforos_param . sem_hornear ), 0 , 2);
	sem_init (& (pthread_data-> semaforos_param . sem_armarSanguche ), 0 , 0);
	// inicializar demas semaforos aqui


	// creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semaforos
    int rc;
    int cont1=0;
	sem_wait(0);
     rc = pthread_create (&p1,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                cortar,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia


     rc = pthread_create (&p2,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                mezclar,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia


     rc = pthread_create (&p3,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                salar,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia
     rc = pthread_create (&p4,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                agregarCarne,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia
 
     rc = pthread_create (&p5,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                empanarMilanesas,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia


     rc = pthread_create (&p6,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                cocinarEnSarten,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia
     rc = pthread_create (&p7,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                hornear,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia

     rc = pthread_create (&p8,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                cortarExtras,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia
     rc = pthread_create (&p9,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                armarSanguche,              // funcion a ejecutar
                                pthread_data);                     // parametros de la funcion a ejecutar, pasado por referencia
	sem_post(1);

	// join de todos los hilos
	pthread_join (p1, NULL );
	pthread_join (p2, NULL );
	pthread_join (p3, NULL );
	pthread_join (p4, NULL );
	pthread_join (p5, NULL );
	pthread_join (p6, NULL );
	pthread_join (p7, NULL );
	pthread_join (p8, NULL );
	pthread_join (p9, NULL );
	// crear unir de demas hilos


	// valido que el hilo se alla creado bien
    if (rc) {
       printf ( " Error: no se puede crear el hilo, %d  \n " , rc);
       exit (-1);
     }

	 
	// destruccion de los semaforos
	sem_destroy (& sem_mezclar);
	sem_destroy (& sem_salar);
	sem_destroy (& sem_agregarCarne);
	sem_destroy (& sem_empanarMilanesas);
	sem_destroy (& sem_cocinarEnSarten);
	sem_destroy (& sem_hornear);
	sem_destroy (& sem_armarSanguche);
	// destruir demas semaforos
	
	// salida del hilo
	 pthread_exit ( NULL );
}


int  main ()
{
	// creo los nombres de los equipos
	int rc;
	int * equipoNombre1 = malloc ( sizeof (* equipoNombre1));
	int * equipoNombre2 = malloc ( sizeof (* equipoNombre2));
	int * equipoNombre3 = malloc ( sizeof (* equipoNombre3));
	int * equipoNombre4 = malloc ( sizeof (* equipoNombre4));
// faltan equipos
  
	* equipoNombre1 = 1 ;
	* equipoNombre2 = 2 ;
	* equipoNombre3 = 3 ;
	* equipoNombre4 = 4 ;

	// creo las variables los hilos de los equipos
	pthread_t equipo1;
	pthread_t equipo2;
	pthread_t equipo3;
	pthread_t equipo4;
// faltan hilos
  
	// inicializo los hilos de los equipos
	pthread_mutex_lock(&mutex);	
	
    rc = pthread_create (& equipo1,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                ejecutarReceta,              // funcion a ejecutar
                                equipoNombre1); 

	pthread_mutex_unlock(&mutex);		                                
	pthread_mutex_lock(&mutex);	
	
    rc = pthread_create (& equipo2,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                ejecutarReceta,              // funcion a ejecutar
                                equipoNombre2);
	
	pthread_mutex_unlock(&mutex);		
	pthread_mutex_lock(&mutex);	
			                                
    rc = pthread_create (& equipo3,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                ejecutarReceta,              // funcion a ejecutar
                                equipoNombre3);
							       
	pthread_mutex_unlock(&mutex);	
	pthread_mutex_lock(&mutex);	
			                         
    rc = pthread_create (& equipo4,                            // identificador unico
                            NULL ,                           // atributos del hilo
                                ejecutarReceta,              // funcion a ejecutar
                                equipoNombre4);
          	
	pthread_mutex_unlock(&mutex);		

  // faltn inicializaciones


   if (rc) {
       printf ( "Error: no se puede crear el hilo, %d  \n " , rc);
       exit (-1);
     } 

	// join de todos los hilos
	pthread_join (equipo1, NULL );
	pthread_join (equipo2, NULL );
	pthread_join (equipo3, NULL );
	pthread_join (equipo4, NULL );	
// .. faltan se une


    pthread_exit ( NULL );
}


// Para compilar: gcc subwayArgento.c -o ejecutable -lpthread
// Para ejecutar: ./ejecutable
