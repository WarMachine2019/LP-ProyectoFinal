
#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

/**
**	Abre un archivo y carga su contenido en un arreglo dinámico (vector).
**
**	@param src Ruta al archivo que se desea cargar.
**
**	@return Arreglo dinámico (vector) con los bytes leídos del archivo. Si el archivo no existe se retorna arreglo con tamaño cero (0).
*/

vector<char>& leerDatos (const char *src)
{
	std::fstream input;
	vector<char> *output = new vector<char> ();

	input.open (src, std::fstream::in);
	if (!input) return *output;

	while (true)
	{
		char ch = input.get();
		if (input.eof()) break;

		output->push_back(ch);
	}

	input.close();
	return *output;
}


/**
**	Función principal.
**
**	Vamos a probar que la función leerDatos() funciona correctamente.
*/

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Utilizar:" << std::endl;
		cout << "    main.exe <archivo>" << std::endl;
		return 1;
	}

	vector<char>& contenido = leerDatos(argv[1]);
	if (!contenido.size())
	{
		cout << "ERROR: El archivo no existe, o no tiene contenido." << endl;
		return 1;
	}

	cout << "**** Datos de archivo: ****" << endl << endl;

	while (contenido.size() > 0)
	{
		int valor = contenido.front();
		cout << valor << " ";

		contenido.erase(contenido.begin());
	}

	cout << endl;

	return 0;
}
