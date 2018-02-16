/*
 * encrypt.cpp
 *
 * Copyright (c) 2014, Danilo Treffiletti <urban82@gmail.com>
 * All rights reserved.
 *
 *     This file is part of Aes256.
 *
 *     Aes256 is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU Lesser General Public License as
 *     published by the Free Software Foundation, either version 2.1
 *     of the License, or (at your option) any later version.
 *
 *     Aes256 is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *     GNU Lesser General Public License for more details.
 *
 *     You should have received a copy of the GNU Lesser General Public
 *     License along with Aes256.
 *     If not, see <http://www.gnu.org/licenses/>.
 */
//a ver lo que hare es un menu i abajo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "aes.hpp"
#include "mycrypt.hpp"
#include <string>
#define BUFFER_SIZE 1024*1024

#ifdef __APPLE__
#  define fseeko64 fseeko
#endif
//este es el menu que puedo hacer
class supercrypt : public crypto{
    public:
    int fichero_e(char* a, char* n, char* c);//este es para encryptoar los archivos
    int fichero_d(char* a, char* n, char* c);
};
int supercrypt::fichero_d(char* a, char* n, char* c){
        //a = key n = input c = ouput
    std::cout << "descifrando fichero.... \n";
    ByteArray key, dec;
    size_t file_len;

    FILE *input, *output;

    srand(time(0));
    size_t key_len = 0;
    while(a[key_len] != 0)
        key.push_back(a[key_len++]);

    input = fopen(n, "rb");
    if (input == 0) {
        fprintf(stderr, "Cannot read file '%s'\n", n);
        return 1;
    }

    output = fopen(c, "wb");
    if (output == 0) {
        fprintf(stderr, "Cannot write file '%s'\n", c);
        return 1;
    }

    Aes256 aes(key);

    fseeko64(input, 0, SEEK_END);
    file_len = ftell(input);
    fseeko64(input, 0, SEEK_SET);
    printf("File is %zd bytes\n", file_len);

    aes.decrypt_start(file_len);

    while (!feof(input)) {
        unsigned char buffer[BUFFER_SIZE];
        size_t buffer_len;

        buffer_len = fread(buffer, 1, BUFFER_SIZE, input);
        printf("Read %zd bytes\n", buffer_len); //lo que no es como cambiar esto vale pos ya esta
        printf("La salida es de %s\n", dec.data());
        if (buffer_len > 0) {
            dec.clear();
            aes.decrypt_continue(buffer, buffer_len, dec);
            fwrite(dec.data(), dec.size(), 1, output);
        }
    }

    dec.clear();
    aes.decrypt_end(dec);
    fwrite(dec.data(), dec.size(), 1, output);

    fclose(input);
    fclose(output);

    return 0;

}
int supercrypt::fichero_e(char* a, char* n, char* c){
    //a = key n = input c = ouput
    std::cout << "cifrado fichero.... \n";
    ByteArray key, enc;
    size_t file_len;
//std::cout << "A ver que da si un int o que ? " << size_t file_len << "\n";
    //lo que no debuelve nada
//El tipo entero sin signo que es el resultado del operador sizeof.
    FILE *input, *output;
//Este guarda los nombres de los ficheros .....
    srand(time(0));
//Este es una semilla de random()
    char *z;
    size_t key_len = 0;
    while(a[key_len] != 0){
        key.push_back(a[key_len++]);//esta es la key del fichero
    }

    input = fopen(n, "rb");//este es el fichero de entrada
    if (input == 0) {
        fprintf(stderr, "Cannot read file '%s'\n", n);
        return 0;
    }

    output = fopen(c, "wb");//esta es el fichero de salida
    if (output == 0) {
        fprintf(stderr, "Cannot write file '%s'\n", c);
        return 0;
    }

    Aes256 aes(key);

    fseeko64(input, 0, SEEK_END);
    file_len = ftell(input);
    fseeko64(input, 0, SEEK_SET);
    printf("File is %zd bytes\n", file_len);

    enc.clear();
    aes.encrypt_start(file_len, enc);
    fwrite(enc.data(), enc.size(), 1, output);

    while (!feof(input)) {//lo que hace es: 
    //La función feof retorna un valor distinto a cero si y sólo si el indicador de final de fichero está activado para stream

        unsigned char buffer[BUFFER_SIZE];
        size_t buffer_len;

        buffer_len = fread(buffer, 1, BUFFER_SIZE, input);
        printf("Read %zd bytes\n", buffer_len);
        printf("La salida es de %s\n", enc.data());
        if (buffer_len > 0) {
            enc.clear();
            aes.encrypt_continue(buffer, buffer_len, enc);
            fwrite(enc.data(), enc.size(), 1, output);
        }
    }

    enc.clear();
    aes.encrypt_end(enc);
    fwrite(enc.data(), enc.size(), 1, output);

    fclose(input);
    fclose(output);
}
void menu(){
    std::cout << "Este es el menu para hacer Puedes eleiguir entre diferentes encryptados\n";
    string aux = "1";
    supercrypt Ocry;
    while(aux != "0"){
        std::cout << "Dime que quieres hacer(0 para salir) \n1)encryptar un string(debil) \n2)encriptar un archivo(fuerte) \n3)desencriptar un  string(debil) \n4)desencriptar un fichero(fuerte)\n";
        std::cin >> aux;
        if(aux == "1"){
            int aux2;
            //este es para hacer que se ecrypte un string
            std::cout << "Dime el string a encryptar\n";
            std::cin >> aux;
            std::cout << "Dime la contrasenya(tinen que ser un int)\n";
            std::cin >> aux2;
            std::cout << "Resultado:  " << Ocry.encrypt(aux, aux2) << "\n";
        }
        if(aux == "2"){
            //este es para encryptar un fichero
            char *a, *b, *c;
            a = new char;
            b = new char;
            c = new char;
            std::cout << "Dime el fichero para encryptar\n";
            std::cin >> b;
            std::cout << "Dime la contrasenya:  ";
            std::cin >> a;
            std::cout << "Dime la direccion de la salida\n";
            std::cin >> c;
            Ocry.fichero_e(a, b, c);
            delete a, b, c;
        }
        if(aux == "3"){
            //este es para que descrypte un string
            int aux2;
            std::cout << "Dime el string a descryptar\n";
            std::cin >> aux;
            std::cout << "Dime la contrasenya(tiene que ser un int)\n";
            std::cin >> aux2;
            std::cout << "resultado: " << Ocry.decrypt(aux, aux2) << "\n";
        }
        if(aux == "4"){
            //este es para que encrypte un fichero
            char *a, *b, *c;
            a = new char;
            b = new char;
            c = new char;
            std::cout << "Dime el fichero para encryptar\n";
            std::cin >> b;
            std::cout << "Dime la contrasenya:  ";
            std::cin >> a;
            std::cout << "Dime la direccion de la salida\n";
            std::cin >> c;
            Ocry.fichero_d(a, b, c);
            delete a, b, c;
        }
        if(aux != "1" && aux != "2" && aux != "3" && aux != "4" && aux != "0"){
             std::cout << "Dato incorrecto\n";
        }
    }
}
void linea_comandos(int argc, char **argv){
    //creo que lo que hace es encryptar los archivos
    ByteArray key, enc;
    size_t file_len;
//std::cout << "A ver que da si un int o que ? " << size_t file_len << "\n";
    //lo que no debuelve nada
//El tipo entero sin signo que es el resultado del operador sizeof.
    FILE *input, *output;
//Este guarda los nombres de los ficheros .....
    srand(time(0));
//Este es una semilla de random()
    if (argc != 4) {
        fprintf(stderr, "Missing argument\n");
        fprintf(stderr, "Usage: %s <key> <input file> <output file>\n", argv[0]);
    }
    char *z;
    size_t key_len = 0;
    while(argv[1][key_len] != 0)
        key.push_back(argv[1][key_len++]);//esta es la key del fichero

    input = fopen(argv[2], "rb");//este es el fichero de entrada
    if (input == 0) {
        fprintf(stderr, "Cannot read file '%s'\n", argv[2]);
    }

    output = fopen(argv[3], "wb");//esta es el fichero de salida
    if (output == 0) {
        fprintf(stderr, "Cannot write file '%s'\n", argv[3]);
    }

    Aes256 aes(key);

    fseeko64(input, 0, SEEK_END);
    file_len = ftell(input);
    fseeko64(input, 0, SEEK_SET);
    printf("File is %zd bytes\n", file_len);

    enc.clear();
    aes.encrypt_start(file_len, enc);
    fwrite(enc.data(), enc.size(), 1, output);

    while (!feof(input)) {//lo que hace es: 
    //La función feof retorna un valor distinto a cero si y sólo si el indicador de final de fichero está activado para stream

        unsigned char buffer[BUFFER_SIZE];
        size_t buffer_len;

        buffer_len = fread(buffer, 1, BUFFER_SIZE, input);
        printf("Read %zd bytes\n", buffer_len);
        printf("La salida es de %s\n", enc.data());
        if (buffer_len > 0) {
            enc.clear();
            aes.encrypt_continue(buffer, buffer_len, enc);
            fwrite(enc.data(), enc.size(), 1, output);
        }
    }

    enc.clear();
    aes.encrypt_end(enc);
    fwrite(enc.data(), enc.size(), 1, output);

    fclose(input);
    fclose(output);
}
int main(int argc, char **argv)
{
    if(argv[1] == "-h"){
        std::cout << "Esta es la seccion de help\n";
         fprintf(stderr, "Usage: %s <key> <input file> <output file>\n", argv[0]);
    }else{
    if(argc > 2){
        linea_comandos(argc, argv);
    }else{
        std::cout << "menu\n";
        menu();
    }
    }
    return 0;
}
