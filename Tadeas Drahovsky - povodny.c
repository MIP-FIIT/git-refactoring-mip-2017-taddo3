#include <stdio.h>
#include <stdlib.h>


FILE *v (int *vykonat){
	FILE *predaj;
	int i, riadky = 1;
	char znak, *vypis_riadok;
	
	// Test + otvorenie suboru
	if((predaj = fopen("predaj.txt", "r")) == NULL){
		printf("Neotvoreny subor\n");
		return;
	}
	else *vykonat = 1;
	
	// Spocitanie riadkov v subore
	do{
		znak = fgetc(predaj);
		if(znak == '\n') riadky++;
	}
	while (znak != EOF);
	
	fseek(predaj, 0, SEEK_SET );
	vypis_riadok = (char *) malloc(50* sizeof(char));
	
	// Vypis suboru
	for (i=0; i<riadky; i++){
		fgets(vypis_riadok, 50, predaj);
		switch (i%6){
			case 0: printf("meno priezvisko: %s", vypis_riadok);
				break;
			case 1: printf("SPZ: %s", vypis_riadok);
				break;
			case 2: printf("typ auta: %s", vypis_riadok);
				break;
			case 3: printf("cena: %s", vypis_riadok);
				break;
			case 4: printf("datum: %s\n", vypis_riadok);
				break;
		}
	}
	
	free(vypis_riadok);
	return predaj;
}


void o(FILE *predaj, int zad_datum){
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


char** n(char **SPZ, int *dealloc, FILE *predaj, int *SPZ_pocet){
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


void s(char **SPZ, int dealloc, int SPZ_pocet){
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
	FILE *predaj;
	int i = 1, vykonat = 0, dealloc = 0, SPZ_pocet, datum;
	char volaj, **SPZ;
	
	// Vyber jednotlivych funkcii
	while (i == 1){
		scanf("%c", &volaj);
		switch(volaj){
			case 'v': 
				predaj = v(&vykonat);
				break;
			case 'o':
				scanf("%d", &datum);
				if (vykonat == 1) o(predaj, datum);
				break;
			case 'n':
				if (vykonat == 1) SPZ = n(SPZ, &dealloc, predaj, &SPZ_pocet);
				break;
			case 's':
				s(SPZ, dealloc, SPZ_pocet);
				break;
			case 'k': 
				i = 0;
				break;
		}
	}
	
	// Vycistenie pamate + zatvorenie suboru
	if (dealloc == 1){
		for (i=0; i<SPZ_pocet; i++){
			free(SPZ[i]);
		}
		free(SPZ);
	}
	if (vykonat == 1) fclose(predaj);
	
	return 0;
}
