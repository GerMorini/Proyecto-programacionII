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

        bool operator()(string str) {
            for (T* i = &arr[0]; i < &arr[0]+len; i++) {
                if (i->get() == str) return true;
            }

            return false;
        }

        T operator[](int n) {
            return arr[n];
        }
};

class Persona {
    private:
        string nombre;
        int dni;
    public:
        Persona() {};
        Persona(string _nombre, int _dni) : nombre(_nombre), dni(_dni) {};

        string get() {
            return nombre;
        }
        int getDNI(){
            return dni;
        }
};

class Autor : public Persona {
    private:
        string medio;
    public:
        Autor() {};
        Autor(string _medio, string _nombre, int _dni) : Persona(_nombre, _dni), medio(_medio) {};
};

class Usuario : public Persona {
    private:
        int edad;
    public:
        Usuario() {};
        Usuario(string _nombre, int _dni, int _edad) : Persona(_nombre, _dni), edad(_edad) {};
};

class Comentario {
    private:
        int numero;
        string texto;
        Usuario usuario;
    public:
        Comentario() {};
        Comentario(int _numero, string _texto, Usuario _usuario) : numero(_numero), texto(_texto), usuario(_usuario) {};
};

class Noticia {
    private:
        string titulo, detalle;
        Fecha publicado;
        Autor autor;
        Arreglo<Comentario> comentarios;
    public:
        Noticia() {};
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

        string get() {
            return titulo;
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

        bool publicar(Noticia n) {
            if(noticias(n.get())) return false;

            noticias + n;
            return true;
        }

        bool registrar_usuario(Usuario user) {
            if(usuarios(user.get())) return false;

            usuarios + user;
            return true;
        }

        bool registrar_autor(Autor aut){
            if(autores(aut.get())) return false;

            autores + aut;
            return true;
        }

        ~NEWS() {
            // TODO: acá deben ir los métodos para guardar en los archivos
        }
};
