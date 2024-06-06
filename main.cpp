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

int numero_validado(int min, int max){
    int x;
    cin >> x;

    while(cin.fail() || x < min || x > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "❌ Entrada invalida, ingrese un numero entre " << min << " - " << max << ": ";
        cin >> x;
    }
    return x;
}

Fecha fecha_validada() {
    int dia, mes, anio;

    while (true) {
        cout << "\tDía > ";
        dia = numero_validado(1, 31);

        cout << "\tMes > ";
        mes = numero_validado(1, 12);

        cout << "\tAño > ";
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
                cout<<"❌ Fecha invalida, inténtelo nuevamente\n";
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
        cout << "✅ Autor registrado con éxito\n";
    } else {
        cout << "❌ El autor ya está registrado\n";
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
        cout << "✅ Usuario registrado con éxito\n";
    } else {
        cout << "❌ El usuario ya está registrado\n";
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
        cout << "✅ Noticia publicada con éxito" << endl;
    } else {
        cout << "⚠️ La noticia ya está registrada\n";
    }
}


void registrarComentario(NEWS &news) {
    cout << "Elegí la noticia a comentar: " << endl;
    int lengthArr = news.getNoticias().length();
    for (int i = 0; i < lengthArr; i++){
        cout << "\t[" << i+1 << "] " << news.getNoticias()[i]->getTitulo() << endl;
    }
    int opt = numero_validado(1, lengthArr);

    string texto;
    cout << "Ingrese el texto del comentario: ";
    cin.ignore();
    getline(cin, texto);

    cout << "Publicando comentario..." << endl;
    esperar(2);
    if(news.comentar(opt, texto)) {
        cout << "✅ Comentario registrado con éxito" << endl;
    } else {
        cout << "⚠️ No está permitido hacer spam" << endl;
    }
}

void listarNoticiasPorAno(NEWS &news, int anio) {
    cout << "Noticias publicadas en el año " << anio << ":" << endl;
    for (int i = 0; i < news.getNoticias().length(); ++i) {
        if (news.getNoticias()[i]->getPublicado().anio == anio) {
            cout << "\t" << i+1 << ") " << news.getNoticias()[i]->getTitulo() << " ("
            << news.getNoticias()[i]->getAutor().getNombre() << ")" << "\n";
        }
    }
}

void listarNoticiasUltimoMes(NEWS &news) {
    time_t t = time(nullptr);
    tm *ahora = localtime(&t);
    int esteMes = ahora->tm_mon + 1;
    int esteAnio = ahora->tm_year + 1900;

    cout << "Noticias publicadas el último mes:\n";
    for (int i = 0; i < news.getNoticias().length(); ++i) {
        Fecha fecha = news.getNoticias()[i]->getPublicado();

        if (fecha.anio == esteAnio && fecha.mes == esteMes) {
            cout << "\t" << i+1 << ") " << news.getNoticias()[i]->getTitulo() << " ("
            << news.getNoticias()[i]->getAutor().getNombre() << ")" << "\n";
        }
    }
}

void mostrarNoticiaConComentarios(NEWS &news, int noticiaId) {
    Noticia noticia = *news.getNoticias()[noticiaId];
    cout << "\t" << noticia.getTitulo() << " (Por " + noticia.getAutor().getNombre() << ")" << endl;
    cout << "\t\t" << noticia.getDetalle() << endl;
    cout << "\t" << "Comentarios:" << endl;
    for (int i = 0; i < noticia.getCantidadComentarios(); i++) {
        cout << "\t\t(" << noticia.getComentarios()[i]->getUsuario().getNombre() << ") "
        <<"\n\t\t\t" << noticia.getComentarios()[i]->getTexto() << "\n";
    }
}

void listarArticulosPorAutor(NEWS &news, string autorNombre) {
    cout << "Artículos publicados escritos por " << autorNombre << ":\n";
    for (int i = 0; i < news.getNoticias().length(); ++i) {
        if (news.getNoticias()[i]->getAutor().getNombre() == autorNombre) {
            cout << "\t" << i+1 << ") " << news.getNoticias()[i]->getTitulo() << "\n";
        }
    }
}

int main() {
    cout << "Descargando datos..." << endl;
    esperar(2);
    int option, dni;
    string nombre;
    // TODO: acá habría que capturar el 'RecordNotFound'
    NEWS news;
    bool loggeado = 0;
    bool esAutor = 0;
    while (!loggeado) {
        cout << "Iniciar sesion: " << endl;
        cout << "\t[1] Usuario" << endl;
        cout << "\t[2] Autor" << endl;
        cout << "\t[3] Salir" << endl;
        cout << ">> ";
        option = numero_validado(1, 3);
        switch (option)
        {
        case 1:
            try {
                cout << "Ingrese el dni: ";
                dni = numero_validado(1000000, 99999999);

                news.login_user(dni);
                loggeado = 1;
                esAutor = 0;
            } catch(RecordNotFoundException& e) {
                cout << "❌ Usuario no registrado\n";
            }
            break;
        case 2:
            try {
                cout << "Ingrese el dni: ";
                dni = numero_validado(1000000, 99999999);

                news.login_autor(dni);
                loggeado = 1;
                esAutor = 1;
            } catch(RecordNotFoundException& e) {
                cout << "❌ Autor no registrado\n";
            }
            break;
        case 3:
            cout << "💾 Saliendo...\n";
            return 0;
        default:
            cout << "❌ Opción inválida\n";
        }
    }
    
    cout << "Cargando menu..." << endl;
    esperar(1);
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Registro de Autores\n";
        cout << "2. Registro de Usuarios\n";
        cout << "3. Carga de Noticias (Solo autores)\n";
        cout << "4. Registro de Comentarios (Solo usuarios)\n";
        cout << "5. Listar Noticias por Año\n";
        cout << "6. Listar Noticias del Último Mes\n";
        cout << "7. Mostrar Noticia y Comentarios\n";
        cout << "8. Listar Artículos por Autor\n";
        cout << "9. Salir\n";
        cout << ">> ";
        option = numero_validado(1, 9);

        switch (option) {
            case 1:
                registrarAutor(news);
                break;
            case 2:
                registrarUsuario(news);
                break;
            case 3:
                if (esAutor) {
                    cargarNoticia(news);
                    break;
                }
                cout<<"Los usuarios no pueden comentar\n";
                break;
            case 4:
                if (esAutor) {
                    cout<<"Los autores no pueden comentar"<<endl;
                    break;
                }
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
                cout << "Elige la noticia a mostrar: " << endl;
                int l = news.getNoticias().length();
                for (int i = 0; i < l; i++){
                    cout << "\t[" << i+1 << "] " << news.getNoticias()[i]->getTitulo() << endl;
                }
                cout << ">> ";
                int opt = numero_validado(1, l);

                cout << "Recopilando información..." << endl;
                esperar(2);
                mostrarNoticiaConComentarios(news, opt-1);
                break;
            }
            case 8: {
                cout << "Elige un autor: " << endl;
                for (int i = 0; i < news.getAutores().length(); i++){
                    cout << "\t[" << i+1 << "] " << news.getAutores()[i]->getNombre() << " (" << news.getAutores()[i]->getMedio() << ")" << endl;
                }
                cout << ">> ";
                int opt = numero_validado(1, news.getAutores().length());

                cout << "Buscando artículos..." << endl;
                esperar(2);
                listarArticulosPorAutor(news, news.getAutores()[opt-1]->getNombre());
                break;
            }
            case 9:
                cout << "💾 Saliendo...\n";
                return 0;
            default:
                cout << "❌ Opción no válida.\n";
        }
    }
}
