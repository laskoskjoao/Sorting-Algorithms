#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#ifndef _SORTING_
#define _SORTING_

enum Algorithm {
	Selection,
	Bubble,
	Insertion,
	My,
	Shell,
	Merge,
	Quick,
	Heap,
	Counting
};

class Sorting {
private:
	bool running, endSorting;
	std::vector<std::pair<int, sf::RectangleShape*>> elements;
	Algorithm algorithm;
	int swaps;
	int comparisons;

	int width, heigth;

	/*Algoritmos de ordena��o*/
	void selectionSort();
	void bubbleSort();
	void insertionSort();
	void swapSort();
	void shellSort();
	void mergeSort(int begin, int end);
	void merge(int begin, int middle, int end);
	void quickSort(int begin, int end);
	void heapSort();
	void countingSort();
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
	std::pair<int, int> lastElementsCompared;

	//Fun��o auxiliar que indica final da ordena��o (deixa elementos verdes)
	void endSort();

	//Fun��o auxiliar para atualizar a posicao de todo o vetor de dados (utilizada pelo heapSort)
	void updateAllPositions();

	//Fun��o auxiliar para atualizar a posicao de um elemento do vetor (utilizada pelo heapSort)
	void updatePosition(int index);

public:
	Sorting(int width, int height);
	~Sorting();

	/*Ger�ncia da thread*/
	void run();
		void endExecution();

	void setAlgorithm(Algorithm algorithm);
	void startSorting();
	bool getEndSorting();
	
	/*Dados*/
	void generateData(int size);
	void setElements(std::vector<std::pair<int, sf::RectangleShape*>> elements);
	std::vector<std::pair<int, sf::RectangleShape*>> getElements();
	void clearElements();
	int getTotalSwaps();
	int getTotalComparisons();
	void reset();
};

#endif _SORTING_