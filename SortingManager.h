#pragma once
#ifndef _SORTING_MANAGER_H_
#define _SORTING_MANAGER_H_
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Sorting.h"
/*
enum Algorithm {
	Selection,
	Bubble,
	Insertion,
	My,
	Merge,
	Quick,
	Counting
};*/

class SortingManager {
private:
	/*Dados*/
	int comparisons;
	int swaps;
	//bool endSorting;
	int size;
	Algorithm algorithm;

	Sorting* sorting;
	/*Coleta de entradas*/
	void menu();

	std::thread sort;

	/*Gerência da janela*/
	sf::RenderWindow window;
	void mainLoop();							//chama os algoritmos de ordenação e desenha na tela
	void draw();
public:
	SortingManager();
	~SortingManager();
};

#endif // _SORTING_MANAGER_H_#

