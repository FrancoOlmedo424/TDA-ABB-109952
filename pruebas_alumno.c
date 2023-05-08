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

void prueba_eliminacion_en_arbol()
{
	abb_t *abb = abb_crear(comparador);
	abb_t *abb_vacio = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	int elemento_5 = 17;
	pa2m_afirmar(abb_quitar(NULL, &elemento) == NULL,
		     "No se puede quitar de un arbol nulo");
	pa2m_afirmar(abb_quitar(abb_vacio, &elemento) == NULL,
		     "No se puede quitar de un arbol sin elementos");
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	pa2m_afirmar(abb_tamanio(abb) == 5,
		     "Se insertan 5 elementos en el arbol");
	void *elemento_quitado = NULL;
	elemento_quitado = abb_quitar(abb, &elemento_3);
	pa2m_afirmar(
		abb->comparador(&elemento_3, elemento_quitado) == 0,
		"Se ha quitado un elemento en el nivel 2 con rama izquierda no nula");
	pa2m_afirmar(abb_tamanio(abb) == 4,
		     "Se ha reducido el tamaño del arbol (4)");
	pa2m_afirmar(abb->comparador(abb->nodo_raiz->derecha->elemento,
				     &elemento_4) == 0,
		     "El elemento del hijo derecho de la raíz es el correcto");
	elemento_quitado = abb_quitar(abb, &elemento_4);
	pa2m_afirmar(
		abb->comparador(&elemento_4, elemento_quitado) == 0,
		"Se quitó un elemento con hijos nulos (hijo derecho de raíz)");
	pa2m_afirmar(abb->nodo_raiz->derecha == NULL,
		     "El hijo derecho de la raíz quedó null");
	pa2m_afirmar(abb_tamanio(abb) == 3,
		     "Se ha reducido el tamaño del arbol (3)");
	elemento_quitado = abb_quitar(abb, &elemento_2);
	pa2m_afirmar(
		abb->comparador(&elemento_2, elemento_quitado) == 0,
		"Se ha quitado un elemento en el nivel 2 con rama derecha no nula");
	pa2m_afirmar(abb_tamanio(abb) == 2,
		     "Se ha reducido el tamaño del arbol (2)");
	pa2m_afirmar(
		abb->comparador(abb->nodo_raiz->izquierda->elemento,
				&elemento_5) == 0,
		"El elemento del hijo izquierdo de la raíz es el correcto");
	elemento_quitado = abb_quitar(abb, &elemento_5);
	pa2m_afirmar(
		abb->comparador(&elemento_5, elemento_quitado) == 0,
		"Se quitó un elemento con hijos nulos (hijo izquierdo de raíz)");
	pa2m_afirmar(abb->nodo_raiz->izquierda == NULL,
		     "El hijo izquierdo de la raíz quedó null");
}

void prueba_eliminacion_con_2_hijos_raiz()
{
	abb_t *abb = abb_crear(comparador);
	int elemento = 23;
	int elemento_2 = 15;
	int elemento_3 = 27;
	int elemento_4 = 25;
	int elemento_5 = 17;
	int elemento_6 = 10;
	int elemento_7 = 30;
	int elemento_8 = 16;
	abb_insertar(abb, &elemento);
	abb_insertar(abb, &elemento_2);
	abb_insertar(abb, &elemento_3);
	abb_insertar(abb, &elemento_4);
	abb_insertar(abb, &elemento_5);
	abb_insertar(abb, &elemento_6);
	abb_insertar(abb, &elemento_7);
	abb_insertar(abb, &elemento_8);
	pa2m_afirmar(
		abb_tamanio(abb) == 8,
		"Se agregaron 8 elementos a la lista, en los dos hijos de la raíz");
	void *elemento_quitado;
	elemento_quitado = abb_quitar(abb, &elemento);
	pa2m_afirmar(abb->comparador(&elemento, elemento_quitado) == 0,
		     "Se quitó el elemento de la raiz (23)");
	pa2m_afirmar(abb->comparador(abb->nodo_raiz->elemento, &elemento_5) ==
			     0,
		     "Se reemplazó por el predecesor inorden (17)");
	elemento_quitado = abb_quitar(abb, &elemento_5);
	pa2m_afirmar(abb->comparador(&elemento_5, elemento_quitado) == 0,
		     "Se quitó el elemento de la raiz (17)");
	pa2m_afirmar(abb->comparador(abb->nodo_raiz->elemento, &elemento_8) ==
			     0,
		     "Se reemplazó por el predecesor inorden (16)");
	elemento_quitado = abb_quitar(abb, &elemento_8);
	pa2m_afirmar(abb->comparador(&elemento_8, elemento_quitado) == 0,
		     "Se quitó el elemento de la raiz (16)");
	pa2m_afirmar(abb->comparador(abb->nodo_raiz->elemento, &elemento_2) ==
			     0,
		     "Se reemplazó por el predecesor inorden (15)");
	abb_quitar(abb, &elemento_2);
	abb_quitar(abb, &elemento_3);
	abb_quitar(abb, &elemento_4);
	abb_quitar(abb, &elemento_6);
	abb_quitar(abb, &elemento_7);
	pa2m_afirmar(
		abb_vacio(abb) == true,
		"Se eliminaron los elementos restantes a través de la raíz, el arbol quedó vacío");
}

int main()
{
	pa2m_nuevo_grupo("\nPruebas creación de arbol");
	prueba_creacion_arbol();
	pa2m_nuevo_grupo("\nPruebas insercion en arbol");
	prueba_insercion_en_arbol();
	pa2m_nuevo_grupo("\nPruebas busqueda en arbol");
	prueba_busqueda_en_arbol();
	pa2m_nuevo_grupo("\n Pruebas eliminacion en arbol");
	prueba_eliminacion_en_arbol();
	pa2m_nuevo_grupo("\n Pruebas eliminacion con 2 hijos desde raíz");

	prueba_eliminacion_con_2_hijos_raiz();

	return pa2m_mostrar_reporte();
}
