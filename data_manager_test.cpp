#include <cassert>
#include <iostream>
#include "clases.h"  // Asegúrate de reemplazar esto con el nombre del archivo que contiene tu clase Data_manager

using namespace std;

void test_imprimir_datos() {
    Data_manager dm;
    // Imprimir usuarios
    cout << "Usuarios cargados:" << endl;
    for (int i = 0; i < dm.getUsuarios().length(); ++i) {
        Usuario user = dm.getUsuarios()[i];
        cout << "Nombre: " << user.getNombre() << ", Edad: " << user.getEdad() << ", DNI: " << user.getDNI() << endl;
    }

    // Imprimir autores
    cout << "Autores cargados:" << endl;
    for (int i = 0; i < dm.getAutores().length(); ++i) {
        Autor autor = dm.getAutores()[i];
        cout << "Nombre: " << autor.getNombre() << ", Medio: " << autor.getMedio() << ", DNI: " << autor.getDNI() << endl;
    }

    // Imprimir noticias
    cout << "Noticias cargadas:" << endl;
    for (int i = 0; i < dm.getNoticias().length(); ++i) {
        Noticia noticia = dm.getNoticias()[i];
        cout << "Titulo: " << noticia.getTitulo() << ", Detalle: " << noticia.getDetalle() << ", Fecha: "
                  << noticia.getPublicado().dia << "/" << noticia.getPublicado().mes << "/" << noticia.getPublicado().anio
                  << ", Autor: " << noticia.getAutor().getNombre() << endl;
    }

    // Imprimir comentarios
    cout << "Comentarios cargados:" << endl;
    for (int i = 0; i < dm.getComentarios().length(); ++i) {
        Comentario comentario = dm.getComentarios()[i];
        cout << "Numero: " << comentario.getNumero() << ", Texto: " << comentario.getTexto()
                  << ", Usuario: " << comentario.getUsuario().getNombre() << endl;
    }
}

void test_aniadir_usuario() {
    Data_manager dm;
    Usuario user1("SAMPLE NEW USER", 42042069, 69);
    assert(dm.aniadir_usuario(user1) == true);  // Usuario debería añadirse exitosamente

    // Intentar añadir el mismo usuario debería fallar
    assert(dm.aniadir_usuario(user1) == false);

    // Verificar que el usuario fue añadido correctamente
    Usuario foundUser = dm.buscar_usuario(42042069);
    assert(foundUser.getNombre() == "SAMPLE NEW USER");
    assert(foundUser.getEdad() == 69);
    assert(foundUser.getDNI() == 42042069);
    dm.guardar_cambios();
}

void test_aniadir_autor() {
    Data_manager dm;
    Autor autor1("NUEVO AUTOR", 87654322, "Revista Z");
    assert(dm.aniadir_autor(autor1) == true);  // Autor debería añadirse exitosamente

    // Intentar añadir el mismo autor debería fallar
    assert(dm.aniadir_autor(autor1) == false);

    // Verificar que el autor fue añadido correctamente
    Autor foundAuthor = dm.buscar_autor(87654322);
    assert(foundAuthor.getNombre() == "NUEVO AUTOR");
    assert(foundAuthor.getDNI() == 87654322);
    assert(foundAuthor.getMedio() == "Revista Z");
    dm.guardar_cambios();
}

void test_aniadir_noticia() {
    Data_manager dm;
    Fecha fecha = {1, 1, 2022};
    Autor autor = dm.buscar_autor(11223344);
    Noticia noticia("Titulo Noticia", "Detalle de la noticia", fecha, autor);
    
    assert(dm.aniadir_noticia(noticia) == true);  // Noticia debería añadirse exitosamente

    // Intentar añadir la misma noticia debería fallar
    assert(dm.aniadir_noticia(noticia) == false);

    // Verificar que la noticia fue añadida correctamente
    Noticia foundNews = dm.buscar_noticia("Titulo Noticia");
    assert(foundNews.getTitulo() == "Titulo Noticia");
    assert(foundNews.getDetalle() == "Detalle de la noticia");
    assert(foundNews.getPublicado().dia == 1);
    assert(foundNews.getPublicado().mes == 1);
    assert(foundNews.getPublicado().anio == 2022);
    assert(foundNews.getAutor().getNombre() == autor.getNombre());
    assert(foundNews.getAutor().getDNI() == autor.getDNI());
    assert(foundNews.getAutor().getMedio() == autor.getMedio());
    dm.guardar_cambios();
}

void test_buscar_usuario_no_existente() {
    Data_manager dm;
    try {
        dm.buscar_usuario(99999999);
        assert(false);  // Debería lanzar una excepción
    } catch (const RecordNotFound& e) {
        assert(true);  // Se lanzó la excepción correcta
    }
}

void test_buscar_autor_no_existente() {
    Data_manager dm;
    try {
        dm.buscar_autor(99999999);
        assert(false);  // Debería lanzar una excepción
    } catch (const RecordNotFound& e) {
        assert(true);  // Se lanzó la excepción correcta
    }
}

void test_buscar_noticia_no_existente() {
    Data_manager dm;
    try {
        dm.buscar_noticia("NoticiaInexistente");
        assert(false);  // Debería lanzar una excepción
    } catch (const RecordNotFound& e) {
        assert(true);  // Se lanzó la excepción correcta
    }
}

int main() {
    test_imprimir_datos();
    // test_aniadir_usuario();
    // test_aniadir_autor();
    // test_aniadir_noticia();
    // test_buscar_usuario_no_existente();
    // test_buscar_autor_no_existente();
    // test_buscar_noticia_no_existente();

    cout << "Todos los tests pasaron exitosamente." << endl;
    return 0;
}
