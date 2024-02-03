#define RIGHT_MOTORS_POWER 14 
#define RIGHT_MOTORS_GROUND 27 
#define LEFT_MOTORS_POWER 26 
#define LEFT_MOTORS_GROUND 25 

void setup() {
    // Setup pins
    pinMode(RIGHT_MOTORS_POWER, OUTPUT);
    pinMode(RIGHT_MOTORS_GROUND, OUTPUT);
    pinMode(LEFT_MOTORS_POWER, OUTPUT);
    pinMode(LEFT_MOTORS_GROUND, OUTPUT);


    // Start motors. 
    // TODO: try different functions.
    drive_forward();
    delay(5000);  // Let motors spin for 2 seconds
    stop();  // Stop function
}
void drive_forward() {
    digitalWrite(RIGHT_MOTORS_POWER,HIGH);
    digitalWrite(RIGHT_MOTORS_GROUND,LOW);

    digitalWrite(LEFT_MOTORS_POWER,HIGH);
    digitalWrite(LEFT_MOTORS_GROUND,LOW);
}

void drive_backward() {
    digitalWrite(RIGHT_MOTORS_POWER,LOW);
    digitalWrite(RIGHT_MOTORS_GROUND,HIGH);

    digitalWrite(LEFT_MOTORS_POWER,LOW);
    digitalWrite(LEFT_MOTORS_GROUND,HIGH);
}

void turn_right() {
    digitalWrite(RIGHT_MOTORS_POWER,HIGH);
    digitalWrite(RIGHT_MOTORS_GROUND,LOW);

    digitalWrite(LEFT_MOTORS_POWER,LOW);
    digitalWrite(LEFT_MOTORS_GROUND,HIGH);
}

void turn_left() {
    digitalWrite(RIGHT_MOTORS_POWER,LOW);
    digitalWrite(RIGHT_MOTORS_GROUND,HIGH);

    digitalWrite(LEFT_MOTORS_POWER,HIGH);
    digitalWrite(LEFT_MOTORS_GROUND,LOW);
}

void stop(){
    digitalWrite(RIGHT_MOTORS_POWER, LOW);
    digitalWrite(RIGHT_MOTORS_GROUND, LOW);

    digitalWrite(LEFT_MOTORS_POWER, LOW);
    digitalWrite(LEFT_MOTORS_GROUND, LOW);
}


void loop() {}
