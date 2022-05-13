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
	pa2m_afirmar(abb->tamanio == 0, "El árbol creado está vacío.");
	pa2m_afirmar(abb->nodo_raiz == NULL, "El árbol creado tiene raíz nula.");

	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de ABB");

	pa2m_nuevo_grupo("Pruebas de creacion");
	al_crear_un_arbol_devuelve_un_arbol_vacio_con_raiz_nula();

	pa2m_nuevo_grupo("Pruebas de insertar");
	


	return pa2m_mostrar_reporte();
}
