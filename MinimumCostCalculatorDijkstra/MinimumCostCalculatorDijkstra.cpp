//Lukas Jehle #20009320

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/* Implement the Graph class  */
struct Node {
    char nodekey;
    int distance;
    Node* next;
};

struct GraphNode {
    char graphNodeKey;
    Node* listpointer;
};

void AddNodeToFront(Node*& listpointer, char newkey, int newdistance) {
    Node* temp;
    temp = new Node;
    temp->nodekey = newkey;
    temp->distance = newdistance;
    temp->next = listpointer;
    listpointer = temp;
}

void PrintLinkedListNodes(Node* listPointer) {
    Node* temp = listPointer;
    while (temp != NULL) {
        if (temp->next != NULL) {
            printf("%c(%d)-->", temp->nodekey, temp->distance);
        }
        else {
            printf("%c(%d)", temp->nodekey, temp->distance);
        }
        temp = temp->next;
    }
}

int min(int distance1, int distance2) {
    if (distance1 < distance2) { return distance1; }
    return distance2;
}



class Graph {
private:
    vector<GraphNode> adjlist;
public:
    Graph() {};
    ~Graph() {};
    void AddNewGraphNode(char newGraphNode);
    void AddNewEdgeBetweenGraphNodes(char source, char destination, int distance);
    void PrintGraph();
    void Dijkstra(char sourceNode);
};

void Graph::AddNewGraphNode(char newGraphNode) {
    GraphNode temp;
    temp.graphNodeKey = newGraphNode;
    temp.listpointer = NULL;
    adjlist.push_back(temp);
}

void Graph::AddNewEdgeBetweenGraphNodes(char source, char destination, int distance) {
    //find index of source node
    unsigned int a;
    for (a = 0; a < adjlist.size(); a++) {
        if (source == adjlist[a].graphNodeKey) break;
    }
    AddNodeToFront(adjlist[a].listpointer, destination, distance);
}

void Graph::PrintGraph() {
    for (unsigned int i = 0; i < adjlist.size(); i++) {
        printf("%c-->", adjlist[i].graphNodeKey);
        PrintLinkedListNodes(adjlist[i].listpointer);
        printf("\n");
    }
}

void Graph::Dijkstra(char sourceNodeKey) {
    int numberOfNodes = adjlist.size();
    int sourceNodeIndex = 0;
    int current;
    int d[20];
    bool s[20];


    //Get index of sourceNodeKey
    for (int i = 0; i < numberOfNodes; i++) {
        if (adjlist[i].graphNodeKey == sourceNodeKey) {
            sourceNodeIndex = i;
            break;
        }
    }
    d[sourceNodeIndex] = 0; //distance sourceNode to sourceNode = 0
    s[sourceNodeIndex] = true; //true = permanent or 'p'
    current = sourceNodeIndex; //load current with sourcenode

    //Load other nodes with temp state and distance = infinte
    for (int i = 0; i < numberOfNodes; i++) {
        if (i != sourceNodeIndex) {
            d[i] = 99999;
            s[i] = false; //false = temporary or 't'
        }
    }
    for (int i = 0; i < numberOfNodes - 1; i++) {
        Node* temp = adjlist[current].listpointer;
        while (temp != NULL) {
            //find index that corresponds to node key
            int indx = 0;
            for (int k = 0; k < numberOfNodes; k++) {
                if (temp->nodekey == adjlist[k].graphNodeKey) {
                    indx = k;
                    break;
                }
            }
            //cout << "updated node " << adjlist[indx].graphNodeKey << " old cost " << d[indx];
            d[indx] = min(d[indx], d[current] + temp->distance);
            //cout << " new cost " << d[indx] << endl;
            temp = temp->next;
        }

        int min = 9999;
        int minIndx = 0;
        for (int j = 0; j < numberOfNodes; j++) {
            if (s[j] == false) {

                if (d[j] < min) {
                    min = d[j];
                    minIndx = j;
                }
            }
        }
        current = minIndx;
        s[current] = true;
    }

    for (char i = 'B'; i <= 'Z'; i++) {
        for (int j = 0; j < numberOfNodes; j++) {
            if (j != sourceNodeIndex) {
                if (adjlist[j].graphNodeKey == i) {
                    printf("From %c to %c:%d\n", sourceNodeKey, adjlist[j].graphNodeKey, d[j]);
                }
            }
        }
    }
}



/* declare a new Graph */
Graph myGraph;


int main(int argc, char** argv) {//get filename from arguments
  //read an input text file
    string expression;
    ifstream input_file;
    if (argc != 2) { cout << "Type a file name. " << endl << argv[1] << endl; exit(0); }
    input_file.open(argv[1]);
    if (input_file.is_open() == false) { cout << "Could not read file: " << endl << argv[1] << endl; exit(0); }
    string token;
    while (!input_file.eof()) {
        getline(input_file, expression);
        stringstream line(expression);
        if (input_file.eof()) break;
        if (expression[0] == '#') continue;//jump line, this is a line of comments
        char node_name;
        if (expression[0] == 'N' && expression[1] == 'o') {//read a Node name, single character
            getline(line, token, ' ');
            getline(line, token, ' ');
            node_name = (token.c_str())[0];
            //cout << "Node " << node_name << endl;//Comment this out on the final version
            /* Insert nodes into the graph */
            myGraph.AddNewGraphNode(node_name);
            /* */
        }
        else {
            char nodefrom;
            getline(line, token, ' ');
            nodefrom = (token.c_str())[0];
            //cout << "From " << nodefrom;//Comment this out on the final version
            char nodeto;
            getline(line, token, ' ');
            nodeto = (token.c_str())[0];
            //cout << " to " << nodeto; //Comment this out on the final version
            int cost;
            getline(line, token, ' ');
            cost = stoi(token);//only works with option -std=c++11
            cost = atoi(token.c_str());//use this one if your compiler is not C++11
            //cout << " costs " << cost << endl;//Comment this out on the final version
            /* Insert these edges into the graph */
            myGraph.AddNewEdgeBetweenGraphNodes(nodefrom, nodeto, cost);
            /*  */
        }
    }
    myGraph.Dijkstra('A');
    /* After loading the graph from the text file in the while loop above, run your implementation of Dijkstra here*/
    /* Dijkstra can be implemented either as a function or as a method of the class Graph


    /* call Dijkstra  */


    /* Print answer in the required format */

}
