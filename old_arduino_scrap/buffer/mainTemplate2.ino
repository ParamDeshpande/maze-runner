void loop()
{  
  delay(400);   
  
  while(1){
    int temp = 0;
    while(!temp)
    {
      move_single_cell();
      delay(1000);
      temp = check_front_wall();
    }
    turn_left();
    delay(1000);
  }
  