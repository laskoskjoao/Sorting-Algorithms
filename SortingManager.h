#pragma once
#ifndef _SORTING_MANAGER_H_
#define _SORTING_MANAGER_H_
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Sorting.h"

class SortingManager {
private:
	/*Dados*/
	int lastComparisons;
	int lastSwaps;
	//bool endSorting;
	int size;
	Algorithm algorithm;

	Sorting sorting;
	sf::Text swapsText;
	sf::Text comparisonsText;

	/*Coleta de entradas*/
	void menu();

	std::thread sort;

	/*Ger?ncia da janela*/
	sf::RenderWindow window;
	void mainLoop();							//chama os algoritmos de ordena??o e desenha na tela
	void draw();
public:
	SortingManager();
	~SortingManager();
};

#endif // _SORTING_MANAGER_H_#

