#include <Servo.h>

#define tcrt1 A3
#define tcrt2 A1
#define serv 3
#define a 4
#define b 7
#define c 13
#define d 12
#define e 8
#define f 2
#define g 5
#define flame A0
#define buzzer A2
#define ldr A4
#define led1 9
#define led2 10

Servo myservo;
int read_tcrt1, read_tcrt2;
int old_read_tcrt1, old_read_tcrt2;
int read_ldr, new_value;
bool read_flame;
int count = 5;
bool flag;

//functions for printing the number of empty places
void print_0();
void print_1();
void print_2();
void print_3();
void print_4();
void print_5();

void light_system();

void fire_system();

void setup() {
  pinMode(tcrt1, INPUT);
  pinMode(tcrt2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(flame, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  myservo.attach(serv);
  Serial.begin(9600);
}

void loop() {
  //entry
  light_system();
  switch (count) {
    case 0:
      print_0();
      break;
    case 1:
      print_1();
      break;
    case 2:
      print_2();
      break;
    case 3:
      print_3();
      break;
    case 4:
      print_4();
      break;
    case 5:
      print_5();
      break;
  }
  read_flame = digitalRead(flame);
  flag = 1;
  read_tcrt1 = digitalRead(tcrt1);

  if (read_tcrt1 == 0 && count != 0) {
    for (int i = 0; i <= 90; i += 5) {
      read_flame = digitalRead(flame);
      if (read_flame == 1) {
        break;
      }
      myservo.write(i);
      delay(20);
      if (i == 90) {
        flag = 0;
      }
    }
    delay(20);
    read_tcrt2 = 1;
    while (read_tcrt1 == 0 || read_tcrt2 == 0) {
      read_flame = digitalRead(flame);
      if (read_flame == 1) {
        break;
      }
      light_system();
      old_read_tcrt2 = read_tcrt2;
      read_tcrt1 = digitalRead(tcrt1);
      read_tcrt2 = digitalRead(tcrt2);
    }
    for (int i = 90; i >= 0; i -= 5) {
      read_flame = digitalRead(flame);
      if (read_flame == 1) {
        break;
      }
      myservo.write(i);
      delay(20);
      if (i == 0) {
        flag = 1;
      }
    }

    if (old_read_tcrt2 == 0)
      count--;
  }
  if (read_flame == 1) {
    if (flag == 1) {
      for (int i = 0; i <= 90; i += 5) {
        myservo.write(i);
        delay(20);
      }
    }
    fire_system();
    for (int i = 90; i >= 0; i -= 5) {
      myservo.write(i);
      delay(20);
    }
  }
  //exit
  read_tcrt2 = digitalRead(tcrt2);
  if (read_tcrt2 == 0) {
    for (int i = 0; i <= 90; i += 5) {
      read_flame = digitalRead(flame);
      if (read_flame == 1) {
        break;
      }
      myservo.write(i);
      delay(20);
      if (i == 90) {
        flag = 0;
      }
    }
    delay(20);
    read_tcrt1 = 1;
    while (read_tcrt1 == 0 || read_tcrt2 == 0) {
      read_flame = digitalRead(flame);
      if (read_flame == 1) {
        break;
      }
      light_system();
      old_read_tcrt1 = read_tcrt1;
      read_tcrt1 = digitalRead(tcrt1);
      read_tcrt2 = digitalRead(tcrt2);
    }
    for (int i = 90; i >= 0; i -= 5) {
      read_flame = digitalRead(flame);
      if (read_flame == 1) {
        break;
      }
      myservo.write(i);
      delay(20);
      if (i == 0) {
        flag = 1;
      }
    }
    if (old_read_tcrt1 == 0) {
      count++;
    }
  }
  if (read_flame == 1) {
    if (flag == 1) {
      for (int i = 0; i <= 90; i += 5) {
        myservo.write(i);
        delay(20);
      }
    }
    fire_system();
    for (int i = 90; i >= 0; i -= 5) {
      myservo.write(i);
      delay(20);
    }
  }
}
//user-defined functions
void print_0() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 1);
  digitalWrite(g, 0);
  return;
}
void print_1() {
  digitalWrite(a, 0);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);
  return;
}
void print_2() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 0);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 0);
  digitalWrite(g, 1);
  return;
}
void print_3() {
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 1);
  return;
}
void print_4() {
  digitalWrite(a, 0);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
  return;
}
void print_5() {
  digitalWrite(a, 1);
  digitalWrite(b, 0);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);
  return;
}
void fire_system() {

  read_flame = digitalRead(flame);
  while (read_flame == 1) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    delay(250);
    read_flame = digitalRead(flame);
  }
  // digitalWrite(buzzer, LOW);

  Serial.println(flame);
}
void light_system() {
  read_ldr = analogRead(ldr);
  new_value = map(read_ldr, 80, 900, 0, 255);
  analogWrite(led1, new_value);
  analogWrite(led2, new_value);
}