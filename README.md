# P1 - Retfærdighed i det amerikanske valgsystem
*****

## Beskrivelse af program
Dette program er lavet i forhold til p1 projekt som omhandler retfærdighed i det
amerikanske valgsystem. C programmet simulerer vælgere, deres præferencer og hvad vil de stemme på. 
Herefter bliver forskellige valgsystemer evalueret på baggrund af social utility efficiency hos deres vinderkandidater.
*****

````
src/h-filer
````
Inderholde header filen men prototyper til deres tilhørende c-filer.

````
static_variables.h
````
Inderholder variabler der er afgørende for programmet simulationer og metoder brugt.

````
src/logiske-funktioner
````
Inderholder c filer til programmet.

````
calculate_winner.c
````
Hjælpefunktion brugt til at calculere vinderkandidaten i et vilkårligt valgsystem.

````
convert.c
````
Konvertere tesktfil til brugbar data til programmet.

````
impartial_generation.c
````
Impartial culture generering af tilfældige stemmer og deres nytte til kandidater.

````
realistic_appropriation.c
````
Spatial voting generering af virkelighedstro stemmer og deres nytte til kandidater.


### [simulering.c](src/logiske-funktioner/simulering.c)
*****
Åbner tekstfiler og kalder de forskellige funktioner fra andre c-filer.

 [utils.c](src/logiske-funktioner/utils.c)
Hjælpefunktion der åbner tekstfil og tester om åbning var succesfuld.





Data i tekstfilen: 4(A0.9 B0.8 C0.7 D0.62 E0.413)

Input til borda_count:
````
array[n] = [A,B,C,D,E]
````

Input til america:
````
struct person {
    stat = 0-51;
    pref = 0-n;
}
````

GUIDELINE FOR KODESKRIVNING:
Kode skrives på engelsk
Hvis flere ord skrives det sådan: hej_dig
Kodekommentar skrives på dansk og akademisk! Det er en del af rapporten så skal se godt ud

Eksempel på kode:

````
/* For loop som udskriver en værdi */
for (int i = 0; i < 5; i++) {
  printf("%d\n", i); // Her printes i
}
````

HUSKELISTE:<br/>
Husk at lave mellemrum mellem funktion så det kan læses! <br/>
Husk gode variabel/funktion navne som klart beskriver hvad vi bruger det til!


Til spatial voting <br\>
https://en.wikipedia.org/wiki/Rejection_sampling

