#define led 13
#define doorpin 9
#define winpin 10
#define buz 12
#define termo A1
#define photo A0
#define bell 5
#define winclose 0
#define winopen 90
#define doorclose 0
#define dooropen 90
#include <Servo.h>
Servo door;
Servo win;
int el;
int et;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(bell, INPUT_PULLUP);
  door.attach(doorpin);
  win.attach(winpin);
  el = analogRead(photo);
  et = analogRead(termo);
  win.write(winclose);
  door.write(doorclose);
}

void loop() {
  Serial.println("=======LOOP END=======");
  Serial.print("photo(el): ");
  Serial.println(el);
  Serial.print("termo(et): ");
  Serial.println(et);
  int l = analogRead(photo);
  if (l < el / 2) {
    Serial.print("photo: ");
    Serial.println(l);
    digitalWrite(led, HIGH);
    win.write(winopen);
  } else {
    digitalWrite(led, LOW);
    win.write(winclose);
  }
  if (!digitalRead(bell)) {
    Serial.print("bell: ");
    Serial.println(digitalRead(bell));
    tone(buz, 440);
    delay(2000);
    noTone(buz);
    door.write(dooropen);
    delay(3000);
    door.write(doorclose);
  }
  if (analogRead(termo) > et * 1.4) {
    Serial.print("termo: ");
    Serial.println(analogRead(termo));
    win.write(winclose);
    for (int i = 0; i < 5; i++) {
      Serial.println("alarm");
      Serial.print("termo: ");
      Serial.println(analogRead(termo));
      digitalWrite(led, HIGH);
      tone(buz, 400);
      delay(300);
      digitalWrite(led, LOW);
      noTone(buz);
      delay(300);
    }
    
  } else if (analogRead(termo) > et * 1.08 && analogRead(termo) < et * 1.4) {
    win.write(winopen);
    delay(5000);
  }

}
