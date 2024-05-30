#include <iostream>
#include <cassert>
#include <string>
#include "clases.h"

using namespace std;

void testPersona() {
    Persona p1("John Doe", 123456);
    assert(p1.get() == "John Doe");
    assert(p1.getDNI() == 123456);
    cout << "Persona tests passed!" << endl;
}

void testAutor() {
    Autor a1("Newspaper", "Jane Doe", 654321);
    assert(a1.get() == "Jane Doe");
    assert(a1.getDNI() == 654321);
    cout << "Autor tests passed!" << endl;
}

void testUsuario() {
    Usuario u1("Alice", 111222, 30);
    assert(u1.get() == "Alice");
    assert(u1.getDNI() == 111222);
    cout << "Usuario tests passed!" << endl;
}

void testComentario() {
    Usuario u1("Bob", 333444, 25);
    Comentario c1(1, "MALISIMO EL ARTICULO !", u1);
    // No hay métodos públicos para probar directamente, 
    // pero se puede ampliar el código para acceder a ellos
    cout << "Comentario tests passed!" << endl;
}

void testNoticia() {
    Fecha f = {1, 1, 2021};
    Autor a1("Website", "Charlie", 555666);
    Noticia n1("Title", "Details", f, a1);

    Usuario u1("David", 777888, 40);
    Comentario c1(1, "Una poronga lo que publicaste 8==>", u1);
    n1.comentar(c1);

    assert(n1.get() == "Title");
    cout << "Noticia tests passed!" << endl;
}

void testNEWS() {
    Fecha f = {2, 2, 2022};
    Autor a1("TV", "Eve", 999000);
    Usuario u1("Frank", 111000, 35);
    Noticia n1("TITULO 1", "More Details", f, a1);
    
    NEWS news;
    assert(news.registrar_autor(a1) == true);
    assert(news.registrar_autor(a1) == false); // Autor ya registrado

    assert(news.registrar_usuario(u1) == true);
    assert(news.registrar_usuario(u1) == false); // Usuario ya registrado

    assert(news.publicar(n1) == true);
    assert(news.publicar(n1) == false); // Noticia ya publicada

    cout << "NEWS tests passed!" << endl;
}

void testArreglo() {
    Arreglo<int> arr;
    arr + 1;
    arr + 2;
    arr + 3;

    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);

    cout << "Arreglo tests passed!" << endl;
}

int main() {
    testPersona();
    testAutor();
    testUsuario();
    testComentario();
    testNoticia();
    testNEWS();
    testArreglo();

    cout << "All tests passed!" << endl;
    return 0;
}
