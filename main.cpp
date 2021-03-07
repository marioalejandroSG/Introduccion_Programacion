// Programa para paquetería que ordena paquetes según peso
// Y muestra el peso total y el monto total obtenido por el envío.
// Autor: Mario Sánchez Gamboa
// 7 Marzo, 2021

#include <iostream>
#include <locale.h>
#include <iomanip>
#include <cctype>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::string;
using std::stof;

// Prototipos
void imprimirBienvenida();
bool tieneLetra(char []);
void imprimirPesos(float [], int);
void ordenarPaquetes(float [], int);
void imprimirPesosOrdenados(float[], int );
void calcularTotales(float [], int);
void imprimirReporte(float [], int);

int main()
{
    // Permite tíldes en el programa
    setlocale(LC_ALL, "Spanish");

    // Capacidad máxima de paquetes
    const int MAX = 50;

    // Array que almacena los pesos de los paquetes
    float pesos[MAX];

    // Arrays tipo string para almacenar los datos de los paquetes ingresados
    string remitente[MAX];
    string receptorNombre[MAX];
    string receptorDireccion[MAX];
    string receptorTelefono[MAX];

    // Contadores
    int numPaquetes = 0;
    int i = 0;

    // Declaraciones
    char valor [10];
    char input;
    char respuesta;
    float peso;

    // Mostrar bienvenida del programa
    imprimirBienvenida();

    // Ingresa datos mientras el usuario digite 'S' ó alcance la capacidad máxima de paquetes (50)
    do
    {
        // Ingresando datos del cliente y almacenándolos
        cout << "\n1) Ingreso de datos del cliente\n" << endl;

        cout << "a) Introduzca el nombre de la persona que envía el paquete: ";
        getline(cin, remitente[i]);

        cout << "b) Introduzca el nombre del cliente: ";
        getline(cin, receptorNombre[i]);

        cout << "c) Introduzca la dirección del cliente: ";
        getline(cin, receptorDireccion[i]);

        cout << "d) Introduzca el número de teléfono del cliente: ";
        getline(cin, receptorTelefono[i]);

        // Ingresando el peso de cada paquete
        cout << "\n2) Ingreso del peso del paquete" << endl;

        // Verifica que ingresen pesos válidos (números positivos y menores ó iguales a 20)
        do
        {
            cout << "\n(El paquete no debe exceder los 20kg, ni incluir caracteres)" << endl;
            cout << "Introduzca el peso del paquete: ";
            cin >> valor;

            // Si el valor es válido (que no posea caracteres), entonces convertirlo de string a float
            if (!tieneLetra(valor))
                peso = stof(valor);
        }
        while ((peso <= 0 || peso > 20) || tieneLetra(valor));

        // Almacena el peso de cada paquete en el arreglo pesos
        pesos[i] = peso;

        // Aumentar contadores en 1
        numPaquetes++;
        i++;

        // Si capacidad de paquetes(50) es alcanzada, salirse del ciclo y no preguntar por más datos
        if (numPaquetes >= MAX)
            break;

        do
        {
            // Si aún hay capacidad para almacenar paquetes, preguntará si desea introducir más datos.
            cout << "\n¿Desea introducir más datos? (S/N): ";
            cin >> input;

            // Hace mayúscula al carácter
            respuesta = toupper(input);
        }
        while (respuesta != 'S' && respuesta != 'N');

        // Limpia la pantalla
        system("cls");

        // Limpia el buffer
        cin.ignore();
    }
    while (respuesta == 'S' && numPaquetes < MAX);

    system("cls");

    // Llama método que muestra el reporte final
    imprimirReporte(pesos, numPaquetes);

    return 0;

}


// Imprime la bienvenida al inicio del programa
void imprimirBienvenida()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 80; j++)
        {
            if (i == 1)
            {
                cout << endl << setw(55) <<"Bienvenidos a la Paquetería Don Pedro" << endl;
                break;
            }
            else
                cout << "*";
        }
        cout << endl;
    }
}

// Devuelve true si encuentra una letra en un array tipo char
bool tieneLetra(char s[])
{
    int n = strlen(s);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(s[i]))
            return true;
    }
    return false;
}


// Imprime el array del peso de los paquetes con su orden inicial
void imprimirPesos(float arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". " << arr[i];
        cout << endl;
    }
    cout << endl;
}


// Ordena array de mayor a menor mediante el método burbuja.
void ordenarPaquetes(float arr[], int n)
{
    int aux;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
}


// Calcula e imprime el peso total en kg y el monto total en colones.
void calcularTotales(float arr[], int n)
{
    float totalKg = 0;
    double totalColones = 0;

    // Recorre el array de pesos y va sumando precios de acuerdo a su peso
    for (int i = 0; i < n; i++)
    {
        if (arr[i] <= 5)
            totalColones += 500;
        else if (arr[i] <= 10)
            totalColones += 1000;
        else if (arr[i] <= 15)
            totalColones += 1500;
        else
            totalColones += 2000;

        totalKg += arr[i];
    }

    // Imprime los resultados
    cout << "El peso total de la carga transportada en kg es: " << totalKg << " kg\n"<< endl;
    cout << "El monto total por envío de paquetes es: " << totalColones <<  " colones\n"<<endl;
}


// Método que muestra los resultados finales en pantalla.
void imprimirReporte(float arr[], int n)
{
    string decoracion = "********************************************************************************";

    // Muestra decoración
    cout << decoracion << endl;
    cout << setw(45) << "Reporte Final\n" << endl;
    cout << decoracion << endl;

    // Muestra arreglo en su orden inicial y luego los ordena e imprime
    cout << "El orden inicial con que se ingresaron los paquetes es: " << endl;
    imprimirPesos(arr, n);

    cout << "Los paquetes ordenados de mayor a menor por peso:" << endl;
    ordenarPaquetes(arr, n);

    imprimirPesosOrdenados(arr, n);

    // Muestra totales obtenidos
    calcularTotales(arr, n);

    cout << decoracion << endl;
}

// Imprime pesos ordenados de mayor a menor
void imprimirPesosOrdenados(float arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] <<  " | ";
    }
    cout << endl << endl;
}
