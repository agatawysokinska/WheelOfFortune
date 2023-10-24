#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include<cstring>
#include <cstdio>
#include <cctype>
#include <algorithm> 

using namespace std;

const int wielkosc = 10;
const int wielkosc2 = 20;	//stale wielkosci tablic
const int wielkosc3 = 5;
const int wielkosc4 = 3;
const int rozmiar_spolgloski = 1;

class Kolo_Fortuny
{
public:
	struct gracz
	{
		string imie;
		int miejsce_w_tablicy;
		int losowanie_kolejnosci;
		string nagroda_gracza[wielkosc];
		int min_miejsca_w_tablicy_ng = 0;
		int max_miejsca_w_tablicy_ng = 1;
		int wartosc_nagrody_gracza = 0;
		int wygrana_kwota = 0;
		int calkowita_wygrana_kwota = 0;
		char kupione_samogloski[wielkosc];
		int kupione = 0;	//ilosc kupionych samoglosek
		int min_zakupionych = 0;
		int max_zakupionych = 1;
	};
	gracz* dane[4];

	void losuj_kolejnosc(gracz* dane);
	void losuj_kategorie(gracz* dane);
	void losuj_haslo(gracz* dane);
	void rysuj_pole(gracz* dane);
	void zakrec_kolem(gracz* dane);
	void wykorzystales_spolgloske(gracz* dane);
	void nieudana_proba(gracz* dane);
	void zgadywanie(gracz* dane);
	void zakup(gracz* dane);
	void uzyj_samogloski(gracz* dane);
	void znam_haslo(gracz* dane);
	void przejscie(gracz* dane);
	void nowa_runda(gracz* dane);
	void koniec(gracz* dane);

private:
	char samogloski[wielkosc] = { 'a','i','e','o','u','y' };
	int ile_osob;
	int miejsce_w_tablicy_gracza;		//miejsce w tablicy aktualnego gracza
	string kategoria;
	unsigned int los;
	int tablica_pol[wielkosc2];
	string haslo;
	string zaszyfrowane_haslo;
	string tab[wielkosc4];
	int min_miejsce_nagrod = 0;
	int max_miejsce_nagrod = 1;
	char spolgloska1[rozmiar_spolgloski];
	char spolgloska2[rozmiar_spolgloski];
	char ktora_spolgloska;
	char uzyte_spolgloski[wielkosc2];
	int uzyte_spolgloski_min = 0;
	int uzyte_spolgloski_max = 1;
	string nagroda;
	int wartosc; //wartosc nagrody
	int tury = 0;
	int rundy = 1;
	unsigned char sign;
	char opcja[wielkosc4]; //wybor tak/nie w funkcji "uzyj samogloski"
	char zakupiona[2];  //zakupiona samogloska
	int odgadniete_pole = 0;
	string zgaduje;

};

void Kolo_Fortuny::losuj_kolejnosc(gracz* dane)
{
	cout << " WITAJ W GRZE KOLO FORTUNY " << endl;
	cout << endl;
	cout << "W ile osob chcesz zagrac?" << endl;
	cout << "wybierz: 1 / 2 / 3 / 4" << endl;
	cin >> ile_osob;							//wczytywanie ilosci graczy
	for (int i = 0; i < ile_osob; i++)
	{
		cout << "Podaj swoje imie: ";		//kazdy gracz podaje swoje imie i otrzymuje odpowiednie miejce w tablicy
		cin >> dane[i].imie;
		dane[i].miejsce_w_tablicy = i;
	}
	cout << endl;
	if (ile_osob == 1)		//jezeli jest tylko 1 osoba to rozpoczyna gre bez losowania
	{
		cout << dane[0].imie << " " << " rozpoczynasz gre, powodzenia!" << endl;
		miejsce_w_tablicy_gracza = 0;		//gracz otrzymuje 0 miejsce w tablicy
		losuj_kategorie(dane);
	}
	else {
		int suma = 25;			//dla wiekszej ilosci graczy generowana jest pula liczb, z ktorej beda losowac kolejnosc gry
		for (int i = 0; i < 16; i++)
		{
			tablica_pol[i] = suma * (i + 1);
		}
		tablica_pol[16] = 500;

		for (int i = 0; i < ile_osob; i++)
		{
			cin.get();
			cout << "zakrec kolem  " << dane[i].imie << ": ";
			cin.get();
			los = (rand() % 16);		//losowanie pola z liczba
			cout << tablica_pol[los] << endl;
			dane[i].losowanie_kolejnosci = tablica_pol[los];  //kolejnym graczom przypisywana jest wartosc wylosowanej liczby
		}

		int max = 0;
		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].losowanie_kolejnosci > max)
				max = dane[i].losowanie_kolejnosci;		//wyznaczenie najwiekszej wylosowanej liczby
		}

		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].losowanie_kolejnosci == max)
				miejsce_w_tablicy_gracza = dane[i].miejsce_w_tablicy;		//osoba, ktora wylosowala najwieksza liczbe zacznie gre
		}

		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].losowanie_kolejnosci == max)
				cout << dane[i].imie << " " << " rozpoczynasz gre, powodzenia!" << endl;
		}
		cout << endl;
		losuj_kategorie(dane);
	}
};

void Kolo_Fortuny::losuj_kategorie(gracz* dane)
{
	string tablica[wielkosc] = { "miejsce" ,"przyslowie/powiedzenie","cytat","osoba","tytul","rzecz","czynnosc","postac","miasto" };

	los = (rand() % 8);		//losowanie kategorii

	kategoria = tablica[los];

	cout << "kategoria: " << kategoria;
	cout << endl;

	losuj_haslo(dane);
};

void Kolo_Fortuny::losuj_haslo(gracz* dane)
{
	string miejsce[wielkosc3] = { "biebrzanski park narodowy","hala stulecia", "warszawskie zoo", "westerplatte", "krakowskie sukiennice" };
	string przyslowie_powiedzenie[wielkosc3] = { "kazal pan musial sam", "bez pracy nie ma kolaczy", "co dwie glowy to nie jedna", "czas to pieniadz","komu w droge temu czas" };
	string cytat[wielkosc3] = { "czlowiek staje sie tym o czym mysli","prawdziwe szczescie jest rzecza wysilku odwagi i pracy","musisz sam sobie zaufac aby mogli zaufac ci inni",
							"male szanse sa czesto poczatkiem wielkich przedsiewziec","madrosc to corka doswiadczenia" };
	string osoba[wielkosc3] = { "tesciowa","wykladowca","gospodarz","instruktor","przyjaciel" };
	string tytul[wielkosc3] = { "mistrz i malgorzata","wladcy pierscieni", "harry potter","lalka","sen nocy letniej" };
	string rzecz[wielkosc3] = { "klawiatura","przescieradlo","piekarnik","kalendarz","zwierciadlo" };
	string czynnosc[wielkosc3] = { "polowanie","odkurzanie","remontowanie","gotowanie","nauczanie" };
	string postac[wielkosc3] = { "john fitzgerald kennedy","michael jackson","mahatma gandhi","freddie mercury","budda" };
	string miasto[wielkosc3] = { "warszawa","berlin","moskwa","waszyngton","londyn" };
	string wylosowane[wielkosc4];
	int min = 0;
	int max = 1;

	los = (rand() % 5); //losowanie hasla


	if (kategoria == "miejsce")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (miejsce[los] != wylosowane[i]) //sprawdzanie czy haslo nie pojawilo sie juz wczesniej
			{
				haslo = miejsce[los];	//ustalenie obecnego hasla
			}
			else los = (rand() % 5);	//jezeli sie pojawilo, ponownie losujemy
		}
		for (min; min < max; min++)
			wylosowane[min] = haslo;	//wpisywanie hasla do tablicy wylosowanych hasel
		max++;	//zwiekszanie miejsca w tablicy
	}
	else if (kategoria == "przyslowie/powiedzenie")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (przyslowie_powiedzenie[los] != wylosowane[i])
			{
				haslo = przyslowie_powiedzenie[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++)
		{
			wylosowane[min] = haslo;
		}
		max++;
	}
	else if (kategoria == "cytat")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (cytat[los] != wylosowane[i])
			{
				haslo = cytat[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++)
		{
			wylosowane[min] = haslo;
		}
		max++;
	}
	else if (kategoria == "osoba")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (osoba[los] != wylosowane[i])
			{
				haslo = osoba[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++) {
			wylosowane[min] = haslo;
		}
		max++;
	}
	else if (kategoria == "tytul")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (tytul[los] != wylosowane[i])
			{
				haslo = tytul[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++) {
			wylosowane[min] = haslo;
		}
		max++;
	}
	else if (kategoria == "rzecz")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (rzecz[los] != wylosowane[i])
			{
				haslo = rzecz[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++) {
			wylosowane[min] = haslo;
		}
		max++;
	}
	else if (kategoria == "czynnosc")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (czynnosc[los] != wylosowane[i])
			{
				haslo = czynnosc[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++)
		{
			wylosowane[min] = haslo;
		}
		max++;
	}
	else if (kategoria == "postac")
	{
		for (int i = 0; i < wielkosc4; i++) {

			if (postac[los] != wylosowane[i])
			{
				haslo = postac[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++) {
			wylosowane[min] = haslo;
		}
		max++;
	}
	else if (kategoria == "miasto")
	{
		for (int i = 0; i < wielkosc4; i++)
		{
			if (miasto[los] != wylosowane[i])
			{
				haslo = miasto[los];
			}
			else los = (rand() % 5);
		}
		for (min; min < max; min++) {
			wylosowane[min] = haslo;
		}
		max++;
	}
	rysuj_pole(dane);
};
void Kolo_Fortuny::rysuj_pole(gracz* dane)
{
	cout << "Haslo: " << endl;
	for (int i = 0; i < haslo.size(); ++i)
	{
		zaszyfrowane_haslo += "_";	//w miejcu hasla wyswietla sie puste pola
	}
	cout << zaszyfrowane_haslo << endl;
	cout << endl;
	zakrec_kolem(dane);
};

void Kolo_Fortuny::zakrec_kolem(gracz* dane)
{

	string tablica[wielkosc] = { "wakacje" ,"samochod","pralka","zmywarka","odkurzacz","smartfon","telewizor" };
	string wylosowane[wielkosc];	//tablica wylosowanych nagrod
	int wartosci_nagrod[wielkosc] = { 4000, 25000, 2300, 2700, 1200, 2000,3000 };

	int suma = 25;

	tab[0] = "NAGRODA";
	tab[1] = "BANKRUT";		//tablica z polami typu string
	tab[2] = "STOP";

	for (int i = 0; i < 16; i++)		//tablica z polami typu int
	{
		tablica_pol[i] = suma * (i + 1);
	}
	if (rundy == 1)
	{
		tablica_pol[16] = 500;
	}
	else if (rundy == 2)
	{
		tablica_pol[16] = 1400;
	}
	else if (rundy == 2)
	{
		tablica_pol[16] = 2000;
	}


	if (tury == 10 || odgadniete_pole == haslo.size())
	{
		przejscie(dane);
	}
	else
	{
		cout << "wcisnij  i zakrec kolem" << endl;
		sign = cin.get();
		sign = cin.get();
		if (sign != '0' && sign != '9' && sign != '8')
		{
			int wybortab = (rand() % 6);		//losowanie tablicy int lub string
			if (wybortab != 1)
			{
				los = (rand() % 16);	//losowanie pola z tablicy int
				int a;
				int b;
				if (los == 0)	//dla wylosowanego pola "0" poprzednie pole wyswietli sie jako koncowe "16"
				{
					a = 16;
					b = los + 1;
				}
				else if (los == 16)		//dla wylosowanego pola "16" nastepne pole wyswietli sie jako poczatkowe "0"
				{
					b = 0;
					a = los - 1;
				}
				else
				{
					a = los - 1;
					b = los + 1;
				}
				tury++;
				cout << "runda: " << rundy << " " << "tura: " << tury << endl;
				cout << endl;
				cout << "--------" << "***********" << "--------" << endl;
				cout << "|" << tablica_pol[a] << " 	*   " << tablica_pol[los] << "   *    " << tablica_pol[b] << "|" << endl;
				cout << "--------" << "***********" << "--------" << endl;

				cout << dane[miejsce_w_tablicy_gracza].imie << " podaj spolgloske" << endl;
				cin >> spolgloska1;			//wczytywanie spolgloski
				ktora_spolgloska = *spolgloska1;

				for (int i = 0; i < 6; i++)
				{
					if (samogloski[i] == spolgloska1[0])	//sprawdzanie czy podana litera nie jest samogloska
					{
						cout << "to jest samogloska!!" << endl;
						nieudana_proba(dane);
					}
				}
				wykorzystales_spolgloske(dane);
			}
			else
			{
				los = (rand() % 2);
				cout << endl;
				int c;
				int d;
				if (los == 0)		//dla wylosowanego pola "0" poprzednie pole wyswietli sie jako koncowe "2"
				{
					c = 2;
					d = los + 1;
				}
				else if (los == 2)		//dla wylosowanego pola "2" nastepne pole wyswietli sie jako poczatkowe "0"
				{
					d = 0;
					c = los - 1;
				}
				else
				{
					c = los - 1;
					d = los + 1;
				}
				tury++;
				cout << "runda: " << rundy << " " << "tura: " << tury << endl;
				cout << endl;
				cout << "---------------" << "***************" << "---------------" << endl;
				cout << "|" << tab[c] << "		*  " << tab[los] << "    *    " << tab[d] << "|" << endl;
				cout << "---------------" << "***************" << "---------------" << endl;

				if (tab[los] == tab[0])
				{
					los = (rand() % 6);

					for (int i = 0; i < 7; i++) {

						if (tablica[los] != wylosowane[i])	//sprawdzanie czy dana nagroda nie zostala wczesniej wylosowana
						{
							for (min_miejsce_nagrod; min_miejsce_nagrod < max_miejsce_nagrod; min_miejsce_nagrod++)
							{
								wylosowane[min_miejsce_nagrod] = tablica[los];	//wpisanie nagrody do tablicy wylosowanych
							}
							nagroda = wylosowane[min_miejsce_nagrod];		//aktualna nagroda
							wartosc = wartosci_nagrod[los];	//wartosc wylosowanej nagrody
						}
						else los = (rand() % 6);
					}
					max_miejsce_nagrod++;
					cout << "nagroda: " << nagroda << " o wartosci " << wartosc << endl;
					cout << endl;

					cout << dane[miejsce_w_tablicy_gracza].imie << " podaj spolgloske" << endl;
					cin >> spolgloska2;
					ktora_spolgloska = *spolgloska2;

					for (int i = 0; i < 6; i++)
					{
						if (samogloski[i] == spolgloska2[0])	//sprawdzanie czy podana litera nie jest samogloska
						{
							cout << "to jest samogloska!!" << endl;
							nieudana_proba(dane);
						}
					}
					wykorzystales_spolgloske(dane);
				}
				else if (tab[los] == tab[1])
				{
					dane[miejsce_w_tablicy_gracza].wygrana_kwota = 0;	//wyzerowanie wygranych pieniedzy w danej rundzie
					cout << "Zostales bankrutem!" << endl;

					nieudana_proba(dane);

				}
				else if (tab[los] == tab[2])
				{
					nieudana_proba(dane);

				}
			}
		}
		else if (sign == '0')
		{
			zakup(dane);
		}
		else if (sign == '9')
		{
			uzyj_samogloski(dane);

		}
		else if (sign == '8')
		{
			znam_haslo(dane);
		}
	}
};
void Kolo_Fortuny::wykorzystales_spolgloske(gracz* dane)
{
	if (ktora_spolgloska == spolgloska1[0])	//jezeli spolgloska byla pobrana przy wygranej z tablicy int
	{
		bool prawda = 1;

		for (int i = 0; i < uzyte_spolgloski_max; i++)
			if (uzyte_spolgloski[i] == spolgloska1[0])	//sprawdzenie czy spolgloska nie zostala wczesniej wykorzystana
				prawda = 0;

		if (prawda == 0)
		{
			cout << dane[miejsce_w_tablicy_gracza].imie << " ta spolgloska zostala juz uzyta" << endl;
			nieudana_proba(dane);
		}
		else if (prawda == 1)
			for (uzyte_spolgloski_min; uzyte_spolgloski_min < uzyte_spolgloski_max; uzyte_spolgloski_min++)
			{
				uzyte_spolgloski[uzyte_spolgloski_min] = spolgloska1[0];		//wpisanie spolgloski do tablicy wylosowanych spolglosek
			}
		uzyte_spolgloski_max++;		//zwiekszanie miejsca w tablicy wylosowanych spolglosek
	}
	else if (ktora_spolgloska == *spolgloska2)	//jezeli spolgloska byla pobrana przy wygranej z tablicy string
	{
		bool prawda1 = 1;
		for (int i = 0; i < uzyte_spolgloski_max; i++)
		{
			if (uzyte_spolgloski[i] == spolgloska2[0])	//sprawdzenie czy spolgloska nie zostala wczesniej wykorzystana
				prawda1 = 0;
		}

		if (prawda1 == 0)
		{
			cout << dane[miejsce_w_tablicy_gracza].imie << " ta spolgloska zostala juz uzyta" << endl;
			nieudana_proba(dane);
		}
		else if (prawda1 == 1)
			for (uzyte_spolgloski_min; uzyte_spolgloski_min < uzyte_spolgloski_max; uzyte_spolgloski_min++)
			{
				uzyte_spolgloski[uzyte_spolgloski_min] = spolgloska2[0];	//wpisanie spolgloski do tablicy wylosowanych spolglosek
			}
		uzyte_spolgloski_max++;	//zwiekszanie miejsca w tablicy wylosowanych spolglosek
		zgadywanie(dane);
	}
	zgadywanie(dane);
};
void Kolo_Fortuny::nieudana_proba(gracz* dane)
{
	if (ile_osob == 1)	//jezeli 1 gracz nie odgadl pola lub hasla
	{
		cout << "sproboj jeszcze raz" << endl;
		zakrec_kolem(dane);
	}
	else
	{
		miejsce_w_tablicy_gracza = (miejsce_w_tablicy_gracza + 1) % ile_osob;	//wybor nastepnego gracza
		cout << "Tracisz kolejke, teraz Twoj ruch : " << dane[miejsce_w_tablicy_gracza].imie << endl;
		sign = cin.get();
		zakrec_kolem(dane);
	}
}

void Kolo_Fortuny::zgadywanie(gracz* dane)
{
	char wylosowana[wielkosc2] = { 'b','c','d','f','g','h','j','k','l','m','n','p','r','s','t','w','x','q','v','z' };
	int a = 0;
	int ile_razy = 0;

	for (int k = 0; k < wielkosc2; k++)
	{
		if (wylosowana[k] == spolgloska1[0])	//sprawdzanie czy litera jest spolgloska
		{

			for (int i = 0; i < haslo.size(); i++)
			{
				if (tolower(haslo[i]) == tolower(spolgloska1[0]))	//sprawdzanie czy spolgloska nalezy do hasla
				{
					ile_razy++;		//liczy ile razy spolgloska pojawia sie w hasle
					zaszyfrowane_haslo[i] = spolgloska1[0];		//wpisanie spolgloski w puste miejsce
				}
			}

			if (ile_razy != 0)	//jezeli spolgloska pojawia sie  w hasle
			{
				for (int i = 0; i < haslo.size(); i++)
				{
					cout << zaszyfrowane_haslo[i];
				}
				cout << endl;
				odgadniete_pole += ile_razy;	//ilosc odgadnietych pol
				dane[miejsce_w_tablicy_gracza].wygrana_kwota += (tablica_pol[los] * ile_razy);	//gracz otrzymuje kwote pomnozona przez ilosc miejsc, w ktorych pojawila sie spolgloska
				cout << dane[miejsce_w_tablicy_gracza].wygrana_kwota << endl;
				ile_razy = 0;
				zakrec_kolem(dane);
			}
			else
			{
				nieudana_proba(dane);
			}
		}
		else if (wylosowana[k] == spolgloska2[0])	//sprawdzanie czy litera jest spolgloska
		{
			for (int i = 0; i < haslo.size(); i++)
			{
				if (tolower(haslo[i]) == tolower(*spolgloska2))
				{
					ile_razy++;		//liczy ile razy spolgloska pojawia sie w hasle
					zaszyfrowane_haslo[i] = spolgloska2[0];		//wpisanie spolgloski w zaszyfrowane miejsce
				}
			}

			if (ile_razy != 0)	//jezeli spolgloska pojawia sie w hasle
			{
				for (int i = 0; i < haslo.size(); i++)
				{
					cout << zaszyfrowane_haslo[i];
				}
				cout << endl;
				odgadniete_pole += ile_razy;

				for (dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng; dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng < dane[miejsce_w_tablicy_gracza].max_miejsca_w_tablicy_ng; dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng++) {

					dane[miejsce_w_tablicy_gracza].nagroda_gracza[dane[miejsce_w_tablicy_gracza].min_miejsca_w_tablicy_ng] = nagroda;		//dla obecnego gracza przypisywana jest nagroda do okreslonego miejsca w tablicy nagrod
				}
				dane[miejsce_w_tablicy_gracza].max_miejsca_w_tablicy_ng++;	//zwiekszanie miejsca w tablicy nagrod

				dane[miejsce_w_tablicy_gracza].wartosc_nagrody_gracza += wartosc;	//sumowanie wartosci wygranych nagrod
				cout << dane[miejsce_w_tablicy_gracza].wartosc_nagrody_gracza << endl;

				ile_razy = 0;
				cout << endl;
				zakrec_kolem(dane);
			}
			else
			{
				nieudana_proba(dane);

			}

		}
	}

};
void Kolo_Fortuny::zakup(gracz* dane)
{

	tury++;
	cout << "suma twoich pieniedzy to: " << dane[miejsce_w_tablicy_gracza].wygrana_kwota << endl;

	if (dane[miejsce_w_tablicy_gracza].wygrana_kwota >= 200)
	{
		cout << "Jaka samogloske chcesz kupic?" << endl;
		cin >> zakupiona;
		for (int k = 0; k < 6; k++)
		{
			if (samogloski[k] == zakupiona[0])	//sprawdzanie czy litera jest samogloska
				for (dane[miejsce_w_tablicy_gracza].min_zakupionych; dane[miejsce_w_tablicy_gracza].min_zakupionych < dane[miejsce_w_tablicy_gracza].max_zakupionych; dane[miejsce_w_tablicy_gracza].min_zakupionych++)
					dane[miejsce_w_tablicy_gracza].kupione_samogloski[dane[miejsce_w_tablicy_gracza].min_zakupionych] = samogloski[k];	//wpisywanie samogloski do tablicy zakupionych samoglosek gracza
		}
		dane[miejsce_w_tablicy_gracza].max_zakupionych++;	//zwiekszanie miejsca w tablicy
		dane[miejsce_w_tablicy_gracza].kupione++;		//licznik samoglosek
		dane[miejsce_w_tablicy_gracza].wygrana_kwota - 200;	//odejmowanie kosztu jednej samogloski
		//zakrec_kolem(dane);
		uzyj_samogloski(dane);
	}
	else cout << "nie masz pieniedzy" << endl;
	zakrec_kolem(dane);

};

void Kolo_Fortuny::uzyj_samogloski(gracz* dane)
{

	if (dane[miejsce_w_tablicy_gracza].kupione != 0)
	{
		cout << "kupione samogloski to: ";
		for (int i = 0; i < dane[miejsce_w_tablicy_gracza].max_zakupionych - 1; i++)
		{
			cout << dane[miejsce_w_tablicy_gracza].kupione_samogloski[i];
		}
	}
	else
	{
		cout << "brak zakupionych samoglosek" << endl;
		zakrec_kolem(dane);
	}
	cout << endl;
	cout << "Czy chcesz wykorzystac samogloske?" << endl;
	cout << "wpisz 'tak' lub 'nie'" << endl;
	cin >> opcja;
	bool jest = 0;
	if (_stricmp(opcja, "tak") == 0)
	{
		cout << "Ktorej samogloski chcesz uzyc?" << endl;
		cin >> zakupiona;


		for (int i = 0; i < dane[miejsce_w_tablicy_gracza].max_zakupionych; i++)
		{
			if (dane[miejsce_w_tablicy_gracza].kupione_samogloski[i] == *zakupiona)		//sprawdzanie czy samogloska znajduje sie w tablicy zakupionych samoglosek danego gracza
			{
				jest = 1;
				for (int i = 0; i < haslo.size(); i++)
				{
					if (haslo[i] == *zakupiona)	//sprawdzanie czy samogloska wystepuje w hasle
						zaszyfrowane_haslo[i] = *zakupiona;	//wpisywanie samogloski do hasla
				}
				for (int i = 0; i < haslo.size(); i++)
				{
					if (haslo[i] == *zakupiona)
						odgadniete_pole++;	//zwiekszanie ilosci odgadnietych pol
				}
				for (int i = 0; i < dane[miejsce_w_tablicy_gracza].max_zakupionych; i++)
				{
					if (dane[miejsce_w_tablicy_gracza].kupione_samogloski[i] == *zakupiona)
						dane[miejsce_w_tablicy_gracza].kupione_samogloski[i] = 0;	//zerowanie miejsca uzytej samogloski
				}
				zakrec_kolem(dane);
			}
		}

		if (jest == 0)
		{
			cout << "Nie kupiles takiej samogloski" << endl;
			zakrec_kolem(dane);
		}
	}
	else if (_stricmp(opcja, "nie") == 0)
	{
		zakrec_kolem(dane);
	}
};

void Kolo_Fortuny::znam_haslo(gracz* dane)
{
	tury++;

	cout << "podaj haslo" << endl;

	getline(cin, zgaduje);
	getline(cin, zgaduje);

	if (zgaduje == haslo)
	{
		cout << endl;
		cout << "brawo " << dane[miejsce_w_tablicy_gracza].imie << " odgadles/as haslo!" << endl;
		cout << "dostajesz bonus 1000zl" << endl;
		dane[miejsce_w_tablicy_gracza].wygrana_kwota += 1000;
		przejscie(dane);
	}
	else
	{
		cout << "To nie jest dobra odpowiedz :( " << endl;
		sign = cin.get();
		nieudana_proba(dane);
	}

};

void Kolo_Fortuny::przejscie(gracz* dane)
{
	cout << endl;
	cout << "Koniec " << rundy << " rundy" << endl;
	rundy++;
	tury = 0;

	if (rundy != 4)
	{
		nowa_runda(dane);
	}
	else
	{
		koniec(dane);
	}

};
void Kolo_Fortuny::nowa_runda(gracz* dane)

{
	int min = 0;

	if (ile_osob == 1)
	{
		cout << "w tej rundzie zdobyles " << dane[0].wygrana_kwota << "zl" << endl;
	}
	else
	{
		for (int i = 0; i < ile_osob; i++)
		{
			if (dane[i].wygrana_kwota < dane[i + 1].wygrana_kwota) //ustalanie najmniejszej wygranej kwoty 
			{
				min = dane[i].wygrana_kwota;
				miejsce_w_tablicy_gracza = i;
			}
		}
		cout << endl;
		cout << dane[miejsce_w_tablicy_gracza].imie << " zdobyles/as namniej pieniedzy: " << min << " zaczynasz nastepna runde" << endl;
	}

	for (int i = 0; i < ile_osob; i++)
	{
		dane[i].calkowita_wygrana_kwota += dane[i].wygrana_kwota;	//przepisanie wygranej kwoty w danej rundzie do calkowitej wygranej kwoty gracza
		dane[i].wygrana_kwota = 0;	//zerowanie wygranej kwoty w danej rundzie
	}


	for (int i = 0; i < uzyte_spolgloski_max; i++)
	{
		uzyte_spolgloski[i] = 0;	//zerowanie tablicy wykorzystanych spolglosek
	}

	uzyte_spolgloski_max = 1;
	uzyte_spolgloski_min = 0;
	odgadniete_pole = 0;

	haslo.clear();
	zaszyfrowane_haslo.clear();

	cout << dane[miejsce_w_tablicy_gracza].imie << " wcisnij aby rozpoczac kolejna runde" << endl;
	char a;
	cin >> a;

	system("cls");
	losuj_kategorie(dane);

};
void Kolo_Fortuny::koniec(gracz* dane)
{

	for (int i = 0; i < ile_osob; i++)
	{
		dane[i].calkowita_wygrana_kwota += dane[i].wygrana_kwota;	//przepisanie wygranej kwoty w danej rundzie do calkowitej wygranej kwoty gracza
	}

	int max = 0;
	for (int i = 0; i < ile_osob; i++)
	{
		if (dane[i].calkowita_wygrana_kwota > max)
			max = dane[i].calkowita_wygrana_kwota;	//ustalenie najwiekszej wygranej kwoty
	}

	for (int i = 0; i < ile_osob; i++)
	{
		if (dane[i].calkowita_wygrana_kwota == max)
			miejsce_w_tablicy_gracza = dane[i].miejsce_w_tablicy;	//ustalenie wygranego gracza
	}

	cout << "GRATULACJE! " << dane[miejsce_w_tablicy_gracza].imie << " " << "wygrywasz gre." << endl;

	cout << " gra ukonczona" << endl;
	cout << endl;
	cout << "GRACZ	| " << "KWOTA	| " << "LACZNA WARTOSC NAGROD  |" << "                 NAGRODY					" << endl;
	cout << "----------------------------------------------------------------------------------------------------------" << endl;

	if (ile_osob == 1)
	{
		cout << dane[0].imie << setw(10) << dane[0].calkowita_wygrana_kwota << setw(13) << dane[0].wartosc_nagrody_gracza << "zl" << setw(25);

		for (int k = 0; k < dane[0].max_miejsca_w_tablicy_ng; k++)
		{
			cout << dane[0].nagroda_gracza[k] << " ";
		}

	}
	else
	{
		for (int i = 0; i < ile_osob; i++)
		{
			cout << dane[i].imie << setw(10) << dane[i].calkowita_wygrana_kwota << setw(13) << dane[i].wartosc_nagrody_gracza << "zl" << setw(25);
			for (int k = 0; k < dane[i].max_miejsca_w_tablicy_ng; k++)
			{
				cout << dane[i].nagroda_gracza[k] << " ";
			}
			cout << endl;
		}
	}
	cout << endl;
	exit(0);
};

int main()
{
	srand(time(NULL));
	cout << "aby zakupic samogloske wcisnij 0" << endl;
	cout << "aby uzyc samogloske wcisnij 9" << endl;
	cout << "aby odgadnac haslo wcisnij 8" << endl;
	cout << endl;

	Kolo_Fortuny::gracz dane[4];

	Kolo_Fortuny gra;
	gra.losuj_kolejnosc(dane);

	return 0;
}