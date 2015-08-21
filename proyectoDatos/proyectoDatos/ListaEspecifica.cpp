#include "ListaEspecifica.h"


NodoEspecifica * ListaEspecifica::dirNodo(char * pcodigo) {
	NodoEspecifica * nodo = getCab();
	while (nodo != nullptr && strcmp(pcodigo, dirCodigoDePasillo(nodo)) != 0) {
		nodo = nodo->getSgte();
	}
	return nodo;
}

NodoEspecifica * ListaEspecifica::dirUltimo() {
	NodoEspecifica *nodo = getCab();
	for (int i = 0; i < getTamanio(); i++)
		nodo = nodo->getSgte();

	return nodo;
}

NodoEspecifica * ListaEspecifica::dirAnterior(char * pcodigo) {
	NodoEspecifica * nodo = dirNodo(pcodigo);

	return nodo != NULL ? nodo->getAnte() : NULL;
}

NodoEspecifica * ListaEspecifica::dirIndex(int pindex) {
	NodoEspecifica * nodo = getCab();
	for (int i = 0; i < pindex; i++)
		nodo = nodo->getSgte();

	return nodo;
}

char * ListaEspecifica::dirCodigoDePasillo(NodoEspecifica * nodo) {
	return nodo->getInfo()->getCodigo();
}

void ListaEspecifica::agregarNodoDespuesDe(NodoEspecifica * nuevo, NodoEspecifica * nodo) {
	if (nodo->getSgte() != NULL) {
		nodo->getSgte()->setAnte(nuevo);
	}
	nuevo->setSgte(nodo->getSgte());
	nuevo->setAnte(nodo);
	nodo->setSgte(nuevo);

	++tamanio;
}

void ListaEspecifica::agregarNodoAntesDe(NodoEspecifica * nuevo, NodoEspecifica * nodo) {

	if (nodo->getAnte() != NULL)
	{
		nodo->getAnte()->setSgte(nuevo);
		nuevo->setSgte(nodo->getAnte());
	}
	else
		setCab(nuevo);

	nuevo->setSgte(nodo);
	nodo->setAnte(nuevo);

	++tamanio;
}



ListaEspecifica::ListaEspecifica(){
	setCab(NULL);
	setTamanio(0);
}

ListaEspecifica::ListaEspecifica(NodoEspecifica * plista){
	setCab(plista);
	setTamanio(1);
}

ListaEspecifica::~ListaEspecifica(){}


void ListaEspecifica::setTamanio(int ptamanio){
	this->tamanio = ptamanio;
}

void ListaEspecifica::setCab(NodoEspecifica * plista){
	this->cab = plista;
}

int ListaEspecifica::getTamanio(){
	return this->tamanio;
}

NodoEspecifica * ListaEspecifica::getCab(){
	return this->cab;
}

bool ListaEspecifica::elimina(char * pcodigo) {
	NodoEspecifica *nodo = dirNodo(pcodigo);
	if (nodo != NULL) {
		eliminarNodo(nodo);
		return true;
	}
	else
		return false;
}

bool ListaEspecifica::eliminarIndex(int pindex) {
	if (getTamanio() >= pindex - 1) {
		NodoEspecifica * nodo = getCab();
		for (int i = 0; i < pindex; i++) {
			nodo = nodo->getSgte();
		}
		eliminarNodo(nodo);
		return true;
	}
	else
		return false;
}

void ListaEspecifica::vaciar() {
	NodoEspecifica * nodo = getCab();
	if (nodo != NULL) {
		NodoEspecifica *temp = nodo;
		nodo = nodo->getSgte();
		delete(temp);
	}
	setCab(NULL);
	setTamanio(0);
}

void ListaEspecifica::eliminarNodo(NodoEspecifica * pnodo) {
	if (pnodo->getSgte() != NULL) {
		pnodo->getSgte()->setAnte(pnodo->getAnte());
	}if (pnodo->getAnte() != NULL) {
		pnodo->getAnte()->setSgte(pnodo->getSgte());
	}
	else {
		setCab(pnodo->getSgte());
	}
	delete(pnodo);
	--tamanio;
}

InfoEspecifica * ListaEspecifica::obtenerDato(char * pcodigo) {
	NodoEspecifica * nodo = dirNodo(pcodigo);
	return nodo != NULL ? nodo->getInfo() : NULL;
}

InfoEspecifica * ListaEspecifica::obtenerPorIndex(int pindex) {
	if (pindex - 1 <= getTamanio()) {
		return dirIndex(pindex)->getInfo();
	}
	else
		return NULL;
}

bool ListaEspecifica::estaVacia() {
	return cab == NULL;
}

bool ListaEspecifica::modificarDatos(char * codigo, InfoEspecifica * info) {
	NodoEspecifica * nodo = dirNodo(codigo);
	if (nodo != NULL) {
		nodo->setInfo(info);
		return true;
	}
	return false;
}

void ListaEspecifica::insetarInicio(InfoEspecifica * pinfo) {
	NodoEspecifica * nodo = new NodoEspecifica(pinfo);
	if (!estaVacia()) {
		getCab()->setAnte(nodo);
		nodo->setSgte(getCab());
	}
	setCab(nodo);

	tamanio++;
}

void ListaEspecifica::insertarFinal(InfoEspecifica * pinfo) {
	NodoEspecifica * nodo = new NodoEspecifica(pinfo);
	if (estaVacia()) {
		setCab(nodo);
	}
	else {
		NodoEspecifica * ultimo = dirUltimo();
		nodo->setAnte(ultimo);
		ultimo->setSgte(nodo);
	}
	tamanio++;
}

bool ListaEspecifica::insertarAntesDe(InfoEspecifica * pinfo, char * pcodigo) {
	NodoEspecifica *aux = dirNodo(pcodigo);
	bool existe = aux != NULL;
	if (existe) {
		NodoEspecifica *nodo = new NodoEspecifica(pinfo);
		agregarNodoAntesDe(nodo, aux);
	}
	return existe;
}

bool ListaEspecifica::insertarDespuesDe(InfoEspecifica * pinfo, char * pcodigo) {
	NodoEspecifica *aux = dirNodo(pcodigo);
	bool existe = aux != NULL;
	if (existe) {
		NodoEspecifica *nodo = new NodoEspecifica(pinfo);
		agregarNodoDespuesDe(nodo, aux);
	}
	return existe;
}

bool ListaEspecifica::insertarAcendente(InfoEspecifica * pinfo) {

	NodoEspecifica * nodo = getCab();
	if (nodo == NULL || strcmp(pinfo->getCodigo(), nodo->getInfo()->getCodigo()) < 0) {
		insetarInicio(pinfo);
	}
	else {
		while (nodo->getSgte() != NULL && strcmp(pinfo->getCodigo(), nodo->getInfo()->getCodigo()) < 0) {
			nodo = nodo->getSgte();
		}
		agregarNodoDespuesDe(new NodoEspecifica(pinfo), nodo);
		return true;
	}

	return false;
}

bool ListaEspecifica::insertarDecendente(InfoEspecifica * pinfo) {

	NodoEspecifica * nodo = getCab();
	if (nodo == NULL || strcmp(pinfo->getCodigo(), nodo->getInfo()->getCodigo()) > 0) {
		insetarInicio(pinfo);
	}
	else {
		while (nodo->getSgte() != NULL && strcmp(pinfo->getCodigo(), nodo->getInfo()->getCodigo()) > 0) {
			nodo = nodo->getSgte();
		}
		agregarNodoDespuesDe(new NodoEspecifica(pinfo), nodo);
		return true;
	}

	return false;
}