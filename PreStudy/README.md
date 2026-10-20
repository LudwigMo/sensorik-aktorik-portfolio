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
### 1. VL53L0X – Time-of-Flight-Distanzsensor

**Hersteller:** STMicroelectronics  
**Sensortyp:** Optischer Abstandssensor (Time-of-Flight, ToF)  
**Datenblatt:** VL53L0X, DS11555 Rev 6

#### 1.1 Funktionsprinzip

Der VL53L0X ist ein optischer Abstandssensor. Er verwendet einen Infrarotlaser mit einer Wellenlänge von 940 nm.

Der Sensor misst die Entfernung mithilfe des Time-of-Flight-Prinzips (ToF). Dabei wird die Laufzeit des reflektierten Lichts zur Bestimmung der Entfernung genutzt.

#### 1.2 Technische Daten

| Parameter | Wert |
|---|---|
| Messgröße | Abstand |
| Messbereich | Bis zu 2 m, abhängig von den Messbedingungen |
| Auflösung | Ausgabe in mm; tatsächliche Messauflösung nicht eindeutig angegeben |
| Messgenauigkeit | Abhängig von Entfernung, Reflexion und Umgebungsbedingungen |
| Messzeit | Typisch 30 ms im Standardmodus |
| Versorgungsspannung | 2,6–3,5 V |
| Betriebstemperatur | −20 bis +70 °C |
| Schnittstelle | I²C, bis 400 kHz |
| Laserwellenlänge | 940 nm |

#### 1.3 Messgenauigkeit und Messbedingungen

Die Messgenauigkeit hängt von verschiedenen Faktoren ab:

- Entfernung zum Messobjekt
- Reflexionsgrad der Oberfläche
- Umgebungslicht
- Temperatur und Versorgungsspannung

Laut Datenblatt beträgt die Standardabweichung bei einer Entfernung von 120 cm zu einem weißen Objekt (88 % Reflexion) im Innenbereich etwa 4 % bei einem Messzeitbudget von 33 ms.

Bei einem grauen Objekt (17 % Reflexion) beträgt die Standardabweichung bei 70 cm etwa 7 %.

Diese Werte beschreiben die Streuung der Messungen und nicht direkt den systematischen Messfehler.

#### 1.4 Messprofile

Der Sensor unterstützt verschiedene Messprofile:

| Messprofil | Messzeitbudget | Anwendung |
|---|---|---|
| Standardmodus | 30 ms | Standardmessungen |
| Hohe Genauigkeit | 200 ms | Präzise Messungen |
| Große Reichweite | 33 ms | Größere Entfernungen bei günstigen Lichtbedingungen |
| Hohe Geschwindigkeit | 20 ms | Schnelle Messungen |

#### 1.5 Schnittstelle und Signalverarbeitung

Der VL53L0X besitzt eine integrierte Signalverarbeitung und einen Mikrocontroller.

Die gemessenen Entfernungswerte werden digital über die I²C-Schnittstelle an einen externen Mikrocontroller übertragen.

**Signalkette:**

Infrarotlaser → Reflexion am Messobjekt → SPAD-Detektor → interne Signalverarbeitung → I²C → Mikrocontroller

#### 1.6 Anwendungen

Typische Anwendungen sind:

- Hinderniserkennung in Robotern
- Abstandsmessung
- Anwesenheitserkennung
- Automatisierungssysteme

#### 1.7 Fazit

Der VL53L0X ist ein kompakter digitaler Abstandssensor mit integrierter Signalverarbeitung.

Seine Vorteile sind die geringe Baugröße, die einfache I²C-Kommunikation und die berührungslose Abstandsmessung.

Die Messleistung hängt jedoch von der Entfernung, dem Reflexionsgrad des Messobjekts und den Umgebungsbedingungen ab.

**Quelle:** STMicroelectronics, *VL53L0X Datasheet*, DS11555, Revision 6, insbesondere Kapitel 2 und 6.

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
