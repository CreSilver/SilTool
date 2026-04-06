# SillverTool Prototyp

SilverTool je aplikace, která jede na frameworku QT, který funguje na principu event-drive, neboli aplikace se obnoví poze pokud je obnovení vyvoláno. Tato palikace má v sobě podporu Chromia a díky tomu dokáže pracovat s plnou podporou html5, css3 a javascriptu.

## Funkcionality

- Spouští webové dokumenty s plnou podporou HTML5, CSS3 a JavaScriptem
- Převodník mezi **metrickou** a **angloamerickou** soustavu
- Převodník mezi **HEX**, **RGB** a **HSV** kódem

## Instalace

- Je důležité mít jako první nainstalovaný framework QT
- Po té dopourčuji využít VScode, kde si dostáhnout plugin pro Cmake
- Taktéž je důlžité mít nainstalovaný g++ kompilátor jinak kompilace nemůže být provedena 

### Kompilace - Fedora pro bash
```
rm -rf build
mkdir build
cd build
cmake ..
make
cd ~/Dokumenty/Programing/Github/SilTool
```



