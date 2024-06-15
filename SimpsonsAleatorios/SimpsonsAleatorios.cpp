#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include <windows.h>

struct Consulta
{
    std::string temporada_unica;
    std::string temporada_inicio;
    std::string temporada_final;
    bool halloween;
    std::string recomendaciones;
};

Consulta reestablecer_consulta();
int menu_principal(Consulta *consulta_actual_f);
int menu_halloween(Consulta *consulta_actual_f);
int menu_recomendaciones(Consulta *consulta_actual_f);
std::string obtener_recomendaciones();
int menu_consulta(Consulta* consulta_actual_f);
std::string seleccionar_temporada();
std::string seleccionar_rango(int opcion);
void evaluar_rango(Consulta* consulta_actual_f);
void consulta_temporada(Consulta* consulta_actual_f);
void consulta_rango(Consulta* consulta_actual_f);
void consulta_aleatoria(Consulta* consulta_actual_f);
std::string agregar_parametros_consulta(std::string consulta_SQL_construccion, Consulta* consulta_actual_f);
std::string dar_formato_numero(std::string numero);
std::string agregar_num_recomendaciones(std::string num_recomendaciones);
std::string evaluar_halloween(std::string consulta_f, bool es_halloween);
static int selectData(const char* s, std::string consulta_SQL_f, Consulta *consulta_actual_f);
static int callback(void* consulta_vacia_f, int argc, char** argv, char** azColName);
int menu_reinicio(std::string consulta_SQL_f, Consulta* consulta_actual_f);

const char* dir = "DB\\simpsons.db";

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int opcion_main;
    Consulta consulta_actual;

    consulta_actual = reestablecer_consulta();

    do
    {
      opcion_main = menu_principal(&consulta_actual);
    } while (opcion_main != 4);

    return 0;
}

Consulta reestablecer_consulta()
{
    Consulta consulta_nueva;

    consulta_nueva.halloween = false;
    consulta_nueva.recomendaciones = "1";
    consulta_nueva.temporada_unica = "todos";
    consulta_nueva.temporada_inicio = "todos";
    consulta_nueva.temporada_final = "todos";

    return consulta_nueva;
}

int menu_principal(Consulta *consulta_actual_f)
{
    int opcion_menu_principal = 0;
    int opcion_menu_consulta = 0;
    int opcion_menu_halloween = 0;
    int opcion_menu_recomendaciones = 0;

    std::cout << "\nSeleccione una opcion\n";
    std::cout << "\n1. Realizar consulta\n";
    std::cout << "\n2. Solo mostrar episodios de halloween\n";
    std::cout << "\n3. Seleccionar numero de recomendaciones\n";
    std::cout << "\n4. Salir del programa\n";
    std::cout << "\nIngrese su opcion: ";

    std::cin >> opcion_menu_principal;

    switch (opcion_menu_principal)
    {
        case 1:
            do
            {
                system("CLS");
                opcion_menu_consulta = menu_consulta(consulta_actual_f);
            } while (opcion_menu_consulta > 3 || opcion_menu_consulta < 1);
            break;
        case 2:
            do
            {
                system("CLS");
                opcion_menu_halloween = menu_halloween(consulta_actual_f);
            } while (opcion_menu_halloween != 3);
            break;
        case 3:
            do
            {
                system("CLS");
                opcion_menu_recomendaciones = menu_recomendaciones(consulta_actual_f);
            } while (opcion_menu_recomendaciones != 2);
            break;
        case 4:
            break;
        default:
            std::cout << "\nIngrese una opcion valida\n\n";
            system("pause");
            system("CLS");
            break;
    }

    return opcion_menu_principal;
}

int menu_halloween(Consulta *consulta_actual_f)
{
    int opcion_menu_halloween = 0;

    std::cout << "\nSeleccione una opcion\n";
    std::cout << "\n1. Mostrar solo episodios de halloween\n";
    std::cout << "\n2. Mostrar todo tipo de episodios\n";
    std::cout << "\n3. Volver al menu principal\n";
    std::cout << "\nIngrese una opcion: ";

    std::cin >> opcion_menu_halloween;

    switch (opcion_menu_halloween)
    {
        case 1:
            consulta_actual_f->halloween = true;
            break;
        case 2:
            consulta_actual_f->halloween = false;
            break;
        case 3:
            system("CLS");
            break;
        default:
            std::cout << "\nIngrese una opcion valida\n\n";
            system("pause");
            system("CLS");
            break;
    }

    return opcion_menu_halloween;
}

int menu_recomendaciones(Consulta* consulta_actual_f)
{
    int opcion_menu_recomendaciones = 0;

    std::cout << "\nSeleccione una opcion\n";
    std::cout << "\n1. Ingresar numero de recomendaciones\n";
    std::cout << "\n2. Volver al menu principal\n";
    std::cout << "\nIngrese su opcion: ";

    std::cin >> opcion_menu_recomendaciones;

    switch (opcion_menu_recomendaciones)
    {
        case 1:
            system("CLS");
            consulta_actual_f->recomendaciones = obtener_recomendaciones();
            break;
        case 2:
            break;
        default:
            std::cout << "\nIngrese una opcion valida\n\n";
            system("pause");
            break;
    }

    system("CLS");

    return opcion_menu_recomendaciones;
}

std::string obtener_recomendaciones()
{
    int numero_recomendaciones;
    std::string cadena_recomendaciones;

    do
    {
        std::cout << "\nIngrese numero de recomendaciones (1-10): ";
        std::cin >> numero_recomendaciones;
    } while (numero_recomendaciones > 10 || numero_recomendaciones < 1);

    cadena_recomendaciones = std::to_string(numero_recomendaciones);

    return cadena_recomendaciones;
}

int menu_consulta(Consulta *consulta_actual_f)
{
    int opcion_menu_consulta;

    std::cout << "\nSelecciona una opcion\n";
    std::cout << "\n1. Consulta por temporada\n";
    std::cout << "\n2. Consulta por rango\n";
    std::cout << "\n3. Consulta completamente aleatoria\n";
    std::cout << "\nIngrese su opcion: ";

    std::cin >> opcion_menu_consulta;

    switch (opcion_menu_consulta)
    {
        case 1:
            consulta_actual_f->temporada_unica = seleccionar_temporada();
            system("CLS");
            consulta_temporada(consulta_actual_f);
            break;
        case 2:
            consulta_actual_f->temporada_inicio = seleccionar_rango(1);
            consulta_actual_f->temporada_final = seleccionar_rango(2);
            evaluar_rango(consulta_actual_f);
            system("CLS");
            consulta_rango(consulta_actual_f);
            break;
        case 3:
            system("CLS");
            consulta_aleatoria(consulta_actual_f);
            break;
        default:
            std::cout << "\nIngrese una opcion valida\n\n";
            system("pause");
            system("CLS");
            break;
    }

    return opcion_menu_consulta;
}

std::string seleccionar_temporada()
{
    int num_temporada;
    std::string num_temporada_string;

    do
    {
        std::cout << "\nIngrese numero de temporada: ";
        std::cin >> num_temporada;
    } while (num_temporada > 34 || num_temporada < 1);

    num_temporada_string = std::to_string(num_temporada);

    return num_temporada_string;
}

std::string seleccionar_rango(int opcion)
{
    int num_temporada_rango;
    std::string num_temporada_rango_string;

    do
    {
        switch (opcion)
        {
        case 1:
            std::cout << "\nIngrese numero de temporada inicial: ";
            break;
        case 2:
            std::cout << "\nIngrese numero de temporada final: ";
            break;
        }

        std::cin >> num_temporada_rango;

    } while (num_temporada_rango > 34 || num_temporada_rango < 1);

    num_temporada_rango_string = std::to_string(num_temporada_rango);

    return num_temporada_rango_string;
}

void evaluar_rango(Consulta* consulta_actual_f)
{
    int num_temporada_inicial = 0;
    int num_temporada_final = 0;

    num_temporada_inicial = std::stoi(consulta_actual_f->temporada_inicio);
    num_temporada_final = std::stoi(consulta_actual_f->temporada_final);

    if (num_temporada_inicial > num_temporada_final)
    {
        std::string aux = consulta_actual_f->temporada_final;
        consulta_actual_f->temporada_final = consulta_actual_f->temporada_inicio;
        consulta_actual_f->temporada_inicio = aux;
    }
}

void consulta_temporada(Consulta* consulta_actual_f)
{
    std::string consulta_SQL = "select titulo, sinopsis, temporada_id_temporada as Temporada from capitulos where temporada_id_temporada = ";

    std::string aux;
    
    aux = dar_formato_numero(consulta_actual_f->temporada_unica);

    consulta_SQL.append(aux);

    consulta_SQL = agregar_parametros_consulta(consulta_SQL, consulta_actual_f);

    selectData(dir, consulta_SQL, consulta_actual_f);
}

void consulta_rango(Consulta* consulta_actual_f)
{
    std::string consulta_SQL = "select titulo, sinopsis, temporada_id_temporada as Temporada from capitulos where temporada_id_temporada between ";

    std::string aux;

    aux = dar_formato_numero(consulta_actual_f->temporada_inicio);

    consulta_SQL.append(aux);

    consulta_SQL.append(" and ");

    aux = dar_formato_numero(consulta_actual_f->temporada_final);

    consulta_SQL.append(aux);

    consulta_SQL = agregar_parametros_consulta(consulta_SQL, consulta_actual_f);

    selectData(dir, consulta_SQL, consulta_actual_f);
}

void consulta_aleatoria(Consulta *consulta_actual_f)
{
    std::string consulta_SQL = "select titulo, sinopsis, temporada_id_temporada as Temporada from capitulos ";

    consulta_SQL = agregar_parametros_consulta(consulta_SQL, consulta_actual_f);

    selectData(dir, consulta_SQL, consulta_actual_f);
}

std::string agregar_parametros_consulta(std::string consulta_SQL_construccion, Consulta *consulta_actual_f)
{
    std::string aux;

    aux = evaluar_halloween(consulta_SQL_construccion, consulta_actual_f->halloween);

    consulta_SQL_construccion.append(aux);

    consulta_SQL_construccion.append(" order by random() ");

    aux = agregar_num_recomendaciones(consulta_actual_f->recomendaciones);

    consulta_SQL_construccion.append(aux);

    return consulta_SQL_construccion;
}

std::string dar_formato_numero(std::string numero)
{
    std::string numero_formateado = "'";

    numero_formateado.append(numero);

    numero_formateado.append("'");

    return numero_formateado;
}

std::string evaluar_halloween(std::string consulta_f, bool es_halloween)
{
    std::string condicion;
    std::string aux;

    if (consulta_f.find("where") != std::string::npos) {
        condicion = " and ";
    }

    else
    {
        condicion = " where ";
    }

    if (es_halloween == true)
    {
        aux.append(condicion);
        aux.append("halloween == '1'");
    }

    return aux;
}

std::string agregar_num_recomendaciones(std::string num_recomendaciones)
{
    std::string aux = " limit ";

    aux.append(num_recomendaciones);

    return aux;
}

static int selectData(const char* s, std::string consulta_SQL_f, Consulta *consulta_actual_f)
{
    bool consulta_vacia = true;
    int opcion_reinicio = 0;

    sqlite3* DB;

    int exit = sqlite3_open(s, &DB);

    sqlite3_exec(DB, consulta_SQL_f.c_str(), callback, &consulta_vacia, NULL);

    if (consulta_vacia)
    {
        std::cout << "\nERROR: No existen capitulos para esa consulta, por favor intente con nuevos parametros\n";
    }

    do
    {
        opcion_reinicio = menu_reinicio(consulta_SQL_f, consulta_actual_f);
    } while (opcion_reinicio < 1 || opcion_reinicio > 3);

    return 0;
}

static int callback(void* consulta_vacia_f, int argc, char** argv, char** azColName)
{
    std::cout << std::endl;

    for (int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << ": " << argv[i] << std::endl << std::endl;
    }

    *(bool*)consulta_vacia_f = false;

    return 0;
}

int menu_reinicio(std::string consulta_SQL_f, Consulta* consulta_actual_f)
{
    int opcion = 0;

    std::cout << "\nSeleccione una opcion\n";
    std::cout << "\n1. Reinicio rapido\n";
    std::cout << "\n2. Reinicio completo\n";
    std::cout << "\n3. Volver al menu principal\n";
    std::cout << "\nIngrese su opcion: ";

    std::cin >> opcion;

    switch (opcion)
    {
    case 1:
        system("CLS");
        selectData(dir, consulta_SQL_f, consulta_actual_f);
        break;
    case 2:
        *consulta_actual_f = reestablecer_consulta();
        system("CLS");
        break;
    case 3:
        system("CLS");
        break;
    default:
        std::cout << "\nERROR: Ingrese una opcion valida\n\n";
        system("pause");
        system("CLS");
        break;
    }

    return opcion;
}