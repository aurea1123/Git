/* 
 * File:   mycrypt.hpp
 * Author: iper
 *
 * Created on 17 de enero de 2018, 16:39
 */

#ifndef MYCRYPT_HPP
#define	MYCRYPT_HPP
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

/*
 * 
 */
class base{
public:
    int *d;
    base();
    string abc;
    int* tranformar(string);//tranforma un string en un int aunque esto se puede hacer con el operador de sbrecarga
    int* cifra(int *i, int c);//c es la contrasenya i esta i es la numeracion transformada anque en una version superior se puede hacer directo con el string
    int* descifra(int *i, int c);
    string string_to_int(int *i);
};
base::base(){
       abc = "abcdefghijklmnoupkqrstvwxyz";//esto se ha de assignar en el contructor
}
string base::string_to_int(int* i){
    string r;
    int q = 0;
    for(; *i != -1; q++){
        while(*i > 26){ *i = *i - 27;}
        while(*i < 0){ *i = *i + 27;}
        r = r + abc[*i];
        i++;
    }
    for(int w = 0; w < q; w++){
        i--;
    }
    return r;
}
int* base::tranformar(string a){ //Se le tiene que pasar un pasar un parametro que se llama final i es -1
    string c;
    string aux;
    //primero se tine que hacer 
    //esto es para hacer que funcione bien 
    int e = 0;
    bool boo;
    for(; boo == true;e++){
        c = a[e];
        aux = a[e + 1];
        d = new int;
        d++;
        if(aux == "1" && c == "-" ) boo = false;
        if(e > 200) break;
        //std::cout << "Abc" << c << "\n";
    }
    //std::cout << e << "\n";
    for(int q = 0; q < e; q++){
            d--;
            //std::cout << "Esto se repite....." << "\n";
    }
    //std::cout << "Esto se acaba\n";
    for(int i = 0; i < e; i++){
        c = a[i];
        //std::cout << "Cuantas veces se repite\n";
        for(int q = 0; q < 27; q++){
            aux = abc[q];
            if(c == aux){
                *d = q;
                //std::cout << "Resultado de tranformar: " << *d << "\n";
                d++;
            }
            if(c == aux) break;
            //std::cout << "Este es el bucle infito\n";
        }
    }
    *d = -1;//este es el numero que marca el final
    for(int i = 0; i < e; i++){
        d--;
        //i--;
    }
    return d;

}

int* base::cifra(int* i, int c){
    int e = 0;
    //delete d;
    for(; *i != -1;e++){
        i++;
    }
    for(int q = 0; q < e; q++){
        i--;
    }
    d = new int[e];
    for(int q = 0; q < e; q++){
        *d = *i + c;
        //std::cout << "Resultado:  " << *d << "\n"; 
        d++;
        i++;
    }
    *d = -1;
    for(int q = 0; q < e; q++){
        d--;
    }
    return d;
}
int* base::descifra(int* i, int c){
    int e = 0;
    //std::cout << "Descifrado el mensaje....\n";
    //delete d;
    for(; *i != -1;e++){
        i++;
    }
    for(int q = 0; q < e; q++){
        i--;
    }
    d = new int[e];
    for(int q = 0; q < e; q++){
        *d = *i - c;
        //std::cout << "Resultado:  " << *d << "\n"; 
        d++;
        i++;
    }
    *d = -1;
    for(int q = 0; q < e; q++){
        d--;
    }
    return d;
}
class crypto : private base{
public:
    crypto();
    string encrypt(string, int); //int es la contrasenya
    string decrypt(string, int);
    static int getHowCrypt(){ return Cc; }
private:
   static int Cc;
};
int crypto::Cc = 0;
crypto::crypto(){
        abc = "abcdefghijklmnoupkqrstvwxyz";
	Cc++;
}
string  crypto::encrypt(string a, int c){
    int *z;
    z = tranformar(a + "-1");
    z = cifra(z, c);
    return string_to_int(z);
}
string crypto::decrypt(string a, int c){
    int *z;
    z = tranformar(a + "-1");
    z++;
    z++;
    z = descifra(z , c);
    return string_to_int(z);
}
void pruevas(){
    base hola;
    string a = "quiero-1";
    int *b;
    int c = 99999999;
    b = hola.tranformar(a);
    //std::cout << "Estoy tonto\n";
    std::cout << "La b vale: " << *b << "\n";
    b = hola.cifra(b, c);
    std::cout << "La b vale: " << *b << "\n";
    std::cout << "El mensaje encriptado es: " << hola.string_to_int(b) << "\n";
    a = hola.string_to_int(b);
    a = a + "-1";
    std::cout << a << "\n";
    b = hola.tranformar(a);
    b++;
    std::cout << *b << "\n";
    b = hola.descifra(b, c);
    std::cout << "Que pasa aqui...";
    std::cout << "El mensaje descirtado es: " << hola.string_to_int(b) << "\n";
}
void pruevas_crypt(string a){
    crypto hola;
    a = hola.encrypt(a, 2);
    std::cout << "Encypt : "<< a << "\n";
    std::cout << "Descifra:  " << hola.decrypt(a, 2) << "\n";
    std::cout << "Que pasa joder\n";
}
void encrypt(string a, int q){
    crypto b;
    cout << b.encrypt(a, q) << "\n";
}
void decrypt(string a, int q){
    crypto b;
    cout << b.decrypt(a, q) << "\n";//de momento se usa 2 pero se ha de hacer 
}
void lim(){
    for(int i = 0; i < 10; i++){
        std::cout << "\n";
    }
}
void lim(int n){
    for(int i = 0; i < n; i++){
        std::cout << "\n";
    }
}
void salida(int a, string in, int c){
    std::cout << "Resultado  ";
        std::cout << "Se uso la funcion crypt  :  "<< crypto::getHowCrypt() << "\n";
    if(a == 1){
        std::cout << "Texto encritado: ";
        encrypt(in, c);
    }
    if(a == 2){
        std::cout << "Texto desencriptado:   ";
        decrypt(in,  c);
    }
    if(a > 2 && a < 0){
        std::cout << "Datos no validos\n";
    }
}


#endif	/* MYCRYPT_HPP */

