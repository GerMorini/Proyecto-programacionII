#include <cstdio>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Fecha {
    int dia, mes, anio;
};

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

        /* TODO: por esto no se guardaban los comentarios, porque no se usaba un puntero
            cuando buscaba la noticia para comentarla se retornaba una copia de la misma
            entonces, el comentario se guardaba en la copia y no en la noticia guardada
            en el arreglo

            culpa de esto tuve que poner '->' en todos lados, hay que preguntar si se puede
        */
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
        Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor) {
            titulo = _titulo;
            detalle = _detalle;
            publicado = _publicacion;
            autor = _autor;
            comentarios = Arreglo<Comentario>(); // TODO: ¿se puede instanciar así?
        };
        
        Noticia(string _titulo, string _detalle, Fecha _publicacion, Autor _autor, Arreglo<Comentario> _comentarios) {
            titulo = _titulo;
            detalle = _detalle;
            publicado = _publicacion;
            autor = _autor;
            comentarios = _comentarios;
        };

        string getTitulo();
        string getDetalle();
        Fecha getPublicado();
        Autor getAutor();
        Arreglo<Comentario> getComentarios();

        void setFecha(Fecha a);
        void comentar(Comentario com);
        int getCantidadComentarios();

        bool operator==(Noticia& n);
};

class FileOpenException : public exception {
    private:
        string msg;
    public:
        FileOpenException(string _msg) {
            msg = "no se pudo abrir el archivo '" + _msg + "'";
        }

        string getMessage() {return msg;}
};

class RecordNotFound : public exception {
    private:
        string msg;
    public:
        RecordNotFound(string _msg) {
            msg = "no se encontró registro para el dato '" + _msg + "'";
        }
        
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
        Data_manager() {
            cargar_usuarios();
            cargar_autores();
            cargar_comentarios();
            cargar_noticias();
        }

        Arreglo<Comentario> buscar_comentarios(int numero);

        Usuario buscar_usuario(int dni);
        
        Autor buscar_autor(int dni);

        Noticia buscar_noticia(string titulo);

        bool aniadir_noticia(Noticia n);

        bool aniadir_usuario(Usuario u);

        bool aniadir_autor(Autor a);

        Arreglo<Usuario> getUsuarios();
        Arreglo<Autor> getAutores();
        Arreglo<Comentario> getComentarios();
        Arreglo<Noticia> getNoticias();

        void guardar_cambios();
};

class NEWS {
    private:
        Data_manager dm;
        // TODO: preguntar como podemos hacer para no usar dos variables
        Usuario loginUser;
        Autor loginAuth;
    public:
        NEWS() {
            dm = Data_manager();
        }

        Arreglo<Noticia> getNoticias() {return dm.getNoticias();}

        bool publicar(string titulo, string detalle, Fecha publicacion) {
            return dm.aniadir_noticia(Noticia(titulo, detalle, publicacion, loginAuth));
        }

        bool registrar_usuario(Usuario user) {
            return dm.aniadir_usuario(user);
        }

        bool registrar_autor(Autor aut) {
            return dm.aniadir_autor(aut);
        }

        void login_user(int dni) {
            loginUser = dm.buscar_usuario(dni);
        }

        void login_autor(int dni) {
            loginAuth = dm.buscar_autor(dni);
        }

        void comentar(int n, string txt) {
            dm.getNoticias()[n-1]->comentar(Comentario(n, txt, loginUser));
        } // los autores no comentan... UWU tit detalle publicacion

        ~NEWS() {
            dm.guardar_cambios();
        }
};
