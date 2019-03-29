# Buzzer

Wenn der Buzzer gestartet ist (Erkennbar an den Roten aufblinken) muss man noch ca. 5-10 Sekunden warten um sicherzugehen das der Code auch wirklich Startet / der Buzzer empfängt.

Um das Spiel zu starten muss der Master einmal den Zurücksetzbutton drücken so das beide Buzzer Grün Leuchten


# Kommentare

1. Bestimmt die CE und CSN Ports des RF24 an dem Arduino (Falls durch gehend gesendet / Empfangen wird müssen die Port im Code getauscht werden (Buzzer 1 und Buzzer 2 sind unterschiedlich angelötet -Unabsichtlich (Wenn ich mich recht erinner war Buzzer 1 9,10 und Buzzer 2 10,9))

2. Bestimmt den Digitalport des Knopfes an dem Arduino

3. Bestimmt den Data Port der LED Stripe an dem Arduino

4. Bestimmt die Anzahl der einzelnen LEDs des LED Stripes 

5. Bestimmt die Buzzer ID (Nur einmal vergeben; Buzzer nummer steht unter den Buzzer (Muss im Master wenn es erweitert wird ebenfalls angepasst werden)

6. Bestimmt die RGB werte des LED Stripes wenn der Buzzer gedrückt wurde UND der erste war.

7. Bestimmt die RGB werte des LED Stripes wenn der Buzzer bereit ist gedrückt zu werden.

8. Bestimmt die RGB werte des LED Stripes für das Signal das der Code bereit ist

9. Bestimmt die RGB werte des LED Stripes für das Signal das der Code bereit ist (Genauer gesagt setz es die Farbe zurück bis der Master einmal auf den Zurücksetzbutton gedrückt hat)
