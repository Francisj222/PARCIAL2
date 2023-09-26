const int buttonAPin = 2; // Pin para el botón A
const int buttonBPin = 3; // Pin para el botón B
const int leds[] = {A0, A1, A2, A3, A4, A5, A6, A7};  // Pines analógicos para los LEDs
const int segmentPins[] = {4, 5, 6, 7, 8, 9, 10}; // Pines para los segmentos a-g
const int displayPins[] = {11, 12}; // Pines para seleccionar display (cátodo común)

byte registroA = 0; byte registroB = 0; byte registroC = 0;
byte nibble1, nibble2;

byte segmentos[] = {
B00111111,	//	0
B00000110,	//	1
B01011011,	//	2
B01001111,	//	3
B01100110,	//	4
B01101101,	//	5
B01111101,	//	6
B00000111,	//	7

 
B01111111,  // 8
B01101111   // 9
};


void setup() {
pinMode(buttonAPin, INPUT_PULLUP); pinMode(buttonBPin, INPUT_PULLUP); for (int i = 0; i < 8; i++) {
pinMode(leds[i], OUTPUT);
}
for (int i = 0; i < 7; i++) {
pinMode(segmentPins[i], OUTPUT);
}
for (int i = 0; i < 2; i++) {
pinMode(displayPins[i], OUTPUT);
}
}

void loop() {
// Control de anti-rebotes para el botón A
if (digitalRead(buttonAPin) == LOW) {
delay(50); // Anti-rebote
if (digitalRead(buttonAPin) == LOW) {
registroA++;
if (registroA > 255) {
registroA = 0;
}
}
}

// Control de anti-rebotes para el botón B
static unsigned long lastButtonBPress = 0;
const unsigned long antiBounceDelay = 50; // milisegundos

if (digitalRead(buttonBPin) == LOW && (millis() - lastButtonBPress >
antiBounceDelay)) { lastButtonBPress = millis(); registroC--;
if (registroC < 0) {
registroC = 255;
}
}

// Suma de registros A y B en C
registroC = registroA + registroB; 

// Separación en nibbles nibble1 = registroC & 0x0F;
nibble2 = (registroC >> 4) & 0x0F;


// Actualizar LEDs para mostrar registros A y B
for (int i = 0; i < 8; i++) {
digitalWrite(leds[i], (registroA & (1 << i)) ? HIGH : LOW);
}

// Visualización de los nibbles en los displays de 7 segmentos displayNumber(nibble1, 0);
delay(5); displayNumber(nibble2, 1); delay(5);
}


void displayNumber(byte number, int display) {
for (int i = 0; i < 7; i++) {
digitalWrite(segmentPins[i], (segmentos[number] >> i) & 0x01);
}
for (int i = 0; i < 2; i++) {
digitalWrite(displayPins[i], i == display ? LOW : HIGH);
}
}


