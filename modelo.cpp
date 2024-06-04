#include"clases.h"

// PERSONA

string Persona::getNombre() {
    return nombre;
}

int Persona::getDNI(){
    return dni;
}

bool Persona::operator==(Persona& p) {
    return dni == p.dni;
}

//Autor

string Autor::getMedio() {return medio;}

//Usuario

int Usuario::getEdad() {return edad;}

//Comentario

int Comentario::getNumero() {return numero;}
string Comentario::getTexto() {return texto;}
Usuario Comentario::getUsuario() {return usuario;}

bool Comentario::operator==(Comentario& com) {
    return texto == com.texto;
}

//Noticia

string Noticia::getTitulo() {return titulo;}
string Noticia::getDetalle() {return detalle;}
Fecha Noticia::getPublicado() {return publicado;}
Autor Noticia::getAutor() {return autor;}
Arreglo<Comentario> Noticia::getComentarios() {return comentarios;}

void Noticia::setFecha(Fecha a){publicado = a;}
void Noticia::comentar(Comentario com) {comentarios + com;}
int Noticia::getCantidadComentarios() {return comentarios.length();}

bool Noticia::operator==(Noticia& n) {
    return titulo == n.titulo;
}

