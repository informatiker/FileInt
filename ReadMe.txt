FileInt

Berechnet CRC32-Prüfsummen für Dateien
Muss gegen WxWidgets 2.8 (http://www.wxwidgets.org/) gelinkt werden

FileIntApp 
stellt die Anwendung dar (WxWidgets-konvention)

FileIntMain 
ist das Hauptfenster

PosixFile
kapselt Dateien mit der "generiere CRC32-Prüfsumme"-Funktionalität

ccrc32
eine CRC32-Implementierung, im Internet gefunden, leider ohne Authorenangabe

crc32generator
eine convenience Klasse die das Benutzen von ccrc32 vereinfacht und zusätzlich
das Bilden von Prüfsummen "byte für byte" ermöglicht, um zwischendurch Feedback
für den User geben zu können (... z.B. durch füllen der ProgressBar)