#pragma once
#include "NodoArticulo.h" 
#include "stdafx.h"

class ListaArticulo
{

private:
	NodoArticulo *cab;
	int tamanio;

	NodoArticulo * dirNodo(char *);
	NodoArticulo * dirUltimo();
	NodoArticulo * dirAnterior(char *);
	NodoArticulo * dirIndex(int);

	void agregarNodoDespuesDe(NodoArticulo * nuevo, NodoArticulo * nodo);

	void agregarNodoAntesDe(NodoArticulo * nuevo, NodoArticulo * nodo);
	int covertirAEntero(char *);
	bool almacenarArticuloEnFichero(InfoArticulo * articulo);


public:
	ListaArticulo();
	~ListaArticulo();

	void setCab(NodoArticulo *);
	void setTamanio(int);
	NodoArticulo * getCab();
	int getTamanio();


	//insertar
	void insetarInicio(InfoArticulo *);
	void insertarFinal(InfoArticulo *);
	bool insertarAntesDe(InfoArticulo *, char *);
	bool insertarDespuesDe(InfoArticulo *, char *);
	bool insertarAcendente(InfoArticulo *);
	bool insertarDecendente(InfoArticulo *);

	int agregar(char * codigo, char * nombre, char * marca, double tamanio, double precio, ListaArticulo * lista);




	//eliminar
	bool elimina(char *);
	bool eliminarIndex(int);
	void vaciar();
	void eliminarNodo(NodoArticulo *);

	// obtener 
	InfoArticulo * obtenerDato(char *);
	InfoArticulo * obtenerPorIndex(int);
	bool estaVacia();

	bool modificarDatos(char * codigo, InfoArticulo * info);
	
	
};

