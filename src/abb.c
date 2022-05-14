#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(!comparador){
		return NULL;
	}
	abb_t *abb = calloc(1, sizeof(abb_t));
	if(!abb){
		return NULL;
	}
	abb->comparador = comparador;
 	return abb;
}

nodo_abb_t *nodo_abb_insertar(nodo_abb_t *raiz, void *elemento, abb_comparador comparador, size_t *tamanio)
{
	if(!raiz){
		nodo_abb_t *nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
		if(!nuevo_nodo){
			return NULL;
		}
		nuevo_nodo->elemento = elemento;
		(*tamanio)++;

		return nuevo_nodo;
	}
	if(comparador(elemento, raiz->elemento) < 0){
		raiz->izquierda = nodo_abb_insertar(raiz->izquierda, elemento, comparador, tamanio);
	}
	else{
		raiz->derecha = nodo_abb_insertar(raiz->derecha, elemento, comparador, tamanio);
	}

	return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(!arbol){
		return NULL;
	}
	arbol->nodo_raiz = nodo_abb_insertar(arbol->nodo_raiz, elemento, arbol->comparador, &arbol->tamanio);

	return arbol;
}

void *nodo_abb_quitar(nodo_abb_t *raiz, void *elemento, abb_comparador comparador)
{
	if(!raiz){
		return NULL;
	}

	if(comparador(elemento, raiz->elemento) == 0){

		if(raiz->derecha && raiz->izquierda){ //TENGO 2 HIJOS

		}
		else{ //TENGO 1 O 0 HIJO
			nodo_abb_t *hijo = NULL;
			if(raiz->derecha){
				hijo = raiz->derecha;
			}
			else if(raiz->izquierda){
				hijo = raiz->izquierda;
			}
			free(raiz);
			return hijo;
		}
	}
	else if(comparador(elemento, raiz->elemento) < 0){
		raiz->izquierda = nodo_abb_quitar(raiz->izquierda, elemento, comparador);
	}
	else{
		raiz->derecha = nodo_abb_quitar(raiz->derecha, elemento, comparador);
	}

	return raiz;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{	
	if(!arbol){
		return NULL;
	}
	nodo_abb_t *quitado = nodo_abb_quitar(arbol->nodo_raiz, elemento, arbol->comparador);
	free(arbol->nodo_raiz);

	return quitado->elemento;
}

void *nodo_abb_buscar(nodo_abb_t *raiz, void *buscado, abb_comparador comparador)
{
	if(!raiz){
		return NULL;
	}

	if(comparador(buscado, raiz->elemento) == 0){
		return raiz->elemento;
	}
	if(comparador(buscado, raiz->elemento) < 0){
		return nodo_abb_buscar(raiz->izquierda, buscado, comparador);
	}
	return nodo_abb_buscar(raiz->derecha, buscado, comparador);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if(!arbol){
		return NULL;
	}
	return nodo_abb_buscar(arbol->nodo_raiz, elemento, arbol->comparador);
}

bool abb_vacio(abb_t *arbol)
{
	if(!arbol || arbol->tamanio == 0){
		return true;
	}
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if(!arbol){
		return 0;
	}
	return arbol->tamanio;
}

void nodo_abb_destruir(nodo_abb_t *raiz)
{
	if(!raiz){
		return;
	}
	nodo_abb_destruir(raiz->derecha);
	nodo_abb_destruir(raiz->izquierda);
	free(raiz);
}

void abb_destruir(abb_t *arbol)
{
	if(!arbol){
		return;
	}
	nodo_abb_destruir(arbol->nodo_raiz);
	free(arbol);
}

void nodo_abb_destruir_todo(nodo_abb_t *raiz, void (*destructor)(void *))
{
	if(!raiz){
		return;
	}
	nodo_abb_destruir_todo(raiz->izquierda, destructor);
	nodo_abb_destruir_todo(raiz->derecha, destructor);
	destructor(raiz->elemento);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if(!arbol){
		return;
	}
	if(destructor){
		nodo_abb_destruir_todo(arbol->nodo_raiz, destructor);
	}
	abb_destruir(arbol);
}

void abb_con_cada_elemento_inorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *), void *aux, size_t *cantidad)
{
	if(!raiz){
		return;
	}
	if(raiz->izquierda){
		abb_con_cada_elemento_inorden(raiz->izquierda, funcion, aux, cantidad);
	}

	funcion(raiz->elemento, aux);
	(*cantidad)++;
	
	if(raiz->derecha){
		abb_con_cada_elemento_inorden(raiz->derecha, funcion, aux, cantidad);
	}
}

void abb_con_cada_elemento_preorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *), void *aux, size_t *cantidad)
{
	if(!raiz){
		return;
	}

	funcion(raiz->elemento, aux);
	(*cantidad)++;

	if(raiz->izquierda){
		abb_con_cada_elemento_preorden(raiz->izquierda, funcion, aux, cantidad);
	}
	
	if(raiz->derecha){
		abb_con_cada_elemento_preorden(raiz->derecha, funcion, aux, cantidad);
	}
}

void abb_con_cada_elemento_postorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *), void *aux, size_t *cantidad)
{
	if(!raiz){
		return;
	}
	if(raiz->izquierda){
		abb_con_cada_elemento_postorden(raiz->izquierda, funcion, aux, cantidad);
	}

	if(raiz->derecha){
		abb_con_cada_elemento_postorden(raiz->derecha, funcion, aux, cantidad);
	}

	funcion(raiz->elemento, aux);
	(*cantidad)++;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux)
{
	if(!arbol || !funcion){
		return 0;
	}
	size_t cantidad = 0;
	if(recorrido == INORDEN){
		abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &cantidad);
	}
	else if(recorrido == PREORDEN){
		abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &cantidad);
	}
	else if(recorrido == POSTORDEN){
		abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &cantidad);
	}
	return cantidad;
}

void abb_recorrer_inorden(nodo_abb_t *raiz, void **array, size_t tamanio_array, size_t *cant_elementos)
{
	if(!raiz || *cant_elementos > tamanio_array){
		return;
	}
	if(raiz->izquierda){
		abb_recorrer_inorden(raiz->izquierda, array, tamanio_array, cant_elementos);
	}

	array[*cant_elementos] = raiz->elemento;
	(*cant_elementos)++;
	
	if(raiz->derecha){
		abb_recorrer_inorden(raiz->derecha, array, tamanio_array, cant_elementos);
	}
}

void abb_recorrer_preorden(nodo_abb_t *raiz, void **array, size_t tamanio_array, size_t *cant_elementos)
{
	if(!raiz || *cant_elementos > tamanio_array){
		return;
	}

	array[*cant_elementos] = raiz->elemento;
	(*cant_elementos)++;

	if(raiz->izquierda){
		abb_recorrer_inorden(raiz->izquierda, array, tamanio_array, cant_elementos);
	}

	if(raiz->derecha){
		abb_recorrer_inorden(raiz->derecha, array, tamanio_array, cant_elementos);
	}
}

void abb_recorrer_postorden(nodo_abb_t *raiz, void **array, size_t tamanio_array, size_t *cant_elementos)
{
	if(!raiz || *cant_elementos > tamanio_array){
		return;
	}

	if(raiz->izquierda){
		abb_recorrer_inorden(raiz->izquierda, array, tamanio_array, cant_elementos);
	}
	if(raiz->derecha){
		abb_recorrer_inorden(raiz->derecha, array, tamanio_array, cant_elementos);
	}

	array[*cant_elementos] = raiz->elemento;
	(*cant_elementos)++;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array, size_t tamanio_array)
{
	if(!arbol){
		return 0;
	}
	size_t tope = 0;
	if(recorrido == INORDEN){
		abb_recorrer_inorden(arbol->nodo_raiz, array, tamanio_array, &tope);
	}
	else if(recorrido == PREORDEN){
		abb_recorrer_preorden(arbol->nodo_raiz, array, tamanio_array, &tope);
	}
	else if(recorrido == POSTORDEN){
		abb_recorrer_postorden(arbol->nodo_raiz, array, tamanio_array, &tope);
	}
	return tope;
}
