#define RIGHT_MOTORS_POWER 26 
#define RIGHT_MOTORS_GROUND 25 
#define LEFT_MOTORS_POWER 33 
#define LEFT_MOTORS_GROUND 32
//#define RIGHT_MOTORS_POWER 14 
//#define RIGHT_MOTORS_GROUND 27 
// #define LEFT_MOTORS_POWER 26 
// #define LEFT_MOTORS_GROUND 25 

#define high 200

void setup() {
    // Setup pins
    pinMode(RIGHT_MOTORS_POWER, OUTPUT);
    pinMode(RIGHT_MOTORS_GROUND, OUTPUT);
    pinMode(LEFT_MOTORS_POWER, OUTPUT);
    pinMode(LEFT_MOTORS_GROUND, OUTPUT);


    // Start motors. 
    // TODO: try different functions.
    drive_forward();
    //delay(5000);  // Let motors spin for 2 seconds
    //stop();  // Stop function
}
void drive_forward() {
    analogWrite(RIGHT_MOTORS_POWER, high);
    digitalWrite(RIGHT_MOTORS_GROUND, LOW);

    analogWrite(LEFT_MOTORS_POWER, high);
    digitalWrite(LEFT_MOTORS_GROUND, LOW);
}

void drive_backward() {
    digitalWrite(RIGHT_MOTORS_POWER,LOW);
    digitalWrite(RIGHT_MOTORS_GROUND,high);

    digitalWrite(LEFT_MOTORS_POWER,LOW);
    digitalWrite(LEFT_MOTORS_GROUND,high);
}

void turn_right() {
    digitalWrite(RIGHT_MOTORS_POWER,high);
    digitalWrite(RIGHT_MOTORS_GROUND,LOW);

    digitalWrite(LEFT_MOTORS_POWER,LOW);
    digitalWrite(LEFT_MOTORS_GROUND,high);
}

void turn_left() {
    digitalWrite(RIGHT_MOTORS_POWER,LOW);
    digitalWrite(RIGHT_MOTORS_GROUND,high);

    digitalWrite(LEFT_MOTORS_POWER,high);
    digitalWrite(LEFT_MOTORS_GROUND,LOW);
}

void stop(){
    digitalWrite(RIGHT_MOTORS_POWER, LOW);
    digitalWrite(RIGHT_MOTORS_GROUND, LOW);

    digitalWrite(LEFT_MOTORS_POWER, LOW);
    digitalWrite(LEFT_MOTORS_GROUND, LOW);
}


void loop() {}
