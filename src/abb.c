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
		nodo_abb_t *nodo = calloc(1, sizeof(nodo_abb_t));
		if(!nodo){
			return NULL;
		}
		nodo->elemento = elemento;
		raiz = nodo;
		(*tamanio)++;
		return raiz;
	}
	if(comparador(elemento, raiz->elemento) <= 0){
		return nodo_abb_insertar(raiz->izquierda, elemento, comparador, tamanio);
	}
	else if(comparador(elemento, raiz->elemento) > 0){
		return nodo_abb_insertar(raiz->derecha, elemento, comparador, tamanio);
	}
	return NULL;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if(!arbol){
		return NULL;
	}
	arbol->nodo_raiz = nodo_abb_insertar(arbol->nodo_raiz, elemento,arbol->comparador, &arbol->tamanio);

	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return NULL;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	return NULL;
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

void abb_destruir(abb_t *arbol)
{
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer_inorden(nodo_abb_t *raiz, void **array, size_t tamanio_array, size_t *tope)
{
	if(!raiz || *tope > tamanio_array){
		return (*tope)+1;
	}
	if(*tope <= tamanio_array){
		array[*tope] = raiz->elemento;
		(*tope)++;
	}
	abb_recorrer_inorden(raiz->izquierda, array, tamanio_array, tope);
	abb_recorrer_inorden(raiz->derecha, array, tamanio_array, tope);
	return (*tope)+1;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array, size_t tamanio_array)
{
	size_t tope = 0;
	if(recorrido == INORDEN){
		return abb_recorrer_inorden(arbol->nodo_raiz, array, tamanio_array, &tope);
	}
	return tope;
}
