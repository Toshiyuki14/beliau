
#include <FreqMeasure.h>

void setup() {
Serial.begin(9600);
FreqMeasure.begin();
}

double frek=0;
byte jumlah=0;

void loop() {
if (FreqMeasure.available()) {
frek = frek + FreqMeasure.read();
jumlah++;
if (jumlah > 30) {
float frekuensi = FreqMeasure.countToFrequency(frek / jumlah);
Serial.println(frekuensi);
frek = 0;
jumlah = 0;
}
}
}