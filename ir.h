void irGetData(){
    int rawValue;
    for (int i = 0; i < sizeof(irPin) / sizeof(irPin[0]); i++){
        rawValue = analogRead(irPin[i]);
        irDistance[i] = 187754 * pow(rawValue, -1.51);
    }
}

double irGetDistance(string direction){
    switch(direction)
    {
    case "front":
        return irDistance[0];
        break;
    case "back":
        return irDistance[1];
        break;
    case "left":
        return irDistance[2];
        break;
    case "right":
        return irDistance[3];
        break;
    case "up":
        return irDistance[4];
        break;
    case "down":
        return irDistance[5];
        break;
} 