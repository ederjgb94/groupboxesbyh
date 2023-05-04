#include <bits/stdc++.h>

#define CANTIDAD_ENCABEZADO 6

using namespace std;

struct Caja{
    int id = -1;
    int ancho = -1;
    int profundidad = -1;
    int alto = -1;
    int peso = -1;
    int volumen = -1;
    bool seleccionado = false;

    bool operator==(const Caja& other) const {
        return id == other.id;
    }
};


/**
 * Variables Globales
 */
int numero_de_encabezado;
int numero_de_cajas;
Caja *cajas;
const int mapa_size = 1000;
/*
 * Fin Globales
 */

void imprimir_cajas(){
    int j;
    for(int i = 0; i<numero_de_cajas; i++){
        cout<<cajas[i].id<<' ';
        cout<<cajas[i].ancho<<' ';
        cout<<cajas[i].profundidad<<' ';
        cout<<cajas[i].alto<<' ';
        cout<<cajas[i].peso<<' ';
        cout<<cajas[i].volumen<<'\n';
        cout<<cajas[i].seleccionado<<'\n';
    }
}
enum Tipos{

    ID = 0,
    ANCHO = 1,
    PROFUNDIDAD = 2,
    ALTO = 3,
    PESO = 4,
    VOLUMEN = 5,
    SELECCIONADO = 6,
};
void imprimir_caja(Caja c){
    cout<<"id:\t"<<c.id<<' ';
    cout<<"ancho:\t"<<c.ancho<<' ';
    cout<<"profundidad:\t"<<c.profundidad<<' ';
    cout<<"alto:\t"<<c.alto<<' ';
    cout<<"peso:\t"<<c.peso<<' ';
    cout<<"volumen:\t"<<c.volumen<<'\n';
}

void obtener_cajas(string nombreDeArchivo){

    ifstream cin(nombreDeArchivo+".csv");

    cin>>numero_de_encabezado;
    cin>>numero_de_cajas;

    cajas = new Caja[numero_de_cajas];//construir arreglo de cajas

    int aux;
    for (int i = 0; i < numero_de_cajas; ++i) {
        cajas[i] = Caja();
        cin>>aux; cajas[i].id = aux;
        cin>>aux; cajas[i].ancho = aux;
        cin>>aux; cajas[i].profundidad = aux;
        cin>>aux; cajas[i].alto = aux;
        cin>>aux; cajas[i].peso = aux;
        cin>>aux; cajas[i].volumen = aux;

    }
}

void escribir_resultados(){
    ofstream MyFile("salida.txt");
    MyFile<<"algo";
    MyFile.close();
}

bool por_volumen(Caja a, Caja b){
    return a.volumen>b.volumen;
}

bool por_size(vector<Caja> a, vector<Caja> b){
    return a.size()>b.size();
}

int main() {
    obtener_cajas("cajas1");
    sort(cajas, cajas+numero_de_cajas, por_volumen);
    //imprimir_cajas();

    array< vector< Caja >, mapa_size > mapa;


    for (int i = 0; i < numero_de_cajas; ++i) {
        //los IF fixean cajas que tienen lados duplicados
        //solo me importa 1 lado único
        mapa[cajas[i].ancho].push_back(cajas[i]);

        if(cajas[i].ancho!= cajas[i].alto)
        mapa[cajas[i].alto].push_back(cajas[i]);

        if(cajas[i].profundidad!= cajas[i].ancho &&
            cajas[i].profundidad!= cajas[i].alto)
        mapa[cajas[i].profundidad].push_back(cajas[i]);
    }

    array< vector< Caja >, mapa_size > cajas_sin_ordenar;
    copy(begin(mapa), end(mapa), begin(cajas_sin_ordenar));
    sort(mapa.begin(), mapa.end(), por_size);

    while(mapa[0].size()>0){
        cout<<"Size "<<mapa[0].size() << ":\n";
        for (int i = 0; i < mapa[0].size(); ++i) {
            imprimir_caja(mapa[0][i]);
            Caja aux = mapa[0][i];
            cajas_sin_ordenar[aux.ancho].erase(
                    remove(cajas_sin_ordenar[aux.ancho].begin(),
                             cajas_sin_ordenar[aux.ancho].end(),
                             aux),
                            cajas_sin_ordenar[aux.ancho].end()
                    );

            if(aux.alto!=aux.ancho)
            cajas_sin_ordenar[aux.alto].erase(
                    remove(cajas_sin_ordenar[aux.alto].begin(),
                           cajas_sin_ordenar[aux.alto].end(),
                           aux),
                    cajas_sin_ordenar[aux.alto].end()
            );

            if(aux.profundidad != aux.alto &&
            aux.profundidad != aux.ancho)
            cajas_sin_ordenar[aux.profundidad].erase(
                    remove(cajas_sin_ordenar[aux.profundidad].begin(),
                           cajas_sin_ordenar[aux.profundidad].end(),
                           aux),
                    cajas_sin_ordenar[aux.profundidad].end()
            );

        }
        //paso el array con los eliminados y ordeno de nuevo
        copy(begin(cajas_sin_ordenar), end(cajas_sin_ordenar), begin(mapa));
        sort(mapa.begin(), mapa.end(), por_size);

    }



    return 0;
}
