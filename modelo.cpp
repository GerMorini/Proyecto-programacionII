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

// AUTOR

string Autor::getMedio() {return medio;}

// USUARIO

int Usuario::getEdad() {return edad;}

// COMENTARIO

int Comentario::getNumero() {return numero;}
string Comentario::getTexto() {return texto;}
Usuario Comentario::getUsuario() {return usuario;}

bool Comentario::operator==(Comentario& com) {
    return numero == com.numero and texto == com.texto and usuario.getDNI() == com.usuario.getDNI();
}

// NOTICIA

Noticia::Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor) {
    titulo = _titulo;
    detalle = _detalle;
    publicado = _publicacion;
    autor = _autor;
    comentarios = Arreglo<Comentario>(); // TODO: ¿se puede instanciar así?
};

Noticia::Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor, Arreglo<Comentario> _comentarios) {
    titulo = _titulo;
    detalle = _detalle;
    publicado = _publicacion;
    autor = _autor;
    comentarios = _comentarios;
};

string Noticia::getTitulo() {return titulo;}
string Noticia::getDetalle() {return detalle;}
Fecha Noticia::getPublicado() {return publicado;}
Autor Noticia::getAutor() {return autor;}
Arreglo<Comentario> Noticia::getComentarios() {return comentarios;}

void Noticia::setFecha(Fecha a){publicado = a;}
bool Noticia::comentar(Comentario com) {return comentarios + com;}
int Noticia::getCantidadComentarios() {return comentarios.length();}

bool Noticia::operator==(Noticia& n) {
    return titulo == n.titulo;
}

