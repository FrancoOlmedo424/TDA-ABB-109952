#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int comparador(void *elemento_1, void *elemento_2)
{
	int *e1 = elemento_1;
	int *e2 = elemento_2;

	return (*e1) - (*e2);
}

void prueba_creacion_arbol()
{
	abb_t *arbol_NULL = abb_crear(NULL);
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(
		arbol_NULL == NULL,
		"No se puede crear un arbol con función nula (abb_crear devuelve NULL)");
	pa2m_afirmar(
		arbol != NULL,
		"El arbol creado no devuelve NULL, se pudo crear el arbol");
	pa2m_afirmar(
		arbol->comparador != NULL,
		"El arbol creado posee una funcion comparadora (el puntero comparador no devuelve NULL)");
	pa2m_afirmar(arbol->tamanio == 0,
		     "El arbol está vacío, su tamaño es 0");
}

void prueba_insercion_en_arbol()
{
	pa2m_afirmar(abb_insertar(NULL, NULL) == NULL,
		     "Intentar insertar en arbol nulo devuelve NULL");
	abb_t *abb = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 37;
	abb_insertar(abb, &elemento);
	pa2m_afirmar(abb->comparador(&elemento, abb->nodo_raiz->elemento) == 0,
		     "Se insertó un elemento en nodo raiz");
	pa2m_afirmar(abb->tamanio == 1, "El tamaño del arbol subió a 1");
	pa2m_afirmar(abb->nodo_raiz->derecha == NULL,
		     "Puntero al nodo derecha de la raíz devuelve NULL");
	pa2m_afirmar(abb->nodo_raiz->izquierda == NULL,
		     "Puntero al nodo izquierda de la raíz devuelve NULL");
	abb_insertar(abb, &elemento_2);
	pa2m_afirmar(
		abb->tamanio == 2,
		"Se insertó un elemento menor, el tamaño del arbol subió a 2");
	abb_insertar(abb, &elemento_3);
	pa2m_afirmar(
		abb->tamanio == 3,
		"Se insertó un elemento mayor, el tamaño del arbol subió a 3");
	pa2m_afirmar(
		abb->nodo_raiz->derecha != NULL,
		"Puntero al nodo derecha de la raíz no devuelve NULL, se insertó el nodo");
	pa2m_afirmar(
		abb->nodo_raiz->izquierda != NULL,
		"Puntero al nodo izquierda de la raíz no devuelve NULL, se insertó el nodo");
}

void prueba_busqueda_en_arbol()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	int elemento = 23;
	int elemento_b = 23;
	int elemento_2 = 15;
	int elemento_3 = 37;
	int elemento_4 = 40;
	int elemento_5 = 12;
	int elemento_6 = 16;
	int elemento_7 = 32;
	abb_insertar(abb, &elemento);
	void *elemento_encontrado = abb_buscar(NULL, &elemento_b);
	pa2m_afirmar(
		elemento_encontrado == NULL,
		"No se puede buscar un elemento en un arbol nulo, devuelve NULL");
	elemento_encontrado = abb_buscar(abb_vacio, &elemento_b);
	pa2m_afirmar(
		elemento_encontrado == NULL,
		"No se puede buscar un elemento en un arbol vacio, devuelve NULL");
	elemento_encontrado = abb_buscar(abb, &elemento_b);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_b) == 0,
		     "Se encontró el elemento en la raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_2);
	pa2m_afirmar(elemento_encontrado == NULL,
		     "Si se busca un elemento inexistente se devuelve NULL");
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	abb_insertar(abb, &elemento_7);
	elemento_encontrado = abb_buscar(abb, &elemento_2);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_2) == 0,
		     "Se encontró el elemento de la izquierda de la raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_3);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_3) == 0,
		     "Se encontró el elemento de la derecha de la raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_4);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_4) == 0,
		     "Se encontró el elemento del subarbol derecho");
	elemento_encontrado = abb_buscar(abb, &elemento_5);
	pa2m_afirmar(comparador(elemento_encontrado, &elemento_5) == 0,
		     "Se encontró el elemento del subarbol izquierdo");
	elemento_encontrado = abb_buscar(abb, &elemento_6);
	pa2m_afirmar(
		comparador(elemento_encontrado, &elemento_6) == 0,
		"Se encontró el elemento del subarbol izquierdo, predecesor inorden a raíz");
	elemento_encontrado = abb_buscar(abb, &elemento_7);
	pa2m_afirmar(
		comparador(elemento_encontrado, &elemento_7) == 0,
		"Se encontró el elemento del subarbol derecho, sucesor inorden a raiz");
}

int main()
{
	pa2m_nuevo_grupo("\nPruebas creación de arbol");
	prueba_creacion_arbol();
	pa2m_nuevo_grupo("\nPruebas insercion en arbol");
	prueba_insercion_en_arbol();
	pa2m_nuevo_grupo("\nPruebas busqueda en arbol");
	prueba_busqueda_en_arbol();

	return pa2m_mostrar_reporte();
}
