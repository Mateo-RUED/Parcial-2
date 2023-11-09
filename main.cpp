#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "HashMap/HashMap.h"
#include "HashMap/HashMapList.h"
#include "HashMap/HashEntry.h"
#include "Lista/Lista.h"

using namespace std;

#include <iostream>

using namespace std;

class Producto{

    public:

    string grupo;
    string codigoDeBarras;
    string articulo;
    Lista<int> depositos;
    unsigned int stock;

    friend ostream &operator<<(ostream &os, const Producto &prod) {

        os<<"Articulo" <<prod.articulo<<" Stock: " << prod.stock;

        return os;
    }
};

void total_art_dif(Lista<Producto> lista_inv);

void total_art(Lista<Producto> lista_inv);

void min_stock_n(int n, Producto arr_men_may[]);

void min_stock_n_depo(int n, int depo, Producto arr_may_men[]);

void stock_art(Lista<string> nombre_articulo, HashMapList<string, Producto> Hash_inv);

void stock_art_depo(Lista<string> nombre_articulo, int depo, HashMapList<string, Producto> Hash_inv);

void max_Stock(int n, Producto arr_may_men[]);

void acciones (const string &command, Lista<string> &args, Lista<Producto> lista_inv, Producto arr_men_may[], Producto arr_may_men[], HashMapList<string, Producto> Hash_inv);



void shellSort(Producto arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Producto temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].stock > temp.stock; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void shellSortReverse(Producto arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Producto temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].stock < temp.stock; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


std::string unirPalabrasConEspacios(Lista<std::string> &listaPalabras) {
    std::string resultado;
    Nodo<std::string> *actual = listaPalabras.getInicio();

    while (actual != nullptr) {
        resultado += actual->getDato() + " ";
        actual = actual->getSiguiente();
    }

    if (!resultado.empty()) {
        resultado.pop_back();
    }

    return resultado;
}


// Función de dispersión personalizada
unsigned int customHash(string key) {

    unsigned int hash = 5381, resp;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c; 
    }

    resp=hash % 1000;

    return resp;

}



int main(int argc, char* argv[]) {

    Lista<Producto> Lista_inv;

    HashMapList<string,Producto> Tabla_inv(1000, &customHash);

    Lista<string> arguments;

    for (int i = 2; i < argc; ++i) {
        arguments.insertarUltimo(argv[i]);
    }

    fstream archivo;

    int canti_columnas=0;

    archivo.open(arguments.getDato(arguments.getTamanio()-1), ios::in);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo CSV." << endl;
        return 404;
    }

    string linea_1, campos;

    getline(archivo,linea_1);

    stringstream tt(linea_1);

    while (getline(tt, campos, ','))
    {
        canti_columnas ++;
    }

    string linea, grupo_aux;

    while(getline(archivo,linea)){

        stringstream ss(linea);
        int stock=0;
        Lista<int> depo;
        string campo;
        Lista<string> columnas;

        while (getline(ss, campo, ',')) {
            columnas.insertarUltimo(campo);
        }
            Producto producto;

            if(columnas.getTamanio() != canti_columnas){

                columnas.insertarUltimo("0");

            }

            if(!(columnas.getDato(0)).empty()){
            producto.grupo=columnas.getDato(0);
            grupo_aux=producto.grupo;
            }

            else{
                producto.grupo=grupo_aux;
            }

            producto.codigoDeBarras=columnas.getDato(1);
            producto.articulo=columnas.getDato(2);

            int depos;

            for(int i=3; i<columnas.getTamanio(); i++){

                if(columnas.getDato(i).empty()){

                   columnas.reemplazar(i, "0");

                }

                istringstream(columnas.getDato(i))>>depos;
                depo.insertarUltimo(depos);

            }


            for (int i = 0; i < depo.getTamanio(); i++)
            {
                stock=stock+depo.getDato(i);
            }

            producto.depositos=depo;

            producto.stock=stock;

         
            Tabla_inv.put(producto.articulo,producto);
       

            Lista_inv.insertarUltimo(producto);

         }

        Producto ArrMenMayStock [Lista_inv.getTamanio()];
        Producto ArrMayMenStock [Lista_inv.getTamanio()];

        for(int i=0; i<Lista_inv.getTamanio(); i++){

            ArrMenMayStock[i]=Lista_inv.getDato(i);
            ArrMayMenStock[i]=Lista_inv.getDato(i);

        }

        shellSort(ArrMenMayStock, Lista_inv.getTamanio());

        shellSortReverse(ArrMayMenStock, Lista_inv.getTamanio());

     if (argc < 2) {
    cerr << "Debe proporcionar al menos un comando." << endl;
    return 1;
    }

    
    Lista<string> argumentos;

    for (int i = 0; i < arguments.getTamanio()-1; i++)
    {
        
        argumentos.insertarUltimo(arguments.getDato(i));

    }

    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();

    acciones(argv[1], argumentos, Lista_inv, ArrMenMayStock, ArrMayMenStock, Tabla_inv);

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs " << elapsed_secs << " \n" << std::endl;

    return 0;
}


void acciones (const string &command, Lista<string> &args, Lista<Producto> lista_inv, Producto arr_men_may[], Producto arr_may_men[], HashMapList<string, Producto> Hash_inv){

    Lista<string> parsedArgs;

    int c=0;

    for (int i=0; i<args.getTamanio(); i++){

        string palabra =args.getDato(i);

        if(palabra.find(',')!= std::string::npos){

            c=1;

        }

    }
    
    for (int i = 0; i < args.getTamanio(); ++i) {
    std::stringstream ss(args.getDato(i));
    std::string item;
    while (std::getline(ss, item, ',')) {
        parsedArgs.insertarUltimo(item);

    }
    }


    if (command == "-total_art_dif") {
        total_art_dif(lista_inv);
    } else if (command == "-total_art") {
        total_art(lista_inv);
    } else if (command == "-min_stock") {


        if (parsedArgs.getTamanio() == 1) {
            int n = stoi(parsedArgs.getDato(0));
            min_stock_n(n, arr_men_may);
        } else if (parsedArgs.getTamanio() == 2) {
            int n = stoi(parsedArgs.getDato(0));
            int deposito = stoi(parsedArgs.getDato(1));
            min_stock_n_depo(n, deposito, arr_may_men);
        } else {
            cerr << "Argumentos incorrectos para min_stock." << endl;
        }
    } else if (command == "-stock") {

        if (c !=1 ) {
            stock_art(args, Hash_inv);
        } else if (c == 1) {
            int deposito = stoi(parsedArgs.getDato( parsedArgs.getTamanio() - 1));
            stock_art_depo(args, deposito, Hash_inv);
        } else {
            cerr << "Argumentos incorrectos para stock." << endl;
        }
    } else if (command == "-max_Stock") {
        if (parsedArgs.getTamanio() == 1) {
            int n = stoi(parsedArgs.getDato(0));
            max_Stock(n, arr_may_men);
        } else {
            cerr << "Argumentos incorrectos para max_Stock." << endl;
        }
    } else {
        cerr << "Comando no reconocido." << endl;
    }
}


void total_art_dif(Lista<Producto> lista_inv) {
    cout<<"La cantidad de articulos diferentes es igual a :"<< lista_inv.getTamanio();
}

void total_art(Lista<Producto> lista_inv) {

    int total_art=0;

    for(int i=0; i<lista_inv.getTamanio(); i++){

        total_art=total_art+lista_inv.getDato(i).stock;

    }

    cout << "La cantidad de articulos es igual a :"<<total_art<< endl;
}

void min_stock_n(int n, Producto arr_men_may[]) {

    cout<<"A continuacion se mostrara un Listado con los articulos que tienen una cantidad "<< n <<" o menor de stock :"<<endl;
    cout<<endl;

    int i=0;

    while(arr_men_may[i].stock <= n){

        cout<<"grupo : "<<arr_men_may[i].grupo<<endl;
        cout<<"nombre : "<<arr_men_may[i].articulo<<endl;
        cout<<"codigo de barras : "<<arr_men_may[i].codigoDeBarras<<endl;

        for (int c = 0; c < arr_men_may[i].depositos.getTamanio(); c++)
        {

            cout<<"deposito "<< c+1 <<" :"<< arr_men_may[i].depositos.getDato(c)<<endl;

        }

        cout<<"stock : "<<arr_men_may[i].stock<<endl;

        cout<<endl;

        i++;
    }

}

void min_stock_n_depo(int n, int depo, Producto arr_may_men[]) {

    cout<<"A continuacion se mostrara un Listado con los articulos que tienen una cantidad "<< n <<" o menor de stock, el deposito "<< depo << ":"<<endl;
    cout<<endl;

    int i=0;

    while(arr_may_men[i].stock >= n){

        if(arr_may_men[i].depositos.getDato(depo-1)<=n){

        cout<<"grupo : "<<arr_may_men[i].grupo<<endl;
        cout<<"nombre : "<<arr_may_men[i].articulo<<endl;
        cout<<"codigo de barras : "<<arr_may_men[i].codigoDeBarras<<endl;

        for (int c = 0; c < arr_may_men[i].depositos.getTamanio(); c++)
        {

            cout<<"deposito "<< c+1 <<" :"<< arr_may_men[i].depositos.getDato(c)<<endl;

        }

        cout<<"stock : "<<arr_may_men[i].stock<<endl;

        cout<<endl;

        }

        i++;
    }
    

}

void stock_art(Lista<string> nombre_articulo, HashMapList<string, Producto> Hash_inv) {

    string nombre_art;

    nombre_art=unirPalabrasConEspacios(nombre_articulo);
    
    Lista<Producto> Lista = Hash_inv.getLista(nombre_art);

    cout<<"La cantidad de stock que tiene el producto "<< nombre_art <<" es igual a : ";

    for(int i=0; i<Lista.getTamanio(); i++){

        if(Lista.getDato(i).articulo == nombre_art){

            cout << Lista.getDato(i).stock;

        }

    }

}

void stock_art_depo(Lista<string> nombre_articulo, int depo, HashMapList<string, Producto> Hash_inv) {

string nombre_art;

string nombre_aux=unirPalabrasConEspacios(nombre_articulo);

size_t pos = nombre_aux.find(',');

    if (pos != std::string::npos) {
        
        nombre_art = nombre_aux.substr(0, pos);
        
    }

Lista<Producto> Lista = Hash_inv.getLista(nombre_art);

cout<<"La cantidad de stock que tiene el producto "<< nombre_art<<", en el deposito "<< depo <<" es igual a : ";

for(int i=0; i<Lista.getTamanio(); i++){

    if(Lista.getDato(i).articulo == nombre_art){

        cout << Lista.getDato(i).depositos.getDato(depo-1);

    }

}

}


void max_Stock(int n, Producto arr_may_men[]) {
    cout<<"A continuacion se mostrara un Listado con los articulos que tienen una cantidad "<< n <<" o mayor de stock :"<<endl;
    cout<<endl;

    int i=0;

    while(arr_may_men[i].stock >= n){

        cout<<"grupo : "<<arr_may_men[i].grupo<<endl;
        cout<<"nombre : "<<arr_may_men[i].articulo<<endl;
        cout<<"codigo de barras : "<<arr_may_men[i].codigoDeBarras<<endl;

        for (int c = 0; c < arr_may_men[i].depositos.getTamanio(); c++)
        {

            cout<<"deposito "<< c+1 <<" :"<< arr_may_men[i].depositos.getDato(c)<<endl;

        }

        cout<<"stock : "<<arr_may_men[i].stock<<endl;

        cout<<endl;

        i++;
    }
}
