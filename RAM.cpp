#include "RAM.h"

//========================================================================================
// DEVUELVE EL �NDICE DEL VECTOR CORRESPONDIENTE DE LA MATRIZ
//========================================================================================

index RAM::position(index i, index j)
{
	if ((i<0) || (i>get_m()) || (j<0) || (j>get_n()))	// Verificamos que est� dentro de los l�mites, para indexar en (1,1), i<1, j< 1, ....
	{
		cerr << "Error en los �ndices de la matriz." << endl;
		return 0;
	}

	return i*get_n() + j;			// (i - 1)*get_n() + (j - 1) si lo queremos indexar desde (1,1) en vez (0,0)
}

//========================================================================================
// DEVUELVE EL STRING PERO ELIMIN�NDOLE TODOS LOS ESPACIOS EN BLANCO
//========================================================================================

string RAM::Trim(string::const_iterator i, string::const_iterator f)
{
	string::const_iterator it;
	string buff;

	for (it = i; it != f; ++it)					// Recorre todo el string
		if (*it != ' ') buff += *it;			// S�lo almacena en buff un caracter que no sea espacio en blanco

	return buff;
}

//========================================================================================
// DEVUELVE EL STRING PERO ELIMIN�NDOLE LOS ESPACIOS DEL LADO IZQUIERDO
//========================================================================================

string RAM::LTrim(string::const_iterator i, string::const_iterator f)
{
	string::const_iterator it;
	string buff;

	while (*i == ' ') i++;						// Recorre los espacios en blanco hasta encontrar un caracter
	for (it = i; it != f; ++it) buff += *it;	// Almacena el resto del string

	return buff;
}

//========================================================================================
// DEVUELVE EL STRING QUE SE ENCUENTRA EN SEGUNDA POSICI�N
//========================================================================================

string RAM::TrimSecond(string::const_iterator i, string::const_iterator f)
{
	string::const_iterator it;
	string buff;

	while (*i == ' ') i++;				// Recorre los espacios en blanco hasta encontrar un caracter
	while (*i != ' ') i++;				// Recorre hasta que se encuentre el primer espacio
	while (*i == ' ') i++;				// Recorre los espacios en blanco hasta encontrar un caracter
	for (it = i; it != f; ++it)			// Recorre hasta el final
		if (*it != ' ') buff += *it;	// Si no tiene espacio en blanco lo almacena en buff

	return buff;
}

//========================================================================================
// DEVUELVE EL STRING QUE SE ENCUENTRA EN PRIMERA POSICI�N
//========================================================================================

string RAM::TrimFirst(string::const_iterator i, string::const_iterator f)
{
	string::const_iterator it;
	string buff;

	while (*i == ' ') i++;		// Recorre los espacios en blanco hasta encontrar un caracter
	while (*i != ' ') {			// Recorre hasta que se encuentre el primer espacio
		buff += *i;				// Almacena en buff la palabra encontrada
		i++;
	}

	return buff;
}

//========================================================================================
// DEVUELVE EL STRING CODIFICADO DEL OPCODE
//========================================================================================

string RAM::codOpcode(string str) {

	string out;								// Devuelve el string con su respectivo c�digo

	if (str == "LOAD") out = "1";
	else if (str == "STORE") out = "2";
	else if (str == "ADD") out = "3";
	else if (str == "SUB") out = "4";
	else if (str == "MULT") out = "5";
	else if (str == "DIV") out = "6";
	else if (str == "READ") out = "7";
	else if (str == "WRITE") out = "8";
	else if (str == "JUMP") out = "9";
	else if (str == "JGTZ") out = "10";
	else if (str == "JZERO") out = "11";
	else if (str == "HALT") out = "12";

	return out;
}

//========================================================================================
// DEVUELVE EL STRING DESCODIFICADO DEL OPCODE
//========================================================================================

string RAM::desOpcode(string str) {

	string out;								// Devuelve el string con su respectivo OPCODE

	if (str == "1") out = "LOAD";
	else if (str == "2") out = "STORE";
	else if (str == "3") out = "ADD";
	else if (str == "4") out = "SUB";
	else if (str == "5") out = "MULT";
	else if (str == "6") out = "DIV";
	else if (str == "7") out = "READ";
	else if (str == "8") out = "WRITE";
	else if (str == "9") out = "JUMP";
	else if (str == "10") out = "JGTZ";
	else if (str == "11") out = "JZERO";
	else if (str == "12") out = "HALT";

	return out;
}

//========================================================================================
// CONSTRUCTOR POR DEFECTO
// El n� de columnas ser� 2 � 3, 1� almacena comando, 2� operando o etiqueta, 3� comentario
//========================================================================================

RAM::RAM():
	m_(0),
	n_(2)
{
}

//========================================================================================
// CONSTRUCTOR QUE ESTABLECE EL N� DE FILAS Y COLUMNAS
//========================================================================================

RAM::RAM(index m, index n) :
m_(m),
n_(n)
{
}

//========================================================================================
// OBTENER LA DIMENSI�N DE LA FILA
//========================================================================================

vector<string> RAM::get_I()
{
	return I_;
}

//========================================================================================
// OBTENER LA DIMENSI�N DE LA FILA
//========================================================================================

index RAM::get_m()
{
	return m_;
}

//========================================================================================
// OBTENER LA DIMENSI�N DE LA COLUMNA
//========================================================================================

index RAM::get_n()
{
	return n_;
}

//========================================================================================
// OBTENER EL VALOR DE LA POSICI�N i,j DE LA MATRIZ
//========================================================================================

string RAM::get_item(index i, index j)
{
	return I_[position(i, j)];
}

//========================================================================================
// ESTABLECE LA DIMENSI�N DE LA FILA
//========================================================================================

void RAM::set_m(index m)
{
	m_ = m;
}

//========================================================================================
// ESTABLECE LA DIMENSI�N DE LA COLUMNA
//========================================================================================

void RAM::set_n(index n)
{
	n_ = n;
}

//========================================================================================
// ESTABLECER EL VALOR DE LA POSICI�N i,j DE LA MATRIZ
//========================================================================================

void RAM::set_item(index i, index j, string item)
{
	I_[position(i, j)] = item;
}

//========================================================================================
// LECTURA DEL FICHERO DE UNA MATRIZ CUADRADA
// ---------------------------------------------------------------------------------------
// Aunque lo dej� preparado para guardar los comentarios, en principio no se almacenan
// ya que no se ped�a. Cuando se profundice en la pr�ctica sabr� si lo necesitar� o no.
// Para ello, lo que tengo pensado es hacer un enum de entrada, y dependiendo la opci�n
// que soliciten (WITHTAG, WITHCOMMTAG, WITHOUT) se habilitar� una zona. Y con ello, la
// n ser� 2, 3 � 4 depediendo las columnas a guardar.
//========================================================================================

istream& RAM::readFile(istream& file)
{
	vector<string> vTag;
	I_.clear();
	set_n(2);									// En esta opci�n s�lo se almacena el opcode y su operando

	string line, tag, comm, instruc, oper;		// Cada l�nea, etiqueta, comentario, opcode, operando/etiqueta
	size_t indexC, indexT;						// �ndice de Comentario, Etiqueta y Et Fin
	int nLine = 1;								// N� de l�neas con c�digo sin comentario. �til para saber donde van las etiquetas

	while (getline(file, line)) {
		// ****** ETIQUETA
		indexT = line.find(":");				// �ndice que guarda el lugar donde termina la etiqueta
		if (indexT < 1000) {					// Si existe etiqueta (el �ndice no puede ser el npos).
			tag = line.substr(0, indexT);		// Substring que contiene desde el inicio hasta el :, almacena el nombre de la etiqueta
			tag = Trim(tag.begin(), tag.end());	// Eliminamos los espacios en blanco
			vTag.push_back(to_string(nLine));	// Se a�ade a un vector el n� de l�nea donde aparece
			vTag.push_back(tag);				// Se a�ade el nombre de la etiqueta
			indexT++;							// Se a�ade uno al �ndice de la etiqueta para no coger el caracter : en las instrucciones
		}
		else {
			indexT = 0;							// Sino se encuentra etiqueta coloco el �ndice en 0, para iniciar desde ah� la b�squeda de la instrucci�n
			tag = "";							// Si me hiciera almacenar m�s adelante el nombre de la etiqueta, saber que aqu� no ten�a
		}
		// ****** COMENTARIO
		indexC = line.find(";");				// Almacena el �ndice donde empieza el comentario
		if (indexC < 1000) {					// Si existe comentario su �ndice es distinto del npos (un n� muy grande)
			comm = line.substr(indexC + 1);		// Almacena el comentario, es un substring desde ; hasta el final (se le a�ade +1 para eliminar ;
		}
		else {
			indexC = line.size();				// Sino se encuentra comentario es hasta el final de la l�nea la instrucci�n
			comm = "";							// Sino existe comentario es ""
		}
		// ****** INSTRUCCIONES = OPCODE + OPERANDO/ETIQUETA/NADA
		if (indexT != indexC) {										// Cuando existe c�digo 
			instruc = line.substr(indexT, indexC - indexT);			// Substring que contiene la instrucci�n y el operando/tag juntos
			instruc.append(" ");									// A�ado un espacio al final para no exista fallo con el �ltimo comando
			instruc = TrimFirst(instruc.begin(), instruc.end());	// Captura la primera palabra
			instruc = codOpcode(instruc);							// Codifico el opcode
			if (instruc != "12") {									// 12 = HALT, entra salvo que sea 12, que no tiene ni tag ni operando
				oper = line.substr(indexT, indexC - indexT);		// Substring que contiene la instrucci�n y el operando/tag juntos
				//oper.append(" ");									
				oper = TrimSecond(oper.begin(), oper.end());		// Se toma la segunda palabra que corresponde con el operando/etiqueta
			}
			else
				oper = "";											// Halt no tiene nada
			I_.push_back(instruc);									// Se a�ade el opcode a la estructura
			I_.push_back(oper);										// Se a�ade el operando/etiqueta a la estructura
			nLine++;												// Se incrementa el n� de l�neas con c�digo, para identificar la etiqueta
		}
	}

	set_m(nLine - 1);												// Al querer s�lo contar las l�neas con c�digo, y estar el tag primero que instrucc
																	// se me hace necesario incrementarlo dentro de �ste, por lo que, al final me sobra uno

	for (int i = 0; i < vTag.size() / 2; i++) {						// Se recorre el vector que almacena las etiquetas y su posici�n
		for (int j = 0; j < get_m(); j++) {							// Se recorre el vector que almacena el opcode y su operando/etiqueta
			if (vTag[2 * i + 1] == get_item(j, 1))					// Si coincide el nombre de la etiqueta con el etiqueta del opcode
				set_item(j, 1, vTag[2 * i]);						// Se cambia por el n� de l�nea
		}
	}

	return file;
}

//========================================================================================
// IMPRIME LA ESTRUCTURA, QUE SE GUARDA CODIFICADA
//========================================================================================

void RAM::printCod() {
	cout << "\t OPCODE \t OPERANDO/ETIQUETA \n";
	cout << "       *******************************\n";
	for (int i = 0; i < get_m(); i++) 
		cout << "L" << i + 1 << "\t  " << get_item(i, 0) << "\t\t" << get_item(i, 1) << "\n";
}

//========================================================================================
// IMPRIME LA ESTRUCTURA, QUE SE GUARDA CODIFICADA
//========================================================================================

void RAM::printDesc() {
	cout << "\t OPCODE \t OPERANDO/ETIQUETA \n";
	cout << "       *******************************\n";
	for (int i = 0; i < get_m(); i++)
		if ((get_item(i, 0) == "9") || (get_item(i, 0) == "10") || (get_item(i, 0) == "11"))
			cout << "L" << i+1 << "\t  " <<  desOpcode(get_item(i, 0)) << "\t\t\tL" << get_item(i, 1) << "\n";
		else
			cout << "L" << i + 1 << "\t  " << desOpcode(get_item(i, 0)) << "\t\t\t" << get_item(i, 1) << "\n";
}

//========================================================================================
// DESTRUCTOR
//========================================================================================

RAM::~RAM()
{
	I_.clear();
}




