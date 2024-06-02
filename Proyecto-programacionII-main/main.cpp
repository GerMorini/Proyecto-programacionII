#include <iostream>
#include <ctime>
#include <string>
#include <limits>
#include <unistd.h>
#include "clases.h"

using namespace std;

void esperar(float segundos) {
    sleep(segundos);
}

// TODO: preguntar si se puede usar cout acá
// TODO: hay que validar las entradas
int numero_validado(int min, int max){
    int x;
    cin >> x;

    while(cin.fail() || x < min || x > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Entrada invalida, ingrese un numero entre " << min << " - " << max << ": ";
        cin >> x;
    }
    return x;
}

Fecha fecha_validada() {
    int dia, mes, anio;

    while (true) {
        cout << "Día > ";
        dia = numero_validado(1, 31);

        cout << "Mes > ";
        mes = numero_validado(1, 12);

        cout << "Año > ";
        anio = numero_validado(1940, 2030);

        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                if (dia < 32 && dia > 0){return Fecha{dia, mes, anio};};
            case 4: case 6: case 9: case 11:
                if (dia < 31 && dia > 0){return Fecha{dia, mes, anio};};
            case 2:
                if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
                    if (dia < 30 && dia > 0){return Fecha{dia, mes, anio};};
                } else {if (dia < 29 && dia > 0){return Fecha{dia, mes, anio};}}
                cout<<"Dia invalido, inténtelo nuevamente\n";
        }
    }

    return Fecha{dia, mes, anio};
}

void registrarAutor(NEWS &news) {
    string nombre, medio;
    int dni;

    cout << "Ingrese el nombre del autor: ";
    cin.ignore();
    getline(cin, nombre);

    cout << "Ingrese el medio del autor: ";
    getline(cin, medio);

    cout << "Ingrese el DNI del autor: ";
    dni = numero_validado(1000000, 99999999);

    cout << "Registrando..." << endl;
    esperar(2);
    Autor autor(nombre, dni, medio);
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
    cin.ignore();
    getline(cin, nombre);

    cout << "Ingrese el DNI del usuario: ";
    dni = numero_validado(1000000, 99999999);

    cout << "Ingrese la edad del usuario: ";
    edad = numero_validado(1, 200);

    cout << "Registrando..." << endl;
    esperar(2);
    Usuario usuario(nombre, dni, edad);
    if (news.registrar_usuario(usuario)) {
        cout << "Usuario registrado con éxito.\n";
    } else {
        cout << "El usuario ya está registrado.\n";
    }
}

void cargarNoticia(NEWS &news) {
    string titulo, detalle;
    Fecha publicacion;

    cout << "Ingrese el título de la noticia: ";
    cin.ignore();
    getline(cin, titulo);

    cout << "Ingrese el detalle de la noticia: ";
    getline(cin, detalle);

    cout << "Fecha de publicación: " << endl;
    publicacion = fecha_validada();

    cout << "Registrando noticia..." << endl;
    esperar(2);
    if (news.publicar(titulo, detalle, publicacion)) {
        cout << "Noticia publicada con éxito." << endl;
    } else {
        cout << "La noticia ya está registrada.\n";
    }
}


void registrarComentario(NEWS &news) {
    cout << "Elegí la noticia a comentar: " << endl;
    int lengthArr = news.getNoticias().length();
    for (int i = 0; i < lengthArr; i++){
        cout << "[" << i+1 << "] " << news.getNoticias()[i].getTitulo() << endl;
    }
    int opt = numero_validado(1, lengthArr);

    string texto;
    cout << "Ingrese el texto del comentario: ";
    cin.ignore();
    getline(cin, texto);

    cout << "Publicando comentario..." << endl;
    esperar(2);
    news.comentar(opt-1, texto); // se comenta
    cout << "Comentario registrado con éxito " << endl;
}

void listarNoticiasPorAno(NEWS &news, int anio) {
    cout << "Noticias publicadas en el año " << anio << endl;
    for (int i = 0; i < news.getNoticias().length(); ++i) {
        if (news.getNoticias()[i].getPublicado().anio == anio) {
            cout << "[" << i+1 << "] " << news.getNoticias()[i].getTitulo() << "\n";
        }
    }
}

void listarNoticiasUltimoMes(NEWS &news) {
    // TODO: ¿que hay con esto? se re nota que se hizo con el Chat
    time_t t = time(nullptr);
    tm *current = localtime(&t);
    int currentMonth = current->tm_mon + 1;
    int currentYear = current->tm_year + 1900;

    cout << "Noticias publicadas el último mes:\n";
    for (int i = 0; i < news.getNoticias().length(); ++i) {
        Fecha fecha = news.getNoticias()[i].getPublicado();
        if (fecha.anio == currentYear && fecha.mes == currentMonth) {
            cout << "[" << i+1 << "] " << news.getNoticias()[i].getTitulo() << "\n";
        }
    }
}

void mostrarNoticiaConComentarios(NEWS &news, int noticiaId) {
    Noticia noticia = news.getNoticias()[noticiaId];
    cout << "Título: " << noticia.getTitulo() << "\n";
    cout << "Comentarios:\n";
    for (int i = 0; i < noticia.getCantidadComentarios() + 1; i++) {
        cout << noticia.getComentarios()[i].getTexto() << "\n";
    }
}

void listarArticulosPorAutor(NEWS &news, string autorNombre) {
    cout << "Artículos publicados escritos por " << autorNombre << ":\n";
    for (int i = 0; i < news.getNoticias().length(); ++i) {
        if (news.getNoticias()[i].getAutor().getNombre() == autorNombre) {
            cout << i+1 << ". " << news.getNoticias()[i].getTitulo() << "\n";
        }
    }
}

int main() {
    cout << "Descargando datos..." << endl;
    esperar(2);
    int option, dni;
    string nombre;
    NEWS news;
    bool loggeado = 0;

    while (!loggeado){
        cout << "Iniciar sesion: " << endl;
        cout << "[1] Usuario" << endl;
        cout << "[2] Autor" << endl;
        cout << "[3] Salir" << endl;
        option = numero_validado(1, 3);
        switch (option)
        {
        case 1:
            try {
                cout << "Ingrese el dni\n";
                dni = numero_validado(1000000, 99999999);

                news.login_user(dni);
                loggeado = 1;

            } catch(RecordNotFound& e) {
                cout << "Usuario no registrado\n";
            }
            break;
        case 2:
            try {
                cout << "Ingrese el dni\n";
                dni = numero_validado(1000000, 99999999);

                news.login_autor(dni);
                loggeado = 1;
            } catch(RecordNotFound& e) {
                cout << "Autor no registrado\n";
            }
            break;
        case 3:
            cout << "Saliendo...\n";
            return 0;
        default:
            cout << "Opción inválida\n";
        }
    }
    
    cout << "Cargando menu..." << endl;
    esperar(1);
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
        option = numero_validado(1, 9);

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
                cout << "Ingrese el año: ";
                int anio = numero_validado(1940, 2030);
                cout << "Buscando noticias..." << endl;
                esperar(2);
                listarNoticiasPorAno(news, anio);
                break;
            }
            case 6:
                cout << "Buscando noticias..." << endl;
                esperar(2);
                listarNoticiasUltimoMes(news);
                break;
            case 7: {
                cout << "Elegí la noticia a mostrar: " << endl;
                for (int i = 0; i < news.getNoticias().length(); i++){
                    cout << "[" << i+1 << "] " << news.getNoticias()[i].getTitulo() << endl;
                }
                int opt = numero_validado(1, news.getNoticias().length());

                cout << "Recopilando información..." << endl;
                esperar(2);
                mostrarNoticiaConComentarios(news, opt-1);
                break;
            }
            case 8: {
                string autorNombre;
                cout << "Ingrese el nombre del autor: ";
                cin.ignore();
                getline(cin, autorNombre);

                cout << "Buscando artículos..." << endl;
                esperar(2);
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
