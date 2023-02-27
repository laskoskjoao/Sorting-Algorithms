#pragma once
#ifndef _SORTING_MANAGER_H_
#define _SORTING_MANAGER_H_
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>

enum Algorithm {
	Selection,
	Bubble,
	Insertion,
	My,
	Merge,
	Quick,
	Couting
};

class SortingManager {
private:
	/*Dados*/
	int comparisons;
	int swaps;
	bool endSorting;
	int size;
	Algorithm algorithm;
	std::vector<std::pair<int, sf::RectangleShape*>> elements;
	void generateData();	//inicializa o vector elements com valores aleatorios

	/*Coleta de entradas*/
	void menu();

	/*Algoritmos de ordena��o*/
	std::thread* sort;
	void selectionSort();
	void bubbleSort();
	void insertionSort();
	void mergeSort(int begin, int end);
		void merge(int begin, int middle, int end);
	void quickSort(int begin, int end);
	void coutingSort();
	void mySort();
		void invertedInsertionSort(int index);
	
	//Fun��o auxiliar para realizar o swap de elementos
	void swap(int firstIndex, int secondIndex); //troca elementos e muda sua cor para destac�-los (� chamada pelos algoritmos de ordena��o)
		std::pair<int, int> lastIndexesSwap;
	//Fun��o auxiliar para a inser��o de elementos
	void insert(int index, std::pair<int, sf::RectangleShape*> element);	//troca elementos e muda sua cor para destac�-los (� chamada pelos algoritmos de ordena��o)
		int lastInsertedIndex;

	//Fun��o auxiliar para indicar a visualiza��o de elementos (destaca o elemento visualizado pelo algoritmo - utilizado pelo couting sort)
	void viewElement(int index);
		int lastViewedElement;

	//Fun��o auxiliar que indica os elementos comparados pelo algoritmo atualmente
	void compareElements(int firstIndex, int secondIndex);
		std::pair<int,int> lastElementsCompared;

	//Fun��o auxiliar que indica final da ordena��o (deixa elementos verdes)
	void endSort();

	/*Ger�ncia da janela*/
	sf::RenderWindow window;
	void mainLoop();							//chama os algoritmos de ordena��o e desenha na tela
	void draw();
public:
	SortingManager();
	~SortingManager();
};

#endif // _SORTING_MANAGER_H_#

