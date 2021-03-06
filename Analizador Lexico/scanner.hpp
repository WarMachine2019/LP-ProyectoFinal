
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
**	Retorna el nombre de un TipoToken como string.
*/
const char *nombreTipoToken (TipoToken valor)
{
	switch (valor)
	{
		case TipoToken::ENTERO:
			return "ENTERO";

		case TipoToken::PORCENTAJE:
			return "PORCENTAJE";

		case TipoToken::SIGNO_ARITMETICO:
			return "SIGNO_ARITMETICO";

		case TipoToken::SIGNO_COMA:
			return "SIGNO_COMA";

		case TipoToken::SIGNO_IGUAL:
			return "SIGNO_IGUAL";

		case TipoToken::SIGNO_CONDICION:
			return "SIGNO_CONDICION";

		case TipoToken::KEYWORD:
			return "KEYWORD";

		case TipoToken::IDENTIFICADOR_VARIABLE:
			return "IDENTIFICADOR_VARIABLE";

		case TipoToken::IDENTIFICADOR_LED:
			return "IDENTIFICADOR_LED";
	}

	return "??";
}

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

	while (contenido.size() != 0)
	{
		char ch = contenido.front();

		switch (estado)
		{
			// **************************************************************
			case 0:
				buffer[buffer_i++] = ch;

				if (ch >= '0' && ch <= '9')
				{
					contenido.erase(contenido.begin());
					estado = 1;
					break;
				}

				switch (ch)
				{
					case ' ': case '\t': case '\r': case '\n':
						contenido.erase(contenido.begin());
						estado = 10;
						break;
				
					case '-': case '+':
						contenido.erase(contenido.begin());
						estado = 4;
						break;

					case ',':
						contenido.erase(contenido.begin());
						estado = 5;
						break;

					case '=':
						contenido.erase(contenido.begin());
						estado = 6;
						break;

					case '<':
						contenido.erase(contenido.begin());
						estado = 7;
						break;

					case '>':
						contenido.erase(contenido.begin());
						estado = 8;
						break;

					case 'W': case 'w':
						contenido.erase(contenido.begin());
						estado = 12;
						break;

					case 'S': case 's':
						contenido.erase(contenido.begin());
						estado = 13;
						break;

					case 'E': case 'e':
						contenido.erase(contenido.begin());
						estado = 14;
						break;

					case 'I': case 'i':
						contenido.erase(contenido.begin());
						estado = 15;
						break;

					case 'L': case 'l':
						contenido.erase(contenido.begin());
						estado = 16;
						break;

					case 'V': case 'v':
						contenido.erase(contenido.begin());
						estado = 17;
						break;

					default:
						cout << "Error: Simbolo " << ch << " no definido" << endl;
						return simbolos;
				}

				break;

			// **************************************************************
			case 1:
				if (ch >= '0' && ch <= '9')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 1;
					break;
				}

				if (ch == '%')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 3;
					break;
				}

				estado = 2;
				break;

			// **************************************************************
			case 2:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::ENTERO, buffer));
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 3:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::PORCENTAJE, buffer));
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 4:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::SIGNO_ARITMETICO, buffer));
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 5:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::SIGNO_COMA, buffer));
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 6:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::SIGNO_IGUAL, buffer));
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 7:
				if (ch == '=')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 9;
					break;
				}

				estado = 9;
				break;

			// **************************************************************
			case 8:
				if (ch == '=')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 9;
					break;
				}

				estado = 9;
				break;

			// **************************************************************
			case 9:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::SIGNO_CONDICION, buffer));
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 10:
				switch (ch)
				{
					case ' ': case '\t': case '\r': case '\n':
						buffer[buffer_i++] = ch;
						contenido.erase(contenido.begin());
						estado = 10;
						break;

					default:
						estado = 11;
						break;
				}

				break;

			// **************************************************************
			case 11:
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 12:
				if (ch == 'H' || ch == 'h')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 18;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 13:
				if (ch == 'E' || ch == 'e')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 23;
					break;
				}

				if (ch == 'L' || ch == 'l')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 25;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 18:
				if (ch == 'I' || ch == 'i')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 19;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 23:
				if (ch == 'T' || ch == 't')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 22;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 25:
				if (ch == 'E' || ch == 'e')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 26;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 19:
				if (ch == 'L' || ch == 'l')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 20;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 22:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::KEYWORD, buffer));
				estado = 0; buffer_i = 0;
				break;

			// **************************************************************
			case 26:
				if (ch == 'E' || ch == 'e')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 27;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 20:
				if (ch == 'E' || ch == 'e')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 22;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 27:
				if (ch == 'P' || ch == 'p')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 22;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 14:
				if (ch == 'N' || ch == 'n')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 28;
					break;
				}

				if (ch == 'X' || ch == 'x')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 29;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 15:
				if (ch == 'F' || ch == 'f')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 22;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 28:
				if (ch == 'D' || ch == 'd')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 22;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 29:
				if (ch == 'I' || ch == 'i')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 30;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 30:
				if (ch == 'T' || ch == 't')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 22;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 16:
				if (ch >= '0' && ch <= '9')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 33;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 17:
				if (ch >= '0' && ch <= '9')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 31;
					break;
				}

				cout << "Error: Simbolo " << ch << " no definido" << endl;
				break;

			// **************************************************************
			case 33:
				if (ch >= '0' && ch <= '9')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 33;
					break;
				}

				estado = 34;
				break;

			// **************************************************************
			case 31:
				if (ch >= '0' && ch <= '9')
				{
					buffer[buffer_i++] = ch;
					contenido.erase(contenido.begin());
					estado = 31;
					break;
				}

				estado = 32;
				break;

			// **************************************************************
			case 32:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::IDENTIFICADOR_VARIABLE, buffer));
				estado = 0; buffer_i = 0;
				break;


			// **************************************************************
			case 34:
				buffer[buffer_i] = '\0';
				simbolos.push_back(Token(TipoToken::IDENTIFICADOR_LED, buffer));
				estado = 0; buffer_i = 0;
				break;
		}
	}

	return simbolos;
}
