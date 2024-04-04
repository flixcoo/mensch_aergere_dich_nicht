# Mensch Ärger Dich Nicht

Dies ist mein Abschlussprojekt in meinem ersten Semester an der HTWK Leipzig im Modul _Grundlagen der Programmierung_. Es handelt sich um ein über die Konsole spielbares "Mensch Ärger Dich Nicht"-Spiel geschrieben in C++.

## Funktionsweise

Zu Anfang werden die vier Player-Objekte erstellt und das Spielfeld wird ausgegeben. Von da an wird in Rotation gespielt. Spieler 1 beginnt und macht seinen Zug, danach Spieler 3, Spieler 4 und wieder von Vorne. Diese Rotation von jeweils einem Spielzug der vier Spieler passiert so oft, bis ein Spieler alle Figuren im Zielfeld hat.
Das Spiel funktioniert nach den üblichen "Mensch Ärgere Dich Nicht"-Regeln. Am Anfang sind alle vier Figuren in den "Lagern". Sobald ein Spieler eine 6 gewuerfelt hat, wird eine zufällige Figur aus seinem Lager ausgewählt und auf sein Startfeld (Feld 0, 10, 20, 30) gesetzt. Dann darf der Spieler erneut würfeln. Sobald ein Spieler mindestens eine Spielfigur auf dem Spielfeld hat, wird er nach jedem mal würfeln gefragt, welche Figur er bewegen möchte. Dies geschieht auch, wenn er nur eine Figur bewegen kann. Sollte der Spieler eine 6 gewürfelt haben und mindestens eine Figur in seinem Lager haben, so wird eine zufällige aus dem Lager ausgewählt und auf das Startfeld gesetzt. Sollte das Startfeld durch eine eigene Figur besetzt sein, wird automatisch die Figur auf dem Startfeld weitergesetzt. 
