# Datenlogger-MK1

 Funktionen (Software V4.0) [F]:
- MCC UART Funktion
- MCC SPI Funktion
- MCC Flash (SD-Karten) Funktion
- MCC FATfs Funktion
- LED Definiert
- Status LED1 für den Abbruch des schreibvorgangs wegen fehlendem Medium.
- 32MHz
- Erzeugt eine .txt Datei und schreibt Messwerte und eine Zahl hinein
- In einer Endlosscheife immer in der nächsten Zeile
- Auslesen des Sensors (LPS33HW)
- Auslesen des ADCs (MCP3221)
- Auslesen der RTC (MCP79410)
- Schreiben der Werte auf die SD-Karte
  - Schreiben der Daten in Datumsabhängige dateien
  - beibehalten des Richtigen Datums/Uhrzeit
