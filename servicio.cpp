#include "clases.h"

NEWS::NEWS() {
    dm = Data_manager();
}

Arreglo<Noticia> NEWS::getNoticias() {return dm.getNoticias();}
Arreglo<Autor> NEWS::getAutores() {return dm.getAutores();}

bool NEWS::publicar(string titulo, string detalle, Fecha publicacion) {
    return dm.aniadir_noticia(Noticia(titulo, detalle, publicacion, loginAuth));
}

bool NEWS::registrar_usuario(Usuario user) {
    return dm.aniadir_usuario(user);
}

bool NEWS::registrar_autor(Autor aut) {
    return dm.aniadir_autor(aut);
}

bool NEWS::comentar(int n, string txt) {
    return dm.getNoticias()[n-1]->comentar(Comentario(n, txt, loginUser));
} // FIXME: los autores no comentan... UWU tit detalle publicacion

void NEWS::login_user(int dni) {
    loginUser = dm.buscar_usuario(dni);
}

void NEWS::login_autor(int dni) {
    loginAuth = dm.buscar_autor(dni);
}


NEWS::~NEWS() {
    dm.guardar_cambios();
}
