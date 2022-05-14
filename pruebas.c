#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int comparador(void* elem1, void* elem2){

	int* elemento1 = elem1;
	int* elemento2 = elem2;

	return *elemento1 - *elemento2;
}

void al_crear_un_arbol_devuelve_un_arbol_vacio_con_raiz_nula(){
	
	abb_t *abb = abb_crear(comparador);

	pa2m_afirmar(abb != NULL, "El árbol creado es válido.");
	pa2m_afirmar(abb_vacio(abb), "El árbol creado está vacío.");
	pa2m_afirmar(abb->nodo_raiz == NULL, "El árbol creado tiene raíz nula.");

	abb_destruir(abb);
}

void inserto_un_elemento_y_aumenta_el_tamanio_del_arbol(){

	abb_t *abb = abb_crear(comparador);
	int a = 10, b = 20, c = 8; 

	pa2m_afirmar(abb_insertar(NULL, &a) == NULL, "No puedo insertar en un arbol nulo.");

	abb_insertar(abb, &a);

	pa2m_afirmar(abb->tamanio == 1, "Inserto un elemento en un arbol vacío y aumenta el tamaño del árbol.");
	pa2m_afirmar(*(int *)abb->nodo_raiz->elemento == a, "Inserto un elemento en un arbol vacío y el elemento de la raíz es ese elemento.");

	abb_insertar(abb, &b);

	pa2m_afirmar(abb->tamanio == 2, "Inserto un elemento en un arbol con elementos y aumenta el tamaño del árbol.");
	pa2m_afirmar(*(int *)abb->nodo_raiz->derecha->elemento == b, "Inserto un elemento mayor a la raíz y se inserta a su derecha.");

	abb_insertar(abb, &c);

	pa2m_afirmar(abb->tamanio == 3, "Inserto otro elemento en un arbol con elementos y aumenta el tamaño del árbol.");
	pa2m_afirmar(*(int *)abb->nodo_raiz->izquierda->elemento == c, "Inserto un elemento menor a la raíz y se inserta a su izquierda.");

	abb_destruir(abb);
}

void busco_un_elemento_y_si_lo_encuentra_lo_devuelve(){

	abb_t *abb = abb_crear(comparador);
	int a = 10, b = 20, c = 8, d = 15;

	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);

	pa2m_afirmar(abb_buscar(NULL, &a) == NULL, "No puedo buscar un elemento en un arbol nulo.");

	pa2m_afirmar(abb_buscar(abb, &a) == abb->nodo_raiz->elemento, "Busco el elemento de la raíz, lo encuentra y lo devuelve.");
	pa2m_afirmar(*(int *)abb_buscar(abb, &b) == b, "Busco un segundo elemento en el árbol, lo encuentra y lo devuelve.");
	pa2m_afirmar(*(int *)abb_buscar(abb, &c) == c, "Busco un tercer elemento en el árbol, lo encuentra y lo devuelve.");

	pa2m_afirmar(abb_buscar(abb, &d) == NULL, "Busco un elemento en el árbol, no lo encuentra y devuelve NULL.");
	

	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");

	pa2m_nuevo_grupo("Pruebas de creacion");
	al_crear_un_arbol_devuelve_un_arbol_vacio_con_raiz_nula();

	pa2m_nuevo_grupo("Pruebas de insertar");
	inserto_un_elemento_y_aumenta_el_tamanio_del_arbol();

	pa2m_nuevo_grupo("Pruebas de buscar");
	busco_un_elemento_y_si_lo_encuentra_lo_devuelve();

	pa2m_nuevo_grupo("Pruebas de quitar");

	return pa2m_mostrar_reporte();
}
