
#include"clases.h"

void Data_manager::cargar_usuarios() {
    ifstream file(USERS_PATH);
    if(!file) throw FileOpenException(USERS_PATH);

    string nombre;
    int dni, edad;

    while(!file.eof()) {
        file >> edad;
        file >> dni;
        file.ignore();
        getline(file, nombre);

        usuarios + Usuario(nombre, dni, edad);
    }
    file.close();
}

void Data_manager::cargar_autores() {
    ifstream file(AUTHORS_PATH);
    if(!file) throw FileOpenException(AUTHORS_PATH);

    string nombre, medio;
    int dni;

    while(!file.eof()) {
        file >> dni;
        file.ignore();
        getline(file, nombre);
        getline(file, medio);

        autores + Autor(nombre, dni, medio);
    }
    file.close();
}

void Data_manager::cargar_comentarios() {
    ifstream file(COMMENTS_PATH);
    if(!file) throw FileOpenException(COMMENTS_PATH);

    string texto;
    int numero, dni_usuario;
    
    while(!file.eof()) {
        file >> numero;
        file >> dni_usuario;
        file.ignore();
        getline(file, texto);

        comentarios + Comentario(numero, texto, buscar_usuario(dni_usuario));
    }
    file.close();
}

void Data_manager::cargar_noticias() {
    ifstream file(NEWS_PATH);
    if(!file) throw FileOpenException(NEWS_PATH);

    string titulo, detalle;
    Fecha publicacion;
    int dni_autor, numero;

    while(!file.eof()) {
        file >> publicacion.dia;
        file >> publicacion.mes;
        file >> publicacion.anio;
        file >> dni_autor;
        file >> numero;
        file.ignore();
        getline(file, titulo);
        getline(file, detalle);

        noticias + Noticia(titulo, detalle, publicacion, buscar_autor(dni_autor), buscar_comentarios(numero));
    }
    file.close();
}

void Data_manager::guardar_usuarios() {
    ofstream file(USERS_PATH);
    if(!file.is_open()) throw FileOpenException(USERS_PATH);

    for (int i = 0; i < usuarios.length(); i++) {
        file << usuarios[i]->getEdad() << " "
        << usuarios[i]->getDNI() << " "
        << usuarios[i]->getNombre() << endl;
    }

    file.close();
}

void Data_manager::guardar_autores() {
    ofstream file(AUTHORS_PATH);
    if(!file.is_open()) throw FileOpenException(AUTHORS_PATH);

    for (int i = 0; i < autores.length(); i++) {
        file << autores[i]->getDNI() << endl
        << autores[i]->getNombre() << endl
        << autores[i]->getMedio() << endl;
    }

    file.close();
}

void Data_manager::guardar_comentarios() {
    ofstream file(COMMENTS_PATH);
    if(!file.is_open()) throw FileOpenException(COMMENTS_PATH);

    for (int i = 0; i < noticias.length(); i++) {
        Arreglo<Comentario> comms = noticias[i]->getComentarios();

        for (int j = 0; j < comms.length(); j++) {
            file << comms[j]->getNumero() << " "
            << comms[j]->getUsuario().getDNI() << " "
            << comms[j]->getTexto() << endl;
        }
    }

    file.close();
}

void Data_manager::guardar_noticias() {
    ofstream file(NEWS_PATH);
    if(!file.is_open()) throw FileOpenException(NEWS_PATH);

    for (int i = 0; i < noticias.length(); i++) {
        file << noticias[i]->getPublicado().dia << " "
        << noticias[i]->getPublicado().mes << " "
        << noticias[i]->getPublicado().anio << " "
        << noticias[i]->getAutor().getDNI() << " "
        << i+1 << endl
        << noticias[i]->getTitulo() << endl
        << noticias[i]->getDetalle() << endl;
    }

    file.close();
}
public:
Data_manager() {
    cargar_usuarios();
    cargar_autores();
    cargar_comentarios();
    cargar_noticias();
}

Arreglo<Comentario> Data_manager::buscar_comentarios(int numero) {
    Arreglo<Comentario> resultados;

    for (int i = 0; i < comentarios.length(); i++) {
        if(comentarios[i]->getNumero() == numero) {
            resultados + *comentarios[i];
        }
    }

    return resultados;
}

Usuario Data_manager::buscar_usuario(int dni) {
    for (int i = 0; i < usuarios.length(); i++) {
        if(usuarios[i]->getDNI() == dni) return *usuarios[i];
    }

    throw RecordNotFound(to_string(dni));
}

Autor Data_manager::buscar_autor(int dni) {
    for (int i = 0; i < autores.length(); i++) {
        if(autores[i]->getDNI() == dni) return *autores[i];
    }

    throw RecordNotFound(to_string(dni));
}

Noticia Data_manager::buscar_noticia(string titulo) {
    for (int i = 0; i < noticias.length(); i++) {
        if(noticias[i]->getTitulo() == titulo) return *noticias[i];
    }

    throw RecordNotFound(titulo);
}

bool Data_manager::aniadir_noticia(Noticia n) {
    return noticias + n;
}

bool Data_manager::aniadir_usuario(Usuario u) {
    return usuarios + u;
}

bool Data_manager::aniadir_autor(Autor a) {
    return autores + a;
}

Arreglo<Usuario> Data_manager::getUsuarios() {return usuarios;}
Arreglo<Autor> Data_manager::getAutores() {return autores;}
Arreglo<Comentario> Data_manager::getComentarios() {return comentarios;}
Arreglo<Noticia> Data_manager::getNoticias() {return noticias;}

void Data_manager::guardar_cambios() {
    guardar_usuarios();
    guardar_autores();
    guardar_comentarios();
    guardar_noticias();
}
