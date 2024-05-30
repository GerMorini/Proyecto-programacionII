#include <iostream>
#include <typeindex>

using namespace std;

struct Fecha {
    int dia, mes, anio;
};

template<class T>
class Arreglo {
    private:
        int len;
        T* arr;
    public:
        Arreglo() {
            len = 0;
            arr = new T[10];
        }

        void operator+(T elem) {
            arr[len++] = elem;
        }
};

class Persona {
    private:
        string nombre;
        int dni;
    public:
        Persona(string _nombre, int _dni) : nombre(_nombre), dni(_dni) {};
};

class Autor : public Persona {
    private:
        string medio;
    public:
        Autor();
        Autor(string _medio, string _nombre, int _dni) : medio(_medio), Persona(_nombre, _dni) {};
};

class Usuario : public Persona {
    private:
        int edad;
    public:
        Usuario(string _nombre, int _dni, int _edad) : Persona(_nombre, _dni), edad(_edad) {};
};

class Comentario {
    private:
        int numero;
        string texto;
        Usuario usuario;
    public:
        Comentario();
        Comentario(int _numero, string _texto, Usuario _usuario) : numero(_numero), texto(_texto), usuario(_usuario) {};
};

class Noticia {
    private:
        string titulo, detalle;
        Fecha publicado;
        Autor autor;
        Arreglo<Comentario> comentarios;
    public:
        Noticia();
        Noticia(string tit, string det, Fecha publi, Autor aut) {
            titulo = tit;
            detalle = det;
            publicado = publi;
            autor = aut;
            comentarios = Arreglo<Comentario>(); // TODO: ¿se puede instanciar así?
        };

        void comentar(Comentario com) {
            comentarios + com;
        }
};

class NEWS {
    private:
        Arreglo<Autor> autores;
        Arreglo<Usuario> usuarios;
        Arreglo<Noticia> noticias;
    public:
        NEWS() {
            // TODO: acá se van a cargar autores y noticias desde archivos
        }

        void publicar(Noticia n) {
            noticias + n;
        }

        void registrar_usuario(Usuario user) {
            usuarios + user;
        }

        void registrar_autor(Autor aut){
            autores + aut;
        }

        ~NEWS() {
            // TODO: acá deben ir los métodos para guardar en los archivos
        }
};
