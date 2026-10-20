# Module 0 – Pre-Study

**Modul:** Sensorik und Aktorik  
**Hochschule:** Hochschule Bielefeld (HSBI)  
**Semester:** Wintersemester 2026/27

In diesem Portfolio dokumentiere ich meine Vorbereitung auf das Modul Sensorik und Aktorik. Dazu gehören theoretische Grundlagen, die Analyse von Sensordatenblättern, eine Wokwi-Simulation und eine erste Projektidee.

## Task Pre-study notes
### Guiding Question 1: Sensor–Actuator Chain

**Beispiel: Digitale Waage**

Eine digitale Waage misst die Gewichtskraft eines Gegenstands und berechnet daraus seine Masse. Dazu verwendet sie eine Messkette mit mehreren Schritten.

**Messkette:**

Gewichtskraft → Dehnungsmessstreifen (DMS) → Signalaufbereitung → ADC → Mikrocontroller → Display

**1. Sensor (Dehnungsmessstreifen)**

Wenn eine Person auf der Waage steht, wird der Sensor mechanisch belastet. Dadurch verformt sich der Dehnungsmessstreifen und sein elektrischer Widerstand verändert sich.

**2. Signalaufbereitung (Signal Conditioning)**

Eine Wheatstone-Brücke wandelt die Widerstandsänderung in eine kleine Spannungsänderung um. Diese Spannung wird anschließend verstärkt und gegebenenfalls gefiltert.

**3. ADC (Analog-Digital-Wandler)**

Der ADC wandelt das analoge Spannungssignal in einen digitalen Wert um.

**4. MCU (Mikrocontroller)**

Der Mikrocontroller verarbeitet die digitalen Messwerte. Mithilfe einer Kalibrierung berechnet er die Masse und kann Messschwankungen durch Filterung reduzieren.

**5. System (Display)**

Das berechnete Ergebnis wird auf dem Display angezeigt, zum Beispiel 80,0 kg.

**Fazit:**

Eine digitale Waage misst die Masse nicht direkt. Sie erfasst zunächst eine mechanische Kraft und wandelt diese über mehrere Schritte in einen digitalen Messwert um.

## Task Datasheet reading

## Task Simulation

## Task Project abstract
### Wokwi-Simulation: ESP32 mit Potentiometer und LED

**Simulationslink:** https://wokwi.com/projects/478437962485792769

**Ziel:**

Das Ziel dieser Simulation ist es, die Analog-Digital-Wandlung (ADC) und die Steuerung einer LED mit Pulsweitenmodulation (PWM) zu untersuchen.

**Verwendete Komponenten:**

- ESP32-Mikrocontroller
- Potentiometer
- LED
- Widerstand (220 Ω)

**Versuchsaufbau:**

Das Potentiometer ist mit dem analogen Eingang GPIO 34 verbunden. Die LED wird über GPIO 25 und einen Vorwiderstand angesteuert.

Der ESP32 liest die analoge Spannung des Potentiometers und wandelt sie in einen digitalen Wert um. Dieser Wert wird anschließend zur Steuerung der LED-Helligkeit verwendet.

**1. Untersuchung der ADC-Auflösung**

Ich habe drei verschiedene ADC-Auflösungen getestet:

| Auflösung | Digitale Stufen | Wertebereich |
|---|---|---|
| 8 Bit | 256 | 0–255 |
| 10 Bit | 1024 | 0–1023 |
| 12 Bit | 4096 | 0–4095 |

Mit zunehmender Auflösung steigt die Anzahl der unterscheidbaren digitalen Werte.

**2. LED-Steuerung mit PWM**

Die ADC-Werte wurden auf einen PWM-Bereich von 0 bis 255 umgerechnet.

Beim Drehen des Potentiometers veränderte sich die Helligkeit der LED.

**3. Untersuchung der groben Quantisierung**

Anschließend habe ich die LED-Helligkeit auf fünf Stufen begrenzt.

Dabei habe ich beobachtet, dass die Helligkeit nicht mehr gleichmäßig verändert wurde, sondern zwischen festen Stufen sprang.

Beispielsweise änderte sich der ADC-Wert von 497 auf 526, während der PWM-Wert von 63 auf 127 sprang.

**Ergebnis und Fazit:**

Die Simulation zeigt den Zusammenhang zwischen analoger Spannung, ADC-Auflösung und digitaler Signalverarbeitung.

Eine höhere ADC-Auflösung ermöglicht eine feinere Unterscheidung von Eingangswerten, führt aber nicht automatisch zu einer höheren Messgenauigkeit.

Eine grobe Quantisierung kann zu sichtbaren Sprüngen bei der LED-Helligkeit führen.
