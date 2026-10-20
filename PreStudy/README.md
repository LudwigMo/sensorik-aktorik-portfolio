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

### Guiding Question 2: Wokwi Observation

In meiner Wokwi-Simulation habe ich die ADC-Auflösung des ESP32 mit 8 Bit, 10 Bit und 12 Bit untersucht.

Die Anzahl der digitalen Stufen berechnet sich mit:

\[
N = 2^n
\]

Dabei ist \(n\) die Anzahl der Bits.

| ADC-Auflösung | Anzahl der Stufen | Wertebereich |
|---|---|---|
| 8 Bit | 256 | 0–255 |
| 10 Bit | 1024 | 0–1023 |
| 12 Bit | 4096 | 0–4095 |

Bei einer höheren ADC-Auflösung kann die analoge Eingangsspannung feiner digitalisiert werden.

Die Auflösung beschreibt jedoch nicht direkt die Messgenauigkeit. Die Genauigkeit kann beispielsweise durch elektrisches Rauschen, Offsetfehler oder eine ungenaue Referenzspannung beeinflusst werden.

**Fazit:** Eine höhere ADC-Auflösung ermöglicht eine feinere Quantisierung, garantiert aber keine genaueren Messwerte.

### Guiding Question 3: Datasheet

**Gewählter Sensor: VL53L0X (Time-of-Flight-Distanzsensor)**

Der VL53L0X verwendet eine **I²C-Schnittstelle** mit einer Übertragungsgeschwindigkeit von bis zu 400 kHz.

Die standardmäßige I²C-Adresse beträgt **0x29 (7 Bit)** beziehungsweise **0x52 (8-Bit-Schreibadresse)**.

Die Messleistung hängt von der Entfernung, dem Reflexionsgrad des Messobjekts und den Umgebungslichtbedingungen ab.

Laut Datenblatt beträgt die Standardabweichung der Messwerte bei einer Entfernung von 120 cm zu einem weißen Objekt (88 % Reflexionsgrad) im Innenbereich ungefähr 4 %. Dabei wird ein Messzeitbudget von 33 ms verwendet.

Dieser Wert beschreibt die **Präzision (Messstreuung)** und nicht unmittelbar die absolute Messgenauigkeit.

**Fazit:** Bei der Bewertung eines Sensors müssen die Messbedingungen berücksichtigt werden. Eine einzelne Prozentangabe reicht nicht aus, um seine Messgenauigkeit vollständig zu beschreiben.

**Quelle:** STMicroelectronics, *VL53L0X Datasheet*, DS11555 Rev. 6.

### Guiding Question 4: Accuracy vs. Precision

**Accuracy (Richtigkeit)** beschreibt, wie nahe ein Messergebnis am tatsächlichen Wert liegt.

**Precision (Präzision)** beschreibt, wie stark die Ergebnisse bei wiederholten Messungen übereinstimmen.

**Beispiel 1: Hohe Präzision, aber geringe Richtigkeit**

Eine falsch kalibrierte digitale Personenwaage zeigt bei einem tatsächlichen Körpergewicht von 80,0 kg wiederholt ungefähr 82,0 kg an.

Die Messwerte liegen sehr nahe beieinander, weichen jedoch systematisch vom tatsächlichen Wert ab.

Die Waage ist daher präzise, aber nicht richtig.

**Beispiel 2: Hohe Richtigkeit im Mittel, aber geringe Präzision**

Eine andere digitale Personenwaage zeigt bei wiederholten Messungen beispielsweise 78, 79, 80, 81 und 82 kg an, obwohl das tatsächliche Gewicht 80,0 kg beträgt.

Der Mittelwert beträgt 80,0 kg und stimmt mit dem tatsächlichen Wert überein. Die einzelnen Messwerte streuen jedoch stark.

Die Waage liefert daher im Mittel einen richtigen Wert, besitzt aber eine geringe Präzision.

**Fazit:**

Eine hohe Präzision bedeutet nicht automatisch eine hohe Richtigkeit. Für zuverlässige Messungen sind sowohl eine geringe systematische Abweichung als auch eine geringe Streuung wichtig.

### Guiding Question 5: I²C Anticipation

Bei der I²C-Kommunikation können mehrere Sensoren dieselben zwei Signalleitungen verwenden:

- **SDA (Serial Data):** Datenübertragung
- **SCL (Serial Clock):** Taktsignal

Wenn mehrere Sensoren an denselben Leitungen angeschlossen sind, muss der Mikrocontroller erkennen können, mit welchem Sensor er kommunizieren möchte.

Dafür besitzt jeder I²C-Sensor eine Geräteadresse.

**Beispiel:**

- VL53L0X: I²C-Adresse 0x29 (7 Bit)
- MPR121: I²C-Adresse 0x5A (Standardadresse, 7 Bit)

Der Mikrocontroller sendet die Adresse des gewünschten Sensors. Normalerweise antwortet nur das Gerät mit der passenden Adresse.

Wenn zwei Sensoren dieselbe Adresse verwenden, kann ein Adresskonflikt entstehen.

**Fazit:**

Die I²C-Adresse ermöglicht die eindeutige Auswahl eines Sensors auf einem gemeinsamen Bus. Dadurch können mehrere Sensoren über dieselben Daten- und Taktleitungen kommunizieren.

### Guiding Question 6: Actuator Choice

**Aufgabe:** Ein kleiner Türverschluss soll alle paar Minuten bewegt werden.

**Meine Wahl: Servomotor**

Ich würde einen Servomotor verwenden, weil er sich einfach steuern lässt und eine bestimmte Winkelposition anfahren kann.

**Begründung:**

1. **Drehmoment:** Ein geeigneter Servomotor kann genügend Drehmoment erzeugen, um einen kleinen Türverschluss über einen Hebelmechanismus zu bewegen.
2. **Einfache Steuerung:** Der Mikrocontroller kann die gewünschte Winkelposition über ein Steuersignal vorgeben. Eine zusätzliche externe Positionsregelung ist normalerweise nicht erforderlich.
3. **Leistungsaufnahme:** Da der Verschluss nur alle paar Minuten bewegt werden muss, kann der Motor zwischen den Bewegungen bei geeigneter Mechanik abgeschaltet werden. Wenn er eine Position aktiv halten muss, benötigt er möglicherweise weiterhin Strom.

**Nicht bevorzugt: Einfacher DC-Motor**

Einen einfachen Gleichstrommotor würde ich für diese Aufgabe nicht bevorzugen.

Er kann zwar eine Drehbewegung erzeugen, aber seine Position lässt sich ohne zusätzliche Sensoren oder Endschalter nicht zuverlässig bestimmen. Außerdem können ein Getriebe und eine zusätzliche Motorsteuerung erforderlich sein.

**Fazit:**

Für einen kleinen Türverschluss ist ein Servomotor eine geeignete Wahl, weil er eine einfache Positionssteuerung ermöglicht und bei passender Auslegung genügend Drehmoment bereitstellt.

### Guiding Question 7: LED Power Math

**Aufgabe:** Ein WS2812-LED-Streifen besteht aus 30 LEDs. Jede LED benötigt bei maximaler Helligkeit und weißem Licht ungefähr 60 mA.

**1. Berechnung des Gesamtstroms**

Gegeben:

- Anzahl der LEDs: 30
- Strom pro LED: 60 mA
- Versorgungsspannung: 5 V

Der maximale Gesamtstrom beträgt:

\[
I_{\mathrm{gesamt}} = 30 \cdot 60\,\mathrm{mA}
= 1800\,\mathrm{mA} = 1{,}8\,\mathrm{A}
\]

Die maximale elektrische Leistung beträgt:

\[
P = U \cdot I = 5\,\mathrm{V} \cdot 1{,}8\,\mathrm{A}
= 9\,\mathrm{W}
\]

**2. Warum reicht der 5-V-Pin des Mikrocontrollers nicht aus?**

Der 5-V-Pin eines ESP32-Entwicklungsboards ist normalerweise nicht dafür ausgelegt, einen LED-Streifen mit einer Stromaufnahme von 1,8 A direkt zu versorgen.

Ein zu hoher Strom kann zu Spannungsabfällen, instabilem Betrieb oder einer Überlastung der Stromversorgung führen.

**3. Geeignete Stromversorgung**

Für den LED-Streifen sollte eine externe 5-V-Stromversorgung mit ausreichender Stromreserve verwendet werden, beispielsweise 5 V / 3 A.

Dabei müssen der ESP32 und die externe Stromversorgung eine gemeinsame Masse (GND) besitzen.

**Fazit:**

Der LED-Streifen benötigt bei voller weißer Helligkeit ungefähr **1,8 A** beziehungsweise **9 W**. Deshalb sollte er nicht direkt über den 5-V-Pin des ESP32 versorgt werden.

### Guiding Question 8: Project Abstract

**Projektidee: Intelligente Parkplatzschranke**

Ich möchte eine intelligente Parkplatzschranke mit einem ESP32 entwickeln.

Dafür verwende ich zwei Sensoren: den **VL53L0X** zur Fahrzeugerkennung und den **MPR121** zur manuellen Freigabe.

Als Aktor wird ein **Servomotor** eingesetzt, der den Schrankenarm öffnet und schließt.

Der ESP32 verarbeitet die Sensorsignale und steuert den Servomotor.

Das Projekt soll zeigen, wie Sensoren und Aktoren in einem einfachen automatisierten System zusammenarbeiten.

Eine ausführlichere Beschreibung befindet sich im Abschnitt **Task Project abstract**.

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

### 2. MPR121 – Kapazitiver Berührungssensor

**Hersteller:** NXP / Freescale Semiconductor  
**Sensortyp:** Kapazitiver Berührungs- und Näherungssensor-Controller  
**Datenblatt:** MPR121 – Proximity Capacitive Touch Sensor Controller

#### 2.1 Funktionsprinzip

Der MPR121 ist ein kapazitiver Berührungssensor. Er erkennt Berührungen und Annäherungen durch Änderungen der elektrischen Kapazität.

Wenn sich ein Finger einer Elektrode nähert oder sie berührt, verändert sich die Kapazität. Diese Änderung wird vom Sensor erfasst, digital verarbeitet und mit einem Referenzwert (Baseline) verglichen.

#### 2.2 Technische Daten

| Parameter | Wert |
|---|---|
| Messgröße | Elektrische Kapazität bzw. Kapazitätsänderung |
| Messbereich | Ca. 10 pF bis über 2000 pF |
| Kapazitätsauflösung | Bis zu 0,01 pF |
| ADC-Auflösung | 10 Bit (1024 digitale Werte) |
| Messgenauigkeit | Keine allgemeine absolute Genauigkeit angegeben |
| Abtastintervall | 1–128 ms, standardmäßig 16 ms |
| Versorgungsspannung | 1,71–3,6 V |
| Betriebstemperatur | −40 bis +85 °C |
| Schnittstelle | I²C |
| I²C-Adresse | 0x5A–0x5D (konfigurierbar) |
| Sensorkanäle | 12 Elektroden und ein zusätzlicher Näherungskanal |

#### 2.3 Messbereich und Auflösung

Der MPR121 kann Kapazitäten von ungefähr 10 pF bis über 2000 pF erfassen.

Laut Datenblatt beträgt die Kapazitätsauflösung bis zu 0,01 pF.

Der Sensor verwendet einen internen 10-Bit-ADC, der theoretisch 1024 digitale Werte unterscheiden kann.

Eine hohe Auflösung bedeutet jedoch nicht automatisch eine hohe Messgenauigkeit.

#### 2.4 Abtastintervall und Reaktionszeit

Das Elektroden-Abtastintervall (Electrode Sample Interval, ESI) kann zwischen 1 ms und 128 ms eingestellt werden.

Der Standardwert beträgt 16 ms. Dies entspricht einer nominellen Abtastfrequenz von 62,5 Hz.

Die tatsächliche Reaktionszeit hängt von der Abtastung, der digitalen Filterung und der Entprellung (Debouncing) ab.

Die zusätzliche Verzögerung durch die Entprellung kann mit folgender Formel beschrieben werden:

\[
t_{\mathrm{Debounce}}=ESI\cdot SFI\cdot DT
\]

Beispielsweise ergibt sich bei ESI = 16 ms, SFI = 4 und DT = 2 eine Verzögerung von 128 ms.

Dieser Wert ist ein Berechnungsbeispiel und keine feste Reaktionszeit des Sensors.

#### 2.5 Messgenauigkeit und Messbedingungen

Das Datenblatt gibt eine Kapazitätsauflösung von bis zu 0,01 pF an. Eine allgemeine absolute Messgenauigkeit wird jedoch nicht eindeutig angegeben.

Die Berührungserkennung hängt unter anderem von folgenden Faktoren ab:

- Größe und Form der Elektroden
- Abstand zwischen Finger und Elektrode
- Elektrische Störungen und Umgebungsbedingungen
- Konfiguration der Filter und Schwellwerte
- Abtastintervall

Der Sensor unterstützt eine automatische Anpassung der Referenzwerte, um Veränderungen der Messbedingungen zu berücksichtigen.

Der spezifizierte Betriebstemperaturbereich beträgt −40 °C bis +85 °C. Daraus lässt sich jedoch keine konkrete temperaturabhängige Messabweichung ableiten.

#### 2.6 Schnittstelle und Signalverarbeitung

Der MPR121 verwendet eine I²C-Schnittstelle zur Kommunikation mit einem Mikrocontroller.

Die I²C-Adresse kann zwischen 0x5A und 0x5D konfiguriert werden.

Die Kapazitätsänderungen werden intern erfasst und durch einen 10-Bit-ADC digitalisiert.

Anschließend werden die Messwerte gefiltert und mit Referenzwerten sowie Schwellwerten verglichen.

**Signalkette:**

Berührung → Kapazitätsänderung → Kapazitätsmessung → 10-Bit-ADC → digitale Filterung → Schwellwertvergleich → I²C → Mikrocontroller

#### 2.7 Anwendungen

Typische Anwendungen sind:

- Kapazitive Touch-Tasten
- Berührungsempfindliche Bedienfelder
- Näherungserkennung
- Interaktive Steuerungssysteme

#### 2.8 Fazit

Der MPR121 ist ein digitaler Controller zur Erkennung von Berührungen und Annäherungen.

Seine Vorteile sind die 12 unabhängigen Elektrodeneingänge, die hohe Empfindlichkeit und die einfache Kommunikation über I²C.

Die zuverlässige Berührungserkennung hängt jedoch von der Elektrodengeometrie, den Umgebungsbedingungen und der richtigen Konfiguration der Filter und Schwellwerte ab.

### Quellen

NXP / Freescale Semiconductor, *MPR121 – Proximity Capacitive Touch Sensor Controller*, Datenblatt, insbesondere Abschnitte zu Device Operation, Electrode Filtered Data, Debounce und Filter Configuration.

## Task Simulation
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

## Task Project abstract
### Intelligente Parkplatzschranke mit ESP32

In meinem Projekt möchte ich eine intelligente Parkplatzschranke entwickeln.

Das System verwendet zwei Sensoren, einen Servomotor und einen ESP32-Mikrocontroller.

Der **VL53L0X-Abstandssensor** erkennt, ob sich ein Fahrzeug der Schranke nähert.

Der **MPR121-Berührungssensor** dient als manuelle Freigabetaste.

Der ESP32 verarbeitet die Signale beider Sensoren und steuert den Servomotor.

Wenn ein Fahrzeug erkannt und die Freigabetaste berührt wird, öffnet der Servomotor die Schranke.

Nach der Freigabe des überwachten Bereichs kann die Schranke nach einer kurzen Wartezeit wieder geschlossen werden.

Ziel des Projekts ist es, das Zusammenspiel von Sensoren, Mikrocontroller und Aktor praktisch zu untersuchen.

Das System ist als vereinfachter Lernprototyp vorgesehen.
