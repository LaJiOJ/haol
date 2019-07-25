#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<queue>
using namespace std;

const int MAX_VERTICES = 10000;
enum Color { WHITE, GRAY, BLACK };
enum BiColor { RED, BLUE };
extern bool FindMatch();
struct Vertex {
	int color;
	int biparititeColor;
	int discoverTime;
	int back;
};
vector<int>edge[MAX_VERTICES];//the adjacency List
vector<Vertex>vertex;
queue<int>queNode;

int main() {
	Vertex tempVertex;
	string inStr;
	tempVertex.back = 0;
	tempVertex.discoverTime = 0;
	tempVertex.color = WHITE;
	tempVertex.biparititeColor = RED;
	int index = 0;
	int linkPoint = 0;
	bool flag = true;
	unsigned i;
	unsigned j;
	while (getline(cin, inStr)) {
		flag = true;
		i = 0;
		j = 0;
		while (i < inStr.size()) {
			if (inStr[i] == ' ') {
				inStr[i] = '\0';
				if (flag) {
					index = stoi(inStr.substr(j, i));
					flag = false;
					vertex.push_back(tempVertex);
				}
				else {
					edge[index].push_back(stoi(inStr.substr(j, i)));
				}
				j = i + 1;
				i = j;
			}
			++i;
		}
	}
	printf("wo yi yue du guan yu chao xi de shuo ming\n");
	if (FindMatch()) {
		for (unsigned i = 0; i < vertex.size(); i++) {
			if (vertex[i].biparititeColor == RED) {
				printf("%d\n", i);
			}
		}
	}
	return 0;
}

bool FindMatch() {
	vertex[0].color = GRAY;
	vertex[0].biparititeColor = RED;
	queNode.push(0);
	int w;
	int x;
	while (!queNode.empty()) {
		w = queNode.front();
		queNode.pop();
		for (int i = 0; i < edge[w].size(); i++) {
			x = edge[w][i];
			if (vertex[x].color == WHITE) {
				vertex[x].color = GRAY;
				vertex[x].biparititeColor = ~vertex[w].biparititeColor;
				queNode.push(x);
			}
			else if (vertex[x].biparititeColor == vertex[w].biparititeColor) {
				return false;
			}
		}
		vertex[w].color = GRAY;
	}
	return true;
}