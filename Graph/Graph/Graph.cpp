#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "time.h"

using namespace std;

// структура вершины графа
struct Top
{
	int number;
	int size;
	vector<int> neighbors;
	string color;

	bool operator <(const Top &rhs) {
		return size > rhs.size;
	}
};

// чтение графа построчно из файла с проверками
vector<vector<int>> readMode(string fileName) {
	cout << endl << endl << "-> =R=E=A=D= =M=O=D=E";

	vector<vector<int>> inputData;
	ifstream myInStream;
	myInStream.open(fileName);

	if (!myInStream)
	{
		if (myInStream.eof()) {
			cout << endl << "Err. Empty file";
		}
		else {
			cout << endl << "File not found or other failure";
		}
	}
	// запись строк посимвольно в вектор nums
	if (myInStream.is_open()) {
		string line;
		while (getline(myInStream, line)) {
			stringstream ss(line);
			vector<int> nums;
			int ti;
			while (ss >> ti) {
				nums.push_back(ti);
			}
           // создание вектора соседей для всех вершин
			inputData.push_back(nums);
		}
	}
	myInStream.close();
	cout << endl << "Job done";
	return inputData;
}

// вывод вектора соседей построчно для каждой вершины
void printMode(vector<vector<int>> inputData) {
	cout << endl << endl << "-> =P=R=I=N=T= =M=O=D=E";

	cout << endl;
	for (int i = 0; i < inputData.size(); i++) {
		cout << endl;
		for (int j = 0; j < inputData[i].size(); j++) {
			cout << " " << inputData[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

// создание вектора структур
vector<Top> getGraph(vector<vector<int>> inputData) {
	vector<Top> graph;
	for (int i = 0; i < inputData.size(); i++) {
		Top tmp;
		tmp.number = i;
		tmp.size = inputData[i].size();
		tmp.color = "-1";
		tmp.neighbors = inputData[i];
		graph.push_back(tmp);
	}
	return graph;
}

// вывод вершин графа на экран
void printModeGraph(vector<Top> graph) {
	cout << endl << endl << "-> =P=R=I=N=T= =M=O=D=E =G=R=A=P=H=";

	cout << endl;
	for (int i = 0; i < graph.size(); i++) {
		cout << endl;
		cout << endl << "number = " << graph[i].number;
		cout << endl << "size = " << graph[i].size;
		cout << endl << "color = " << graph[i].color;
		cout << endl << "neighbors:" << endl;
		for (int j = 0; j < graph[i].neighbors.size(); j++) {
			cout << " " << graph[i].neighbors[j];
		}
		cout << endl;
	}
	cout << endl;
}

// функция раскраски графа в 4 цвета по принципу приближенного алгоритма
vector<Top> coloring(vector<Top> igraph) {
	cout << endl << endl << "-> =C=O=L=O=R=I=N=G= =G=R=A=P=H=";
	vector<Top> sgraph = igraph;
	sort(sgraph.begin(), sgraph.end());

	//1 2 3 4 

	//1 ZONE
	{
		sgraph[0].color = "1";
		int index = sgraph[0].number;
		igraph[index].color = "1";

		for (int i = 0; i < sgraph.size(); i++) {
			bool flag = true;

			for (int j = 0; j < sgraph[i].neighbors.size(); j++) {

				if (sgraph[i].neighbors[j] == index) {
					flag = false;
				}

				if (igraph[sgraph[i].neighbors[j]].color == "1") {
					flag = false;
				}
			}
			if (flag) {
				sgraph[i].color = "1";
				igraph[sgraph[i].number].color = "1";
			}
		}
	}
	//1 ZONE END

	//2 ZONE
	{
		int index = -1;
		for (int i = 0; i < sgraph.size(); i++) {
			if (sgraph[i].color == "-1") {
				index = i;
				break;
			}
		}

		if (index == -1) {
			cout << endl << "Job done";
			return igraph;
		}

		sgraph[index].color = "2";
		index = sgraph[index].number;
		igraph[index].color = "2";


		for (int i = 0; i < sgraph.size(); i++) {
			bool flag = true;
			for (int j = 0; j < sgraph[i].neighbors.size(); j++) {
				if (sgraph[i].neighbors[j] == index) {
					flag = false;
				}
				if (igraph[sgraph[i].neighbors[j]].color == "2") {
					flag = false;
				}
			}
			if ((flag) && (sgraph[i].color == "-1")) {
				sgraph[i].color = "2";
				igraph[sgraph[i].number].color = "2";
			}
		}
	}
	//2 ZONE END

	//3 ZONE
	{
		int index = -1;
		for (int i = 0; i < sgraph.size(); i++) {
			if (sgraph[i].color == "-1") {
				index = i;
				break;
			}
		}

		if (index == -1) {
			cout << endl << "Job done";
			return igraph;
		}
		sgraph[index].color = "3";
		index = sgraph[index].number;
		igraph[index].color = "3";

		for (int i = 0; i < sgraph.size(); i++) {
			bool flag = true;
			for (int j = 0; j < sgraph[i].neighbors.size(); j++) {
				if (sgraph[i].neighbors[j] == index) {
					flag = false;
				}
				if (igraph[sgraph[i].neighbors[j]].color == "3") {
					flag = false;
				}
			}
			if ((flag) && (sgraph[i].color == "-1")) {
				sgraph[i].color = "3";
				igraph[sgraph[i].number].color = "3";
			}
		}
	}
	//3 ZONE END

	//4 ZONE
	{
		int index = -1;
		for (int i = 0; i < sgraph.size(); i++) {
			if (sgraph[i].color == "-1") {
				index = i;
				break;
			}
		}

		if (index == -1) {
			cout << endl << "Job done";
			return igraph;
		}
		sgraph[index].color = "4";
		index = sgraph[index].number;
		igraph[index].color = "4";

		for (int i = 0; i < sgraph.size(); i++) {
			bool flag = true;
			for (int j = 0; j < sgraph[i].neighbors.size(); j++) {
				if (sgraph[i].neighbors[j] == index) {
					flag = false;
				}
				if (igraph[sgraph[i].neighbors[j]].color == "4") {
					flag = false;
				}
			}
			if ((flag) && (sgraph[i].color == "-1")) {
				sgraph[i].color = "4";
				igraph[sgraph[i].number].color = "4";
			}
		}
	}
	//4 ZONE END

	
	cout << endl << "Job done";
	return igraph;
}


int main()
{
	
	string fileName = "in.txt";
	cout << endl << "-> file name: " << fileName;
	vector<vector<int>> inputData;

	inputData = readMode(fileName);
	printMode(inputData);

	vector<Top> graph;
	graph = getGraph(inputData);
	printModeGraph(graph);

	
	
	vector<Top> coloringGraph;
	double t = clock();
	coloringGraph = coloring(graph);
	double tFin = (clock() - t) / CLOCKS_PER_SEC;
	printModeGraph(coloringGraph);
	cout << endl << "time:" << tFin << " sec" << endl;

	system("pause");
	return 0;
}