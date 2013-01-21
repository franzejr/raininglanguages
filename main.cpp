#include <string.h>
#ifdef __APPLE__ 
#include <GLUI/glui.h>
#else
#include <GL/glui.h>
#endif

#include "Automato.h"
#include "Importer.h"
#include <regex>

int main_window, paused, qtd_estados, old_qtd_estados;

Automato *automato = NULL;

GLUI_EditText *edittext;

Importer *importer = new Importer();

set<string> palavrasDaRegex;

std::string text;

std::string regexDoUsuario;
std::string oldRegexDoUsuario;

void getRegex(int control)
{ 
	palavrasDaRegex.clear();
	
	oldRegexDoUsuario = regexDoUsuario;
	string regexDada = edittext->get_text();
	regexDoUsuario = regexDada;
	
	if (regexDada.size()==0) return;
	
	importer->gerarArquivoComPalavras(regexDada);
	
	if (regex_match ("", regex(regexDada)))
	{
		FILE *arquivo = fopen("strings","a");
		fprintf(arquivo,"E");
		fclose(arquivo);
	}
	
	palavrasDaRegex = importer->getPalavras("strings");
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

int main(int argc, char* argv[])
{
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
