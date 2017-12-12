#include <stdio.h>
#include <stdlib.h>

FILE* otvorenie_a_vypis_suboru (int *otvoreny_subor){
	FILE *subor;
	int cislo_riadku, pocet_riadkov = 1;
	char znak, *jeden_riadok;
	
	// Test + otvorenie suboru
	if((subor = fopen("predaj.txt", "r")) == NULL){
		printf("Neotvoreny subor\n");
		return;
	}
	else *otvoreny_subor = 1;
	
	// Spocitanie riadkov v subore
	do{
		znak = fgetc(subor);
		if(znak == '\n') pocet_riadkov++;
	}
	while (znak != EOF);
	
	fseek(subor, 0, SEEK_SET );
	jeden_riadok = (char *) malloc(50* sizeof(char));
	
	// Vypis suboru
	for (cislo_riadku = 0; cislo_riadku < pocet_riadkov; cislo_riadku++){
		fgets(jeden_riadok, 50, subor);
		switch (cislo_riadku % 6){
			case 0: printf("meno priezvisko: %s", jeden_riadok);
				break;
			case 1: printf("SPZ: %s", jeden_riadok);
				break;
			case 2: printf("typ auta: %s", jeden_riadok);
				break;
			case 3: printf("cena: %s", jeden_riadok);
				break;
			case 4: printf("datum: %s\n", jeden_riadok);
				break;
		}
	}
	free(jeden_riadok);
	
	return subor;
}


void vypis_odmien (FILE *subor, int datum){
	char meno_zo_suboru[50], SPZ_zo_suboru[8], znak, akt_dat[9];
	int pocet_riadkov = 1, cislo_riadku, j = 10000000, znak_v_poli, typ_vozidla, akt_dat_int = 0;
	float cena_vozidla, odmena_pre_predajcu;
	
	// Zistenie riadkov v subore
	fseek(subor, 0, SEEK_SET );
	do{
		znak = fgetc(subor);
		if(znak == '\n') pocet_riadkov++;
	}
	while (znak != EOF);
	
	// Ziskanie casu
	akt_dat_int = datum;
	
	
	// Vypis dokumentu podla pravidiel
	fseek(subor, 0, SEEK_SET );
	for (cislo_riadku = 0; cislo_riadku < pocet_riadkov; cislo_riadku++){
		switch (cislo_riadku % 6){
			case 0: fgets(meno_zo_suboru, 50, subor);
				break;
			case 1: fgets(SPZ_zo_suboru, 8, subor);
				break;
			case 2: fscanf(subor, "%d", &typ_vozidla);
				break;
			case 3: fscanf(subor, "%f", &cena_vozidla);
				break;
			case 4: fscanf(subor, "%d", &datum);
				fgetc(subor);
				
				if ((akt_dat_int - datum) >= 10000){
					if (typ_vozidla == 1) odmena_pre_predajcu = cena_vozidla * 15 / 1000;
					else odmena_pre_predajcu = cena_vozidla * 22 / 1000;
					
					for (znak_v_poli = 0; znak_v_poli < 50; znak_v_poli++){
						if (meno_zo_suboru[znak_v_poli] == '\n') break;
						putchar(meno_zo_suboru[znak_v_poli]);
					}
					putchar(' ');
					
					for (znak_v_poli = 0; znak_v_poli < 8; znak_v_poli++){
						if (SPZ_zo_suboru[znak_v_poli] == '\n') break;
						putchar(SPZ_zo_suboru[znak_v_poli]);
					}
					putchar(' ');
					
					printf("%.2f", odmena_pre_predajcu);
					putchar('\n');
				}
				
				do{
					znak = fgetc(subor);
					if(znak == '\n') break;
				}
				while (znak != EOF);
				break;
		}
	}
}


char** nacitat_SPZ_do_pola (char **pole_SPZ, int *vytvorene_pole, FILE *subor, int *pocet_SPZ){
	int i, j, pocet_riadkov = 1;
	char znak;
	
	// Spocitanie riadkov v subore
	fseek(subor, 0, SEEK_SET );
	do{
		znak = fgetc(subor);
		if(znak == '\n') pocet_riadkov++;
	}
	while (znak != EOF);
	
	// Pocet SPZ v subore
	pocet_riadkov = (pocet_riadkov - 1) / 6;
	*pocet_SPZ = (pocet_riadkov + 1);
	
	// Dealokovanie predchadzajuceho pola SPZtiek, ak uz raz bolo vytvorene
	if (*vytvorene_pole == 1){
		for (i = 0; i < (*pocet_SPZ); i++){
			free(pole_SPZ[i]);
		}
		free(pole_SPZ);
	}
	*vytvorene_pole = 1;
	
	// Alokovanie dvojrozmerneho pola pre SPZtky
	pole_SPZ = (char **) malloc((*pocet_SPZ)* sizeof(char *));
	for (i = 0; i < (*pocet_SPZ); i++){
		pole_SPZ[i] = (char *) malloc(8* sizeof(char));
	}
	
	
	// Naplnenie pola SPZtkami
	fseek(subor, 0, SEEK_SET );
	for (i = 0; i < (*pocet_SPZ); i++){
		do{
			znak = fgetc(subor);
			if(znak == '\n') break;
		}
		while (znak != EOF);
		
		fgets(pole_SPZ[i], 8, subor);
		
		for (j = 0; j < 5; j++){
			do{
				znak = fgetc(subor);
				if(znak == '\n') break;
			}
			while (znak != EOF);	
		}
	}
	
	return pole_SPZ;
}


void vypis_SPZ_z_pola (char **pole_SPZ, int vytvorene_pole, int pocet_SPZ){
	int poradove_cislo;
	
	// Vypis pola SPZtiek
	if (vytvorene_pole == 0) printf("Pole nie je vytvorene\n");
	else{
		for (poradove_cislo = 0; poradove_cislo < pocet_SPZ; poradove_cislo++){
			printf("%c%c %c%c%c %c%c", pole_SPZ[poradove_cislo][0], pole_SPZ[poradove_cislo][1], pole_SPZ[poradove_cislo][2], pole_SPZ[poradove_cislo][3], pole_SPZ[poradove_cislo][4], pole_SPZ[poradove_cislo][5], pole_SPZ[poradove_cislo][6]);
			printf("\n");
		}
	}
}


int main(){
	FILE *subor;
	int otvoreny_subor = 0, vytvorene_pole = 0, pocet_SPZ, datum, poradie_v_poli;
	char pismenko, **pole_SPZ;
	
	// Vyber jednotlivych funkcii
	while (1){
		
		scanf("%c", &pismenko);
		switch(pismenko){
			case 'v': 
				subor = otvorenie_a_vypis_suboru (&otvoreny_subor);
				break;
			case 'o':
				scanf("%d", &datum);
				if (otvoreny_subor == 1) vypis_odmien (subor, datum);
				break;
			case 'n':
				if (otvoreny_subor == 1) pole_SPZ = nacitat_SPZ_do_pola (pole_SPZ, &vytvorene_pole, subor, &pocet_SPZ);
				break;
			case 's':
				vypis_SPZ_z_pola (pole_SPZ, vytvorene_pole, pocet_SPZ);
				break;
			case 'k': 
				// Vycistenie pamate + zatvorenie suboru
				if (vytvorene_pole == 1){
					for (poradie_v_poli = 0; poradie_v_poli < pocet_SPZ; poradie_v_poli++){
						free(pole_SPZ[poradie_v_poli]);
					}
					free(pole_SPZ);
				}
				if (otvoreny_subor == 1) fclose(subor);
				
				return 0;
				
		}
	}
}
