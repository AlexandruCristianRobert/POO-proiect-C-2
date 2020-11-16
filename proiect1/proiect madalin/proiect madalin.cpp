/*

gestionarea unui parc auto

tine evidenta :		revizii
					asigurari
					taxe de drum
clasa autovehicul
		obiecte			revizie
						asigurari
						taxe de drum

*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<iomanip>
#include<string>
using namespace std;
class ParcAuto
{
private:
	int la;
	char* nume_autovehicul;
	string revizie;
	string asigurare;
	string taxaDeDrum;
	int  luniAn[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
public:
	static int FaraRevizie;
	static int FaraTaxa;
	static int FaraAsig;
	static int MasiniOk;
	static int Masini;
	//constructor
	ParcAuto(string frevizie, string ftaxaDeDrum, string fasigurare, const char* fnume_autovehicul = "Nedefinit") :revizie(frevizie), asigurare(fasigurare), taxaDeDrum(ftaxaDeDrum)
	{
		la = strlen(fnume_autovehicul);
		nume_autovehicul = new char[la + 1];
		strcpy(nume_autovehicul, fnume_autovehicul);
		FaraAsig += IM(asigurare);
		FaraRevizie += IM(revizie);
		FaraTaxa += IM(taxaDeDrum);
		if (IM(revizie) == 0 && IM(asigurare) == 0 && IM(taxaDeDrum) == 0)
			MasiniOk++;
		Masini++;
	}

	// constructor de copiere
	ParcAuto(ParcAuto& ob) :revizie(ob.revizie), asigurare(ob.asigurare), taxaDeDrum(ob.taxaDeDrum)
	{
		la = strlen(ob.nume_autovehicul);
		this->nume_autovehicul = new char[la + 1];
		strcpy(nume_autovehicul, ob.nume_autovehicul);
		FaraAsig += IM(asigurare);
		FaraRevizie += IM(revizie);
		FaraTaxa += IM(taxaDeDrum);
		if (IM(revizie) == 1 && IM(asigurare) == 1 && IM(taxaDeDrum) == 1)
			MasiniOk++;
		Masini++;

	}

	void afisare()
	{

		set_revizie(revizie);
		set_asigurare(asigurare);
		set_taxaDeDrum(taxaDeDrum);
		cout << setw(10) << nume_autovehicul << " " << setw(25) << revizie << setw(25) << asigurare << setw(25) << taxaDeDrum << endl;
	}

	void set_revizie(string revizie_autovehicul)
	{
		if (revizie != "X")
		{
			revizie = revizie_autovehicul;
			return;
		}
		else
		{
			revizie = "Nu este facuta";
			return;
		}
		cerr << "Revizia " << revizie << " nu este facuta";
	}
	string get_revizie()
	{

		return revizie;
	}

	void set_nume(const char* nume)
	{
		if (la < strlen(nume))
		{
			la = strlen(nume);
			delete[] nume_autovehicul;
			nume_autovehicul = new char[la + 1];
		}
		strcpy(nume_autovehicul, nume);
	}

	char* get_nume()
	{
		return nume_autovehicul;

	}

	void set_asigurare(string asigurare_autovehicul)
	{
		if (asigurare_autovehicul != "X")
		{
			asigurare = asigurare_autovehicul;
			return;
		}
		else
		{
			asigurare = "Nu e facuta";
			return;
		}
		cerr << "Asigurarea " << revizie << " nu este facuta";
	}

	string get_asigurare()
	{
		return asigurare;
	}

	void set_taxaDeDrum(string taxaDeDrum_autovehicul)
	{
		if (taxaDeDrum_autovehicul != "X")
		{
			taxaDeDrum = taxaDeDrum_autovehicul;
			return;
		}
		else
		{
			taxaDeDrum = "Nu e facuta";
			return;
		}

		cerr << "Taxa de drum" << taxaDeDrum << " nu este facuta";
	}

	string get_taxaDeDrum()
	{
		return taxaDeDrum;
	}


	~ParcAuto()
	{
		delete[] nume_autovehicul;
	}
	int a[3]{ 0,0,0 };
	void transformare(string text)//  transformam string-ul ce are o data introdusa intr-un vector ce retine dd mm yyyy
	{
		a[0] = 0;
		a[1] = 0;
		a[2] = 0;
		int nr;
		for (int i = 0;i < 2;i++)
		{
			nr = 0;
			for (char j = '0';j <= '9';j++)
			{
				if (text[i] == j)
					a[0] = a[0] * 10 + nr;
				nr++;
			}
		}

		for (int i = 3;i < 5;i++)
		{
			nr = 0;
			for (char j = '0';j <= '9';j++)
			{
				if (text[i] == j)
					a[1] = a[1] * 10 + nr;
				nr++;
			}
		}

		for (int i = 6;i < 10;i++)
		{
			nr = 0;
			for (char j = '0';j <= '9';j++)
			{
				if (text[i] == j)
					a[2] = a[2] * 10 + nr;
				nr++;
			}
		}


	}
	bool comparare(int data_masina[], int data_verificare[])// la fel, data_masina e data introdusa si data_veriifcare e cand expira x/y/z
	{
		if (data_masina[2] - data_verificare[2] > 1)
			return false;
		if (data_masina[2] - data_verificare[2] == 1 && data_masina[1] < data_verificare[1])
			return false;
		if (data_masina[2] - data_verificare[2] == 1 && data_masina[1] == data_verificare[1] && data_masina[0] <= data_verificare[0])
			return false;
		if (data_masina[2] == data_verificare[2] && data_masina[1] < data_verificare[1])
			return false;
		if (data_masina[2] == data_verificare[2] && data_masina[1] == data_verificare[1] && data_masina[0] <= data_verificare[0])
			return false;

		return true;
	}
	int data_car[3]{ 0,0,0 };
	int data_verif[3]{ 0,0,0 };
	int nr_zile = 0;
	bool compararecuData(string data_masina, string data_verificare)// la fel, data_masina e data introdusa si data_veriifcare e cand expira x/y/z
	{

		data_car[0] = 0;
		data_car[1] = 0;
		data_car[2] = 0;
		data_verif[0] = 0;
		data_verif[1] = 0;
		data_verif[2] = 0;
		transformare(data_masina);
		for (int i = 0;i < 3;i++)
			data_car[i] = a[i];
		transformare(data_verificare);
		for (int i = 0;i < 3;i++)
			data_verif[i] = a[i];
		data_verif[2]++;//  aici la data se adauga un an , adica valabilitatea asigurarii/taxei de drum/reviziei.

		if (!comparare(data_car, data_verif))
			return  false;
		return true;
	}


	void zileRamase()//de fapt data_car e data pe care o verificam si data_verif e data cand expira revizia/asig/taxa
	{
		int  i;
		nr_zile = 0;

		if (data_verif[2] > data_car[2])
		{
			nr_zile = luniAn[data_car[1] - 1] - data_car[0];// pentru ca am stocate zilele pe luna in luniAN si sunt stocate pe pozitia anterioara
			i = data_car[1];
			while (i < 12)
			{
				nr_zile += luniAn[i];
				i++;
			}
			i = 0;
			while (i < data_verif[1] - 1)
			{
				nr_zile += luniAn[i];
				i++;
			}

			nr_zile = nr_zile + data_verif[0];


		}
		else
			if (data_verif[1] > data_car[1])
			{
				i = data_car[1];
				nr_zile = luniAn[data_car[1] - 1] - data_car[0];
				while (i < data_verif[1] - 1)
				{
					nr_zile += luniAn[i];
					i++;
				}
				nr_zile = nr_zile + data_verif[0];

			}
			else
				nr_zile = data_car[0] - data_verif[0];


	}

	void verificareData(string data)
	{
		cout << "La data de " << data << " masina " << nume_autovehicul << " are urmatoarele:" << endl << endl;
		if (revizie == "X")
			cout << "Revizia nu este facuta" << endl;
		else
			if (compararecuData(data, revizie))
			{
				zileRamase();
				cout << "Revizia mai e valabila timp de " << nr_zile << " zile la aceasta data" << endl;
			}
			else
				cout << "Revizia a expirat." << endl;
		if (taxaDeDrum == "X")
			cout << "Taxa de drum nu este platita" << endl;
		else
			if (compararecuData(data, taxaDeDrum))
			{
				zileRamase();
				cout << "Taxa de drum mai e valabila timp de " << nr_zile << " zile la aceasta data" << endl;
			}
			else
				cout << "Taxa de drum trebuie platita." << endl;
		if (asigurare == "X")
			cout << "Asigurarea nu este facuta" << endl;
		else
			if (compararecuData(data, asigurare))
			{
				zileRamase();
				cout << "Asigurarea mai e valabila timp de " << nr_zile << " zile la aceasta data" << endl;
			}
			else
				cout << "Asigurarea a expirat." << endl;

	}

	int IM(string caracteristica) // Incadrare Masina
	{

		if (caracteristica == "X")
			return 1;
		return 0;
	}
};
int ParcAuto::FaraAsig = 0;
int ParcAuto::FaraRevizie = 0;
int ParcAuto::FaraTaxa = 0;
int ParcAuto::MasiniOk = 0;
int ParcAuto::Masini = 0;
void main()
{

	/* 
	
												Instructiuni de utilizare
		Se introduc masinile in parc de forma 

		ParcAuto numitor_masina(data la care s-a facut revizia sau X daca nu o are,data la care s-a platit taxa de drum sau X daca nu o are,data la care s-a facut asigurarea sau X daca nu o are, numarul de inmatriculare")
		
		RESTRICTII
		Data se va introduce de forma DD/MM/YYYY, programul lucreaza doar cu data de forma aceea (semnele pot varia, dar maxim|minim un semn intre numere

		Verificarea starii unei masini se va face cu functia verificareData(data la care vrem sa verificam)

		Pentru afisarea masinilor cu caracteristicile lor se va folosi afisare();

		Pentru afisare se recomanda penultimul rand sa fie trecut.

	*/
	ParcAuto s1("25.09.1997", "22.09.1996", "24.09.1997", "IF 97 SEP");

	cout << "In momentul de fata, in parcul auto sunt " << ParcAuto::Masini << " autovehicule din care:" << endl;
	cout << endl;
	cout << "Masini care au revizia, asigurarea si taxa de drum platite " << ParcAuto::MasiniOk << endl;
	cout << "Masini fara revizie " << ParcAuto::FaraRevizie << endl;
	cout << "Masini fara asigurare " << ParcAuto::FaraAsig << endl;
	cout << "Masini cu taxa de drum neplatita " << ParcAuto::FaraTaxa << endl;
	cout << endl;
	s1.verificareData("25.09.1997");

	//cout << setw(10) << "Nume Autovehicul" << " " << setw(20) << "revizie" << setw(25) << "asigurare" << setw(25) << "Taxa De Drum" << endl;
	s1.afisare();





}