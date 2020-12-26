# MonkeyApocalypse
Game in c++ ascii graphic

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

SPECIFICHE DI THESNOW:
La mappa deve avere una grafica ASCII, è possibile utilizzare solo le librerie conio.h, windows.h e curses/ncurses.h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ROBA DA FARE:

LEGENDA:
  ✔ = fatto
  ✖ = non iniziato
  △ = lavoro in corso

△ Rendere il gioco il più ganzo possibile.

✖ Menu
 
✖ Apparizione del player + mappa

✖ Movimento del player nella mappa

✖ salvataggio della mappa per i movimenti

✖ Armi per il player

✖ Nemico

✖ Nemici

✖ Sistema per le vite e il punteggio

✖ Nuove tipologie di nemici

✖ Bonus (armi diverse, punti e vite)

✖ Morte player

✖ Difficoltà sempre maggiore

✖ Redpillate

✖ Multiplayer

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Consegne migliorie varie:
  MENU:
  - Sistemare la freccia del menù
  - Rimuovere / risolvere le parentesi delle voci del menù
  - Definire i bordi della finestra di gioco (altrimenti varia da terminale in terminale)

  VARIE:
  - Definire una classe padre character (riciclando Actor)
  - Creare la sottoclasse enemy e player

  - Variabili protette da aggiungere a Character:
    - float life
    - float speed
  
- Probabili classi da implementare:
  - Classe MeeleWeapon
    - char Meelename[30]
    - float MeeleDamage
    - float MeeleAttackSpeed

  - Classe GunWeapon
    - char nameWeapon[30]
    - float bulletDamage
    - float bulletAttackSpeed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

TRAMA:
In un mondo di sole scimmie, un virus si è diffuso contagiando la quasi totalità del pianeta.
Le scimmie infette hanno perso ogni capacità di ragionare, intendere e di volere, trasformandosi in pazze bestie di merda in preda alla follia con un unico desiderio (causato dal virus), mangiare, mangiare sino alla morte.
Una volta finiti i cibi vegetali sono passate alla volta della carne dandosi al cannibalismo divorando le scimmie ancora sane.

Corri veloce come flash e fallo come un veloce coglione per sfuggire alla furioso appetito di queste pazze scimmie bastarde. 
Trova ed usa armi di vario tipo per fargli il culo e salvare il tuo, dato che te lo vogliono letteralmente mangiare.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
