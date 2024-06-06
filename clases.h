#include <exception>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Fecha {
    int dia, mes, anio;
};

// FIXME: traté de moverlo a 'modelo.cpp', pero arroja errores al compilar
template<class T>
class Arreglo {
    private:
        int len;
        int size;
        T* arr;
    public:
        Arreglo() {
            len = 0;
            size = 20;
            arr = new T[size];
        }

        int length() {return len;}

        bool operator+(T elem) {
            if (len >= size) {
                size += 20;
                T* new_arr = new T[size];

                for (int i = 0; i < len; i++) {
                    new_arr[i] = arr[i];
                }

                delete[] arr;
                arr = new_arr;
            }

            if (not (*this ^ elem)) {
                arr[len++] = elem;
                return true;
            }
            
            return false;
        }

        T* operator[](int n) {
            if (n < 0) n = 0;
            return &arr[n];
        }

        bool operator^(T elem) {
            for (int i = 0; i < len; i++) {
                if (arr[i] == elem) return true;            
            }

            return false;
        }
};

class Persona {
    private:
        string nombre;
        int dni;
    public:
        Persona() {};
        Persona(string _nombre, int _dni) : nombre(_nombre), dni(_dni) {};

        string getNombre();

        int getDNI();

        bool operator==(Persona& p);
};

class Autor : public Persona {
    private:
        string medio;
    public:
        Autor() {};
        Autor(string _nombre, int _dni, string _medio) : Persona(_nombre, _dni), medio(_medio) {};

        string getMedio();
};

class Usuario : public Persona {
    private:
        int edad;
    public:
        Usuario() {};
        Usuario(string _nombre, int _dni, int _edad) : Persona(_nombre, _dni), edad(_edad) {};

        int getEdad();
};

class Comentario {
    private:
        int numero;
        string texto;
        Usuario usuario;
    public:
        Comentario() {};
        Comentario(int _numero, string _texto, Usuario _usuario) : numero(_numero), texto(_texto), usuario(_usuario) {};

        int getNumero();
        string getTexto();
        Usuario getUsuario();

        bool operator==(Comentario& com);
};

class Noticia {
    private:
        string titulo, detalle;
        Fecha publicado;
        Autor autor;
        Arreglo<Comentario> comentarios;
        
    public:
        Noticia() {};
        Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor);
        Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor, Arreglo<Comentario> _comentarios);

        string getTitulo();
        string getDetalle();
        Fecha getPublicado();
        Autor getAutor();
        Arreglo<Comentario> getComentarios();

        void setFecha(Fecha a);
        bool comentar(Comentario com);
        int getCantidadComentarios();

        bool operator==(Noticia& n);
};

class FileOpenException : public exception {
    private:
        string msg;
    public:
        FileOpenException(string _msg) : msg(_msg) {}

        string getMessage() {return msg;}
};

class RecordNotFoundException : public exception {
    private:
        string msg;
    public:
        RecordNotFoundException(string _msg) : msg(_msg) {}
        
        string getMessage() {return msg;}
};

class Data_manager {
    private:
        Arreglo<Usuario> usuarios;
        Arreglo<Autor> autores;
        Arreglo<Comentario> comentarios;
        Arreglo<Noticia> noticias;

        string USERS_PATH = "usuarios.csv";
        string AUTHORS_PATH = "autores.csv";
        string COMMENTS_PATH = "comentarios.csv";
        string NEWS_PATH = "noticias.csv";

        void cargar_usuarios();

        void cargar_autores();

        void cargar_comentarios();

        void cargar_noticias();

        void guardar_usuarios();
        
        void guardar_autores();

        void guardar_comentarios();

        void guardar_noticias();
        
    public:
        Data_manager();

        Arreglo<Usuario> getUsuarios();
        Arreglo<Autor> getAutores();
        Arreglo<Comentario> getComentarios();
        Arreglo<Noticia> getNoticias();

        Arreglo<Comentario> buscar_comentarios(int numero);

        Usuario buscar_usuario(int dni);
        
        Autor buscar_autor(int dni);

        Noticia buscar_noticia(string titulo);

        bool aniadir_noticia(Noticia n);

        bool aniadir_usuario(Usuario u);

        bool aniadir_autor(Autor a);

        void guardar_cambios();
};

class NEWS {
    private:
        Data_manager dm;
        // TODO: preguntar como podemos hacer para no usar dos variables
        Usuario loginUser;
        Autor loginAuth;
    public:
        NEWS();

        Arreglo<Noticia> getNoticias();
        Arreglo<Autor> getAutores();

        bool publicar(string titulo, string detalle, Fecha publicacion);

        bool registrar_usuario(Usuario user);

        bool registrar_autor(Autor aut);

        bool comentar(int n, string txt);

        void login_user(int dni);

        void login_autor(int dni);

        ~NEWS();
};
