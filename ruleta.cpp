//Usamos las Librerias para el Juego de la Ruleta
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<windows.h>

const int RULETA=37; //aqui se define la cantidad de posiciones que tendra el vector

typedef char tcad[30];

using  namespace std;



//Definicion de Estructura para la Ruleta (Utilizo Lista Dobles Circular)
typedef struct tipo_ruleta *pruleta;
typedef struct tipo_ruleta {
						   int dato;
						   pruleta ant;
						   pruleta sig;
						  };
typedef struct truleta {
						pruleta inicio;
						pruleta final;
						};
						
//Definicion de Estructura para el Tapete (Guarda los datos en un archivo tapete.txt y muestra en una Lista Simple )
//Estructura Registro del Numero para tapete con sus respectivos Atributos
typedef struct tnum {
					int numero;
					int color;
					int paridad;
					int docena;
					int mitad;
					int columna;
                  };                  
typedef struct tipo_tapete *ptapete;						
typedef struct tipo_tapete{
					 tnum dato;
					 ptapete sig;
 				   };	
typedef struct ttapete{
					   ptapete inicio;
					   ptapete final;
					};

//Definicion de Estructura para el Jugador						
//Estructura Registro del Jugador para el archivo
typedef struct tjugador *pjugador;
typedef struct tjugador {
							 int id;
							 tcad nombre;
							 tcad apellido;
							 float monto;
							 float ganancia;
							 pjugador sig;
							};

//Definicion de Estructura para Listar Jugadores por Ganancias;
//Estructura Registro para el ABB Ganancias
typedef struct tarbol *parbol;
typedef struct tarbol{
					tjugador dato;
					parbol izq;
					parbol der;
                  };

//Definicion de Estructura para las Apuestas;
//Estructura Registro para las Apuestas
typedef struct tapuestas{
    tjugador jugador;
	int monto_inicial;
	int apuesta_nro;
	int monto_nro;
	int apuesta_color;
	int monto_color;
	int apuesta_paridad;
	int monto_paridad;
	int apuesta_docena;
	int monto_docena;
	int apuesta_columna;
	int monto_columna;
	int apuesta_mitad;
	int monto_mitad;
	int ganancia;
	int monto_final;
};


//Estructura lista Simple(Sirve para pregutar al jugdor si desea jugar)
typedef struct tnodo *pnodo;
typedef struct tnodo {
	tjugador dato;
	pnodo sig;
};

typedef struct tlista{
	pnodo inicio;
	pnodo final;
};

//Estructura Simple (para cargar apuestas)
typedef struct tnodoApuesta *papuesta;
typedef struct tnodoApuesta{
	tapuestas dato;
	papuesta sig;
};

typedef struct tlistaApuesta{
	papuesta inicio;
	papuesta final;
};


typedef FILE *fnumero;	//Tipo Archivo para Numero
typedef FILE *fjugador;	//Tipo Archivo para Jugador
	
void menuPrincipal(int &opc);  //menu de la pantalla principal
void menuSecundario(int &opc);  //menu de la pantalla de juego
void menuJugador(int &opc);     //menu de jugador

//Ruleta
void iniciar_ruleta(truleta &ruleta);
void crearNodoRuleta(pruleta &nuevo , int valor);
void agregar_finalRuleta(truleta &ruleta, pruleta nuevo);
void mostrarRuleta(truleta ruleta);
bool buscar_nodoRuleta(truleta ruleta, int valor);
void generar_ruleta(truleta &ruleta);
int girar_ruleta(truleta ruleta, int sentido);

//Tapete
void carga_Tapete(tnum &n, int i);
void alta_Tapete(fnumero f);
void listar_Tapete(fnumero p, ttapete &l );
void iniciar_lista_Tapete(ttapete &lista);
void crear_Nodo_Tapete(ptapete &nuevo, tnum valor);
void agregar_final_Tapete(ttapete &lista, ptapete nuevo);
void mostrar_Nro_Tapete(tnum num);
void mostrar_Tapete(ttapete lista);

//Jugador
int generarid( fjugador fj );
void cargarjugador(tjugador &j, fjugador fj);
void alta_jugador(fjugador fj);
void mostrar_jugador(tjugador j);
void listar_jugador(fjugador fj);
void consulta_jugador(fjugador fj,int id);
void validarModificacion(tjugador &j);
void modificar_jugador(fjugador fj,int id);
void iniciar_Arbol_Jugador(parbol &a);
void crearNodoArbolJugador(parbol &nuevo, tjugador j);
void insercion_Arbol_Jugador(parbol &a,parbol nuevo);
void listarJugadorArbol(fjugador fj, parbol &a );
void orden_Decreciente(parbol a);

//Jugador Habilitado
void listarJugadorHabilitado(fjugador fj, tlista &l );
void crearNodoJugadorParticipante(pnodo &nuevo, tjugador j);
void iniciarListaParticipante(tlista &l);
void insertarFinalParticipante(tlista &l, pnodo nuevo);
void mostrarParticipantes(tlista l);

//Apuesta
void apuestaParticipante(tlista l,tlistaApuesta &ap);
void apuesta_nro(tapuestas &apuesta, int &disponible);
void apuesta_monto(int &x, int &disponible);
void apuesta_color(tapuestas &apuesta, int &disponible);
void apuesta_paridad(tapuestas &apuesta, int &disponible);
void apuesta_docena(tapuestas &apuesta, int &disponible);
void apuesta_columna(tapuestas &apuesta, int &disponible);
void apuesta_mitad(tapuestas &apuesta, int &disponible);

void iniciarListaApuesta(tlistaApuesta &l);
void crearNodoApuesta(papuesta &nuevo, tapuestas a);
void insertarFinalListaApuesta(tlistaApuesta &l, papuesta nuevo);
void mostrarApuestas(tlistaApuesta l);
void mostrar_Apuesta(tapuestas a);

ptapete buscarTapete(ttapete t, int x);
void mostrar_Nro_Tapete_Ganador(ptapete t);
void ganador(tlistaApuesta &l, ptapete a, fjugador fj);

void modificar_jugador_ganador(fjugador fj,int id, int totalApos, int ganancia);

///liberar
void Liberar(truleta &lista);
pruleta quitar_inicio(truleta &lista);

void LiberarTapete(ttapete &lista);
ptapete quitar_final(ttapete &lista);

void LiberarArbol(parbol &a);
parbol quitarArbol(parbol &a);



int main(){
 truleta r;
 ttapete t;

 fnumero num;
 fjugador jugador;
 
 int opcion,valor,id,resp, opc4,sentido;
 char op;
 bool opc1=false,opc2=false,opc3=false,band=false;//variables de control para opcion 1,2y3
 parbol a,b;
 tlista l;
 tlistaApuesta ap;
 ptapete nganador;
 do{
  menuPrincipal(opcion);
  switch(opcion)
  {case 1: iniciar_ruleta(r);
		   generar_ruleta(r);
		   mostrarRuleta(r);
		   opc1=false;
	       break; 
	
    case 2:
           cout<<"\n********* TAPETE DE APUESTAS *********"<<endl;
    	   iniciar_lista_Tapete(t);
	       alta_Tapete(num);
	       listar_Tapete(num,t);
	       cout<<"\n********* FIN TAPETE DE APUESTAS *********"<<endl;    
	       opc2=true;	       
	       break; 
			    
    case 3:
    	   system("cls");
	       cout<<"\n********* CARGAR JUGADOR *********"<<endl;
    	   do{
    	      alta_jugador(jugador);
    	      cout << "\nJugador Agregado Exitosamente!!!!!" << endl;
		      cout<<"\nDesea Ingresar mas Jugadores s/n ??? ";
              cin >> op;
	       }while(op!='n'&& op!='N');
	       cout<<""<<endl;
		   system("pause");
           system("cls");
           cout<<"\n********* LISTADO DE JUGADORES *********"<<endl;
	       listar_jugador(jugador);
	       opc3=true;
		   break; 
   
   case 4:
   	      system("cls");
   		  jugador=fopen("jugador.txt","rb");
          if(jugador!=NULL){
          	        fclose(jugador);
		   		    do{
		  			menuJugador(resp);
		  			switch(resp){   
					    case 1:cout <<"\nIngrese Id del Jugador: ";
		    	            cin >> id;
					        consulta_jugador(jugador,id);break; 
					    case 2:cout <<"\nIngrese Id del Jugador: ";
		    	              cin >> id;
					          modificar_jugador(jugador, id);break; 
    			 		 case 3:break;
		   			   default :cout<<"\nOpcion Incorrecta...."<<endl;break;
		  			}
		   			cout << "" << endl;
		   			system("pause");
		   			system("cls");
					}while (resp!=3);
          }else{ 
             cout<<"\nPRIMERO DEBE REGISTRAR JUGADOR, Elija Opcion Nro 3"<<endl;
		  }     
	      break;
		
	case 5:jugador=fopen("jugador.txt","rb");
	         iniciar_Arbol_Jugador(a);
	       if(jugador!=NULL){
	       	 fclose(jugador);
	         cout<<"\n********* LISTA JUGADOR *********"<<endl; 
    	     listarJugadorArbol(jugador,a);//carga jugador al arbol
    	     cout<<"*********** FIN LISTA JUGADOR ***********"<<endl;
    	   }else{
			 if(opc3==false)
			    cout<<"\nPRIMERO DEBE REGISTRAR JUGADOR, Elija Opcion Nro 3"<<endl;
	       } 
		    break;	
	case 6:
		   system("cls");
		   jugador=fopen("jugador.txt","rb");//rb Apertura en modo de sólo lectura. El archivo debe existir.
   	       num=fopen("tapete.txt","rb");
	       if(jugador!=NULL  &&  num!=NULL  && opc1==false ){
		        fclose(num);
	            fclose(jugador);
		   do{
				menuSecundario(opc4);
				
				switch(opc4){
				case 1://Selecciona Jugador que participaran del Juego(deben tener moto mayor a 0) 
					jugador=fopen("jugador.txt", "rb"); //rb Apertura en modo de sólo lectura. El archivo debe existir.
					iniciarListaParticipante(l);//Inicia ListaParticipantes
		   			listarJugadorHabilitado(jugador,l);//invita participantes a jugar
		   			fclose(jugador);
		   			if(l.inicio!=NULL){
		   				band=true;
					   }
					break;
				case 2://Selecciona el número y categorías en las que cada jugador realizará apuestas
				     if(band){
				     	  iniciarListaApuesta(ap);//inicia lista nul
				          apuestaParticipante(l,ap);//l jugador aceptaron participar  y ap  a realizar apuesta
				          
					      system("pause");
					}else{
						cout<<"\n********NO HA SELECCIONADO JUGADORES(ELIJA OPCION 1)********"<<endl;
						system("pause");
					}
					break;
				case 3:
				//Gira Ruleta y paga apuestas
				       cout << "\n***********Ingrese Sentido para Girar Ruleta***********"<<endl;
				       cout <<"\n1-Sentido Horario";
				       cout << "\t2-Sentido AntiHorario"<<endl;
		               cin >> sentido;                       
                       cout<<endl<<"\n*************************************************"<<endl;							  
					   nganador = buscarTapete(t,girar_ruleta(r,sentido));//pasa el tapete y nro ruleta, lo asigna al ngabador (tipo ptapete)
					   mostrar_Nro_Tapete_Ganador(nganador); //muestra nro ganador con todos sus datos
					   ganador(ap, nganador, jugador);//
					   cout<<endl<<"*************************************************"<<endl;
					   system("pause");
					   system("CLS");
					break;
				case 4: //Salir
					cout<<"\nGRACIAS POR JUGAR EN EL CASINO DEL APU 2008 - VUELVA PRONTO!!!"<<endl;
					system("pause");
					break;
				default:
				    cout<<"\nOPCION INCORRECTA, intente de nuevo"<<endl;
				    system("pause");
					break;									
				}
				system("cls");
			}while(opc4 != 4);
			}else{
	       	  cout<<"1, 2, y 3 se ejecutaron antes."<<endl;
		   }
		   break;
			   
		   
    case 7:cout<<"\nFIN DE PROGRAMA"<<endl;
           Liberar(r);
           LiberarTapete(t);
           LiberarArbol(a);
           exit(0);break;
   
   default :cout<<"\nOpcion Incorrecta...."<<endl;break;

  }
   cout << "" << endl;
   system("pause");
   system("cls");
}while (opcion!=7);
system("pause");
}

//------------------------------------------------MENU------------------------------------------------//

//Menu Principal 
void menuPrincipal(int &opc){
	cout<<"********** BIENVENIDO CASINO APU **********"<<endl;
	cout<<"1_ Generar Ruleta"<<endl;
	cout<<"2_ Crear/Leer el Tapete de Apuestas"<<endl;
	cout<<"3_ Registrar Jugador"<<endl;
	cout<<"4_ Consultar/Modificar Jugador"<<endl;
	cout<<"5_ Lista Jugadores"<<endl;
	cout<<"6_ Jugar"<<endl;
	cout<<"7_ Salir"<<endl;
	cout<<"*************************************************"<<endl;
	cout<<"Elija una opcion: ";
	cin>>opc;
}

//Menu Juego
void menuSecundario(int &opc){
	cout<<"********* JUEGO DE RULETA *********"<<endl;
	cout<<"1_ Seleccionar Jugadores"<<endl;
	cout<<"2_ Realizar Apuesta"<<endl;
	cout<<"3_ Girar Ruleta"<<endl;
	cout<<"4_ Salir"<<endl;
	cout<<"**************************************"<<endl;
	cout<<"Elija una opcion: ";
	cin>>opc;	
}

//Menu Consulta/Modificacion
void menuJugador(int &opc){
	cout<<"********* CONSULTAR/MODIFICAR JUGADOR *********"<<endl;
	cout<<"1_ Consulta por Jugadores"<<endl;
	cout<<"2_ Modificar Monto de Jugadores"<<endl;
	cout<<"3_ Salir"<<endl;
	cout<<"**************************************"<<endl;
	cout<<"Elija una opcion: ";
	cin>>opc;	
}

//------------------------------------------------RULETA------------------------------------------------//

// Funcion y Procedimientos para Generar y Girar la Ruleta
//Iniciamos la Ruleta
void iniciar_ruleta(truleta &ruleta){
	ruleta.inicio=NULL;
	ruleta.final=NULL;
}

//Creamos Nodo con Dato para la Ruleta
void crearNodoRuleta(pruleta &nuevo , int valor){	
 	nuevo=new tipo_ruleta;
 	if(nuevo!=NULL){
 		nuevo->dato=valor;
 		nuevo->ant=NULL;
		nuevo->sig=NULL;
	}else{
		cout<<"MEMORIA INSUFICIENTE"<<endl;
	}
}

//Agregamos los Numeros a la Ruleta(Usando Lista Doble Circular por el Final)
void agregar_finalRuleta(truleta &ruleta, pruleta nuevo){
	if(ruleta.inicio==NULL){
		ruleta.inicio=nuevo;
		ruleta.final=nuevo;
	}else{
		nuevo->ant=ruleta.final;
		ruleta.final->sig=nuevo;
    	ruleta.final = nuevo;
	}
	ruleta.final->sig=ruleta.inicio;
	ruleta.inicio->ant=ruleta.final;
}

//Mostramos los Numeros de la Ruleta(Lista Doble Circular)
void mostrarRuleta(truleta ruleta){
	pruleta i;
	int j=0;
	if(ruleta.inicio!=NULL){
		cout<<endl;
		cout<<endl<<"\n\t\t+ + + + + + + + + + + + + + + + + + R U L E T A + + + + + + + + + + + + + + + + + +"<<endl<<endl;
     	for (i=ruleta.inicio;i!=ruleta.final;i=i->sig){
			cout<<"("<<j<<") - "<<i->dato <<" | ";
			j++;
		}
		cout<<"("<<j<<") - "<<i->dato <<" | ";
		cout<<endl;
	}else{
		cout<< "\n RULETA VACIA"<<endl;
	}
}

//Busca un Numero en la Ruleta(para agregarlo o no)
bool buscar_nodoRuleta(truleta ruleta, int valor){
	pruleta i;
    bool existe=false;
    for(i=ruleta.inicio; i->sig!=ruleta.inicio && valor != i->dato ;i=i->sig);
	  if(valor==i->dato){
	  	existe=true;
	  }
return existe;
}

//Genera la Ruleta con Numeros No Repetido Aleatorios de 0 a 37
void generar_ruleta(truleta &ruleta){
	int i,aux;
	bool distinto=true;	
	srand(time(NULL)); //inicializa la generacion de numeros aleatorios
	pruleta nuevo;
	for(i=0;i<RULETA;i++){
		if(ruleta.inicio==NULL){			
			crearNodoRuleta(nuevo,rand()%37);
			agregar_finalRuleta(ruleta,nuevo);
		}else{
			distinto=true;
			do{
				aux=rand()%37;
				if(buscar_nodoRuleta(ruleta,aux)==false){//Valida Si hay Repetidos
					crearNodoRuleta(nuevo,aux);			
			        agregar_finalRuleta(ruleta,nuevo);
			        distinto=false;
				}
			}while(distinto==true);		
	    }	
    }
}

//Gira la Ruleta con un Sentido Horario(1) o con un Sentido Antihorario(2)
int girar_ruleta(truleta ruleta, int sentido){
	pruleta i;
	int aux,cont;
	srand(time(NULL)); //inicializa la generacion de numeros aleatorios
	aux=rand()%200;
	if(sentido==1){   //Sentido Horario
		i=ruleta.inicio;
	    while(cont<=aux){
          i=i->sig;
	  	  cont++;
	   }	
	}else{             //Sentido Antihorario
		i=ruleta.inicio;
	    while(cont<=aux){
          i=i->ant;
	  	  cont++;
	   }
	}
	return i->dato;  //Devuelve el dato donde se posiciono i
}



//------------------------------------------------TAPETE------------------------------------------------//
//Carga el Registro de Numero con los Valores de i para el Tapete
void carga_Tapete(tnum &n, int i){ 
   n.numero=i;    //  Numero toma el Valor pasado por i

// El Valor i define la paridad y el color
if((i%2)!=0){// 1=impar y Rojo
   n.color=1;
   n.paridad=1;
}else{ // 2=par y Negro
   n.color=2;
   n.paridad=2;				
}

// El Valor i define la Columna
if(i%3==0){         // 3= 3er columna
	n.columna=3;
}else{
   if(i%3==1){     // 1= 1era columna
      n.columna=1;
   }else{           // 2= 2da columna
      n.columna=2;
   }
}

// El Valor i define la pertenencia a docenas
if(i<=12){ // 1= 1ra docena
	n.docena=1;
}else{
	if(i>12 && i<=24){//2= 2da docena
    	n.docena=2;
	}else{	// 3= 3ra docena
		n.docena=3;
    }
}				

// El Valor i define la pertenencia a mitades
if(i<=18){        //1era mitad
	n.mitad=1;
}else{            //2da mitad 
    n.mitad=2;
}
}

//Guarda los Datos del Registro(a) a un Archivo(f)
void alta_Tapete(fnumero f){
	tnum a;
	int i;
	f=fopen("tapete.txt","rb"); //Abre el archivo solo lectura, debe existir
	if(f==NULL){
		fclose (f);     //Cierra Archivo
		f=fopen("tapete.txt","wb");  //Abre el archivo solo escritura. Si el archivo existe lo reescribire y si no existe lo crea.
		for(i=1;i<=RULETA-1;i++){
			carga_Tapete(a,i);     //Carga el Registro de Numero(a) con los valores que toma i
			fwrite(&a,sizeof(a),1,f); //Escribe del Registro Numero(a) información al Archivo(f)
		}
		fclose (f); //Cierra Archivo
	}
}

//Lista del Archivo(p) a una Lista Simple 
void listar_Tapete(fnumero p, ttapete &l ){
tnum a;
ptapete nuevo;
p=fopen("tapete.txt","rb");//Abre el archivo solo lectura, debe existir
if(p==NULL){
	cout << "El archivo no existe" << endl;
}else{
     while (!feof(p)){    //feof: si se alcanzó el final de un archivo
	    fread(&a,sizeof(a),1,p);  //Lee información almacenada en un Archivo(p) y se guarda en un Registro(a)
	    if (!feof(p)){   //feof: si se alcanzó el final de un archivo
	     crear_Nodo_Tapete(nuevo,a);    //Crea Nodo 
	     agregar_final_Tapete(l,nuevo); //Agrega el Nodo a la Lista Simple
		}
    }
    mostrar_Tapete(l);	//Recorre la Lisra
 }
 fclose(p);  //Cierra Archivo
}

//Inicializa el Tapete
void iniciar_lista_Tapete(ttapete &lista){
	lista.inicio=NULL;
	lista.final=NULL;
}

//Crea el Nodo para Lista Simple
void crear_Nodo_Tapete(ptapete &nuevo, tnum valor){
 	nuevo=new tipo_tapete;
 	if(nuevo!=NULL){
	    nuevo->dato=valor;
        nuevo->sig=NULL;
	}else{
		cout<<"MEMORIA INSUFICIENTE"<<endl;}
}

//Agrega el Nodo al Final de la Lista
void agregar_final_Tapete(ttapete &lista, ptapete nuevo){
	if(lista.inicio==NULL){
		lista.inicio=nuevo;
		lista.final=nuevo;
	}else{
		lista.final->sig=nuevo;
    	lista.final = nuevo;
	}
}

//Muestra el Registro(num) ya Cargados del Tapete
void mostrar_Nro_Tapete(tnum num){
	cout<<"Numero: "<<num.numero <<endl;
	cout<<"Color: ";
	if(num.color==1){
		cout<<"Rojo"<<endl;
	}else{
		cout<<"Negro"<<endl;
    }
		
	cout<<"Paridad: ";
	if(num.paridad==1){
		cout<<"Impar"<<endl;
	}else{
		cout<<"Par"<<endl;
    }
		
	cout<<"Columna: ";
	if(num.columna==1){
		cout<<"1ra Columna"<<endl;
	}else{
		if(num.columna==2)
		cout<<"2da Columna"<<endl;
		else
		cout<<"3ra Columna"<<endl;	
	}	
	cout<<"Docena: ";
	if(num.docena==1){
		cout<<"1ra Docena"<<endl;
	}else{
		if(num.docena==2)
		cout<<"2da Docena"<<endl;
		else
		cout<<"3ra Docena"<<endl;
	}
	cout<<"Mitad: ";
	if(num.mitad==1){
		cout<<"1ra Mitad"<<endl;
	}else {
		cout<<"2da Mitad"<<endl;
	}
	cout<<"********************"<<endl;
}

//Muestra Lista del Tapete
void mostrar_Tapete(ttapete lista){
	ptapete i;
	if(lista.inicio!=NULL){
		for(i=lista.inicio;i!=NULL;i=i->sig)
  				mostrar_Nro_Tapete(i->dato);
	}else{
		cout<< "\n LISTA VACIA"<<endl;
	}
}

void mostrarNumGanador(ptapete t){
	mostrar_Nro_Tapete(t->dato);
}

//------------------------------------------------JUGADOR------------------------------------------------//

//Genera Id Automaticamente 
int generarid( fjugador fj ){
tjugador a;
int aux=0;	
	fj=fopen("jugador.txt","rb"); //Abre el Archivo en modo sólo lectura, archivo debe existir
	if(fj!=NULL){
		while (!feof(fj)){
		    fread(&a,sizeof(a),1,fj);
		    if (!feof(fj))
		       aux=a.id;
        }
	}
	fclose (fj);
    return aux;	//Retorna 0 si no hay Jugadores sino retorna el ultimo Id    
}

//Carga los Datos del Jugador
void cargarjugador(tjugador &j, fjugador fj){ 
bool band=true;
	j.id=generarid(fj) + 1;
	cout << "\nNombre: ";
	cin >> j.nombre;
	cout << "\nApellido: ";
	cin >> j.apellido;
	do{
        cout << "\nMonto: $ ";
		cin >> j.monto;	
	    if(j.monto>=0){
	    	band=false;
		}else{
			cout <<"\n----------Debe Ingrasar Monto Mayores a 0----------"<<endl;
		}
	}while(band!=false);
	 j.ganancia=0;
}

//Guarda los Datos del Registro(j) a un Archivo(fj)
void alta_jugador(fjugador fj){
	tjugador j;
	char opc;
        fj=fopen("jugador.txt","ab"); //Apertura en modo de agregar.Si el archivo existe,los datos se agregan al final del archivo,en caso contrario,el archivo se crea
			cargarjugador(j,fj);      //Ingresa datos del Jugador al archivo
			fwrite(&j,sizeof(j),1,fj); //Escribe del Registro Numero(j) información al Archivo(fj)
		fclose (fj);
}

//Muestra los Jugadores Cargados 
void mostrar_jugador(tjugador j){
	cout <<"----------------------"<<endl;
	cout << "\nId Jugador: " << j.id << endl;
	cout << "\nNombre: " << j.nombre << endl;
	cout << "\nApellido : " << j.apellido << endl;
	cout << "\nMonto : $ " << j.monto << endl;
	cout <<"----------------------"<<endl;
}

//Lista los Jugadores almacenados en el Archivo(fj)
void listar_jugador(fjugador fj){ 
tjugador j;
	fj=fopen("jugador.txt","rb");
	if(fj==NULL){
	   cout << "\nEl ARCHIVO NO EXISTE" << endl;
	}else{
		while(!feof(fj)){ 
			fread(&j,sizeof(j),1,fj); //Lee información almacenada en un Archivo(fj) y se guarda en un Registro(j)
			if (!feof(fj))             //feof: si se alcanzó el final de un archivo
			mostrar_jugador(j);        //Muestra Jugadores
		}
	 }
	fclose(fj);    //Cierra Archivo
}

//Realiza la consulta de por Jugador
void consulta_jugador(fjugador fj,int id){ 
tjugador j;
bool existe=false;
fj=fopen("jugador.txt","rb");
if(fj==NULL){
   cout << "\nEl ARCHIVO NO EXISTE" << endl;
}else{
    while(!feof(fj) && !existe){ 
		fread(&j,sizeof(j),1,fj);     //Lee información almacenada en un Archivo(fj) y se guarda en un Registro(j)
		if (!feof(fj) && id==j.id){ 
			mostrar_jugador( j);     //Muestra un Solo Jugador
			existe=true;
		}
    }	
}
if(!existe){
   cout << "\nEl JUGADOR INEXISTENTE" << endl;	
}
fclose(fj);
}

//Valida el Monto del Jugador
void validarModificacion(tjugador &j){
int op;
float monto;
   cout<<"\nMonto Actual: $"<<j.monto<<endl;
   cout<<"\n\t--------------Modificar Monto--------------"<<endl;
   cout<<"\n1-Agregar: $                     2-Quitar: $"<<endl;
   cin>>op;
   if(op==1){
       cout<<"\nAgregar Monto: $";
       cin>>monto;
       j.monto=j.monto+monto;	
   }else{
   	   cout<<"\nQuitar Monto: $";
       cin>>monto;
       if(j.monto>=monto){
         j.monto=j.monto-monto;		
	   }else{
	   	 if(j.monto==0){
	   	 	  cout<<"\n*******No tiene Monto Suficiente para Quitar*******"<<endl;
	   	 	  cout<<"\nMonto: $"<<0<<endl;
         }else{
         	cout<<"\n*******No tiene Monto Suficiente para Quitar*******"<<endl;
         	cout<<"\nMonto: $"<<j.monto<<endl;
		 }	   	 
	   }
   }   
   cout<<"\n************Monto Modificado Exitosamente************"<<endl;
   cout<<"\nMonto Actualizado: $"<<j.monto<<endl;	
}

void modificar_jugador(fjugador fj,int id){ 
tjugador j;
bool existe=false;
fj=fopen("jugador.txt","rb+");   //Abre el Archivo en en modo de lectura/escritura. El archivo debe existir.
if(fj==NULL){
     cout << "El ARCHIVO del JUGADOR NO EXISTE" << endl;
}else{
     while(!feof(fj) && !existe){ 
		fread(&j,sizeof(j),1,fj);    //Lee información almacenada en un Archivo(fj) y se guarda en un Registro(j)
		if (!feof(fj) && id==j.id)
		    existe=true;
     }	
}
if(existe==true){
   mostrar_jugador(j);
   validarModificacion(j);
   fseek(fj,-sizeof(j),1);    //fseek  Ubica el puntero en una posición específica del archivo
   fwrite(&j,sizeof(j),1,fj);  //Escribe del Registro Numero(a) información al Archivo(f)
}else{
 cout << "\n El JUGADOR INEXISTENTE" << endl;	
}
fclose(fj);
}


//Procedimiento Inicializa el Arbol
void iniciar_Arbol_Jugador(parbol &a){
	a=NULL;
}

//Procedimiento Crea Nodo
void crearNodoArbolJugador(parbol &nuevo, tjugador j){
 	nuevo=new tarbol;
 	if(nuevo!=NULL){
	    nuevo->dato=j;
        nuevo->izq=NULL;
        nuevo->der=NULL;
	}else{
		cout<<"MEMORIA INSUFICIENTE"<<endl;}
}

//Procedimiento Agregar Nodo al Arbol
void insercion_Arbol_Jugador(parbol & a,parbol nuevo) { 
   if (a==NULL){
   	  a=nuevo; 
   }else {
      if (nuevo->dato.ganancia < a->dato.ganancia) {
   	   	  insercion_Arbol_Jugador(a->izq,nuevo); 
	  }else{
          insercion_Arbol_Jugador(a->der,nuevo); 
	  }     
   }    
}
//Muestra los Jugadores en Orden Decreciente por ganancia
void orden_Decreciente(parbol a){ 
  if(a!=NULL){ 
    orden_Decreciente(a->der);
    mostrar_jugador(a->dato);
	orden_Decreciente(a->izq);
  }
}

//Carga un jugador a un arbol
void listarJugadorArbol(fjugador fj, parbol &a ){
tjugador j;
parbol nuevo;
fj=fopen("jugador.txt","rb");
if(fj==NULL){
	cout << "\nEl ARCHIVO NO EXISTE" << endl;
}else{
     while (!feof(fj)){
	    fread(&j,sizeof(j),1,fj);
	    if (!feof(fj)){
	     crearNodoArbolJugador(nuevo,j);
	     insercion_Arbol_Jugador(a,nuevo);	
		}	
    }
    orden_Decreciente(a);
}
}

//Lista Jugadores e Invita a Jugar
void listarJugadorHabilitado(fjugador fj, tlista &l ){
tjugador j;
char resp;
pnodo nuevo;
fj=fopen("jugador.txt","rb");
if(fj==NULL){
	cout << "\nEl ARCHIVO NO EXISTE" << endl;
}else{
     while (!feof(fj)){
	    fread(&j,sizeof(j),1,fj); //Lee información almacenada en un Archivo(fj) y se guarda en un Registro(j)
	    if (!feof(fj)){
	    	if(j.monto>0){
	    		cout<<"\nBienvenido Jugador: "<<j.apellido<<" ID: "<< j.id <<endl;
	    		cout<<"\nDesea Participar en el Juego S/N? ";
				cin>>resp; 
	     		if(resp=='S'||resp=='s'){
	     			crearNodoJugadorParticipante(nuevo,j);
	     			insertarFinalParticipante(l,nuevo);
    			    cout << "\n ** Jugador Acepto Invitacion **"<<endl;
				 }else{
				 	cout << "\n ** Jugador NO Acepto Invitacion **"<<endl;
				 }
			}	
		}	
    }
    mostrarParticipantes(l);
    system("pause");
}}

//Inicializa Lista de Jugadores que acpetaron la invitacion para Jugar
void iniciarListaParticipante(tlista &l){
	l.inicio=NULL;
	l.final=NULL;
}

//Crea Nodo de Jugadores que acpetaron la invitacion para Jugar
void crearNodoJugadorParticipante(pnodo &nuevo, tjugador j){
	nuevo = new tnodo;
	if(nuevo!=NULL){
		nuevo->dato = j;
		nuevo->sig = NULL;
	}else{
		cout << "MEMORIA INSUFICIENTE";
	}
}

//Agrega Jugadores que acpetaron la invitacion para Jugar
void insertarFinalParticipante(tlista &l, pnodo nuevo){
	if(l.inicio==NULL){
		l.inicio=nuevo;
		l.final=nuevo;
	}else{
		l.final->sig=nuevo;
		l.final=nuevo;
	}
}

//Muestra Jugadores que acpetaron la invitacion para Jugar
void mostrarParticipantes(tlista l){
	pnodo i;
	if(l.inicio!=NULL){
		for(i=l.inicio;i!=NULL;i=i->sig){
			mostrar_jugador(i->dato);
		}
	}else{
		cout<<"\n NO hay Participante para Jugar"<<endl;
	}
}

//------------------------------------------------APUESTA------------------------------------------------//
//Carga jugador que aceptaron jugar y sus apuestas
void apuestaParticipante(tlista l,tlistaApuesta &ap){
	pnodo i;
	tapuestas apuesta;
	int disponible;
    int nroapuesta,nromonto;
    papuesta nuevo;
    
	if(l.inicio!=NULL){
		for(i=l.inicio;i!=NULL;i=i->sig){
			cout << "\nREALICE SUS APUESTAS ..."<<endl;
			cout <<"\n** Apuestas del Jugador "<< i->dato.nombre << " (ID "<< i->dato.id<< ") **"<<endl;
			apuesta.jugador=i->dato;//guarda el jugardor en un campo de la lista
			disponible=i->dato.monto;//toma el Valor del Monto total del jugador
	
			if(disponible>0){
					apuesta_nro(apuesta,disponible);
					cout<<"\nDisponible: "<<disponible<<endl;
					if(disponible>0){
						apuesta_color(apuesta,disponible);
					    cout<<"\nDisponible: "<<disponible<<endl;
					    if(disponible>0){
					    	apuesta_paridad(apuesta,disponible);
							cout<<"\nDisponible: "<<disponible<<endl;
							if(disponible>0){
								apuesta_docena(apuesta,disponible);
								cout<<"\nDisponible: "<<disponible<<endl;
								if(disponible>0){
									apuesta_columna(apuesta,disponible);
									cout<<"\nDisponible: "<<disponible<<endl;
									if(disponible>0){
										apuesta_mitad(apuesta,disponible);
										cout<<"\nDisponible: "<<disponible<<endl;
										crearNodoApuesta(nuevo,apuesta);
										insertarFinalListaApuesta(ap,nuevo);
									}
								}
							}
						}
					}
			}else{
				cout << "No tiene monto Disponible..."<<endl;
			}		
									
	}
	cout <<"\n...........No va mas.................."<<endl;
	
	mostrarApuestas(ap);
	
}
}
//ingresa monto por cada apuesta
void apuesta_monto(int &x, int &disponible){
	int nromonto;
	bool band=false;
	do{
		cout<<"\nIngrese Monto: $";
		cin>>nromonto;
		if(nromonto<=disponible){
			disponible=disponible-nromonto;
			x=nromonto;//Asigna a los Diferentes montos de Apuestas(monto nro, monto color.....)
			band=true;
		}else{
			cout<<"\nUsted ah ingresado un monto mayor al que posee"<<endl;
		}
	}while(!band);	
}

//Apuesta Numero
void apuesta_nro(tapuestas &apuesta, int &disponible){
	int nro;
	bool band;
	do{
		cout<<"\nSeleccionar Numero: ";
		cin>>nro;
		if(nro>=0 && nro<=36){
			apuesta.apuesta_nro=nro;
			band=true;
		}else{
			cout<<"\nEl Numero Apostado debe estar entre 0-36"<<endl;
		}
	}while(!band);
	apuesta_monto(apuesta.monto_nro,disponible);	
}

//Apuesta por Color
void apuesta_color(tapuestas &apuesta, int &disponible){
	int color;
	bool band=false;
	do{
		cout<<"\nSeleccionar Color (0- ninguno, 1- negro, 2- rojo): ";
		cin>> color;
		if(color==0){
			apuesta.apuesta_color=color;
			apuesta.monto_color=color;
			band=true;
		}else{
			if(color >0 && color<=2){
				apuesta.apuesta_color=color;
				apuesta_monto(apuesta.monto_color, disponible);
				band=true;
			}else{
				cout<<"\nError, ha ingresado un valor no permitido. Intente nuevamente"<<endl;
			}
		}
	}while(!band);
}

//Apuesta por  Paridad
void apuesta_paridad(tapuestas &apuesta, int &disponible){
	int paridad;
	bool band=false;
	do{
		cout<<"\nSeleccionar Paridad (0- ninguno, 1- impar, 2- par): ";
		cin>> paridad;
		if(paridad==0){
			apuesta.apuesta_paridad=paridad;
			apuesta.monto_paridad=paridad;
			band=true;
		}else{
			if(paridad>0 && paridad<=2){
				apuesta.apuesta_paridad=paridad;
				apuesta_monto(apuesta.monto_paridad, disponible);
				band=true;
			}else{
				cout<<"\nError, ha ingresado un valor no permitido. Intente nuevamente"<<endl;
			}
		}
	}while(!band);
}

//Apuesta por  Docena
void apuesta_docena(tapuestas &apuesta, int &disponible){
	int docena;
	bool band=false;
	do{
		cout<<"\nSeleccionar Docena (0- ninguna, 1- primera, 2- segunda, 3- tercera): ";
		cin>> docena;
		if(docena==0){
			apuesta.apuesta_docena=docena;
			apuesta.monto_docena=docena;
			band=true;
		}else{
			if(docena>0 && docena<=3){
				apuesta.apuesta_docena=docena;
				apuesta_monto(apuesta.monto_docena, disponible);
				band=true;
			}else{
				cout<<"\nError, ha ingresado un valor no permitido. Intente nuevamente"<<endl;
			}
		}
	}while(!band);
}

//Apuesta por  Columna
void apuesta_columna(tapuestas &apuesta, int &disponible){
	int columna;
	bool band=false;
	do{
		cout<<"\nSeleccionar columna (0- ninguna, 1- primera, 2- segunda, 3- tercera): ";
		cin>> columna;
		if(columna==0){
			apuesta.apuesta_columna=columna;
			apuesta.monto_columna=columna;
			band=true;
		}else{
			if(columna>0 && columna<=3){
				apuesta.apuesta_columna=columna;
				apuesta_monto(apuesta.monto_columna, disponible);
				band=true;
			}else{
				cout<<"\nError, ha ingresado un valor no permitido. Intente nuevamente"<<endl;
			}
		}
	}while(!band);
}

//Apuesta por Mitad
void apuesta_mitad(tapuestas &apuesta, int &disponible){
	int mitad;
	bool band=false;
	do{
		cout<<"\nSeleccionar mitad (0- ninguna, 1- primera, 2- segunda): ";
		cin>> mitad;
		if(mitad==0){
			apuesta.apuesta_mitad=mitad;
			apuesta.monto_mitad=mitad;
			band=true;
		}else{
			if(mitad>0 && mitad<=2){
				apuesta.apuesta_mitad=mitad;
				apuesta_monto(apuesta.monto_mitad, disponible);
				band=true;
			}else{
				cout<<"\nError, ha ingresado un valor no permitido. Intente nuevamente"<<endl;
			}
		}
	}while(!band);
}

//Lista Apuestas
void iniciarListaApuesta(tlistaApuesta &l){
	l.inicio=NULL;
	l.final=NULL;
}

void crearNodoApuesta(papuesta &nuevo, tapuestas a){
	nuevo = new tnodoApuesta;
	if(nuevo!=NULL){
		nuevo->dato = a;
		nuevo->sig = NULL;
	}else{
		cout << "MEMORIA INSUFICIENTE";
	}
}
void insertarFinalListaApuesta(tlistaApuesta &l, papuesta nuevo){
	if(l.inicio==NULL){
		l.inicio=nuevo;
		l.final=nuevo;
	}else{
		l.final->sig=nuevo;
		l.final=nuevo;
	}
}

void mostrarApuestas(tlistaApuesta l){
	papuesta i;
	if(l.inicio!=NULL){
		for(i=l.inicio;i!=NULL;i=i->sig){
			mostrar_Apuesta(i->dato);
		}
	}else{
		cout<<"\n NO hay Participante para Jugar"<<endl;
	}
}


void mostrar_Apuesta(tapuestas a){
	cout <<"----------------------"<<endl;
	cout << "\nId Jugador: " << a.jugador.id << endl;
	cout << "\nNombre: " << a.jugador.nombre << endl;
	cout << "\nApellido : " << a.jugador.apellido << endl;
	cout << "\nNumero de Apuesta : " << a.apuesta_nro << endl;
	cout <<"----------------------"<<endl;
}

 ptapete buscarTapete(ttapete t, int x){//busca en el tapete el nro
	ptapete i;
	bool existe=false;
	for(i=t.inicio;existe==false&& i!=NULL;i=i->sig){
		if(i->dato.numero==x){
			existe=true;
		}
	}
	return i;
}

//Muestra Numero Ganador y sus campos
void mostrar_Nro_Tapete_Ganador(ptapete t){
	cout<<"NUMERO GANADOOOOR !!!--> --> "" "<<t->dato.numero<<" "" <-- <--"<<endl;
	cout<<"Color: ";
	if(t->dato.color==1){
		cout<<"Rojo"<<endl;
	}else{
		cout<<"Negro"<<endl;
    }
		
	cout<<"Paridad: ";
	if(t->dato.paridad==1){
		cout<<"Impar"<<endl;
	}else{
		cout<<"Par"<<endl;
    }
		
	cout<<"Columna: ";
	if(t->dato.columna==1){
		cout<<"1ra Columna"<<endl;
	}else{
		if(t->dato.columna==2)
		cout<<"2da Columna"<<endl;
		else
		cout<<"3ra Columna"<<endl;	
	}	
	cout<<"Docena: ";
	if(t->dato.docena==1){
		cout<<"1ra Docena"<<endl;
	}else{
		if(t->dato.docena==2)
		cout<<"2da Docena"<<endl;
		else
		cout<<"3ra Docena"<<endl;
	}
	cout<<"Mitad: ";
	if(t->dato.mitad==1){
		cout<<"1ra Mitad"<<endl;
	}else {
		cout<<"2da Mitad"<<endl;
	}
	cout<<"********************"<<endl;
}

//Busca el Jugador Ganador entre lista de Jugadores que quisieron participar y guarda su monto actualizado
void ganador(tlistaApuesta &l, ptapete a, fjugador fj){//l jugadores quisieron jugar,     a  registro del numero ganador en el tapete
	papuesta i;
	int ganancia=0, montoApostado=0, cantidadApostada=0;
	bool existe=false;
	for(i=l.inicio;existe==false && i!=NULL; i=i->sig){ // i contiene primer jugador y recorre lista
	
		if(i->dato.apuesta_nro==a->dato.numero){
			montoApostado=montoApostado+i->dato.monto_nro;//Suma su monto que aposto
		}
		if(i->dato.apuesta_color==a->dato.color){
			montoApostado=montoApostado+i->dato.monto_color;
		}
		if(i->dato.apuesta_columna==a->dato.columna){
			montoApostado=montoApostado+i->dato.monto_columna;
		}
		if(i->dato.apuesta_docena==a->dato.docena){
			montoApostado=montoApostado+i->dato.monto_docena;
		}
					      
		if(i->dato.apuesta_mitad==a->dato.mitad){
			montoApostado=montoApostado+i->dato.monto_mitad;
		}
					          
		if(i->dato.apuesta_paridad==a->dato.paridad){
			montoApostado=montoApostado+i->dato.monto_paridad;
	    }	                      
  
			ganancia=montoApostado*2; //ganancia es la suma de todas la apuestas ganadas 
			cantidadApostada=i->dato.monto_nro+i->dato.monto_columna+i->dato.monto_docena+i->dato.monto_mitad+i->dato.monto_color+i->dato.monto_paridad; //Suma de Todas la Apuestas
			modificar_jugador_ganador(fj,i->dato.jugador.id, cantidadApostada, ganancia);
			cout << "Jugador " << i->dato.jugador.nombre << ": Ganaste " << ganancia << " pesos" << endl ;
		}
}

//Modifica el monto del Jugador en el Acrhivo
void modificar_jugador_ganador(fjugador fj,int id, int totalApos, int ganancia){ 
tjugador j;
bool existe=false;
fj=fopen("jugador.txt","rb+");   //Abre el Archivo en en modo de lectura/escritura. El archivo debe existir.
if(fj==NULL){
     cout << "El ARCHIVO del JUGADOR NO EXISTE" << endl;
}else{
     while(!feof(fj) && !existe){ 
		fread(&j,sizeof(j),1,fj);    //Lee información almacenada en un Archivo(fj) y se guarda en un Registro(j)
		if (!feof(fj) && id==j.id)
		    existe=true;
     }	
}
if(existe==true){
   //mostrar_jugador(j);
   j.monto = j.monto-totalApos;
   j.monto = j.monto+ganancia;
   fseek(fj,-sizeof(j),1);    //fseek  Ubica el puntero en una posición específica del archivo
   fwrite(&j,sizeof(j),1,fj);  //Escribe del Registro Numero(a) información al Archivo(f)
}else{
 cout << "\n El JUGADOR INEXISTENTE" << endl;	
}
fclose(fj);
}

//-----------------------------------------------Liberacion de Nodo-----------------------------
//RUlETA
pruleta quitar_inicio(truleta &lista){
	pruleta borrado;
	if(lista.inicio==NULL){
		borrado=NULL;
	}else{
		if(lista.inicio==lista.final){
			borrado=lista.inicio;
			lista.inicio=NULL;
			lista.final=NULL;
		}else{
			borrado=lista.inicio;
			lista.inicio=borrado->sig;
			borrado->sig=NULL;
			lista.inicio->ant=NULL;
			borrado->ant=NULL;
			lista.final->sig=lista.inicio;
			lista.inicio->ant=lista.final;
		}
	}
	return borrado;
}

void Liberar(truleta &lista){
	while(lista.inicio!=NULL){
		 delete(quitar_inicio(lista));	
    }
}


//TAPETE

ptapete quitar_final(ttapete &lista){
	ptapete borrado,i;
	if(lista.inicio==NULL){
		borrado=NULL;
	}else{
		if (lista.inicio==lista.final){
	      borrado = lista.inicio;
	      lista.inicio = NULL;
	      lista.final = NULL;
	    }else{
	      for (i=lista.inicio;(i->sig)->sig!=NULL;i=i->sig);
	      borrado = lista.final;
	      lista.final = i;
	      lista.final->sig = NULL;
	    }	
	}
	return borrado;
}

void LiberarTapete(ttapete &lista){
	 while(lista.inicio!=NULL){	  	
	  	delete(quitar_final(lista));
	  }
}


//ARBOL
parbol quitarArbol(parbol &a) { 
parbol aux;
   if (a==NULL){
   	  aux=NULL;
   }else {
     if(a->izq!=NULL){
     	quitarArbol(a->izq);
	 }else{
	 	if(a->der!=NULL){
	 		quitarArbol(a->der);
		 }else{
		 	aux=a;
		 	a=NULL;
		 }
	 }
     
   }
   return aux;    
}

void LiberarArbol(parbol &a){
	 while(a!=NULL){	  	
	  	delete(quitarArbol(a));
	  }
}