#include "../include/commons.h"

#include "../include/test_run.h"
#include "../include/path_planner.h"


void init_MAZE(void){
    /**maze solving setup**/
  my_maze = new_Maze(); //initialize new maze
  my_stack = new_Stack(); //initialize new stack
  x = START_X;
  y = START_Y;
  direction = NORTH;
  found_dest = FALSE;
  
  frontwallflag = 0;
  noWall = 0;
}

void swipe_to_begin(void){

//swipe
  while(!leftSeen || !rightSeen )
  {
    Serial.println(leftSensor); 
    readSensor(); 
    if( leftSensor > 600 )
      leftSeen = true;
    if( rightSensor > 600 ) 
      rightSeen = true; 
  }
  delay(400);   
  
}

///////////////////
///// DEBUG ///////
///////////////////
/* prints the flood values of each cell in the maze */
void print_map_serial (const Maze * this_maze) {

  short i, j;

  Serial.print("CURRENT MAP VALUES: \n");
  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      if(MAPIJ->floodval < 10)
        Serial.print(" ");
      Serial.print(MAPIJ->floodval);
      Serial.print(" ");
    } 
    Serial.print("\n");
  }
  Serial.print("\n");
}




void while_not_finished(void){

//  while the center destination hasn't been reached
  while(!found_dest){
    Serial.println("start"); 
     fire_and_get();
     
     visit_next_node(my_maze,my_stack,x,y,TRUE); //visit node in front to detect LEFT/RIGHTwalls
     visit_node(my_maze,my_stack,x,y,TRUE); //visit current node to detect FRONT walFpls
     delay(100); //Why the delay ??
     
     change_dir(my_maze,&x,&y,&direction); //turns the mouse to face the direction of best path. updates location (x,y)
     delay(100); 
     move_single_cell();   // move a single cell forward in direction chosen by change_dir
     

     check_goal_reached(&x, &y, &found_dest); //neccesary to know if mouse should stop, will t found_dest flag
     
     print_map_serial(my_maze); //Debugging: prints out flood values of the maze to Serial port
     Serial.println("end"); 
  }

  ////redo floodfill

  ////speed runs?
}
