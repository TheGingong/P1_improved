# P1 - Retfærdighed i det amerikanske valgsystem
*****

## Beskrivelse af program
Dette program er lavet i forhold til p1 projekt som omhandler retfærdighed i det
amerikanske valgsystem. C programmet simulerer vælgere, deres præferencer og hvad vil de stemme på. 
Herefter bliver forskellige valgsystemer evalueret på baggrund af social utility efficiency hos deres vinderkandidater.
*****


## [h-filer](src/h-filer)

Inderholde header filen men prototyper til deres tilhørende c-filer.


### [static_variables.h](src/h-filer/static_variables.h)

Inderholder variabler der er afgørende for programmet simulationer og metoder brugt.

*****
## [logiske-funktioner](src/logiske-funktioner)

Inderholder c filer til programmet.

### [calculate_winner.c](src/logiske-funktioner/calculate_winner.c)

Hjælpefunktion brugt til at calculere vinderkandidaten i et vilkårligt valgsystem.


### [convert.c](src/logiske-funktioner/convert.c)

Konvertere tesktfil til brugbar data til programmet.


### [impartial_generation.c](src/logiske-funktioner/impartial_generation.c)

Impartial culture generering af tilfældige stemmer og deres nytte til kandidater.


### [realistic_appropriation.c](src/logiske-funktioner/realistic_appropriation.c)

Spatial voting generering af virkelighedstro stemmer og deres nytte til kandidater.


### [simulering.c](src/logiske-funktioner/simulering.c)

Åbner tekstfiler og kalder de forskellige funktioner fra andre c-filer.

### [utils.c](src/logiske-funktioner/utils.c)
Hjælpefunktion der åbner tekstfil og tester om åbning var succesfuld.

### [welfare_score.c](src/logiske-funktioner/welfare_score.c)
Beregner velfærd for forskellige kandidater og udregner social utility efficiency scoren.

## [text-files](text-files)
De to tekstfiler tilhører henholdsvis impartial og spatial stemme generering. Fil format ser 
sådan ud:
``````
34(B0.979 A0.943 C0.847 D0.472 E0.000)
24(A0.987 B0.977 C0.891 D0.516 E0.044)
43(B0.960 A0.925 C0.830 D0.463 E0.000)
39(A0.987 B0.979 C0.892 D0.525 E0.062)
13(B0.985 A0.980 C0.886 D0.519 E0.056)
``````
Hver linje i tekstfilen repræsenterer en vælger. Tallet før parantesens start fortæller hvilken
stat vælgeren er fra. Hvert bogstav i linjen er en kandidat, rangeret ud fra vælgerens præference.
Tallet efter kandidaten repræsenterer den potentielle nytte for kandidaten.



*****
## [test](test)
I mappen test ligger tests på diverse funktioner som er essentielle for programmet. De
er lavet ud fra Arrange-Act-Assert princippet og til de funktioenr der har brug for det, er der
tilsvarende tekstfiler.
*****

## Hvordan programmet bruges
[static_variables.h](src/h-filer/static_variables.h) bruges til at ændre på parametre i simulationen.

- NUMBER_CANDIDATES: Hvor mange kandidater der skal simuleres
- NUMBER_SIMULATIONS: Hvor mange simulationer der skal køres
- TOTAL_VOTERS: Det totale antal vælgere
- DIMENSIONS: Antal dimensioner i spatial voting modellen
- CLUSTERS: Antal klynger i spatial voting modellen
- PRINT_GRAPH: Laver graf til vilkårlig dimension
- RUN_REJECTION: Kører rejection sampling
- RUN_BOXMULLER: Kører Box-Muller algoritmen
- CHOSEN_FILE: Filen der skal skrives til og læses fra


## Samarbejdspartnere
- Frederik Sperling Schacksen (https://github.com/FrederikSperling)
- Søren Emil Schmidt-Laugesen (https://github.com/SorenAAU)
- Mathias Østerskov Kejser (https://github.com/GakkiOne)
- David Henning Bach (https://github.com/DrMachoo)
- Mads Møller Pedersen (https://github.com/MadsMoneyCrank)
- Victoria Myrup Pedersen (https://github.com/Venil0u)
- William Strandby Bauer (https://github.com/TheGingong)
