#include <string.h>
#ifdef __APPLE__ 
#include <GLUI/glui.h>
#else
#include <GL/glui.h>
#endif

#include "Automato.h"
#include "Importer.h"
#include <regex>

using namespace std;

int main_window, paused, qtd_estados, old_qtd_estados;

Automato *automato = NULL;

GLUI_EditText *edittext;

Importer *importer = new Importer();

set<string> palavrasDaRegex;

string text;

string regexDoUsuario;
string oldRegexDoUsuario;

bool palavra_pertence_ao_automato(string);
bool palavra_pertence_a_regex(string);

void getRegex(int control)
{ 
	palavrasDaRegex.clear();
	
	oldRegexDoUsuario = regexDoUsuario;
	string regexDada = edittext->get_text();
	regexDoUsuario = regexDada;
	
	if (regexDada.size()==0 || regexDada == "Q") return;
	
	importer->gerarArquivoComPalavras(regexDada);
	
	if (regex_match ("", regex(regexDada)))
	{
		FILE *arquivo = fopen("strings","a");
		fprintf(arquivo,"E");
		fclose(arquivo);
	}
	
	palavrasDaRegex = importer->getPalavras("strings");
	
	double perc_regex, perc_aut;
	int count;
	
	count = 0;
	for (set<string>::iterator it=palavrasDaRegex.begin(); it!=palavrasDaRegex.end(); ++it) if( palavra_pertence_ao_automato(*it) ) count++;
	perc_regex = (double)(count)*100.0/(double)(palavrasDaRegex.size());
	
	count = 0;
	for (set<string>::iterator it=automato->palavrasDoAutomato.begin(); it!=automato->palavrasDoAutomato.end(); ++it) if( palavra_pertence_a_regex(*it) ) count++;
	perc_aut = (double)(count)*100.0/(double)(automato->palavrasDoAutomato.size());
	
	printf("%s | %.2lf | %.2lf\n", regexDada.c_str(), perc_regex, perc_aut);
	
}

#include "draw"

void init()
{
	/* set clear color to black */

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 2.0, 0.0, 1.0, 0.0, 1.0);
}

/**************************************** main() ********************/

void imprimir_help()
{
	char word[55], i;
	FILE *help = fopen("help", "r");
	while(1)
	{
		
		fscanf(help,"%s",word);
		if (word[strlen(word)-1] == '#')
		{
			for (i = 0; i<strlen(word)-1; i++) printf("%c",word[i]);
			printf("\n");
		}
		else if (word[strlen(word)-1] == '@') break;
		else printf("%s ",word);		
	}
}

int main(int argc, char* argv[])
{
	int a;
	do
	{
		system("clear");
		imprimir_help();
		printf("continuar? (1 para sim) "); scanf("%d", &a);
	}while(a != 1);

	paused=0;
	qtd_estados=2;
	old_qtd_estados=2;
	automato = new Automato(qtd_estados);

	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc,argv); 
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(800,400);
	glutInitWindowPosition(0,0);
	main_window = glutCreateWindow("It's raining languages!");
	init();
	
	glutDisplayFunc(display);
	glutIdleFunc(animate);
	

	/****************************************/
	/*         Here's the GLUI code         */
	/****************************************/

	GLUI *glui = GLUI_Master.create_glui( "GLUI" );
	new GLUI_Checkbox( glui, "Paused", &paused );
	(new GLUI_Spinner( glui, "Qtd. Estados:", &qtd_estados ))->set_int_limits( 2, 6 );
	edittext = new GLUI_EditText(glui, "Text:", text,3, getRegex);

	glui->set_main_gfx_window( main_window );

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc( animate );

	glutMainLoop();

  return 0;
}
