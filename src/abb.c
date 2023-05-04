#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL)
		return NULL;
	abb_t *arbol = calloc(1, sizeof(abb_t));
	arbol->comparador = comparador;
	return arbol;
}

nodo_abb_t *abb_insertar_recursivo(nodo_abb_t *raiz, void *elemento,
				   abb_comparador comparador, bool *error)
{
	if (raiz == NULL) {
		nodo_abb_t *nodo_insertar = malloc(sizeof(nodo_abb_t));
		if (nodo_insertar == NULL) {
			*error = true;
			return NULL;
		}
		nodo_insertar->elemento = elemento;
		nodo_insertar->derecha = NULL;
		nodo_insertar->izquierda = NULL;
		return nodo_insertar;
	}

	if (comparador(raiz->elemento, elemento) >= 0)
		raiz->izquierda = abb_insertar_recursivo(
			raiz->izquierda, elemento, comparador, error);
	if (comparador(raiz->elemento, elemento) < 0)
		raiz->derecha = abb_insertar_recursivo(raiz->derecha, elemento,
						       comparador, error);
	return raiz;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;
	bool error = false;
	arbol->nodo_raiz = abb_insertar_recursivo(arbol->nodo_raiz, elemento,
						  arbol->comparador, &error);
	if (error)
		return NULL;
	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return elemento;
}

void *abb_buscar_recursivo(nodo_abb_t *raiz, void *elemento,
			   abb_comparador comparador, void *elemento_encontrado)
{
	if (raiz == NULL)
		return NULL;
	if (comparador(raiz->elemento, elemento) == 0)
		return raiz->elemento;
	if (comparador(raiz->elemento, elemento) >= 0)
		elemento_encontrado = abb_buscar_recursivo(raiz->izquierda,
							   elemento, comparador,
							   elemento_encontrado);
	if (comparador(raiz->elemento, elemento) < 0)
		elemento_encontrado = abb_buscar_recursivo(raiz->derecha,
							   elemento, comparador,
							   elemento_encontrado);
	return elemento_encontrado;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	void *elemento_encontrado = NULL;
	if (abb_vacio(arbol))
		return NULL;
	elemento_encontrado = abb_buscar_recursivo(arbol->nodo_raiz, elemento,
						   arbol->comparador,
						   elemento_encontrado);
	return elemento_encontrado;
}

bool abb_vacio(abb_t *arbol)
{
	if (arbol == NULL || arbol->tamanio == 0)
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL)
		return 0;
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	free(arbol);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
