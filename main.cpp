#include <iostream>
#include <ctime>
#include "clases.h"

using namespace std;

void registrarAutor(NEWS &news) {
    string nombre, medio;
    int dni;
    cout << "Ingrese el nombre del autor: ";
    cin >> nombre;
    cout << "Ingrese el medio del autor: ";
    cin >> medio;
    cout << "Ingrese el DNI del autor: ";
    cin >> dni;

    Autor autor(medio, nombre, dni);
    if (news.registrar_autor(autor)) {
        cout << "Autor registrado con éxito.\n";
    } else {
        cout << "El autor ya está registrado.\n";
    }
}

void registrarUsuario(NEWS &news) {
    string nombre;
    int dni, edad;
    cout << "Ingrese el nombre del usuario: ";
    cin >> nombre;
    cout << "Ingrese el DNI del usuario: ";
    cin >> dni;
    cout << "Ingrese la edad del usuario: ";
    cin >> edad;

    Usuario usuario(nombre, dni, edad);
    if (news.registrar_usuario(usuario)) {
        cout << "Usuario registrado con éxito.\n";
    } else {
        cout << "El usuario ya está registrado.\n";
    }
}

void cargarNoticia(NEWS &news, Autor &autor) {
    string titulo, detalle, autorNombre;
    int dia, mes, anio, autorDni;

    cout << "Ingrese el título de la noticia: ";
    cin.ignore();
    getline(cin, titulo);
    cout << "Ingrese el detalle de la noticia: ";
    getline(cin, detalle);
    cout << "Ingrese el día de publicación: ";
    cin >> dia;
    cout << "Ingrese el mes de publicación: ";
    cin >> mes;
    cout << "Ingrese el año de publicación: ";
    cin >> anio;

    Fecha fecha = {dia, mes, anio};
    Noticia noticia(titulo, detalle, fecha, autor);
    if (news.publicar(noticia)) {
        cout << "Noticia publicada." << endl;
    } else {
        cout << "La noticia ya está registrada.\n";
    }
}

void registrarComentario(NEWS &news, Usuario &user, int n) {
    cout << "Elegí la noticia a comentar: " << endl;
    for (int i = 0; i < news.getNoticias().length(); i++){
        cout << "[" << i+1 << "] " << news.getNoticias()[i].get() << endl;
    }
    int op;
    cin >> op;

    int comentarioNum = news.getNoticias()[op].getCantidadComentarios()+1;
    string texto;
    cout << "Ingrese el texto del comentario: ";
    cin.ignore();
    getline(cin, texto);

    Comentario comentario(comentarioNum, texto, user);
    news.getNoticias()[op].comentar(comentario); // se comenta
    cout << "Comentario registrado con éxito " << endl;
}

void listarNoticiasPorAno(NEWS &news, int anio) {
    cout << "Noticias publicadas en el año " << anio << endl;
    for (int i = 0; i < news.getNoticias().size(); ++i) {
        if (news.getNoticias()[i].getFecha().anio == anio) {
            cout << news.getNoticias()[i].get() << "\n";
        }
    }
}

void listarNoticiasUltimoMes(NEWS &news) {
    time_t t = time(nullptr);
    tm *current = localtime(&t);
    int currentMonth = current->tm_mon + 1;
    int currentYear = current->tm_year + 1900;

    cout << "Noticias publicadas el último mes:\n";
    for (int i = 0; i < news.getNoticias().size(); ++i) {
        Fecha fecha = news.getNoticias()[i].getFecha();
        if (fecha.anio == currentYear && fecha.mes == currentMonth) {
            cout << news.getNoticias()[i].get() << "\n";
        }
    }
}

void mostrarNoticiaConComentarios(NEWS &news, int noticiaId) {
    Noticia noticia = news.getNoticias()[noticiaId];
    cout << "Título: " << noticia.get() << "\n";
    cout << "Comentarios:\n";
    for (int i = 0; i < noticia.getComentarios().size(); ++i) {
        cout << noticia.getComentarios()[i].getTexto() << "\n";
    }
}

void listarArticulosPorAutor(NEWS &news, string autorNombre) {
    cout << "Artículos publicados por " << autorNombre << ":\n";
    for (int i = 0; i < news.getNoticias().size(); ++i) {
        if (news.getNoticias()[i].getAutor().get() == autorNombre) {
            cout << news.getNoticias()[i].get() << "\n";
        }
    }
}

int main() {
    NEWS news;
    int option;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Registro de Autores\n";
        cout << "2. Registro de Usuarios\n";
        cout << "3. Carga de Noticias\n";
        cout << "4. Registro de Comentarios\n";
        cout << "5. Listar Noticias por Año\n";
        cout << "6. Listar Noticias del Último Mes\n";
        cout << "7. Mostrar Noticia y Comentarios\n";
        cout << "8. Listar Artículos por Autor\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> option;

        switch (option) {
            case 1:
                registrarAutor(news);
                break;
            case 2:
                registrarUsuario(news);
                break;
            case 3:
                cargarNoticia(news);
                break;
            case 4:
                
                registrarComentario(news);
                break;
            case 5: {
                int anio;
                cout << "Ingrese el año: ";
                cin >> anio;
                listarNoticiasPorAno(news, anio);
                break;
            }
            case 6:
                listarNoticiasUltimoMes(news);
                break;
            case 7: {
                int noticiaId;
                cout << "Ingrese el ID de la noticia: ";
                cin >> noticiaId;
                mostrarNoticiaConComentarios(news, noticiaId);
                break;
            }
            case 8: {
                string autorNombre;
                cout << "Ingrese el nombre del autor: ";
                cin.ignore();
                getline(cin, autorNombre);
                listarArticulosPorAutor(news, autorNombre);
                break;
            }
            case 9:
                cout << "Saliendo...\n";
                return 0;
            default:
                cout << "Opción no válida.\n";
        }
    }

    return 0;
}
