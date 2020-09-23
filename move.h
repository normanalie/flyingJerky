void move(string direction){
    int step = 1;
    switch(direction)
    {
    case "front":
        moveFront(step);
        break;
    
    case "back":
        moveBack(step);
        break;

    case "left":
        moveLeft(step);
        break;

    case "right":
        moveRight(step);
        break;

    case "up":
        moveUp(step);
        break;
 
    case "back":
        moveBack(step);
        break;
    }
    
    case "stop":
        flat();
        break;
    
    case default;
        flat();
        break;
}

