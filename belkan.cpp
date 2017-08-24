#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

bool aporK = false, aporZap = false, aporBik = false, aporLlave = false, aporPuerta = false, intercambio = false;
bool primeraVez = true;
int avanza = 0, giro = 0, Kvista = 0, enCual, contInter = 0, cont = 0, pasos = 20000;
int filmenos, colmenos, direntorno = 0;
char sentido;

// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}

// PasarVectorMatrizPulgarcito(y_, x_, matriz_pulgarcito, VISTA_, orientacion_)
void Agent::PasarVectoraMatrizPulgarcito(int fila, int columna, int m[200][200], char *v, int brujula){

    switch(brujula){
        case 0: // Orientacion Norte

        	if(v[1]=='D' or v[1]=='M' or v[1]=='P' or NPCDelante()){

    				m[fila-1][columna]=100;

    			}else if(v[1]=='B' and EN_USO_!='6'){

    				m[fila-1][columna]=110;

    			}else if(v[1]=='A' and EN_USO_!=0){

    				m[fila-1][columna]=105;

			}

			for (int i=0; i<3; i++){

				if(v[2+i]=='D' or v[2+i]=='M' or v[2+i]=='P'){

					m[fila-2][columna+i-1]=100;

				}else if((v[2+i]=='B' and EN_USO_!='6')){

					m[fila-2][columna+i-1]=110;

				}else if(v[2+i]=='A' and EN_USO_!=0){

					m[fila-2][columna+i-1]=105;

				}


			}

			for (int j=0; j<5; j++){

				if(v[5+j]=='D' or v[5+j]=='M' or v[5+j]=='P'){

					m[fila-3][columna+j-2]=100;

				}else if(v[5+j]=='B' and EN_USO_!='6'){

					m[fila-3][columna+j-2]=110;

				}else if(v[5+j]=='A' and EN_USO_!=0){

					m[fila-3][columna+j-2]=105;

				}

			}
		        break;
		case 1: // Orientacion Este

			if(v[1]=='D' or v[1]=='M' or v[1]=='P' or NPCDelante()){

				m[fila][columna+1]=100;

			}else if(v[1]=='B' and EN_USO_!='6'){

				m[fila][columna+1]=110;

			}else if(v[1]=='A' and EN_USO_!=0){

				m[fila][columna+1]=105;

			}

			for (int i=0; i<3; i++){

				if(v[2+i]=='D' or v[2+i]=='M' or v[2+i]=='P'){

					m[fila+i-1][columna+2]=100;

				}else if(v[2+i]=='B' and EN_USO_!='6'){

					m[fila+i-1][columna+2]=110;

				}else if(v[2+i]=='A' and EN_USO_!=0){

					m[fila+i-1][columna+2]=105;

				}

			}
			for (int j=0; j<5; j++){

				if(v[5+j]=='D' or v[5+j]=='M' or v[15+j]=='P'){

					m[fila+j-2][columna+3]=100;

				}else if(v[5+j]=='B' and EN_USO_!='6'){

					m[fila+j-2][columna+3]=110;

				}else if(v[5+j]=='A' and EN_USO_!=0){

					m[fila+j-2][columna+3]=105;

				}

			}
		        break;
        case 2: // Orientacion Sur

        	if(v[1]=='D' or v[1]=='M' or v[1]=='P' or NPCDelante()){

				m[fila+1][columna]=100;

			}else if(v[1]=='B' and EN_USO_!='6'){

				m[fila+1][columna]=110;

			}else if(v[1]=='A' and EN_USO_!=0){

				m[fila+1][columna]=105;

			}

			for (int i=0; i<3; i++){

				if(v[2+i]=='D' or v[2+i]=='M' or v[2+i]=='P'){

					m[fila+2][columna+1-i]=100;

				}else if(v[2+i]=='B' and EN_USO_!='6'){

					m[fila+2][columna+1-i]=110;

				}else if(v[2+i]=='A' and EN_USO_!=0){

					m[fila+2][columna+1-i]=105;

				}

			}
			for (int j=0; j<5; j++){

				if(v[5+j]=='D' or v[5+j]=='M' or v[5+j]=='P'){

					m[fila+3][columna+2-j]=100;

				}else if(v[5+j]=='B' and EN_USO_!='6'){

					m[fila+3][columna+2-j]=110;

				}else if(v[5+j]=='A' and EN_USO_!=0){

					m[fila+3][columna+2-j]=105;

				}

			}
			    break;
        case 3: // Orientacion Oeste

        	if(v[1]=='D' or v[1]=='M' or v[1]=='P' or NPCDelante()){

				m[fila][columna-1]=100;

			}else if(v[1]=='B' and EN_USO_!='6'){

				m[fila][columna-1]=110;

			}else if(v[1]=='A' and EN_USO_!=0){

				m[fila][columna-1]=105;

			}

			for (int i=0; i<3; i++){

				if(v[2+i]=='D' or v[2+i]=='M' or v[2+i]=='P'){

					m[fila+1-i][columna-2]=100;

				}else if(v[2+i]=='B' and EN_USO_!='6'){

					m[fila+1-i][columna-2]=110;

				}else if(v[2+i]=='A' and EN_USO_!=0){

					m[fila+1-i][columna-2]=105;

				}

			}

			for (int j=0; j<5; j++){

				if(v[5+j]=='D' or v[5+j]=='M' or v[5+j]=='P'){

					m[fila+2-j][columna-3]=100;

				}else if(v[5+j]=='B' and EN_USO_!='6'){

					m[fila+2-j][columna-3]=110;

				}else if(v[5+j]=='A' and EN_USO_!=0){

					m[fila+2-j][columna-3]=105;

				}

			}

                break;
    }

}

// PasarVectoraMapaSolucion(y_, x_, mapa_solucion_, VISTA_, orientacion_);

// -----------------------------------------------------------
void PasarVectoraMapaSolucion(int fila, int columna, char m[100][100], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}

// -----------------------------------------------------------
void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}


// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}

// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
	if (REINICIADO_){
		// Lo que tengas que hacer si eres reposicionado en el juego
		for(int i=0; i<200; i++)
			for(int j=0; j<200; j++){

				mapa_entorno_[i][j] = '?';
				mapa_objetos_[i][j] = '?';
				matriz_pulgarcito[i][j] = 0;

			}

		x_=99;
		y_=99;
		orientacion_=3;
		Kvista=0;
		primeraVez=true;

	}

	switch(last_accion_){
	  case 0: //avanzar
	  switch(orientacion_){
	    case 0: // norte
		    y_--;
		    break;
	    case 1: // este
		    x_++;
		    break;
	    case 2: // sur
		    y_++;
		    break;
	    case 3: // oeste
		    x_--;
		    break;
	  }
	  break;
	  case 1: // girar izq
		  orientacion_=(orientacion_+3)%4;
		  break;
	  case 2: // girar dch
		  orientacion_=(orientacion_+1)%4;
		  break;
	}

	// Comprobacion para no salirme del rango del mapa
	bool algo_va_mal=false;
	if (y_<0){
		y_=0;
		algo_va_mal=true;
	}
	else if (y_>199){
		y_=199;
		algo_va_mal=true;
	}
	if (x_<0){
		x_=0;
		algo_va_mal=true;
	}
	else if (x_>199){
		x_=199;
		algo_va_mal=true;
	}

	if (algo_va_mal){
		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
	}

	if(MENSAJE_=="Has chocado con un obstaculo movil. "){

		if(orientacion_==0){

			y_++;

		}else if(orientacion_==1){

			x_--;

		}else if(orientacion_==2){

			y_--;

		}else if(orientacion_==3){

			x_++;

		}

	}

	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);

	// Pulgarcito ---------------------------------------------------------------------

	PasarVectoraMatrizPulgarcito(y_, x_, matriz_pulgarcito, VISTA_, orientacion_);

	if(orientacion_==0){

		valorF = matriz_pulgarcito[y_-1][x_];
		valorI = matriz_pulgarcito[y_][x_-1];
		valorD = matriz_pulgarcito[y_][x_+1];

	}else if(orientacion_==1){

		valorF = matriz_pulgarcito[y_][x_+1];
		valorI = matriz_pulgarcito[y_-1][x_];
		valorD = matriz_pulgarcito[y_+1][x_];


	}else if(orientacion_==2){

		valorF = matriz_pulgarcito[y_+1][x_];
		valorI = matriz_pulgarcito[y_][x_+1];
		valorD = matriz_pulgarcito[y_][x_-1];

	}else if(orientacion_==3){

		valorF = matriz_pulgarcito[y_][x_-1];
		valorI = matriz_pulgarcito[y_+1][x_];
		valorD = matriz_pulgarcito[y_-1][x_];

	}

	if(last_accion_==0){

		matriz_pulgarcito[y_][x_]+=1;

	}

	cout << " " << valorI << " " << valorF << " " << valorD << " ";

	//------------------------------------------------------------------------

	env->ActualizarMatrizUsuario(mapa_entorno_);

}

// -----------------------------------------------------------
void Agent::actualizarSolucion(int direntorno){

	if(primeraVez){

		if(os==0){

			ys++;

		}else if(os==1){

			xs--;

		}else if(os==2){

			ys--;

		}else if(os==3){

			xs++;

		}

	}

	switch(direntorno){
		case 0: // Norte -> direccion a la que apunta mapa_entorno_
			switch(last_accion_){
			  case 0: //avanzar
			  switch(orientacion_){
			    case 0: // norte
				    ys--;
				    break;
			    case 1: // este
				    xs++;
				    break;
			    case 2: // sur
				    ys++;
				    break;
			    case 3: // oeste
				    xs--;
				    break;
			  }
			  break;
			  case 1: // girar izq
				  os=(os+3)%4;
				  break;
			  case 2: // girar dch
				  os=(os+1)%4;
				  break;
			}
				break;
		case 1: // Este --> direccion a la que apunta mapa_entorno_
			switch(last_accion_){
			  case 0: //avanzar
			  switch(orientacion_){
			    case 0: // norte
				    xs++;
				    break;
			    case 1: // este
				    ys++;
				    break;
			    case 2: // sur
				    xs--;
				    break;
			    case 3: // oeste
				    ys--;
				    break;
			  }
			  break;
			  case 1: // girar izq
				  os=(os+3)%4;
				  break;
			  case 2: // girar dch
				  os=(os+1)%4;
				  break;
			}
				break;
		case 2: // Sur --> direccion a la que apunta mapa_entorno_
			switch(last_accion_){
			  case 0: //avanzar
			  switch(orientacion_){
			    case 0: // norte
				    ys++;
				    break;
			    case 1: // este
				    xs--;
				    break;
			    case 2: // sur
				    ys--;
				    break;
			    case 3: // oeste
				    xs++;
				    break;
			  }
			  break;
			  case 1: // girar izq
				  os=(os+3)%4;
				  break;
			  case 2: // girar dch
				  os=(os+1)%4;
				  break;
			}
				break;
		case 3: // Oeste --> direccion a la que apunta mapa_entorno_
			switch(last_accion_){
			  case 0: //avanzar
			  switch(orientacion_){
			    case 0: // norte
				    xs--;
				    break;
			    case 1: // este
				    ys--;
				    break;
			    case 2: // sur
				    xs++;
				    break;
			    case 3: // oeste
				    ys++;
				    break;
			  }
			  break;
			  case 1: // girar izq
				  os=(os+3)%4;
				  break;
			  case 2: // girar dch
				  os=(os+1)%4;
				  break;
			}
				break;

	}

	if(primeraVez){

	 	if(direntorno==1){

			os = (orientacion_+1)%4;

		}else if(direntorno==2){

			os = (orientacion_+2)%4;

		}else if(direntorno==3){

			os = (orientacion_+3)%4;

		}else os = orientacion_;

		primeraVez = false;

	}



}

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	Agent::ActionType accion;

	if(estaCosa(VISTA_, 'K', enCual) and  Kvista<2){

		aporK = true;

	}else if(estaCosa(SURFACE_, '6', enCual) and EN_USO_!='6' and !aporK){

		aporZap = true;

	}else if(estaCosa(SURFACE_, '0', enCual) and EN_USO_!='0' and !tengoBikini() and !aporK and !aporZap){

		aporBik = true;

	}else if(pisoRegalo() and !tengoRegalo() and !aporK and !aporZap and !aporBik){

		cojoRegalo = true;

	}else if(hayFamoso() and (tengoRegalo() or EN_USO_=='4' or EN_USO_=='5' or EN_USO_=='8' or EN_USO_=='9') and !aporK and !aporZap and !aporBik and !cojoRegalo){

		darRegalo = true;
		cout << "Voy a darle algo" << endl;

	}/*else if(estaCosa(SURFACE_, '2', enCual) and !aporK and !aporZap and !aporBik){

		aporLlave = true;


	}else if(estaCosa(VISTA_, 'D', enCual) and !aporK and !aporZap and !aporBik and !aporLlave){

		if(EN_USO_=='2'){

			aporPuerta = true;
			cout << "Tengo la llave de esa puerta" << endl;

		}else{

			for(int i=0; i<4; i++){

				if(MOCHILLA_[i]=='2'){

					aporPuerta = true;
					accion = ponerEnUso('2');
					cout << "Sacamos la llave para abrir la puerta" << endl;

				}

			}

		}

	}*/else if(EN_USO_!='6' /*and !aporPuerta*/){

		for(int i=0; i<4; i++){

			if(MOCHILLA_[i]=='6'){

				intercambio = true;
				cout << "Hagamos el intercambio" << endl;

			}

		}

	}

	// tomar accion
	if(!aporK and !aporZap and !aporBik and /*!aporLlave and !aporPuerta and*/ !cojoRegalo and !darRegalo and !intercambio){

		//accion = andarAleatorio();

		accion = andarPulgarcito();

	}else if(aporK){

		accion = persiguelo(VISTA_, 'K');

	}else if(aporZap){

		accion = persiguelo(SURFACE_, '6');

	}else if(aporBik){

		accion = persiguelo(SURFACE_, '0');

	/*}else if(aporLlave){

		accion = persiguelo(SURFACE_, '2');

	}else if(aporPuerta and EN_USO_=='2'){

		accion = entrarCastillos();

	*/}else if(cojoRegalo){

		if(EN_USO_!='-' or EN_USO_=='4' or EN_USO_=='5' or EN_USO_=='8' or EN_USO_=='9'){

			accion = actPUSH;

		}else if(EN_USO_=='-'){

			accion = actPICKUP;

			for(int i=0; i<4; i++){

				if(MOCHILLA_[i]=='4' or MOCHILLA_[i]=='5' or MOCHILLA_[i]=='8' or MOCHILLA_[i]=='9'){

					cojoRegalo = false;

				}

			}

		}

	}else if(darRegalo){

		if(!regaloEnMano()){

			for(int i=0; i<4; i++){

				if(MOCHILLA_[i]=='4' or MOCHILLA_[i]=='5' or MOCHILLA_[i]=='8' or MOCHILLA_[i]=='9'){

					accion = ponerEnUso(MOCHILLA_[i]);
					break;

				}

			}

		}else if(regaloEnMano()){

			accion = actGIVE;
			cout << "Se lo doy" << endl;
			darRegalo = false;

		}

	}else if(intercambio){

		accion = ponerEnUso('6');

	}

	if(Kvista==2){

		actualizarSolucion(direntorno);
		PasarVectoraMapaSolucion(ys,xs,mapa_solucion_,VISTA_,os);

	}

	// recuerdo la ultima accion realizada
	last_accion_ = accion;

	pasos--;
	cout << pasos << endl;

	/*if(Kvista==2){

		for(int i=0; i<100; i++){
			for(int j=0; j<100; j++){

				cout << mapa_solucion_[i][j];

			}

			cout << endl;

		}

	}*/

	if(pasos==1){

		for(int i=0; i<100; i++)
			for(int j=0; j<100; j++){

				if(mapa_solucion_[i][j]=='?'){

					mapa_solucion_[i][j]='S';

				}

			}

	}

	return accion;

}

//hayFamoso --> Devuelve true si tengo un famosillo delante
bool Agent::hayFamoso(){

	bool hay = false;

	if(SURFACE_[1]>='g' and SURFACE_[1]<='p'){

		hay = true;

	}

	return hay;

}

//tengoBikini() --> Devuelve true si tengo el bikini en la mochila
bool Agent::tengoBikini(){

	bool tengo = false;

	for(int i=0; i<4; i++){

		if(MOCHILLA_[i]=='0'){

			tengo = true;

		}

	}

	return tengo;

}

//pisoRegalo --> Devuelve true si tengo un regalo debajo
bool Agent::pisoRegalo(){

	bool piso = false;

	if(SURFACE_[0]=='4' or SURFACE_[0]=='5' or SURFACE_[0]=='8' or SURFACE_[0]=='9'){

		piso = true;

	}

	return piso;

}

//tengoRegalo --> Devuelve si tengo algun regalo en la mochila
bool Agent::tengoRegalo(){

	bool tengo = false;

	for(int i=0; i<4; i++){

		if(MOCHILLA_[i]=='4' or MOCHILLA_[i]=='5' or MOCHILLA_[i]=='8' or MOCHILLA_[i]=='9'){

			tengo = true;

		}

	}

	return tengo;

}

//regaloEnMano --> Devuelve true si tiene un objeto en la mano
bool Agent::regaloEnMano(){

	bool tengo = false;

	if(EN_USO_=='4' or EN_USO_=='5' or EN_USO_=='8' or EN_USO_=='9'){

		tengo = true;

	}

	return tengo;

}

// entrarCastillos -> va hacia la puerta del castillo y entra
Agent::ActionType Agent::entrarCastillos(){

	Agent::ActionType accion;

	if(enCual==2 or enCual==5 or enCual==6){

		sentido='i';
		if(enCual==2){

			cont = 2;

		}else cont = 3;

	}else if(enCual==4 or enCual==8 or enCual==9){

		sentido='d';
		if(enCual==4){

			cont = 2;

		}else cont = 3;

	}

	cout << "Veo la puerta y voy a por ella " << cont << endl;

	if(VISTA_[0]=='D' and PuedeAndar() and !NPCDelante()){

		accion = actFORWARD;
		aporPuerta = false;

	}else if(VISTA_[1]=='D'){

		if(orientacion_==0){

			matriz_pulgarcito[y_-1][x_]=0;

		}else if(orientacion_==1){

			matriz_pulgarcito[y_][x_+1]=0;

		}else if(orientacion_==2){

			matriz_pulgarcito[y_+1][x_]=0;

		}else if(orientacion_==3){

			matriz_pulgarcito[y_][x_-1]=0;

		}
		accion = actFORWARD;

	}else if(VISTA_[3]=='D' or VISTA_[7]=='D'){

		accion = actFORWARD;

	}else if(!PuedeAndar() or NPCDelante()){

		if(nopuede<25){

				accion = actTURN_L;

		}else if(nopuede>=25){

				accion = actTURN_R;

		}

		aporPuerta = false;

	}else if(cont>0){

		accion = actFORWARD;
		cont--;

	}else if(cont==0){

		if(sentido=='d'){

			accion = actTURN_R;

		}else if(sentido=='i'){

			accion = actTURN_L;

		}

	}

	return accion;

}

//andarAleatorio -------------------------------------------------------------------------------------
Agent::ActionType Agent::andarAleatorio(){

	Agent::ActionType accion;

	puede = rand() % 151;
	nopuede = rand() % 50;

	if(PuedeAndar() and !NPCDelante()){

			if(puede>=0 and puede<=139){

				accion = actFORWARD;

			}else if(puede>=140 and puede<=144){

				accion = actTURN_L;

			}else if(puede>145){

				accion = actTURN_R;

			}

	}else if(!PuedeAndar() or NPCDelante()){

		if(nopuede<25){

				accion = actTURN_L;

		}else if(nopuede>=25){

				accion = actTURN_R;

		}

	}

	return accion;

}

//andarPulgarcito -------------------------------------------------------------------------------------
Agent::ActionType Agent::andarPulgarcito(){

	Agent::ActionType accion;

	if(PuedeAndar() and !NPCDelante()){

		if((valorD<valorF and valorD<valorI) or (valorI==valorD and valorD<valorF)){

			accion =actTURN_R;

		}else if(valorI<valorF and valorI<valorD){

			accion =actTURN_L;

		}else if((valorF<valorD and valorF<valorI) or (valorF==valorI and valorF==valorD) or (valorF==valorD and valorF<valorI) or (valorF==valorI and valorF<valorD)){

			accion =actFORWARD;

		}

	}else if(!PuedeAndar() or NPCDelante()){

		if(((valorD<valorI) or (valorI==valorD))){

			accion =actTURN_R;

		}else if(valorI<valorD){

			accion =actTURN_L;

		}
	}

	return accion;

}

//PuedeAndar --> Devuelve true si en la casilla de justo delante no tengo obstaculo y false si lo tengo.
bool Agent::PuedeAndar(){

	bool puede = true;

	if(VISTA_[1]=='P' or VISTA_[1]=='M'){

		puede = false;

	}else if(VISTA_[1]=='A'){

		if(EN_USO_=='0') puede = true;
		else puede = false;

	}else if(VISTA_[1]=='B'){

		if(EN_USO_=='6') puede = true;
		else puede = false;

	}else if(VISTA_[1]=='D'){

		if(EN_USO_=='2') puede = true;
		else puede = false;

	}

	return puede;

}

//NPCDelante --> Devuelve true si en la casilla de justo delante hay un NPC o aldeano en la 3 y false si no
bool Agent::NPCDelante(){

	bool hay = false;

	if((SURFACE_[1]>='a' and SURFACE_[1]<='z') or (SURFACE_[3]=='e' or SURFACE_[3]=='f')){

		hay = true;

	}

	return hay;

}

//estaCosa --> Devuelve true si la cosa que esta buscando esta en alguna posicion del vector donde y false si no
bool Agent::estaCosa(char *donde, char cosa, int &enCual){

	bool esta = false;

	for(int i=1; i<=9; i++){

		if(donde[i]==cosa){

			esta = true;
			enCual = i;
			break;

		}else enCual = -1;

	}

	return esta;

}

//ponerEnUso --> Intercambia los objetos en la mochila. cosa1 quedara en uso.
Agent::ActionType Agent::ponerEnUso(char cosa1){

	Agent::ActionType accion;

	if(contInter==0){

		for(int i=0; i<4; i++){

			if(MOCHILLA_[i]==cosa1){

				contInter = i+3;
				break;

			}

		}

		accion = actIDLE;

	}else if(contInter>1 and EN_USO_!='-'){

		cout << "Guardo en mochila" << EN_USO_ << endl;
		accion = actPUSH;
		contInter--;

	}else if(contInter>1 and EN_USO_=='-'){

		cout << "Saco de la mochila" << MOCHILLA_[0] << endl;
		accion = actPOP;
		contInter--;

	}else if(contInter==1 and EN_USO_=='-'){

		cout << "Saco de la mochila" << MOCHILLA_[0] << endl;
		accion = actPOP;

	}else if(contInter==1 and EN_USO_!='-' and EN_USO_!=cosa1){

		cout << "Guardo en mochila" << EN_USO_ << endl;
		accion = actPUSH;

	}else if(EN_USO_==cosa1){

		intercambio = false;
		contInter=0;
		cout << "Intercambio realizado" << endl;

	}

	return accion;

}

//extraerCoord --> Extrae las coordenadas de MENSAJE_
void Agent::extraerCoord(int &filas, int &columnas){

	string fil(MENSAJE_, 9, 10);
	string col(MENSAJE_, 20, 21);

	filas = atoi(fil.c_str());
	columnas = atoi(col.c_str());

}

//loQueLlevoASolucion --> Guarda en solucion lo visto antes de la segunda k
void Agent::loQueLlevoASolucion(){

	int filarriba, filabajo, columnaizquierda, columnaderecha;

	if(direntorno==0){

		filarriba = k2c[0] - k2[0];
		filabajo = filarriba + 99;
		columnaizquierda = k2c[1] - k2[1];
		columnaderecha = columnaizquierda + 99;

	}else if(direntorno==1){

		filabajo = k2c[0] + k2[1];
		filarriba = filabajo - 99;
		columnaizquierda = k2c[1] - k2[0];
		columnaderecha = columnaizquierda + 99;

	}else if(direntorno==2){

		filabajo = k2c[0] + k2[0];
		filarriba = filabajo - 99;
		columnaderecha = k2c[1] + k2[1];
		columnaizquierda = columnaderecha - 99;

	}else if(direntorno==3){

		filarriba = k2c[0] - k2[1];
		filabajo = filarriba + 99;
		columnaderecha = k2c[1] + k2[0];
		columnaizquierda = columnaderecha - 99;

	}

	cout << filarriba << " " << filabajo << " " << columnaizquierda << " " << columnaderecha << endl;

	for(int i=0; i<100; i++)

		for(int j=0; j<100; j++){

			if(i==0 or i==1 or i==2 or i==97 or i==98 or i==99 or j==0 or j==1 or j==2 or j==97 or j==98 or j==99){

				mapa_solucion_[i][j]='P';

			}//else mapa_solucion_[i][j]='S';

		}

	for(int i=0; i<200; i++)
		for(int j=0; j<200; j++){

			if((i>=filarriba and i<=filabajo) and (j>=columnaizquierda and j<=columnaderecha)){

				//mapa_solucion_[i-filarriba][j-columnaizquierda] = mapa_entorno_[i][j];
				mataux[i-filarriba][j-columnaizquierda] = mapa_entorno_[i][j];

			}

		}

	if(direntorno==1){

		girarMatSol(0);

	}else if(direntorno==2){

		girarMatSol(0);
		girarMatSol(0);

	}else if(direntorno==3){

		girarMatSol(1);

	}

	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++){

			if(mataux[i][j]!='?'){

				mapa_solucion_[i][j] = mataux[i][j];

			}

		}

}

//persiguelo --> Devuelve la accion a realizar para llegar hasta cosa.
Agent::ActionType Agent::persiguelo(char *donde, char cosa){

	Agent::ActionType accion;
	int fila, columna, ori;

	if(enCual==4 or enCual==8 or enCual==9){

		sentido = 'd';

	}else if(enCual==2 or enCual==5 or enCual==6){

		sentido = 'i';

	}

	if(donde[0]==cosa){

		if(cosa=='K'){

			extraerCoord(fila, columna);
			cout << "(" << fila << "," << columna << ")" << "(" << y_ << "," << x_ << ")" << endl;
			aporK = false;

			if(Kvista == 0){

				k1[0]=fila;
				k1[1]=columna;
				k1c[0]=y_;
				k1c[1]=x_;
				Kvista++;

				mapa_solucion_[fila][columna]='K';

				cout << "He visto una K" << endl;

			}else{

				if(!(k1[0]==fila and k1[1]==columna)){

					k2[0]=fila;
					k2[1]=columna;
					k2c[0]=y_;
					k2c[1]=x_;
					Kvista++;

					mapa_solucion_[fila][columna]='K';

					cout << "He visto dos K y procedo a calcular la orientacion del mapa!" << endl;

					direntorno = calcOrientacion();

					loQueLlevoASolucion();

					xs = columna;
					ys = fila;

					os = (orientacion_+direntorno)%4;

				}else cout << "Este " << cosa << " ya lo habia visto" << endl;

			}

			if(!PuedeAndar() or NPCDelante()){

				if(((valorD<valorI) or (valorI==valorD))){

					accion =actTURN_R;

				}else if(valorI<valorD){

					accion =actTURN_L;

				}

			}else accion = actFORWARD;

		}else if(cosa=='6'){

			if(EN_USO_!='-'){

				accion = actPUSH;
				return accion;

			}else{

				aporZap=false;
				accion = actPICKUP;

				// Poner el bosque zona libre de paso

				for(int i=0; i<200; i++)
					for(int j=0; j<200; j++){

						if(matriz_pulgarcito[i][j]==110){

							matriz_pulgarcito[i][j]=0;

						}

					}

				// ------------------------------------------------------

				cout << "Tengo unas zapatillas!" << endl;
				return accion;

			}

		}else if(cosa=='0'){

			if(EN_USO_!='-'){

				accion = actPUSH;
				return accion;

			}else{

				aporBik=false;
				accion = actPICKUP;

				// Poner el agua zona libre de paso

				for(int i=0; i<200; i++)
					for(int j=0; j<200; j++){

						if(matriz_pulgarcito[i][j]==105){

							matriz_pulgarcito[i][j]=0;

						}

					}

				// ------------------------------------------------------

				cout << "Tengo un bikini!" << endl;
				return accion;

			}

		}else if(cosa=='2'){

			if(EN_USO_!='-'){

				accion = actPUSH;
				return accion;

			}else{

				aporLlave=false;
				accion = actPICKUP;
				cout << "Tengo las llaves!" << endl;
				return accion;

			}

		}

		giro=0;

	}else if(!PuedeAndar() or NPCDelante()){

		if(((valorD<valorI) or (valorI==valorD))){

			accion =actTURN_R;

		}else if(valorI<valorD){

			accion =actTURN_L;

		}

		if(cosa=='K') aporK = false;
		else if(cosa=='6') aporZap = false;
		else if(cosa=='0') aporBik = false;
		else if(cosa=='2') aporLlave = false;
		giro=0;
		cout << "Retirada que hay un muro :)" << endl;

	}else if(estaCosa(donde, cosa, enCual)){ // Seguir adelante hasta que no lo vea, entonces empiezo a girar

			accion = actFORWARD;
			giro=0;

	}else if(giro == 0){

		if(sentido=='d'){

			accion = actTURN_R;
			giro+=2;

		}else if(sentido=='i'){

			accion = actTURN_L;
			giro+=2;

		}

	}else if(giro==2){

		if(last_accion_==actTURN_R){

			accion = actTURN_L;
			giro--;

		}else{

			accion = actTURN_R;
			giro--;

		}

	}else if(giro==1){

		accion = actFORWARD;
		giro--;

	}

	return accion;

}

//calcOrientacion --> calcula la orientacion del mapa de 200x200
int Agent::calcOrientacion(){

	int sol1[2], sol2[2], pos=0;

	sol1[0] = k2[0] - k1[0];
	sol1[1] = k2[1] - k1[1];

	sol2[0] = k2c[0] - k1c[0];
	sol2[1] = k2c[1] - k1c[1];

	cout << sol1[0] << "," << sol1[1] << endl;
	cout << sol2[0] << "," << sol2[1] << endl;

	cout << "F1 = " << sol1[0] << endl;
	cout << "F2 = " << sol2[0] << endl;
	cout << "C2 = " << sol2[1] << endl;

	if(sol1[0] == sol2[0]){

		cout << "Mapa con orientacion al norte, confirmamos!" << endl;

	}else if(sol1[0] == sol2[0]*(-1)){

		cout << "Mapa con orientacion al sur, confirmamos!" << endl;
		pos=2;

	}else if(sol1[0] == sol2[1]){

		cout << "Mapa con orientacion al este, confirmamos!" << endl;
		pos=1;

	}else if(sol1[0] == sol2[1]*(-1)){

		cout << "Mapa con orientacion al oeste, confirmamos!" << endl;
		pos=3;

	}

	return pos;

}

//girarMat --> Gira una matriz hacia dir.
void Agent::girarMatSol(int dir){

	char aux[100][100];

	// Rotamos a la derecha
	if(dir==0){

		for(int i=0; i<100; i++){

			for(int j=0; j<100; j++){

				//aux[j][100-1-i] = mapa_solucion_[i][j];
				aux[j][100-1-i] = mataux[i][j];

			}

		}

	// Rotamos a la izquierda
	}else if(dir==1){

		for(int i=0; i<100; i++){

			for(int j=0; j<100; j++){

				//aux[j][i] = mapa_solucion_[i][100-1-j];
				aux[j][i] = mataux[i][100-1-j];

			}

		}

	}

	for(int i=0; i<100; i++){

		for(int j=0; j<100; j++){

			//mapa_solucion_[i][j] = aux[i][j];
			mataux[i][j] = aux[i][j];

		}

	}

}
