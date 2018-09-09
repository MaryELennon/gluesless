#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>

#include "Snap.h"

//#include <progress.hpp>
//#include <progress_bar.hpp>

//#include "Idea.h"
//#include "Networkland.h"
#include "Timeline.h"

//! main
/*!
  main method
  */
  
int main(int argc, char* argv[]){
  
  // manage input arguments
  TStr pajek_file_path;
  std::string ideas_file_path;
  std::string output_file_path;
  for (int i = 1; i < argc; i++) {  
    if (i + 1 != argc){
      if (strcmp(argv[i], "-pajekfile") == 0 | strcmp(argv[i], "-pi") == 0) {
          pajek_file_path = argv[i + 1];
          i++;
      }
      if (strcmp(argv[i], "-ideasfile") == 0 | strcmp(argv[i], "-ii") == 0) {
          ideas_file_path = argv[i + 1];
          i++;
      }
      if (strcmp(argv[i], "-outputfile") == 0 | strcmp(argv[i], "-o") == 0) {
          output_file_path = argv[i + 1];
          i++;
      }
    }
  }
  
  // create world
  Networkland* real = new Networkland(pajek_file_path);
  Aether* overmind = new Aether(real, ideas_file_path);
  Timeline* thyme = new Timeline(overmind);

  // create ideas
  // Idea* cremation = new Idea("cremation", real, {1});
  // Idea* inhumation = new Idea("inhumation", real, {2});
  // Idea* flat = new Idea("flat", real);
  // Idea* mound = new Idea("mound", real);
  
  // overmind->add_idea_to_mindspace(cremation);
  // overmind->add_idea_to_mindspace(inhumation);
  // overmind->add_idea_to_mindspace(flat);
  // overmind->add_idea_to_mindspace(mound);
  
  // develop
  int graph_size;
  while (true) {
    
    thyme->develop();
    
    int new_graph_size = thyme->get_graph_size_over_time().back();
    if (graph_size == new_graph_size) {
      break;
    }
    graph_size = new_graph_size;
    
    printf("remaining nodes: ");
    printf(std::to_string(graph_size).c_str());
    printf("      ");
    printf("\r");
    fflush(stdout);
    
  }
  
  // file output
  thyme->export_to_text_file(output_file_path);

  // console output
  // std::vector<int> cremation_nodes = cremation->get_nodes();
  // std::vector<int> inhumation_nodes = inhumation->get_nodes();

  printf("remaining nodes: ");
  printf(std::to_string(thyme->get_graph_size_over_time().back()).c_str());
  printf(" (final)");
  printf("\n");
  // printf("cremation: ");
  // printf(std::to_string(cremation_nodes.size()).c_str());
  // printf("\n");
  // printf("inhumation: ");
  // printf(std::to_string(inhumation_nodes.size()).c_str());
  // printf("\n");

  // cleaning up 
  delete real;
  delete overmind;
  delete thyme;
  // delete cremation;
  // delete inhumation;
  // delete flat;
  // delete mound;

  return 0;
}
