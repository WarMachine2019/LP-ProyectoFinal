
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
		}
	}

	return simbolos;
}
