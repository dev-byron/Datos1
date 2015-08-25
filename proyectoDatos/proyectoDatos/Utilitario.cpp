#include "Utilitario.h"


char * Utilitario::toChar(System::String ^ variable){
	char * charReturn = (char*)(void*)Marshal::StringToHGlobalAnsi(variable);
	return charReturn;
}

int Utilitario::toInt(System::Int32 ^ variable){
	int intReturn = (int)variable;
	return intReturn;
}

System::String ^ Utilitario::toSystemString(char * variable){
	System::String ^ retorno = gcnew System::String(variable);
	return retorno;
}

System::Int32 ^ Utilitario::toInt32(int numero){
	System::Int32  valor = numero;
	return valor;
}

char * Utilitario::intToChar(int numero){
	System::String^	var = System::Convert::ToString(numero);
	return toChar(var);
}

double Utilitario::toDouble(System::String ^ variable)
{
	double foo = System::Convert::ToDouble(variable);

	return foo;
}


