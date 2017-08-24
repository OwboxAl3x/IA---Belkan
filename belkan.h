
#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
#include <cstdlib>
#include "conexion.h"
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
		srand (time(NULL));
		x_= 99;
		y_= 99;
		orientacion_=3;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false;
		size_=200;

		valorF, valorI, valorD=0;
		cojoRegalo = false, darRegalo = false;

		for (int i=0;i<200;i++)
		    for(int j=0;j<200;j++){
		      mapa_entorno_[i][j]='?';
		      mapa_objetos_[i][j]='?';

		      matriz_pulgarcito[i][j]=0;

		    }

		for (int i=0;i<100;i++)
		    for(int j=0;j<100;j++){
		      mapa_solucion_[i][j]='?';
		  	  mataux[i][j]='?';
		  	}

	}

	enum ActionType
	{
	    actFORWARD, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};

	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	void PasarVectoraMatrizPulgarcito(int fila, int columna, int m[200][200], char *v, int brujula);
	void loQueLlevoASolucion();
	ActionType Think();
	ActionType andarAleatorio();
	ActionType andarPulgarcito();
	ActionType persiguelo(char *donde, char cosa);
	ActionType entrarCastillos();
	bool PuedeAndar();
	bool NPCDelante();
	bool estaCosa(char *donde, char cosa, int &enCual);
	bool pisoRegalo();
	bool tengoRegalo();
	bool hayFamoso();
	bool regaloEnMano();
	bool tengoBikini();
	ActionType ponerEnUso(char cosa1);
	void extraerCoord(int &filas, int &columnas);
	void girarMatSol(int dir);
	int calcOrientacion();
	void comenzarMapa();
	void actualizarSolucion(int direntorno);
	void FixLastAction(Agent::ActionType x){last_accion_=x;};

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_solucion_[100][100]; // Mapa que almacena la solucion que el alumno propone
	int matriz_pulgarcito[200][200];
	int mataux[100][100];
	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};


private:
	//Variables de interaccion con el entorno grafico
	int size_;	

	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;

	//Variables de estado
	int x_,y_, orientacion_;
	int xs, ys, os;
	int valorF, valorI, valorD;
	int puede, nopuede;
	bool cojoRegalo, darRegalo;
	int k1[2], k1c[2], k2[2], k2c[2];
	int last_accion_;
	string role_;

};

string ActionStr(Agent::ActionType);

#endif
