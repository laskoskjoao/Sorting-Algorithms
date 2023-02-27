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
	Merge
};

class SortingManager {
private:
	/*Dados*/
	int comparisons;
	int swaps;
	bool endSort;
	int size;
	Algorithm algorithm;
	std::vector<std::pair<int, sf::RectangleShape*>> elements;
	void generateData();	//inicializa o vector elements com valores aleatorios

	/*Coleta de entradas*/
	void menu();

	/*Algoritmos de ordenação*/
	std::thread* sort;
	void selectionSort();
	void bubbleSort();
	void insertionSort();
	void mergeSort(int begin, int end);
		void merge(int begin, int middle, int end);
	void differentSort();
	
	//Função auxiliar para realizar o swap de elementos
	void swap(int firstIndex, int secondIndex); //troca elementos e muda sua cor para destacá-los (é chamada pelos algoritmos de ordenação)
		std::pair<int, int> lastIndexesSwap;
	//Função auxiliar para a inserção de elementos
	void insert(int index, std::pair<int, sf::RectangleShape*> element);	//troca elementos e muda sua cor para destacá-los (é chamada pelos algoritmos de ordenação)
		int lastInsertedIndex;
	
	//Função auxiliar que indica os elementos comparados pelo algoritmo atualmente
	void compareElements(int firstIndex, int secondIndex);
		std::pair<int,int> lastElementsCompared;

	/*Gerência da janela*/
	sf::RenderWindow window;
	void mainLoop();							//chama os algoritmos de ordenação e desenha na tela
	void draw();
public:
	SortingManager();
	~SortingManager();
};

#endif // _SORTING_MANAGER_H_#

