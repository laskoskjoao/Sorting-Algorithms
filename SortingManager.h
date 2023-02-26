#pragma once
#ifndef _SORTING_MANAGER_H_
#define _SORTING_MANAGER_H_
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>

enum Algorithm {
	Selection,
	Bubble
};

class SortingManager {
private:
	/*Dados*/
	bool endSort;
	int size;
	Algorithm algorithm;
	std::vector<std::pair<int, sf::RectangleShape*>> elements;
	void generateData();	//inicializa o vector elements

	/*Coleta de entradas*/
	void menu();

	/*Algoritmos de ordenação*/
	void selectionSort();
	
	//Função auxiliar para realizar o swap de elementos
	void swap(int firstIndex, int secondIndex); //troca elementos e muda sua cor para destacá-los (é chamada pelos algoritmos de ordenação)
	std::pair<int, int> lastIndexesSwap;

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

