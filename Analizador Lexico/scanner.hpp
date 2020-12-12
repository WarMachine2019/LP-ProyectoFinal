
#include <string.h>

/*
**	Tipos de token.
*/
enum TipoToken
{
	ENTERO,
	PORCENTAJE,
	SIGNO_ARITMETICO,
	SIGNO_COMA,
	SIGNO_IGUAL,
	SIGNO_CONDICION,
	KEYWORD,
	IDENTIFICADOR_VARIABLE,
	IDENTIFICADOR_LED
};

/*
**	Estructura de un token.
*/
struct Token
{
	TipoToken tipo;
	char valor[1024];

	Token (TipoToken tipo, const char *valor)
	{
		this->tipo = tipo;
		strcpy(this->valor, valor);
	}
};

/*
**	Analiza un vector de char (contenido) y retorna una tabla de simbolos.
*/
vector<Token> analizar (vector<char>& contenido)
{
	static char buffer[1024];
	static int buffer_i;

	int estado;
	vector<Token> simbolos;

	estado = 0;
	buffer_i = 0;

	return simbolos;
}
