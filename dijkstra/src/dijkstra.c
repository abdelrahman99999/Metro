/*
 ============================================================================
 Name        : dijkstra.c
 Author      : Abdelrahman Elsayed
 Version     : v.1
 Description : Metro application
 ============================================================================
 */

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_VERTICES 100



char * stations_names[MAX_VERTICES]={
		"Helwan",
		"Ain Helwan",
		"Helwan University",
		"Wadi Hof",
		"Helwan Gardens",
		"Elmasarah",
		"Tora Cement",
		"Kotsika",
		"Tora El Balad",
		"Maadi Thaknat",
		"Maadi",
		"Maadi Gardens",
		"Dar ElSalaam",
		"Al-Zahra",
		"Saint George",
		"The good king",
		"Elsyda Zeinab",
		"Saad Zaghloul",
		"Anwar Sadat",
		"Gamal Abdel Nasser",
		"Ahmed Orabi",
		"Elshohda",
		"Gamra",
		"Demerdash",
		"Manshiet Al-Sadr",
		"Qubba Bridge",
		"Qubba baths",
		"Saray al-Qubba",
		"Olive Gardens",
		"Helmeyat al-Zaytoun",
		"Al-Mataria",
		"Ain Shams",
		"Ezbet El Nakhl",
		"Al-Marj",
		"New Marj",

		"Al-Munib",
		"Saqia Mekki",
		"Om Elmasryeen",
		"Giza",
		"Faisal",
		"Cairo University",
		"Elbhoth",
		"Dokki",
		"Opera",
		"",//Anwar Sadat
		"Muhammad Naguib",
		"Attaba",
		"",//Elshohda
		"msraa",
		"Rawd Al-Faraj",
		"Santa Teresa",
		"Al-Khalafawi",
		"Elmzlat",
		"College of Agriculture",
		"Shubra El Kheima",

		"Adly Mansour",
		"Al-Haikstab",
		"Omar bin al-khattab",
		"Quba",
		"Hisham Barakat",
		"Nozha",
		"Sun Club",
		"Alf Maskn",
		"Heliopolis",
		"Aaron",
		"Al-Ahram ",
		"Girls' College",
		"Stadium",
		"Fair grounds",
		"Abbasiya",
		"Abdo Pasha",
		"Elgysh",
		"Bab Elshaarya",
		" ",//Attaba
		"  ",//Gamal Abdel Nasser
		"Maspero",
		"Safaa Hegazy",
		"Kit Kat",
		"Sudan",
		"Imbaba",
		"Bohy",
		"Elkomya",
		"Ring road",
		"Rod Al-Farag axis",
		"Eltofykya",
		"Nile Vally",
		"League Of Arab States",
		"Bolak Eldkror",
		" "//Cairo University


};

// Structure to represent a graph
struct Graph {
    int numVertices;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
};

// Function to initialize a graph
void initializeGraph(struct Graph* graph, int numVertices) {
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->adjacencyMatrix[src][dest] = weight;
    graph->adjacencyMatrix[dest][src] = weight;
}

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[], int numVertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < numVertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to print the shortest path
void printPath(int parent[], int dest) {
    if (parent[dest] == -1) {
        printf("%s -> ", stations_names[dest]);
        return;
    }

    printPath(parent, parent[dest]);
    printf("%s -> ", stations_names[dest]);
}


// Function to implement Dijkstra's algorithm
void dijkstra(struct Graph* graph, int src, int dest) {
    int numVertices = graph->numVertices;
    int dist[numVertices];  // Array to store the shortest distance from source to each vertex
    bool visited[numVertices];  // Array to keep track of visited vertices
    int parent[numVertices];  // Array to store the shortest path tree

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = minDistance(dist, visited, numVertices);
        visited[u] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph->adjacencyMatrix[u][v] != 0 &&
                dist[u] != INT_MAX && dist[u] + graph->adjacencyMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjacencyMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Shortest path from %s to %s: \n", stations_names[src], stations_names[dest]);
    printPath(parent, dest);
    printf("\nShortest distance: %d\n", dist[dest]);
}

// Example usage
int main() {
    struct Graph graph;
    int numVertices = 100;
    initializeGraph(&graph, numVertices);

    // Adding edges to the graph
    //1st line
    addEdge(&graph, 0, 1, 1);			//  Helwan               - 	Ain Helwan
    addEdge(&graph, 1, 2, 1);           //  Ain Helwan           - 	Helwan University
    addEdge(&graph, 2, 3, 1);           //  Helwan University    - 	Wadi Hof
    addEdge(&graph, 3, 4, 1);           //  Wadi Hof             - 	Helwan Gardens
    addEdge(&graph, 4, 5, 1);           //  Helwan Gardens       - 	Elmasarah
    addEdge(&graph, 5, 6, 1);           //  Elmasarah            - 	Tora Cement
    addEdge(&graph, 6, 7, 1);           //  Tora Cement          - 	Kotsika
    addEdge(&graph, 7, 9, 1);           //  Kotsika              - 	Tora El Balad
    addEdge(&graph, 8, 9, 1);           //  Tora El Balad        - 	Maadi Thaknat
    addEdge(&graph, 9, 10, 1);          //	Maadi Thaknat        -  Maadi
    addEdge(&graph, 10, 11, 1);         //	Maadi                -  Maadi Gardens
    addEdge(&graph, 11, 12, 1);         //	Maadi Gardens        -  Dar ElSalaam
    addEdge(&graph, 12, 13, 1);         //	Dar ElSalaam	     -  Al-Zahra
    addEdge(&graph, 13, 14, 1);         //	Al-Zahra 	         -  Saint George
    addEdge(&graph, 14, 15, 1);         //	Saint George 	     -  The good king
    addEdge(&graph, 15, 16, 1);         //	The good king 	     -  Elsyda Zeinab
    addEdge(&graph, 16, 17, 1);         //	Elsyda Zeinab 	     -  Saad Zaghloul
    addEdge(&graph, 17, 18, 1);         //	Saad Zaghloul 	     -  Anwar Sadat
    addEdge(&graph, 18, 19, 1);         //	Anwar Sadat          -  Gamal Abdel Nasser
    addEdge(&graph, 19, 20, 1);         //	Gamal Abdel Nasser   -  Ahmed Orabi
    addEdge(&graph, 20, 21, 1);         //	Ahmed Orabi 	     -  Elshohda
    addEdge(&graph, 21, 22, 1);         //	Elshohda 	         -  Gamra
    addEdge(&graph, 22, 23, 1);         //	Gamra 	             -  Demerdash
    addEdge(&graph, 23, 24, 1);         //	Demerdash            -  Manshiet Al-Sadr
    addEdge(&graph, 24, 25, 1);         //	Manshiet Al-Sadr     -  Qubba Bridge
    addEdge(&graph, 25, 26, 1);         //	Qubba Bridge         -  Qubba baths
    addEdge(&graph, 26, 27, 1);         //	Qubba baths          -  Saray al-Qubba
    addEdge(&graph, 27, 28, 1);         //	Saray al-Qubba 	     -  Olive Gardens
    addEdge(&graph, 28, 29, 1);         //	Olive Gardens 	     -  Helmeyat al-Zaytoun
    addEdge(&graph, 29, 30, 1);         //	Helmeyat al-Zaytoun  -  Al-Mataria
    addEdge(&graph, 30, 31, 1);         //	Al-Mataria           -  Ain Shams
    addEdge(&graph, 31, 32, 1);         //	Ain Shams 		     -  Ezbet El Nakhl
    addEdge(&graph, 32, 33, 1);         //	Ezbet El Nakhl 	     -  Al-Marj
    addEdge(&graph, 33, 34, 1);         //	Al-Marj 	         -  New Marj

    //2nd line
    addEdge(&graph, 35+0, 35+1, 1);     //  Al-Munib                -  	Saqia Mekki
    addEdge(&graph, 35+1, 35+2, 1);     //  Saqia Mekki 		    -  	Om Elmasryeen
    addEdge(&graph, 35+2, 35+3, 1);     //  Om Elmasryeen           -  	Giza
    addEdge(&graph, 35+3, 35+4, 1);     //  Giza 			        -  	Faisal
    addEdge(&graph, 35+4, 40, 1);       //  Faisal 			        -  	Cairo University
    addEdge(&graph, 40, 35+6, 1);       //  Cairo University 	    -  	Elbhoth
    addEdge(&graph, 35+6, 35+7, 1);     //  Elbhoth                 -  	Dokki
    addEdge(&graph, 35+7, 35+8, 1);     //  Dokki 			        -  	Opera
    addEdge(&graph, 35+8, 18, 1);       //  Opera 			        -  	Anwar Sadat
    addEdge(&graph,18, 35+10, 1);       //	Anwar Sadat             -  	Muhammad Naguib
    addEdge(&graph, 35+10,35+ 11, 1);   //	Muhammad Naguib 		-  	Attaba
    addEdge(&graph, 35+11,21, 1);       //	Attaba                  -  	Elshohda
    addEdge(&graph, 21,35+ 13, 1);      //	Elshohda 	            -  	msraa
    addEdge(&graph, 35+13,35+ 14, 1);   //	msraa 				    -  	Rawd Al-Faraj
    addEdge(&graph, 35+14,35+ 15, 1);   //	Rawd Al-Faraj 			-  	Santa Teresa
    addEdge(&graph, 35+15,35+ 16, 1);   //	Santa Teresa 			-  	Al-Khalafawi
    addEdge(&graph, 35+16,35+ 17, 1);   //	Al-Khalafawi 			-  	Elmzlat
    addEdge(&graph, 35+17,35+ 18, 1);   //	Elmzlat			        -  	College of Agriculture
    addEdge(&graph, 35+18,35+ 19, 1);   //	College of Agriculture 	-  	Shubra El Kheima


    //3rd line
    addEdge(&graph, 55+0, 55+1, 1);      //	Adly Mansour	      - 	Al-Haikstab
    addEdge(&graph, 55+1, 55+2, 1);      //	Al-Haikstab			  - 	Omar bin al-khattab
    addEdge(&graph, 55+2, 55+3, 1);      //	Omar bin al-khattab	  - 	Quba
    addEdge(&graph, 55+3, 55+4, 1);      //	Quba			      - 	Hisham Barakat
    addEdge(&graph, 55+4, 55+5, 1);      //	Hisham Barakat	      - 	Nozha
    addEdge(&graph, 55+5, 55+6, 1);      //	Nozha	              - 	Sun Club
    addEdge(&graph, 55+6, 55+7, 1);      //	Sun Club	          - 	Alf Maskn
    addEdge(&graph, 55+7, 55+9, 1);      //	Alf Maskn             - 	Heliopolis
    addEdge(&graph, 55+8, 55+9, 1);      //	Heliopolis            - 	Aaron
    addEdge(&graph, 55+9, 55+10, 1);     //	Aaron                 - 	Al-Ahram
    addEdge(&graph, 55+10,55+ 11, 1);    //	Al-Ahram              - 	Girls' College
    addEdge(&graph, 55+11,55+ 12, 1);    //	Girls' College        - 	Stadium
    addEdge(&graph, 55+12,55+ 13, 1);    //	Stadium               - 	Fair grounds
    addEdge(&graph, 55+13,55+ 14, 1);    //	Fair grounds 	      - 	Abbasiya
    addEdge(&graph, 55+14,55+ 15, 1);    //	Abbasiya 	          - 	Abdo Pasha
    addEdge(&graph, 55+15,55+ 16, 1);    //	Abdo Pasha 		      - 	Elgysh
    addEdge(&graph, 55+16,55+ 17, 1);    //	Elgysh 	              - 	Bab Elshaarya
    addEdge(&graph, 55+17,46, 1);        //	Bab Elshaarya         - 	Attaba
    addEdge(&graph, 46, 19, 1);          //	Attaba	              - 	Gamal Abdel Nasser
    addEdge(&graph, 19,55+ 20, 1);       //	Gamal Abdel Nasser    - 	Maspero
    addEdge(&graph, 55+20,55+ 21, 1);    //	Maspero               - 	Safaa Hegazy
    addEdge(&graph, 55+21,77, 1);        //	Safaa Hegazy 	      - 	Kit Kat
    addEdge(&graph, 77,55+ 23, 1);       //	Kit Kat 	          - 	Sudan
    addEdge(&graph, 55+23,55+ 24, 1);    //	Sudan	              - 	Imbaba
    addEdge(&graph, 55+24,55+ 25, 1);    //	Imbaba	              - 	Bohy
    addEdge(&graph, 55+25,55+ 26, 1);    //	Bohy                  - 	Elkomya
    addEdge(&graph, 55+26,55+ 27, 1);    //	Elkomya               - 	Ring road
    addEdge(&graph, 55+27,55+ 28, 1);    //	Ring road             - 	Rod Al-Farag axis
    addEdge(&graph, 77,55+ 29, 1);       //	Kit Kat               -     Eltofykya
    addEdge(&graph, 55+29,55+ 30, 1);    // Eltofykya             - 	Nile Vally
    addEdge(&graph, 55+30,55+ 31, 1);    // Nile Vally            -     League Of Arab States
    addEdge(&graph, 55+31,55+ 32, 1);    // League Of Arab States -     Bolak Eldkror
    addEdge(&graph, 55+32,40, 1);        // Bolak Eldkror         -     Cairo University


    int source = 35;
    int destination = 77;
    dijkstra(&graph, source, destination);

    return 0;
}


