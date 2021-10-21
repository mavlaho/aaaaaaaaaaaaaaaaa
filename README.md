# Osnove CMake sustava


## Što je CMake

CMake je alat za izgradnju, testiranje i pakiranje softvera.
CMake kontrolira kompilaciju softvera i povezivanje s potrebnim bibliotekama.
Njegova osnovna značajka je neovisnost o platformi (operacijskom sustavu) što znači da se
izvorni kod softvera razvijenog na jednoj platformi (na primjer na Linux-u) može premjestiti na drugu
platformu (na primjer na Window sustav) i tamo kompilirati.
CMake će prilikom pokretanja ispitati svojstva platforme, pronaći potrebne biblioteke i datoteke zaglavlja,
odrediti opcije koje treba predati prevodiocu i linkeru i generirati datoteke potrebne za kompilaciju.



Bazični CMake tutorijal može se naći na stranici https://cmake.org/cmake/help/latest/guide/tutorial/index.html.


## Prvi primjer

U direktoriju `ex1` imamo C++ program u datoteci `main.cpp`.  
Ako želimo taj program kompilirati pomoću `CMake` sustava trebamo u direktoriju `ex1` kreirati datoteku
`CMakeLists.txt` sljedećeg sadržaja:



```CMake
cmake_minimum_required(VERSION 3.2)
project(ex1_project)
add_executable(ex1prog main.cpp)
```

`CMake` je kontroliran pomoću datoteke `CMakeLists.txt` čije ime je zadano i ne može se mijenjati.
Datoteka  `CMakeLists.txt` informira `CMake` koje programe i biblioteke treba izgraditi.

U ovom primjeru imamo minimalnu  `CMakeLists.txt` datoteku. Prva linija u njoj je **uvijek**
`cmake_minimum_required()`
naredba koja daje minimalnu verziju `CMake` programa koja će biti korištena. Ukoliko na sustavu nije
instaliran `cmake` te verzije ili noviji pri pokretanju `cmake`-a bit će javljena greška.

Druga naredba u svakoj  `CMakeLists.txt` datoteci je `project()` naredba kojom se daje ime projekta, u našem
slučaju `ex1_project`. Ova je naredba obavezna kao i `cmake_minimum_required()` naredba.

Treća naredba u  `CMakeLists.txt` datoteci je `add_executable()` koja kaže koji program treba izraditi.
Oblik narebe `add_executable()` je sljedeći:

```CMake
add_executable(program izvornaDatoteka1 [izvornaDatoteka2 ...])
```
Prvi argument koji se predaje naredbi `add_executable()` je ime programa koji treba izgraditi. Preostali
argumenti su imena izvornih datoteka koje sudjeluju u izgradnji programa, odvojeni bjelinama.

**Napomena**: Argumenti svih CMake naredbi  odvajaju se bjelinama, što uključuje i prijelaz u novi red.
      Naredbe se mogu pisati i velikim i malim slovima, ali se velika i mala slova razlikuju u argumentima naredbi.

U našem slučaju program se zove `ex1prog` i u njegovoj izgradnji sudjeluje samo jedna izvorna datoteka:
`main.cpp`.


### Izgradnja programa

Naša trenutna struktura direktorija na disku je sljedeća: imamo direktorij `CMake` unutar kojeg se
nalazi direktorij `ex1` koji sadrži izvorni kod našeg programa i  `CMakeLists.txt` datoteku.


Program bismo mogli kompilirati unutar direktorija  `ex1` (_in source build_) no tu mogućnost ne koristimo jer
bismo tada pomiješali izvorne datoteke s datotekama koje generira `CMake`, što otežava održavanje koda.
Stoga je uobičajena praksa generirati kod izvan direktorija izvornog koda. Na primjer, napravit ćemo novi direktorij
`build-ex1` paralelan s direktorijem   `ex1` i generirat ćemo kod u njemu (_out of source build_).



Da bismo izgradili program ulazimo u direktorij `build-ex1` i pozivamo `cmake` naredbu na sljedeći način:

```
cmake ../ex1
```

Tu smo programu `cmake` predali (relativnu) stazu do direktorija s izvornim kodom (`../ex1`). Nakon toga
će `cmake`  ispisati niz poruka i završiti porukama:

```
-- Configuring done
-- Generating done
-- Build files have been written to: .../CMake/build-ex1
```

Sam `cmake` ne kompilira program već generira sustav za kompilaciju programa. Da bismo konačno kompilirali
naš program trebamo u  `build-ex1` otipkati

```
cmake --build .
```

U ovoj naredbi `.` predstavlja direktorij u kojem se nalazimo. Da smo naredbu  `cmake` pozvali iz direktorija `CMake`
pisali bismo:

```
cmake --build build-ex1/
```
Nakon toga u `build-ex1/` nalazimo naš program `ex1prog`.

Time smo opisali način korištenja `CMake` sustava u najjednostavnijem slučaju kompilacije jednog programa koji ne treba
povezivanje s vanjskim bibliotekama. Pored toga smo upoznali tri osnovne `CMake` naredbe o kojima ćemo
sada reći nešto više.


###  Verzija CMake sustava

Prva naredba u  `CMakeLists.txt` datoteci mora biti  `cmake_minimum_required()` u kojoj postavljamo verziju
`CMake` sustava s kojom ćemo raditi. Taj korak je vrlo važan jer je  `CMake` prilično evoluirao tijekom svog razvoja.
Najveće promjene su se desile na kraju verzije 2 i pri prijelazu na verziju 3. Pri tom prijelazu od verzije 2 na verziju
3 desila se i promjena načina korištenja `CMake` sustava, tako da su neke konstrukcije i tehnike danas zastarjele i ne treba ih koristiti.
Najnovija verzija  `CMake` sustava je trenutno 3.12.

Svi novi projekti bi trebali koristiti najnoviju verziju ukoliko je prisutna na sustavu. Kada je važna prenosivost
programa na druge operacijske sustave potrebno je uzeti onu verziju `CMake` sustava koja je prisutna na svim operacijskim
sustavima od interesa. To u principu znači smanjiti verziju, no kod novih projekta bi odabrana verzija trebala biti barem verzija *3.2*.


### `project()` naredba

Ova naredba dolazi odmah nakon  `cmake_minimum_required()` naredbe i daje ime projektu koje ima
svoje značenje u dokumentiranju i pakiraju koda. 
Pored imena projekta ova naredba postavlja i programske
jezike koji se koriste u kodu. Na primjer, možemo pisati

```
project(ex1_project C CXX)
```

Ta naredba kaže da se u projektu čije je ime `ex1_project` koriste programski jezici C i C++. To u našoj
`CMakeLists.txt` datoteci nismo trebali pisati jer se ta dva jezika podrazumijevaju ako ne navedemo niti jedan jezik.
`CMake` verzije 3.0 i veće uveo je malo prirodniju sintaksu za zadavanje jezika uvodeći ključnu riječ LANGUAGES.
Tako bismo da je projekt `ex1_project` pisan u Javi pisali:

```
project(ex1_project LANGUAGES Java)
```
no prihvatljivo je i

```
project(ex1_project Java)
```

### Generatori

Da bismo kompilirali naš program trebali smo izvršiti dvije naredbe u direktoriju `build-ex1`:

```
cmake ../ex1
cmake --build .
```
Prva naredba generira sustav za izgradnju programa, a druga pokreće samu izgradnju. Važno je uočiti da izgradnju
programa ne vrši sam `CMake`. Uloga  `CMake` sustava je samo da pripremi program za kompilaciju pomoću nekog
*generatora* (sustava za izgradnju) koji je prisutan na sustavu. U naredbi `cmake --build .`, `cmake` samo poziva generator koji
kompilira program.

*Generator* mora biti prisutan na sustavu da bi `CMake` mogao odraditi svoj dio posla. Na Unix i Linux sustavima
generator je `make` program, te `CMake` samo generira odgovarajuće `Makefile` datoteke koje  `make` naredbi govore
koje programe treba izgraditi i kako. Stoga na Unix i Linux sustavima naredbu  `cmake --build .` možemo zamijeniti
naredbom `make all`.
Na MS Window sustavu  `CMake` će generirati ulazne datoteke za odgovarajuću verziju  `Visual Studio` integrirane okoline,
dok će na Mac sustavima generirati ulazne datoteke za `Xcode`. Kako na istom sustavu može postojati više različitih
sustava za izgradnju `cmake` uzima kao argument generator koji želimo koristiti. Generator ne moramo eksplicitno
zadavati ako smo zadovoljni s implicitno određenim generatorom za dani sustav. Na primjer, na Linux sustavu
uvijek imamo `make` program, no pored njega možemo imati instaliran `Ninja` sustav za izgradnju. Kako je  `make`
implicitno određen sustav za izgradnju, poziv `cmake` naredbi oblika

```
cmake ../ex1
```
generira datoteke potrebne za pokretanje  `make` programa. Ako želimo koristiti `Ninja` sustav za izgradnju moramo to
eksplicitno reći  pomoću opcije `-G` i imena generatora:

```
cmake -G Ninja ../ex1
```
Sada će biti generirane datoteke za Ninja sustav za izgradnju.


### Konfiguracija i generiranje datoteka

Naredba

```
cmake ../ex1
```
odvija se u dvije faze. U prvoj se čita `CMakeLists.txt` datoteka i konfigurira se projekt u memoriji računala.
U toj fazi `cmake` naredba ispisuje najveći dio svojih poruka i završava s porukom:

```
-- Configuring done
```

Nakon toga počinje faza generiranja datoteka za selektirani generator i u toj fazi obično nema novih poruka na
ekranu, tek

```
-- Generating done
```

kada je generiranje završilo.

Jedna od važnih datoteka koja se generira u drugoj fazi je `CMakeCache.txt`. U toj datoteci se pamte podaci iz
faze konfiguracije kako ne bi bilo potrebno ponovo raditi konfiguraciju ukoliko smo mijenjali izvorne datoteke
i trebamo ponovo kompilirati program. U tom slučaju je dovoljno izvršiti samo naredbu

```
cmake --build .
```
Nova konfiguracija je potrebna samo ako se mijenjaju `CMakeLists.txt` datoteke.

### Tip izgradnje programa

Postoje različiti tipovi izgradnje programa: osnovni su izgradnja optimizirane verzije programa (eng. _Release mode_)
i izgradnja verzije za traženje grešaka (eng. _Debug mode_). Programer je onaj koji odlučuje koju će verziju izgraditi
u kojem trenutku te hoće li svaka verzija biti u svom zasebnom direktoriju.

Trenutni tip izgradnje se pamti u jednoj varijabli koja se zove `CMAKE_BUILD_TYPE` i koja se čuva u  `CMakeCache.txt`
datoteci (u _cache_ -u). To znači da se treba postaviti samo jednom prilikom konfiguracije. Varijabla
`CMAKE_BUILD_TYPE` ima vrijednost `Release` ako se radi o optimiziranoj izgradnji, ili `Debug` ako se radi o
izgradnji za traženje grešaka. Kada želimo postaviti jedan od ta dva tipa izgradnje trebamo pomoću opcije `-D` definirati
varijablu `CMAKE_BUILD_TYPE` prilikom poziva naredbe  `cmake`. Na primjer,

```
cmake -DCMAKE_BUILD_TYPE=Debug ../ex1
```
konfigurira sustav izgradnje za traženje grešaka. Program neće biti optimiziran i imat će u sebi simbole nužne programu
za traženje grešaka (eng. _debugger_). Kada želimo promijeniti tip izgradnje trebamo rekonfigurirati projekt naredbom

```
cmake -DCMAKE_BUILD_TYPE=Release ../ex1
```
## Poddirektoriji


Vrlo se rijetko  čitav kod nalazi u jednom direktoriju. Ako imamo C++   kod onda je prirodno
izvorne datoteke staviti u poddirektorij `src`, datoteke zaglavlja u `include`, dokumentaciju
u `doc` i slično.

Datoteka `CMakeLists.txt` uvijek se nalazi u korijenskom direktoriju projekta. Ukoliko
želimo u projekt uvesti poddirektorij kao dio projekta onda trebamo učiniti dvije stvari:

- U `CMakeLists.txt` datoteku staviti poziv `add_subdirectory()` naredbi;
- U novom poddirektoriju kreirati (moguće i praznu) `CMakeLists.txt` datoteku.

U direktoriju `ex2` ćemo korigirati naš prvi primjer iz `ex1` tako što ćemo kod smjestiti u `src` direktorij.

Datoteka `CMakeLists.txt` u korijenskom direktoriju imat će samo tri naredbe:

```
cmake_minimum_required(VERSION 3.2)
project(ex2_project)
add_subdirectory(src)
```

Program će biti izgrađen u `src` direktoriju i stoga je `add_executable` naredba prebačena tamo:

```
add_executable(ex2prog main.cpp)
```

S druge strane, `cmake` program će izgraditi direktorij s izvršnim kodom iste strukture koju
ima izvorni kod. Recimo da se direktorij s izvršnim kodom zove `build-ex2` i da je na istoj
razini kao i izvorni direktorij `ex2`.
Tada direktorij  `build-ex2` ima poddirektorij `src` i program `ex2prog` se nalazi u njemu.
Svaki direktorij u izvornom kodu sa  `CMakeLists.txt` datotekom generirat će isti takav
direktorij u izvršnim kodu. Cilj će biti generiran u onom direktoriju u kojem se nalazi
`add_executable()` naredba.



## Izgradnja biblioteka

Ponekad umjesto programa želimo izgraditi biblioteku ili dio modula koji čine program
želimo kompilirati kao biblioteku s  kojom ćemo povezati glavni program. Naš prethodni primjer ćemo
modificirati tako funkciju `sqrt()` iz standardne biblioteke zamijenimo vlastitom implementacijom
koju ćemo nazvati `Sqrt()`. Novu verziju funkcije ćemo izgraditi kao biblioteku s kojom će
glavni program biti povezan.

Izmijenjeni glavni program je dan u ex3/src/main.cpp.
Funkcija  `Sqrt()` je deklarirana u zaglavlju `ex3/include/sqrt.h`,
a implementacija funkcije je dana u `ex3/src/sqrt.cpp`:

Za kompilaciju ovog programa trebaju nam dvije nove CMake naredbe: `add_library()`
koja je slična kao `add_executable()`, ali izgrađuje biblioteku umjesto izvršnog
programa, i `target_link_libraries()` koja povezuje program s potrebnim bibliotekama.
Datoteka `ex3/src/CMakeLists.txt` je dana ovdje:


```
add_library(Sqrt STATIC sqrt.cpp ../include/sqrt.h)
add_executable(ex3prog main.cpp)
target_link_libraries(ex3prog Sqrt)
```


### Naredba `add_library()`

Ova naredba dodaje biblioteku kao cilj koji treba izgraditi.
Njena signatura je sljedeća:


```
add_library(targetName [STATIC | SHARED | MODULE]
source1 [source2 ...]
)
```

Ovdje je `targetName` ime biblioteke koju izgrađujemo, a `source1`, `source2` itd. su
izvorne datoteke koje koristimo za izgradnju biblioteke. Parametri u uglatim zagradama
se mogu pojaviti ali nisu obavezni. Vertikalna crta ima značenje "ili".

Biblioteku možemo izgraditi kao *statičku* biranjem parametra `STATIC`.
To su biblioteke s ekstenzijom `.a` pod linuxom ili `.lib` pod window sustavom.
Biranjem parametra `SHARED` kreiramo *dinamičku* biblioteku (ekstenzija `.so` pod linuxom ili
`.dll` pod window sustavom). Pomoću parametra `MODULE` dobivamo dinamičku biblioteku koja
se ne povezuje s programom za vrijeme kompilacije  već se po potrebi može uključiti
u program za vrijeme izvršavanja.

Parametar  `STATIC`,  `SHARED` ili `MODULE` ne mora biti zadan. Tada `CMake` bira tip
biblioteke koji će izgraditi (statičku pod Linuxom). Programer može za vrijeme
poziva `cmake` komande odrediti tip biblioteke pomoću varijable `BUILD_SHARED_LIBS`,
 čija vrijednost može biti `YES` ili `NO`, na sljedeći način:

```
cmake  -DBUILD_SHARED_LIBS=YES ../ex3
```

Ova naredba izgrađuje dinamičku biblioteku. Ako se `YES` zamjeni sa `NO` izgradit će se
statička biblioteka. Ako parametar  `STATIC`,  `SHARED` ili `MODULE`  zadamo u `add_library()`
naredbi varijabla  `BUILD_SHARED_LIBS` će biti ignorirana.

Najfleksibilniji način izgradnje biblioteke je onaj u kojem  u `add_library()`
ne navodimo tip biblioteke već ostavljamo programeru da bira za vrijeme konfiguracije kakvu će
biblioteku izgraditi.

### Naredba  `target_link_libraries()`

Ova naredba povezuje program s bibliotekom. Najjednostavniji joj je oblik


```
target_link_libraries(targetName  biblioteka1 ...)
```

Ime `targetName` mora biti ime programa (ili biblioteke) koji se izgrađuje u tekućem direktoriju
pomoću `add_executable()` ili `add_libraries()`.
Ostali argumenti `target_link_libraries()` su imena biblioteka s kojima treba povezati program;
tih biblioteka može biti više.


### Svojstva ciljeva

Naš prethodni projekt koristi jezik C++   koji se u posljednje vrijeme razvija vrlo brzo
što je rezultiralo s više novih standarda: C++-11, C++-17 i C++-20. Ukoliko želimo specificirati
standard prilikom kompilacije trebamo koristi *svojstva* ciljeva.

Svaki cilj ima pridružen niz svojstava (eng. _properties_). Radi se o nizu varijabli pridruženih cilju
čije vrijednosti možemo mijenjati  `set_target_properties()` naredbom. Kada se radi o postavljanju standarda
imamo tri svojstva koja ga kontroliraju:  `CXX_STANDARD`,  `CXX_EXTENSIONS` i  `CXX_STANDARD_REQUIRED`.
Na primjer, u `CMakeLists.txt` datoteku možemo ubaciti naredbu:


```
set_target_properties(ex2prog
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )
```


-    `CXX_STANDARD` određuje standard koji treba koristiti (98, 11, 14, ili 17)
-    `CXX_EXTENSIONS` određuje treba li koristiti ekstenzije prevodioca koji se koristi (`ON`) ili ne (`OFF`).
-    `CXX_STANDARD_REQUIRED` određuje je li standard specificiran u `CXX_STANDARD` nužan (`ON`) ili nije (`OFF`).
Ako je nužan, a prevodilac ga ne podržava `CMake` će zaustaviti konfiguraciju
s greškom.  Ako je svojstvo stavljeno na `OFF` a prevodilac ne podržava standard,
`CMake` će specificirati najnoviji dostupni standard.



Naredba `set_target_properties()` općenito ima sljedeću formu:


```
set_target_properties(target1 [target2...]
PROPERTIES
propertyName1 value1
[propertyName2 value2] ... )
```

Svojstva se mogu shvatiti kao uređeni parovi imena svojstva i vrijednosti.


Neka svojstva cilja su ključna za izgradnju cilja, što znači za kompilaciju programa ili biblioteke.
To su sljedeća svojstva:

- `INCLUDE_DIRECTORIES` - Lista direktorija s potrebnim datotekama zaglavlja; staze moraju biti apsolutne.
- `COMPILE_DEFINITIONS` - Lista definicija koje će biti prisutne na komandnoj liniji pri kompilaciji.
- `COMPILE_OPTIONS` - Lista zastavica pri kompilaciji koje ne ulaze u prve dvije kategorije.
- `LINK_LIBRARIES` - Lista biblioteka s kojima se cilj mora povezati. To su apsolutne staze do biblioteka
ili samo imena biblioteka bez prefikasa i sufikasa koje biblioteke dobivaju na ojedinim platformama.

Detalji se mogu vidjeti na primjer u knjizi *Profesional CMake*, https://crascit.com/professional-cmake/. 
Mi se više nećemo baviti svojstvima ciljeva.


## Nalaženje stvari u datotečnom sustavu

Projekti općenito ovise o vanjskim bibliotekama, programima, datotekama zaglavlja i slično.
CMake ima niz naredbi za nalaženje svih tih stavaka u datotečnom sustavu.
To su sljedeće naredbe:

-    `find_file` -- nađi punu stazu do datoteke (obično datoteke zaglavlja);     
-    `find_library` -- nađi biblioteku;   
-    `find_path` -- nađi direktorij koji sadrži zadanu datoteku;  
-    `find_program` -- nađi program.
-    `find_package` -- nađi i učitaj postavke vanjskog projekta;             `


Prve četiri naredbe predstavljaju naredbe niske razine i namijenjene su pisanju cmake skripti
(modula) za nalaženje vanjskih biblioteka. Za nalaženje biblioteke s kojom trebamo povezati naš
program koristimo   `find_package()` naredbu.

Kada se program mora povezati s nekom bibliotekom nije dovoljno naći samo stazu do te
biblioteke (odnosno koristiti samo  `find_library()`). Potrebno je locirati i datoteke zaglavlja,
naći eventualne definicije i opcije prevodioca koje su nužne za kompilaciju, a moguće je da
povezivanje s bibliotekom zahtijeva i povezivanje s nekim drugim bibliotekama.

Naredba  `find_package()` ima ulogu naći sve potrebne informacije, odnosno tretira biblioteku
kao _instalacijski paket_, odakle naziv naredbe.  Pojednostavljena verzija naredbe ima ovaj
oblik:


```
find_package(packageName [version [EXACT]] [REQUIRED])
```

Možemo tražiti paket određene verzije i ako nije zadana opcija `EXACT` svaka novija
verzija će biti prihvaćena. Ako je zadana opcija `REQUIRED` cmake će se zaustaviti ako ne nađe
paket.

Naredba  `find_package()` funkcionira tako da potraži modul za nalaženje paketa. Modul je kod
pisan u `CMake` jeziku koji pronalazi paket i kao rezultat postavlja neke varijable i/ili
eksportira neke ciljeve što daje sve potrebne informacije o lokaciji biblioteke i datateka
zaglavlja te opcijama prevodioca i linkera. Što je točno rezultat rada modula treba vidjeti
u njegovoj dokumentaciji jer `CMake` daje samo smjernice kako moduli trebaju raditi.

Naredba  `find_package()` koja traži paket imena `packageName` potražit će modul imena
`Find<packageName>.cmake` i izvršiti kod u njemu. `CMake` sustav dolazi sa nizom takvih modula za
nalaženje često korištenih biblioteka. Opis svakog modula može se naći u CMake dokumentaciji
u sekciji `cmake-modules`. Alternativno, na komandnoj liniji možemo dobiti informaciju o modulu
naredbom:


```
cmake  --help-module ImeModula
```
Lista svih modula dobiva se naredbom

```
cmake --help-module-list
```

Modul za nalaženje biblioteke ne pišu kreatori biblioteke već korisnici. Jedan dio modula je
već ugrađen u CMake, a druge možemo preuzeti na web-u ili ih napisati sami. Takve dodatne module
stavljamo u neki direktorij (često naziva `cmake/modules`) i `CMake` -u trebamo reći da pretraži
i taj direktorij u potrazi za modulima. To se čini tako da se definira
varijabla `CMAKE_MODULE_PATH` u koju se stavlja lista direktorija koje treba pretražiti prije
no što se modul potraži na standardnim mjestima unutar `CMake` sustava.


Kada se biblioteka razvija pod `CMake` sustavom, onda razvijatelj obično eksportira konfiguracijske
detalje koji omogućavaju "automatsko" povezivanje s bibliotekom.  Ti se detalji zadaju u datoteci
imena `<packageName>Config.cmake` (ili rijeđe `<lowercasePackageName>-config.cmake`). U tom
slučaju modul za nalaženje nije potreban i `find_package` će naći sve potrebne informacije u
config-datoteci. Taj se način preferira jer je robusniji i omogućava puno jednostavije povezivanje
s bibliotekom, ali veliki broj biblioteka nije razvijen korištenjem CMake sustava i stoga ih moramo
tražiti pomoći modula za traženje. Kako traženje funkcionira najbolje je pokazati na primjeru.

### Nalaženje Boost biblioteka

Boost je niz C++ biblioteka opće namjene koje često daju funkcionalnost koja će u nekoj
sljedećoj standardizaciji C++ jezika ući u standardnu biblioteku STL. Stoga su mnoge Boost biblioteke
korištene u brojnim C++ projektima.

Boost promatramo kao jednu biblioteku, a svaku biblioteku unutar nje kao *komponentu*. U takvim situacijama
koristimo malo proširenu verziju   `find_package()` naredbe u kojoj se navodi komponenta ili komponente
koje se zahtijevaju:

```
find_package(packageName [version [EXACT]] [REQUIRED] [[COMPONENTS] component1 [component2...]])
```

U našem slučaju mi ćemo iz `Boost` biblioteke tražiti komponetu `filesystem`:

```
find_package(Boost 1.54 REQUIRED COMPONENTS filesystem)
```

Pogledajmo jedan primjer. Imamo program  'CMake/ex4/main.cpp'
i sljedeću `CMakeLists.txt` datoteku:


```
cmake_minimum_required(VERSION 3.2)

project(ex4_project)

find_package(Boost 1.54 REQUIRED COMPONENTS filesystem)

add_executable(ex4prog main.cpp)
target_link_libraries(ex4prog  Boost::filesystem)


set_target_properties(ex4prog
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )
```

Ova je  `CMakeLists.txt` datoteka izuzetno jednostavna što je posljedica načina na koji je konstruiran modul
`FindBoost.cmake` čiju dokumentaciju možete vidjeti naredbom

```
cmake --help-module FindBoost
```

Naime, ovaj modul, osim što postavlja različite varijable, eksportira i ciljeve. Jedan takav cilj je
`Boost::filesystem` koji smo iskoristili u `target_link_libraries()`. Takav cilj sa sobom donosi sve informacije
potrebne za kompilaciju programa i njegovo povezivanje s bibliotekom. To se vidi kada program kompiliramo
s opcijom `VERBOSE=1` (na Linuxu):

```
cmake --build  . -- VERBOSE=1
```

Kompilacijska linija (na Linux sustavu) izgleda ovako (staza do izvornog koda je zamijenjena s `/path`):

```
/usr/bin/c++     -std=c++11 -o CMakeFiles/path-info.dir/main.cpp.o -c /path/main.cpp
```
Poziv linkera izgleda ovako:

```
/usr/bin/c++      CMakeFiles/path-info.dir/main.cpp.o  -o path-info /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/usr/lib/x86_64-linux-gnu/libboost_system.so
```
Ovdje vidimo da biblioteka `libboost_filesystem` ovisi o biblioteci `libboost_system` te da je ta zavisnost
dodana automatski bez naše intervencije.

Napomenimo još da modul koji eksportira ciljeve čini to u "imeniku" koji ima ime paketa.
U ovom slučaju to je `Boost` te se ciljevi zovu `Boost::filesystem` i slično. To je konvencija koju
slijede praktički svi moduli koji eksportiraju ciljeve.


### Nalaženje fmt biblioteke

FMT biblioteka je standardizirana u C++20 i nudi verziju `printf()` funkcije adaptiranu za moderni C++.
Biblioteku možemo potražiti jednostavno naredbom 

```
find_package(fmt REQUIRED)
```

Biblioteka se može koristiti kao _header only_, odnosno dovoljno je uključiti zaglavlje `<fmt/core.h>`
(i neka druga) za korištenje biblioteke. Nije potrebno nikakvo vezanje s vanjskom bibliotekom, statičkom ili dinamičkom.
Naredba `target_link_libraries()`  ima zato ovaj oblik:


```
target_link_libraries(vector PRIVATE fmt::fmt-header-only)
```




## Testovi

Za testiranje koristimo biblioteku `googletest.` Za preuzimanje i kompilaciju googletesta koristimo novi 
CMake modul **FetchContent** koji je prisutan u CMake-u od verzije 3.11. 
U korijensku `CMakeLists.txt`  datoteku trebamo uključiti sljedeći sadržaj:

```
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG     e2239ee6043f73722e7aa812a459f54a28552929  # release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
```
`GIT_TAG` treba uvijek biti najnoviji.  Prilikom kompilacije googletest će biti preuzet u 
`_dep` poddirektoriju direktorija izvršnog koda i tamo će biti i izrađen. 


Program se nalazi u direktoriju `src` i sastoji se od datoteka `data.h`, `data.cpp` i `main.cpp`.
Testovi se nalaze u direktoriju `test` u datoteci `test.cpp`.

Datoteka `CMakeLists.txt` u `test` direktoriju ima sljedeći sadržaj:

```
add_executable("testData" test.cpp ../src/data.cpp)
target_link_libraries("testData"  gtest_main)

add_test(NAME testData COMMAND testData)
```
Prve dvije naredbe kompiliraju test program i povezuju ga sa `googletest` bibliotekom (i `pthread`  bibliotekom).
Zadnja naredba ima oblik


```
add_test(NAME testName COMMAND command [arg...])
```
i ona dodaje test. Sve tako definirane testove izvršavamo tako što i izvršnom poddirektoriju
otipkamo

```
ctest -V
```
Izlaz može biti sljedeći:

```
   Start 1: testData

1: Test command: /home/jurak/mytext/Teaching/C++/GitHub/CMake/ex5/build/test/testData
1: Test timeout computed to be: 9.99988e+06
1: [==========] Running 2 tests from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 2 tests from Data
1: [ RUN      ] Data.size
1: [       OK ] Data.size (0 ms)
1: [ RUN      ] Data.sort
1: [       OK ] Data.sort (0 ms)
1: [----------] 2 tests from Data (0 ms total)
1:
1: [----------] Global test environment tear-down
1: [==========] 2 tests from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 2 tests.
1/1 Test #1: testData .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec

```



## Kopiranje datoteka

Često smo u situaciji da izvršni program treba pročitati neku datoteku 
koju čuvamo u izvornom kodu. Tada nakon kompilacije programa datoteku treba kopirati
iz direktorija izvornog koda u direktorij izvršnog koda.

Tu nam pomaže naredba `configure_file()` koja kopira datoteke i vrši supstituciju
varijabli u izvornoj datoteci.  Pojednostavljena signatura funkcije je sljedeća:

```
configure_file(source destination [COPYONLY])
```

Datoteka `source` je dana relativno u odnosu na `CMAKE_CURRENT_SOURCE_DIR`, to znači
relativno u odnosu na direktorij u kojem se nalazi trenutna `CMakeLists.txt` datoteka.
Datoteka `destination` je dana relativno u odnosu na `CMAKE_CURRENT_BINARY_DIR`, 
dakle u odnosu na sliku izvornog direktorija u izvršnom direktoriju. 
Naredba će kopirati `source` na  `destination`. `COPYONLY` koristimo kada ne vršimo nikakve 
supstitucije varijabli (samo kopiranje). 

Na primjer u direktoriju `ex6` imamo poddirektorij `src` sa `CMakeLists.txt` datotekom 

```
add_executable(ex6prog main.cpp)
configure_file(text.txt text.txt COPYONLY)
```

Ako je izvršni kod u `ex6/build/`, onda se `ex6/src/text.txt` kopira u `ex6/build/src/text.txt`.


## Kompilacija testova ako je `googletest` lokalno instaliran

Primjer je napravljen u direktoriju `ex7`.
