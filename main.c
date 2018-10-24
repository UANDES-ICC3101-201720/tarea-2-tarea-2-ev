#include "page_table.h"
#include "disk.h"
#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int counterP,diskR,diskW = 0;
char *virtmem;
char *physmem;
int *auxArray;
char *argv3;
int auxdta;
int auxdta2;
int auxPag;
int npages;
int nframes;
struct disk *disk;

typedef struct Nodo
{
	int pagina;
	int dta;
	struct Nodo * siguiente;
} Nodo;

typedef struct Tabla
{
	Nodo * inicial;
}Tabla;

Tabla *data;
//no sirve
/*void Next(Nodo * node)
{
	node=node->siguiente;
}*/
int GetRandom(int min,int max)
{
	int dif=max-min;
	int random=lrand48()%dif;
	random=min+random;
	return random;
	
}
int GetPagina(Nodo *actual,int auxdta)//No sé por que no funciona con recursividad, fué cambiado por loop
{
	while (actual!=NULL)
	{
		if (actual->dta==auxdta)
		{
			return actual->pagina;
		}
		actual=actual->siguiente;
	}
	return -1;
}
/*void Imprimir()
{
	Nodo* actual=data->inicial;
	while (actual!=NULL)
	{
		printf("%d\n",actual->pagina);printf("%d\n",actual->dta);printf("\n");
		actual=actual->siguiente;
	}
}*/
void CambiarPagina(Nodo *actual,int inputdta,int inputPagina)
{
	if(actual==NULL){}
	else if(actual->dta==inputdta){actual->pagina=inputPagina;}
	else if(actual->dta!=inputdta){CambiarPagina(actual->siguiente,inputdta,inputPagina);}
}
/*void SacarUltimo()
{
	new=data->inicial;
	while(new->siguiente!=NULL){new=new->siguiente;}
	new->siguiente=malloc(sizeof(Nodo));
	new=NULL;
}
*/
void AgregarNodo(Nodo *new,int inputdta,int inputpagina)
{
	new=data->inicial;
	while(new->siguiente!=NULL){new=new->siguiente;}
	new->siguiente=malloc(sizeof(Nodo));
	new=new->siguiente;
	new->pagina=inputpagina;
	new->dta=inputdta;
}
void EliminarPrimerNodo(){data->inicial = data->inicial->siguiente;}
/*void SacarX(int i)
{
	new.....
*/

//-------------------------------------------------------------------------------------------------//
// MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK //
//------------------------------------------------------------------------------------------------//
void page_fault_handler(struct page_table *pt, int page)
{                          
	int activar=1;counterP++;int auxC=0;	
	for (int i=0;i<nframes;i++)
	{
	if(auxArray[i]!=-1)
	{
	//printf("Error en page_fault_handler");"
	diskR++;disk_read(disk,page,&physmem[i*PAGE_SIZE]);
	page_table_set_entry(pt,page,i,PROT_READ|PROT_WRITE|PROT_EXEC);
	Nodo *new=data->inicial;AgregarNodo(new,i,page);
	auxC++;activar=0;auxArray[i]=-1;
	break;
	}
	}
//-------------------------------------------------------------------------------------------------//
// MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK MARK //
//------------------------------------------------------------------------------------------------// 


//METhod codes//
	if (activar==1)
	{
		if (!strcmp(argv3, "fifo"))
		{
			auxdta = data->inicial->dta;
			auxPag = data->inicial->pagina;
			EliminarPrimerNodo();
			Nodo *new = data->inicial;AgregarNodo(new,auxdta,page);
			diskW++;disk_write(disk,auxPag,&physmem[auxdta*PAGE_SIZE]);
			diskR++;disk_read(disk, page, &physmem[auxdta*PAGE_SIZE]);
			
		}
		if (!strcmp(argv3, "custom"))//ciclico
		{
			auxdta2--;
			if(auxdta2==1){auxdta2=nframes-1;}
			auxdta=auxdta2;
			auxPag = GetPagina(data->inicial,auxdta);
			diskW++;disk_write(disk,auxPag, &physmem[auxdta*PAGE_SIZE]);
			diskR++;disk_read(disk, page, &physmem[auxdta*PAGE_SIZE]);
			CambiarPagina(data->inicial,auxdta,page);
		}
		if (!strcmp(argv3, "random"))
		{
			auxdta =GetRandom(0,nframes);
			auxPag = GetPagina(data->inicial,auxdta);
			diskW++;disk_write(disk,auxPag, &physmem[auxdta*PAGE_SIZE]);
			diskR++;disk_read(disk, page, &physmem[auxdta*PAGE_SIZE]);
			CambiarPagina(data->inicial,auxdta,page);
			
		}
		
		page_table_set_entry(pt,auxPag,auxdta, 0);
		page_table_set_entry(pt, page,auxdta,PROT_READ|PROT_WRITE|PROT_EXEC);
	}
}

int main(int argc, char *argv[])
{
	
	argv3 = argv[3];
	data = malloc(sizeof(Tabla));
	data->inicial = malloc(sizeof(Nodo));
	npages = atoi(argv[1]);
	nframes = atoi(argv[2]);
	auxdta2=nframes-1;
	int aux[nframes];
	auxArray=aux;
	for(int j=0;j<nframes;++j){auxArray[j]=j;}

	const char *program = argv[4];

	disk = disk_open("myvirtualdisk", npages);
	if (!disk)
	{
		fprintf(stderr, "couldn't create virtual disk: %s\n", strerror(errno));
		return 1;
	}

	struct page_table *pt = page_table_create(npages, nframes, page_fault_handler);

	if (!pt)
	{
		fprintf(stderr, "couldn't create page table: %s\n", strerror(errno));
		return 1;
	}

	virtmem = page_table_get_virtmem(pt);
	physmem = page_table_get_physmem(pt);
	for (int i=0; i < nframes; ++i)
	{
		disk_write(disk, i, &physmem[i * BLOCK_SIZE]);
	}

	if (!strcmp(program, "sort"))
	{
		//printf("Error en sort_program");"
		sort_program(virtmem, npages * PAGE_SIZE);
	}
	else if (!strcmp(program, "scan"))
	{
		scan_program(virtmem, npages * PAGE_SIZE);
	}
	else if (!strcmp(program, "focus"))
	{
		focus_program(virtmem, npages * PAGE_SIZE);
	}
	else
	{
		fprintf(stderr, "unknown program: %s\n", argv[4]);
	}
	printf("Pages Faults: %i\nDisk Writes: %i\nDisk Reads: %i\n", counterP, diskW, diskR);
	page_table_delete(pt);
	disk_close(disk);
	free(data);
	return 1;
}
