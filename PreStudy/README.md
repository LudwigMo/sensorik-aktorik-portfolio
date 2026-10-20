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
