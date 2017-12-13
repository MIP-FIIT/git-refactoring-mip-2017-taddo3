#include <stdio.h>
#include <stdlib.h>


int pocet_riadkov_v_subore (FILE *subor){
	
	int pocet_riadkov = 1;
	char znak;
	
	rewind(subor);
	
	do{
		znak = fgetc(subor);
		if(znak == '\n') pocet_riadkov++;
	}
	while (znak != EOF);
	
	rewind(subor);
	
	return pocet_riadkov;
}


FILE* otvorenie_a_vypis_suboru (int *otvoreny_subor){
	
	FILE *subor;
	int cislo_riadku, pocet_riadkov;
	char znak, *jeden_riadok;

	if((subor = fopen("predaj.txt", "r")) == NULL){
		printf("Neotvoreny subor\n");
		return;
	}
	else *otvoreny_subor = 1;
	
	pocet_riadkov = pocet_riadkov_v_subore(subor);
	
	jeden_riadok = (char *) malloc(50* sizeof(char));
	
	for (cislo_riadku = 0; cislo_riadku < pocet_riadkov; cislo_riadku++){
		
		fgets(jeden_riadok, 50, subor);
		
		switch (cislo_riadku % 6){	
		
			case 0: 
				printf("meno priezvisko: %s", jeden_riadok);
				break;	
					
			case 1: 
				printf("SPZ: %s", jeden_riadok);
				break;
					
			case 2: 
				printf("typ auta: %s", jeden_riadok);
				break;
					
			case 3: 
				printf("cena: %s", jeden_riadok);
				break;
					
			case 4: 
				printf("datum: %s\n", jeden_riadok);
				break;
		}
	}
	free(jeden_riadok);
	
	return subor;
}


void vypis_odmien (FILE *subor, int zadany_datum){
	
	char meno_zo_suboru[50], SPZ_zo_suboru[8], znak;
	int pocet_riadkov = 1, cislo_riadku, znak_v_poli, typ_vozidla, datum_zo_suboru;
	float cena_vozidla, odmena_pre_predajcu;
	
	pocet_riadkov = pocet_riadkov_v_subore(subor);
	
	for (cislo_riadku = 0; cislo_riadku < pocet_riadkov / 6 + 1; cislo_riadku++){
		
		fgets(meno_zo_suboru, 50, subor);
		fgets(SPZ_zo_suboru, 8, subor);
		fscanf(subor, "%d", &typ_vozidla);
		fscanf(subor, "%f", &cena_vozidla);
		fscanf(subor, "%d", &datum_zo_suboru);
		fgetc(subor);
		fgetc(subor);
			
		if ((zadany_datum - datum_zo_suboru) >= 10000){
			
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
	}
}


char** nacitat_SPZ_do_pola (char **pole_SPZ, int *vytvorene_pole, FILE *subor, int *pocet_SPZ){
	
	int i, j, pocet_riadkov = 1;
	char znak;
	
	*pocet_SPZ = pocet_riadkov_v_subore(subor) / 6 + 1;
	
	if (*vytvorene_pole == 1){
		for (i = 0; i < (*pocet_SPZ); i++){
			free(pole_SPZ[i]);
		}
		free(pole_SPZ);
	}
	*vytvorene_pole = 1;
	
	pole_SPZ = (char **) malloc((*pocet_SPZ)* sizeof(char *));
	for (i = 0; i < (*pocet_SPZ); i++){
		pole_SPZ[i] = (char *) malloc(8* sizeof(char));
	}
	
	// Naplnenie pola SPZtkami zo suboru, cykly sluzia ako offset
	rewind(subor);
	
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
	
	int poradove_cislo, cislo_znaku;
	
	if (vytvorene_pole == 0) printf("Pole nie je vytvorene\n");
	else{
		for (poradove_cislo = 0; poradove_cislo < pocet_SPZ; poradove_cislo++){
			for (cislo_znaku = 0; cislo_znaku <= 6; cislo_znaku++){
				printf("%c", pole_SPZ[poradove_cislo][cislo_znaku]);
			}
			printf("\n");
		}
	}
}


int main(){
	
	FILE *subor;
	int otvoreny_subor = 0, vytvorene_pole = 0, pocet_SPZ, datum, poradie_v_poli;
	char pismenko, **pole_SPZ;
	
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
