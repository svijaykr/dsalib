#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <time.h>
#include "graph.h"
using namespace std;

int main(int arc, char **argv) {
    Vertex<string>* from_airport_node;
    Vertex<string>* to_airport_node;
    Edge<string>* flight;
    Graph<string> routes;

    set<Vertex<string>*, Vertex<string>::VertexCmp> airports;
    set<Vertex<string>*, Vertex<string>::VertexCmp>::iterator it;
    set<Edge<string>*, Edge<string>::Undirected> flights;
    set<Edge<string>*>::iterator it_set;

    std::string line;
    string  airline, from_airport, to_airport;

    time_t begin, end;
    
    set<Vertex<string> >::iterator t_it;

    ifstream infile("routes_test.dat");
    while (getline(infile, line)) {
        time(&begin);
        std::istringstream iss(line);
        if (!(iss >> airline >> from_airport >> to_airport)) { 
            break; 
        } // error
        if (from_airport > to_airport)
            from_airport.swap(to_airport);
        
        cout << flights.size() << endl;
        from_airport_node = new Vertex<string>(from_airport);
        it =  airports.find(from_airport_node);
        time(&end);
        cout << "Debug 1: Time Elapsed: " << difftime(end,begin) << endl;
        time(&begin);
        if (it != airports.end()) {
            from_airport_node = *it;
        }
        else {
            airports.insert(from_airport_node);
        }

        to_airport_node =  new Vertex<string>(to_airport);
        it = airports.find(to_airport_node);
        if (it != airports.end()) {
            to_airport_node = *it;
        }
        else {
            airports.insert(to_airport_node);
        }
        time(&end);
        cout << "Debug 2: Time Elapsed: " << difftime(end,begin) << endl;
        time(&begin);
        flight = new Edge<string>(airline, *from_airport_node, *to_airport_node);
        time(&end);
        cout << "Debug 3: Time Elapsed: " << difftime(end,begin) << endl;
        time(&begin);
        from_airport_node->AddEdge(*flight);
        to_airport_node->AddEdge(*flight);
        cout << flight->GetEdgeValue() << endl;
        flights.insert(flight);
        time(&end);
        cout << "Debug 4: Time Elapsed: " << difftime(end,begin) << endl;
    }
    routes = Graph<string>(airports,flights);
    set<Edge<string> > flight_set;
    Edge<string> carrier;
    set<Edge<string> >::iterator fs_it;
    airports = routes.GetVertexSet();
    Vertex<string>* node;
    for (it = airports.begin(); it != airports.end(); ++it) {
        node = *it;
        cout << "Routes from " << node->GetValue() << endl;
        flight_set = node->GetEdgeSet();
        for (fs_it = flight_set.begin(); fs_it != flight_set.end(); ++fs_it) {
            carrier = *fs_it;
            cout << carrier.GetEdgeValue() << ": " << carrier.GetHeadVertex().GetValue() ;
            cout << "- " << carrier.GetTailVertex().GetValue() << endl;
        }
    }
}
