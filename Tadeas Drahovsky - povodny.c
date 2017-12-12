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


void vypis_odmien (FILE *predaj, int zad_datum){
	char meno[50], SPZ[8], znak, akt_dat[9];
	int riadky = 1, i, j = 10000000, k, typ, datum, akt_dat_int = 0;
	float cena, odmena;
	
	// Zistenie riadkov v subore
	fseek(predaj, 0, SEEK_SET );
	do{
		znak = fgetc(predaj);
		if(znak == '\n') riadky++;
	}
	while (znak != EOF);
	
	// Ziskanie casu
	akt_dat_int = zad_datum;
	
	
	// Vypis dokumentu podla pravidiel
	fseek(predaj, 0, SEEK_SET );
	for (i=0; i<riadky; i++){
		switch (i%6){
			case 0: fgets(meno, 50, predaj);
				break;
			case 1: fgets(SPZ, 8, predaj);
				break;
			case 2: fscanf(predaj, "%d", &typ);
				break;
			case 3: fscanf(predaj, "%f", &cena);
				break;
			case 4: fscanf(predaj, "%d", &datum);
				fgetc(predaj);
				
				if ((akt_dat_int - datum) >= 10000){
					if (typ == 1) odmena = cena * 15 / 1000;
					else odmena = cena * 22 / 1000;
					
					for (k=0; k<50; k++){
						if (meno[k] == '\n') break;
						putchar(meno[k]);
					}
					putchar(' ');
					
					for (k=0; k<8; k++){
						if (SPZ[k] == '\n') break;
						putchar(SPZ[k]);
					}
					putchar(' ');
					
					printf("%.2f", odmena);
					putchar('\n');
				}
				
				do{
					znak = fgetc(predaj);
					if(znak == '\n') break;
				}
				while (znak != EOF);
				break;
		}
	}
}


char** nacitat_SPZ_do_pola (char **SPZ, int *dealloc, FILE *predaj, int *SPZ_pocet){
	int i, j, riadky = 1;
	char znak;
	
	// Spocitanie riadkov v subore
	fseek(predaj, 0, SEEK_SET );
	do{
		znak = fgetc(predaj);
		if(znak == '\n') riadky++;
	}
	while (znak != EOF);
	
	// Pocet SPZ v subore
	riadky = (riadky - 1) / 6;
	*SPZ_pocet = (riadky + 1);
	
	// Dealokovanie predchadzajuceho pola SPZtiek, ak uz raz bolo vytvorene
	if (*dealloc == 1){
		for (i=0; i<(*SPZ_pocet); i++){
			free(SPZ[i]);
		}
		free(SPZ);
	}
	*dealloc = 1;
	
	// Alokovanie dvojrozmerneho pola pre SPZtky
	SPZ = (char **) malloc((*SPZ_pocet)* sizeof(char *));
	for (i=0; i<(*SPZ_pocet); i++){
		SPZ[i] = (char *) malloc(8* sizeof(char));
	}
	
	
	// Naplnenie pola SPZtkami
	fseek(predaj, 0, SEEK_SET );
	for (i=0; i<(*SPZ_pocet); i++){
		do{
			znak = fgetc(predaj);
			if(znak == '\n') break;
		}
		while (znak != EOF);
		
		fgets(SPZ[i], 8, predaj);
		
		for (j=0; j<5; j++){
			do{
				znak = fgetc(predaj);
				if(znak == '\n') break;
			}
			while (znak != EOF);	
		}
	}
	
	return SPZ;
}


void vypis_SPZ_z_pola (char **SPZ, int dealloc, int SPZ_pocet){
	int i;
	
	// Vypis pola SPZtiek
	if (dealloc == 0) printf("Pole nie je vytvorene\n");
	else{
		for (i=0; i<SPZ_pocet; i++){
			printf("%c%c %c%c%c %c%c", SPZ[i][0], SPZ[i][1], SPZ[i][2], SPZ[i][3], SPZ[i][4], SPZ[i][5], SPZ[i][6]);
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
